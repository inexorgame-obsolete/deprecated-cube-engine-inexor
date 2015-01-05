#ifndef _CEF_WINDOW_INFO_H
#define _CEF_WINDOW_INFO_H
#pragma once

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
};

#endif
