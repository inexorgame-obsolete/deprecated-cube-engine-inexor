#include "inexor/client/gamemode/capture_client.hpp"

namespace game {

VARP(capturetether, 0, 1, 1);
VARP(autorepammo, 0, 1, 1);
VARP(basenumbers, 0, 0, 1);

ICOMMAND(repammo, "", (), capturemode.replenishammo());
ICOMMAND(insidebases, "", (),
{
    vector<char> buf;
    if(m_capture && player1->state == CS_ALIVE) loopv(capturemode.bases)
    {
        captureclientmode::baseinfo &b = capturemode.bases[i];
        if(b.valid() && capturemode.insidebase(b, player1->feetpos()))
        {
            if(buf.length()) buf.add(' ');
            defformatstring(basenum, "%d", i+1);
            buf.put(basenum, strlen(basenum));
        }
    }
    buf.add('\0');
    result(buf.getbuf());
});

void captureclientmode::drawblips(fpsent *d, float blipsize, int fw, int fh, int type, bool skipenemy)
{
    float scale = calcradarscale();
    int blips = 0;
    loopv(bases)
    {
        baseinfo &b = bases[i];
        if(!b.valid()) continue;
        if(skipenemy && b.enemy[0]) continue;
        switch(type)
        {
            case 1: if(!b.owner[0] || strcmp(b.owner, player1->team)) continue; break;
            case 0: if(b.owner[0]) continue; break;
            case -1: if(!b.owner[0] || !strcmp(b.owner, player1->team)) continue; break;
            case -2: if(!b.enemy[0] || !strcmp(b.enemy, player1->team)) continue; break;
        }
        vec dir(d->o);
        dir.sub(b.o).div(scale);
        float dist = dir.magnitude2(), maxdist = 1 - 0.05f - blipsize;
        if(dist >= maxdist) dir.mul(maxdist/dist);
        dir.rotate_around_z(-camera1->yaw*RAD);
        if(basenumbers)
        {
            static string blip;
            formatstring(blip, "%d", i+1);
            int tw, th;
            text_bounds(blip, tw, th);
            draw_text(blip, int(0.5f*(dir.x*fw/blipsize - tw)), int(0.5f*(dir.y*fh/blipsize - th)));
        }
        else
        {
            if(!blips) { gle::defvertex(2); gle::deftexcoord0(); gle::begin(GL_QUADS); }
            float x = 0.5f*(dir.x*fw/blipsize - fw), y = 0.5f*(dir.y*fh/blipsize - fh);
            gle::attribf(x, y);    gle::attribf(0, 0);
            gle::attribf(x+fw, y);    gle::attribf(1, 0);
            gle::attribf(x+fw, y+fh); gle::attribf(1, 1);
            gle::attribf(x, y+fh); gle::attribf(0, 1);
        }
        blips++;
    }
    if(blips && !basenumbers) gle::end();
}

void captureclientmode::drawhud(fpsent *d, int w, int h)
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    int s = 1800/4, x = 1800*w/h - s - s/10, y = s/10;
    gle::colorf(1, 1, 1, minimapalpha);
    if(minimapalpha >= 1) glDisable(GL_BLEND);
    bindminimap();
    drawminimap(d, x, y, s);
    if(minimapalpha >= 1) glEnable(GL_BLEND);
    gle::colorf(1, 1, 1);
    float margin = 0.04f, roffset = s*margin, rsize = s + 2*roffset;
    setradartex();
    drawradar(x - roffset, y - roffset, rsize);
    bool showenemies = lastmillis%1000 >= 500;
    int fw = 1, fh = 1;
    if(basenumbers)
    {
        pushfont();
        setfont("digit_blue");
        text_bounds(" ", fw, fh);
    }
    else setbliptex(TEAM_OWN);
    glPushMatrix();

    float blipsize = basenumbers ? 0.1f : 0.05f;
    pushhudmatrix();
    hudmatrix.translate(x + 0.5f*s, y + 0.5f*s, 0);
    hudmatrix.scale((s*blipsize)/fw, (s*blipsize)/fh, 1.0f);
    flushhudmatrix();
    drawblips(d, blipsize, fw, fh, 1, showenemies);

    if(basenumbers) setfont("digit_grey");
    else setbliptex(TEAM_NONE);
    drawblips(d, blipsize, fw, fh, 0, showenemies);

