extern void logoutf(const char *fmt, ...);
#include "cefmouse.h"

void InexorCefMouse::Render()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_BLEND);
//    glEnable(GL_TEXTURE_2D);

    float fx = (2.0f * ((float) x / (float) max_x)) - 1.0f;
    float fy = 1.0f -(2.0f * ((float) y / (float) max_y));

    glBegin(GL_TRIANGLES);
    glColor4f(0.75f, 0.75f, 0.75f, 0.75f);
    glVertex3f(fx, fy, 1.0f);
    glVertex3f(fx + 0.02f, fy - 0.01f, 1.0f);
    glVertex3f(fx + 0.01f, fy - 0.02f, 1.0f);
    glEnd();
}
