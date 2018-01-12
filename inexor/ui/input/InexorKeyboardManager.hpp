#pragma once

#include <SDL.h>
#include <string>                                       // for string
#include <utility>                                      // for move

#include "SDL_events.h"                                 // for SDL_Event
#include "include/cef_app.h"
#include "include/cef_base.h"                           // for CefRefPtr
#include "include/cef_keyboard_handler.h"               // for CefKeyboardHa...
#include "include/cef_v8.h"                             // for CefV8Value (p...
#include "inexor/ui/context/InexorContextProvider.hpp"  // for InexorContext...
#include "inexor/ui/layer/InexorLayerManager.hpp"       // for InexorLayerMa...

class CefBrowser;

namespace inexor {
namespace ui {
namespace input {

class InexorKeyboardManager : public inexor::ui::context::InexorContextProvider,
                              public CefKeyboardHandler
{

    public:
        InexorKeyboardManager(CefRefPtr<inexor::ui::layer::InexorLayerManager> layer_manager) : layer_manager(std::move(layer_manager)) {}

        /// Forward text input and key events to CEF.
        /// Key events can be seen like Joystick keys, textinput differs from that since it can be composited from multiply keys.
        void SendKeyEvent(SDL_Event &e) ;

        // InexorCefContextProvider
        void InitializeContext() override {}
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) override;
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception) override;
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception) override;
        std::string GetContextName() override { return "keyboard"; };

        // CefKeyboardHandler
        bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event, bool* is_keyboard_shortcut) override;
        bool OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event) override;

    private:

        // Layer Manager
        CefRefPtr<inexor::ui::layer::InexorLayerManager> layer_manager;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorKeyboardManager);

};

} } } // ns inexor::ui::input