    if(basenumbers) setfont("digit_red");
    else setbliptex(TEAM_OPPONENT);
    drawblips(d, blipsize, fw, fh, -1, showenemies);
    if(showenemies) drawblips(d, blipsize, fw, fh, -2);
    pophudmatrix();
    if(basenumbers) popfont();
    drawteammates(d, x, y, s);
    if(d->state == CS_DEAD)
    {
        int wait = respawnwait(d);
        if(wait>=0)
        {
            pushhudmatrix();
            hudmatrix.scale(2, 2, 1);
            flushhudmatrix();
            bool flash = wait>0 && d==player1 && lastspawnattempt>=d->lastpain && lastmillis < lastspawnattempt+100;
            draw_textf("%s%d", (x+s/2)/2-(wait>=10 ? 28 : 16), (y+s/2)/2-32, flash ? COL_RED : "", wait);
            pophudmatrix();
        }
    }
}

void captureclientmode::updatebase(int i, const char *owner, const char *enemy, int converted, int ammo)
{
    using inexor::sound::playsound;
    if(!bases.inrange(i)) return;
    baseinfo &b = bases[i];
    if(owner[0])
    {
        if(strcmp(b.owner, owner))
        {
            if(!b.name[0]) spdlog::get("gameplay")->info("{0} captured base {1}", teamcolor(owner, owner), i+1);
            else if(basenumbers) spdlog::get("gameplay")->info("{0} captured {1}({2})", teamcolor(owner, owner), b.name, (i+1));
            else spdlog::get("gameplay")->info("{0} captured {1}", teamcolor(owner, owner), b.name);
            if(!strcmp(owner, player1->team)) playsound(S_V_BASECAP);
        }
    }
    else if(b.owner[0])
    {
        if(!b.name[0]) spdlog::get("gameplay")->info("{0} lost base {1}", teamcolor(b.owner, b.owner), i+1);
        else if(basenumbers) spdlog::get("gameplay")->info("{0} lost {1}({2})", teamcolor(b.owner, b.owner), b.name, (i+1));
        else spdlog::get("gameplay")->info("{0} lost {1}", teamcolor(b.owner, b.owner), b.name);
        if(!strcmp(b.owner, player1->team)) playsound(S_V_BASELOST);
    }
    if(strcmp(b.owner, owner)) particle_splash(PART_SPARK, 200, 250, b.ammopos, owner[0] ? (strcmp(owner, player1->team) ? 0x802020 : 0x2020FF) : 0x208020, 0.24f);
    copystring(b.owner, owner);
    copystring(b.enemy, enemy);
    b.converted = converted;
    if(ammo>b.ammo)
    {
        playsound(S_ITEMSPAWN, &b.o);
        int icon = b.valid() ? itemstats[b.ammotype-1].icon : -1;
        if(icon >= 0) particle_icon(vec(b.ammopos.x, b.ammopos.y, b.ammopos.z + AMMOHEIGHT + 1.0f), icon%4, icon/4, PART_HUD_ICON, 2000, 0xFFFFFF, 2.0f, -8);
    }
    b.ammo = ammo;
}

void captureclientmode::checkitems(fpsent *d)
{
    if(m_regencapture || !autorepammo || d!=player1 || d->state!=CS_ALIVE) return;
    vec o = d->feetpos();
    loopv(bases)
    {
        baseinfo &b = bases[i];
        if(b.valid() && insidebase(b, d->feetpos()) && !strcmp(b.owner, d->team) && b.o.dist(o) < 12)
        {
            if(d->lastrepammo!=i)
            {
                if(b.ammo > 0 && !player1->hasmaxammo(b.ammotype-1+I_SHELLS)) addmsg(N_REPAMMO, "rc", d);
                d->lastrepammo = i;
            }
            return;
        }
    }
    d->lastrepammo = -1;
}

