#ifdef SERVMODE
VAR(ctftkpenalty, 0, 1, 1);

struct bombservmode : servmode
#else
struct bombclientmode : clientmode
#endif
{
	void drawhud(fpsent *d, int w, int h)
	{
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        int s = 1800/4, x = 1800*w/h - s - s/10, y = s/10;
        glColor4f(1, 1, 1, minimapalpha);
        if(minimapalpha >= 1) glDisable(GL_BLEND);
        bindminimap();
        drawminimap(d, x, y, s);
        if(minimapalpha >= 1) glEnable(GL_BLEND);
        glColor3f(1, 1, 1);
        float margin = 0.04f, roffset = s*margin, rsize = s + 2*roffset;
        settexture("packages/hud/radar.png", 3);
        drawradar(x - roffset, y - roffset, rsize);
        #if 0
        settexture("packages/hud/compass.png", 3);
        glPushMatrix();
        glTranslatef(x - roffset + 0.5f*rsize, y - roffset + 0.5f*rsize, 0);
        glRotatef(camera1->yaw + 180, 0, 0, -1);
        drawradar(-0.5f*rsize, -0.5f*rsize, rsize);
        glPopMatrix();
        #endif
	}
};
extern bombclientmode bombmode;
