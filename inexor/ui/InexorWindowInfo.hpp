#ifndef INEXOR_UI_INEXOR_WINDOW_INFO_HEADER
#define INEXOR_UI_INEXOR_WINDOW_INFO_HEADER
#pragma once

#include "include/cef_app.h"

namespace inexor {
namespace ui {

class InexorWindowInfo : public CefWindowInfo {

    public:
        InexorWindowInfo() {
	        x = 0;
	        y = 0;
	        width = 1920;
	        height = 1080;
	        windowless_rendering_enabled = true;
	        transparent_painting_enabled = true;
        };

        InexorWindowInfo(int x, int y, int width, int height) {
        	this->x = x;
        	this->y = y;
        	this->width = width;
        	this->height = height;
	        windowless_rendering_enabled = true;
	        transparent_painting_enabled = true;
        };

};

}
}

#endif
