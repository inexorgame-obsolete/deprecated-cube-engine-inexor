#include <iostream>

#include "inexor/ui/InexorUserInterface.hpp"

void InexorUserInterface::Reload()
{
    std::string url = GetUrl();
    SetUrl(url);
}

void InexorUserInterface::Resize(int x, int y, int width, int height)
{
    if (is_visible && layer.get()) {
        std::cerr << "Resize inexor user interface: (" << x << ", " << y << ", " << width << ", " << height << ")\n";
        if (layer->GetInexorRenderHandler()->SetViewRect(x, y, width, height)) {
            layer->GetBrowser()->GetHost()->WasResized();
        }
    }
}

void InexorUserInterface::AutoResize(int width, int height)
{
    if (layer.get()) {
        if (width != layer->GetInexorRenderHandler()->GetViewWidth() || height != layer->GetInexorRenderHandler()->GetViewHeight()) {
            Resize(0, 0, width, height);
        }
    }
}

void InexorUserInterface::SetVisibility(bool _is_visible)
{
    if (_is_visible != GetVisibility()) {
        AbstractInexorLayerProvider::SetVisibility(_is_visible);
        FireUiEvent("isVisible", _is_visible);
    }
}

void InexorUserInterface::SetAcceptingKeyInput(bool _is_accepting_key_input)
{
    if (_is_accepting_key_input != GetAcceptingKeyInput()) {
        AbstractInexorLayerProvider::SetAcceptingKeyInput(_is_accepting_key_input);
        FireUiEvent("isAcceptingKeyInput", _is_accepting_key_input);
    }
}

void InexorUserInterface::SetAcceptingMouseInput(bool _is_accepting_mouse_input)
{
    if (_is_accepting_mouse_input != GetAcceptingMouseInput()) {
        AbstractInexorLayerProvider::SetAcceptingMouseInput(_is_accepting_mouse_input);
        FireUiEvent("isAcceptingMouseInput", _is_accepting_mouse_input);
    }
}

void InexorUserInterface::SetMenuVisibility(bool _is_menu_visible)
{
    if (_is_menu_visible != GetMenuVisibility()) {
        this->is_menu_visible = _is_menu_visible;
        FireUiEvent("isMenuVisible", _is_menu_visible);
    }
}

void InexorUserInterface::SetMenuState(std::string _menu_state)
{
    if (_menu_state != GetMenuState()) {
        this->menu_state = _menu_state;
        FireUiEvent("menuState", _menu_state);
    }
}

void InexorUserInterface::SetMenuParentState(std::string _menu_parent_state)
{
    if (_menu_parent_state != GetMenuParentState()) {
        this->menu_parent_state = _menu_parent_state;
        FireUiEvent("menuParentState", _menu_parent_state);
    }
}

void InexorUserInterface::FireUiEvent(std::string name, bool value)
{
    CefRefPtr<CefProcessMessage> ui_event = CefProcessMessage::Create("user_interface");
    CefRefPtr<CefListValue> arguments = ui_event->GetArgumentList();
    arguments->SetString(0, name);
    arguments->SetBool(1, value);
    // Send the process message to the render process.
    // Use PID_BROWSER instead when sending a message to the browser process.
    if (layer.get()) {
        layer->GetBrowser()->SendProcessMessage(PID_RENDERER, ui_event);
    }
}

void InexorUserInterface::FireUiEvent(std::string name, std::string value)
{
    CefRefPtr<CefProcessMessage> ui_event = CefProcessMessage::Create("user_interface");
    CefRefPtr<CefListValue> arguments = ui_event->GetArgumentList();
    arguments->SetString(0, name);
    arguments->SetString(1, value);
    // Send the process message to the render process.
    // Use PID_BROWSER instead when sending a message to the browser process.
    if (layer.get()) {
        layer->GetBrowser()->SendProcessMessage(PID_RENDERER, ui_event);
    }
}

void InexorUserInterface::InitializeContext()
{
}

bool InexorUserInterface::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorUserInterface::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorUserInterface::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}
