#ifndef _CEF_MOUSE_H
#define _CEF_MOUSE_H

#include "cefbrowsersettings.h"
#include "cefclienthandler.h"
#include "cefwindowinfo.h"
#include "include/cef_app.h"
#include "engine.h"

class InexorCefMouse
{

    public:
        InexorCefMouse() : x(0), y(0), max_x(0), max_y(0) {};
        void Render();
        int x;
        int y;
        int max_x;
        int max_y;

	private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefMouse);

};

#endif  // _CEF_MOUSE_H
