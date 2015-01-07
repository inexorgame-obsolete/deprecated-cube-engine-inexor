#ifndef _CEF_MOUSE_H
#define _CEF_MOUSE_H

#include "cefbrowsersettings.h"
#include "cefclienthandler.h"
#include "cefwindowinfo.h"
#include "include/cef_app.h"
#include "engine.h"

extern bool settexture(const char *name, int clamp);

class InexorCefMouse
{

    public:
        InexorCefMouse() : x(0), y(0), max_x(0), max_y(0), size(0.03f), visible(false) {
            SetFilename("media/interface/guicursor.png");
        };
        InexorCefMouse(int width, int height) : x(0), y(0), size(0.03f), visible(true) {
            SetFilename("media/interface/guicursor.png");
            SetMax(width, height);
        };

        void Update(const CefMouseEvent& event) {
            x = event.x;
            y = event.y;
        }

        void SetMax(int width, int height) {
            max_x = width;
            max_y = height;
        };

        void SetFilename(std::string filename) {
            this->filename = filename;
        }

        bool IsVisible() {
            return visible;
        };

        void Hide() {
            visible = false;
        };

        void Show() {
            visible = true;
        };

        void Render();

	private:
        int x;
        int y;
        int max_x;
        int max_y;
        float size;
        bool visible;
        std::string filename;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefMouse);

};

#endif  // _CEF_MOUSE_H
