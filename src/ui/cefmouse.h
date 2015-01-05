#ifndef _CEF_MOUSE_H
#define _CEF_MOUSE_H

#include "cefbrowsersettings.h"
#include "cefclienthandler.h"
#include "cefwindowinfo.h"
#include "include/cef_app.h"

class InexorCefMouse
{

    public:
        InexorCefMouse(std::string name, int x, int y, int width, int height, std::string url) {};
        void Render();

	private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefMouse);

};

#endif  // _CEF_MOUSE_H
