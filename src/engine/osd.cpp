// sound.cpp: basic positional sound using sdl_mixer

#include "engine.h"

FVARP(osdscale, 1e-3f, 1.0f, 1e3f);
FVARP(osdalpha, 0, 1, 1);

struct osdobject {
    int type; // id?
    int left, top;
    int height;
    float zoom;
    float alpha;
    char* file;
    char* text;
    int begin, duration, timeout;
};
vector<osdobject> osdobjects;

void renderosdtext(osdobject o, int w, int h) {
    // conoutf("renderosdtext %s w: %d h: %d left: %d top: %d scale: %f zoom: %f", o.text, w, h, o.left, o.top, osdscale, o.zoom);
    int conw = int(w * o.zoom/osdscale);
    int conh = int(h * o.zoom/osdscale);
    int left, top;

    if (o.left >= 0) {
        left = o.left*FONTH;
    } else {
        left = conw-(-o.left)*FONTH;
    }
    if (o.top >= 0) {
        top = FONTH*o.top/2;
    } else {
        top = conh-FONTH*(-o.top)/2;
    }

    glPushMatrix();
    glScalef(osdscale * o.zoom, osdscale * o.zoom, 1);

    draw_text(o.text, left, top);
    glPopMatrix();

/*
    int fw, fh;
    float scale = osdscale * o.zoom;
    int left = 0, top = 0;
    if (o.left >= 0) {
        left = o.left;
    } else {
        left = w + o.left;
    }
    if (o.top >= 0) {
        top = o.top;
    } else {
        top = h + o.top;
    }
    conoutf("scale: %f left: %d top: %d", scale, left, top);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glColor4f(1.0f, 1.0f, 1.0f, osdalpha);
    // if(osdalpha >= 1) glDisable(GL_BLEND);

    // glScalef(h/scale, h/scale, 1);
    // glScalef(h/scale, h/scale, 1);
    // draw_text(text, w*scale/h - fw/2 - left, scale - fh/2 - top);
    // conoutf("modifier x: %f --- %f", w/h - fw/2 - o.left, w*scale/h - fw/2 - o.left);
    // conoutf("modifier y: %f --- %f", fh/2 - o.top, scale - fh/2 - o.top);
    //  glEnable(GL_BLEND);
    // conoutf("%s left: %d top: %d scale: %f w: %d h: %d", left, top, scale, w, h);
    conoutf("scaled: %d %d", left*h/scale,top*h/scale);
    draw_text(o.text, left*h/scale, top*h/scale);
    // text_bounds(o.text, fw, fh);
    // draw_text(o.text, left - (fw/2), top - (fh/2));
    // draw_text(o.text, w*scale/h - (fw/2) - left, scale - (fh/2) - top);
    glPopMatrix();
*/
}

void renderosdimage(osdobject o, int w, int h) {
    int conw = int(w * o.zoom/osdscale);
    int conh = int(h * o.zoom/osdscale);
    int left, top;
    // float sz = osdscale*h; // min(w,h);
    float sz = osdscale*o.height;

    if (o.left >= 0) {
        left = o.left*FONTH;
    } else {
        left = conw-(-o.left)*FONTH;
    }
    if (o.top >= 0) {
        top = FONTH*o.top/2;
    } else {
        top = conh-FONTH*(-o.top)/2;
    }

    glPushMatrix();
    glScalef(osdscale * o.zoom, osdscale * o.zoom, 1);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, osdalpha * o.alpha);
    if(osdalpha >= 1) glDisable(GL_BLEND);
    settexture(o.file, 0);
    glEnable(GL_BLEND);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0, 0); glVertex2f(left,    top);
    glTexCoord2f(1, 0); glVertex2f(left+sz, top);
    glTexCoord2f(0, 1); glVertex2f(left,    top+sz);
    glTexCoord2f(1, 1); glVertex2f(left+sz, top+sz);
    glEnd();
    glPopMatrix();
/*
    float scale = osdscale * o.zoom;
    float sz = scale*min(w, h); // , msz = (0.75f*min(w, h) - sz)/(infowidth + FONTH), x = 0.5f*(w-sz), y = ly+lh - sz/15;
    int left = 0, top = 0;
    if (o.left >= 0) {
        left = o.left;
    } else {
        left = w + o.left;
    }
    if (o.top >= 0) {
        top = o.top;
    } else {
        top = h + o.top;
    }
    // conoutf("renderosdimage %s zoom: %f sz: %f", o.file, o.zoom, sz);
    glPushMatrix();
    glScalef(h/scale, h/scale, 1);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, osdalpha);
    if(osdalpha >= 1) glDisable(GL_BLEND);
    settexture(o.file, 0);
    glEnable(GL_BLEND);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0, 0); glVertex2f(left,    top);
    glTexCoord2f(1, 0); glVertex2f(left+sz, top);
    glTexCoord2f(0, 1); glVertex2f(left,    top+sz);
    glTexCoord2f(1, 1); glVertex2f(left+sz, top+sz);
    glEnd();
    glPopMatrix();
*/
}

void addosdtext(char* text, int *left, int *top, float *zoom, float *alpha, int *duration) {
    // conoutf("addosdtext: left: %d top: %d zoom: %f duration: %i text: %s", *left, *top, *zoom, *duration, text);
    osdobject &o = osdobjects.add();
    o.type = 0;
    o.left = *left;
    o.top = *top;
    o.zoom = *zoom;
    o.alpha = *alpha;
    o.begin = totalmillis;
    o.duration = *duration;
    if (*duration > 0) {
        o.timeout = totalmillis + *duration;
    } else {
        o.timeout = 0;
    }
    // copystring(o.text, text);
    o.text = newstring(text);
}
COMMANDN(addosdtext, addosdtext, "siiffi");


void addosdimage(char* file, int *left, int *top, int *height, float *zoom, float *alpha, int *duration) {
    // conoutf("addosdimage: left: %d top: %d duration: %d file %d", *left, *top, *duration, file);
    osdobject &o = osdobjects.add();
    o.type = 1;
    o.left = *left;
    o.top = *top;
    o.height = *height;
    o.zoom = *zoom;
    o.alpha = *alpha;
    o.begin = totalmillis;
    o.duration = *duration;
    if (*duration > 0) {
        o.timeout = totalmillis + *duration;
    } else {
        o.timeout = 0;
    }
    o.file = newstring(file);
}
COMMAND(addosdimage, "siiiffi");

void clearosd() {
    osdobjects.remove(0, osdobjects.length()); //deletecontents();
}
COMMAND(clearosd, "");

void drawosd(int w, int h) {
    loopv(osdobjects) {
        osdobject o = osdobjects[i];
        // conoutf("drawosd type: %d left: %d top: %d zoom: %f", o.type, o.left, o.top, o.zoom);
        if (o.duration > 0 && o.timeout < totalmillis) continue;
        switch(o.type) {
            case 0:
                renderosdtext(o, w, h);
                break;
            case 1:
                renderosdimage(o, w, h);
                break;
        }
    }
    loopv(osdobjects) if (osdobjects[i].duration > 0 && osdobjects[i].timeout < totalmillis) {
        // conoutf("remove osdobject");
        osdobjects.remove(i); //i--;
    }
}


