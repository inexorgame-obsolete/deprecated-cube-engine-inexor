#include <iostream>

#include "inexor/ui/layer/InexorConsoleLayer.hpp"
#include "inexor/util/Logging.hpp"
#include "inexor/ui.hpp"
#include "inexor/network/SharedTree.hpp"

namespace inexor {
namespace ui {
namespace layer {

    void update_console_layer();

    VARFP(showconsolelayer, 0, 0, 1, update_console_layer());

    void update_console_layer()
    {
        if (showconsolelayer) {
            inexor::ui::cef_app->GetConsoleLayer()->Show();
        } else {
            inexor::ui::cef_app->GetConsoleLayer()->Hide();
        }
    }

void InexorConsoleLayer::Reload()
{
    std::string url = GetUrl();
    SetUrl(url);
}

void InexorConsoleLayer::Resize(int x, int y, int width, int height)
{
    if (is_visible && layer.get()) {
        spdlog::get("global")->info("Resize CONSOLE layer: ({0}x{1} at {2}, {3})", width, height, x, y);
        if (layer->GetInexorRenderHandler()->SetViewRect(x, y, width, height)) {
            layer->GetBrowser()->GetHost()->WasResized();
        }
    }
}

void InexorConsoleLayer::AutoResize(int width, int height)
{
    if (layer.get()) {
        if (width != layer->GetInexorRenderHandler()->GetViewWidth() || height != layer->GetInexorRenderHandler()->GetViewHeight()) {
            Resize(0, 0, width, height);
        }
    }
}

void InexorConsoleLayer::SetVisibility(bool _is_visible)
{
    if (_is_visible != GetVisibility()) {
        AbstractInexorLayerProvider::SetVisibility(_is_visible);
    }
}

void InexorConsoleLayer::SetAcceptingKeyInput(bool _is_accepting_key_input)
{
    if (_is_accepting_key_input != GetAcceptingKeyInput()) {
        AbstractInexorLayerProvider::SetAcceptingKeyInput(_is_accepting_key_input);
    }
}

void InexorConsoleLayer::SetAcceptingMouseInput(bool _is_accepting_mouse_input)
{
    if (_is_accepting_mouse_input != GetAcceptingMouseInput()) {
        AbstractInexorLayerProvider::SetAcceptingMouseInput(_is_accepting_mouse_input);
    }
}

void InexorConsoleLayer::InitializeContext()
{
}

bool InexorConsoleLayer::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorConsoleLayer::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorConsoleLayer::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

}
}
}