void captureclientmode::rendergame()
{
    if(capturetether && canaddparticles())
    {
        loopv(players)
        {
            fpsent *d = players[i];
            if(d) rendertether(d);
        }
        rendertether(player1);
    }
    loopv(bases)
    {
        baseinfo &b = bases[i];
        if(!b.valid()) continue;
        const char *basename = b.owner[0] ? (strcmp(b.owner, player1->team) ? "game/base/red" : "game/base/blue") : "game/base/neutral";
        rendermodel(&b.light, basename, ANIM_MAPMODEL|ANIM_LOOP, b.o, 0, 0, MDL_SHADOW | MDL_CULL_VFC | MDL_CULL_OCCLUDED);
        float fradius = 1.0f, fheight = 0.5f;
        regular_particle_flame(PART_FLAME, vec(b.ammopos.x, b.ammopos.y, b.ammopos.z - 4.5f), fradius, fheight, b.owner[0] ? (strcmp(b.owner, player1->team) ? 0x802020 : 0x2020FF) : 0x208020, 3, 2.0f);
        //regular_particle_flame(PART_SMOKE, vec(b.ammopos.x, b.ammopos.y, b.ammopos.z - 4.5f + 4.0f*min(fradius, fheight)), fradius, fheight, 0x303020, 1, 4.0f, 100.0f, 2000.0f, -20);

        //            particle_fireball(b.ammopos, 4.8f, PART_EXPLOSION, 0, b.owner[0] ? (strcmp(b.owner, player1->team) ? 0x802020 : 0x2020FF) : 0x208020, 4.8f);

        const char *ammoname = entities::entmdlname(I_SHELLS+b.ammotype-1);
        if(m_regencapture)
        {
            vec height(0, 0, 0);
            abovemodel(height, ammoname);
            vec ammopos(b.ammopos);
            ammopos.z -= height.z/2 + sinf(lastmillis/100.0f)/20;
            rendermodel(&b.light, ammoname, ANIM_MAPMODEL|ANIM_LOOP, ammopos, lastmillis/10.0f, 0, MDL_SHADOW | MDL_CULL_VFC | MDL_CULL_OCCLUDED);
        }
        else loopj(b.ammo)
        {
            float angle = 2*M_PI*(lastmillis/4000.0f + j/float(MAXAMMO));
            vec ammopos(b.o);
            ammopos.x += 10*cosf(angle);
            ammopos.y += 10*sinf(angle);
            ammopos.z += 4;
            rendermodel(&b.light, entities::entmdlname(I_SHELLS+b.ammotype-1), ANIM_MAPMODEL|ANIM_LOOP, ammopos, 0, 0, MDL_SHADOW | MDL_CULL_VFC | MDL_CULL_OCCLUDED);
        }

        int tcolor = 0x1EC850, mtype = -1, mcolor = 0xFFFFFF, mcolor2 = 0;
        if(b.owner[0])
        {
            bool isowner = !strcmp(b.owner, player1->team);
            if(b.enemy[0]) { mtype = PART_METER_VS; mcolor = 0xFF1932; mcolor2 = 0x3219FF; if(!isowner) swap(mcolor, mcolor2); }
            if(!b.name[0]) formatstring(b.info, "base %d: %s", i+1, b.owner);
            else if(basenumbers) formatstring(b.info, "%s (%d): %s", b.name, i+1, b.owner);
            else formatstring(b.info, "%s: %s", b.name, b.owner);
            tcolor = isowner ? 0x6496FF : 0xFF4B19;
        }
        else if(b.enemy[0])
        {
            if(!b.name[0]) formatstring(b.info, "base %d: %s", i+1, b.enemy);
            else if(basenumbers) formatstring(b.info, "%s (%d): %s", b.name, i+1, b.enemy);
            else formatstring(b.info, "%s: %s", b.name, b.enemy);
            if(strcmp(b.enemy, player1->team)) { tcolor = 0xFF4B19; mtype = PART_METER; mcolor = 0xFF1932; }
            else { tcolor = 0x6496FF; mtype = PART_METER; mcolor = 0x3219FF; }
        }
        else if(!b.name[0]) formatstring(b.info, "base %d", i+1);
        else if(basenumbers) formatstring(b.info, "%s (%d)", b.name, i+1);
        else copystring(b.info, b.name);

        vec above(b.ammopos);
        above.z += AMMOHEIGHT;
        if(b.info[0]) particle_text(above, b.info, PART_TEXT, 1, tcolor, 2.0f);
        if(mtype>=0)
        {
            above.z += 3.0f;
            particle_meter(above, b.converted/float((b.owner[0] ? int(OCCUPYENEMYLIMIT) : int(OCCUPYNEUTRALLIMIT))), mtype, 1, mcolor, mcolor2, 2.0f);
        }
    }
}

} // ns game
