#ifndef INEXOR_UI_INEXOR_KEYBOARD_MANAGER_HEADER
#define INEXOR_UI_INEXOR_KEYBOARD_MANAGER_HEADER

#include "include/cef_app.h"
#include "include/cef_client.h"

#include "inexor/ui/context/InexorContextProvider.hpp"
#include "inexor/ui/input/SDL2Keyboard.hpp"
#include "inexor/ui/layer/InexorLayerManager.hpp"

namespace inexor {
namespace ui {
namespace input {

class InexorKeyboardManager : public inexor::ui::context::InexorContextProvider,
                              public CefKeyboardHandler
{

    public:
        InexorKeyboardManager(CefRefPtr<inexor::ui::layer::InexorLayerManager> layer_manager);

        void SendKeyEvent(SDL_Event event);

        // InexorCefContextProvider
        void InitializeContext();
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);
        std::string GetContextName() { return "keyboard"; };

        // CefKeyboardHandler
        bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event, bool* is_keyboard_shortcut);
        bool OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event);

    private:

        // Layer Manager
        CefRefPtr<inexor::ui::layer::InexorLayerManager> layer_manager;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorKeyboardManager);

};

}
}
}

#endif
