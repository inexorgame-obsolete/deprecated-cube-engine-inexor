#include "cefmouse.h"

void InexorCefMouse::Render()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float fx = (2.0f * ((float) x / (float) max_x)) - 1.0f;
    float fy = 1.0f -(2.0f * ((float) y / (float) max_y));
    float ratio = (float) max_x / (float) max_y;
    float gx = size;
    float gy = size * ratio;
    // logoutf("fx: %2f fy: %2f gx: %2f gy: %2f ratio: %2f", fx, fy, gx, gy, ratio);

    // glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_ONE, GL_ONE);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    settexture(filename.c_str(), 3);

    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(fx, fy, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(fx + gx, fy, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(fx + gx, fy - gy, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(fx, fy - gy, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}
