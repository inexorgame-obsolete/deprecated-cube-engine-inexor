#ifndef _CEF_WINDOW_INFO_H
#define _CEF_WINDOW_INFO_H
#pragma once

#include "include/cef_app.h"

class InexorCefWindowInfo : public CefWindowInfo {

    public:
        InexorCefWindowInfo() {
	        x = 0;
	        y = 0;
	        width = 320;
	        height = 240;
	        windowless_rendering_enabled = true;
	        transparent_painting_enabled = true;
        };

        InexorCefWindowInfo(int x, int y, int width, int height) {
        	this->x = x;
        	this->y = y;
        	this->width = width;
        	this->height = height;
	        windowless_rendering_enabled = true;
	        transparent_painting_enabled = true;
        };

};

#endif
