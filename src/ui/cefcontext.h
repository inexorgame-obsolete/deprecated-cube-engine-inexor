#ifndef _CEF_CONEXT_H
#define _CEF_CONEXT_H

#include "engine.h"
#include "fpsgame/game.h"
#include "include/cef_app.h"
#include "include/cef_render_process_handler.h"
#include "include/wrapper/cef_helpers.h"

extern void quit();

extern int fullscreen;
extern int scr_w;
extern int scr_h;
extern int vsync;

namespace game {
    extern fpsent *player1;
    extern void switchname(const char *name);
}

class InexorCefContext : public CefV8Handler,
                         public CefV8Accessor
{

    public:
        InexorCefContext() {}

        // Initializes the common context as a V8 object
        void InitializeContext();

        // Returns the common context as a V8 object
        CefRefPtr<CefV8Value> GetContext();

        // CefV8Handler
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);

        // CefV8Accessor
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);

	private:
	    CefRefPtr<CefV8Value> context;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefContext);

};

#endif  // _CEF_CONEXT_H
