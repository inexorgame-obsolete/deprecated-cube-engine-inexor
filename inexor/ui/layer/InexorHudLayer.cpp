#include <iostream>

#include "inexor/ui/layer/InexorHudLayer.hpp"
#include "inexor/util/Logging.hpp"
#include "inexor/ui.hpp"
#include "inexor/rpc/SharedTree.hpp"

namespace inexor {
namespace ui {
namespace layer {

    void update_hud_layer();

    VARFP(showhudlayer, 0, 0, 1, update_hud_layer());

    void update_hud_layer()
    {
        if (showhudlayer) {
            inexor::ui::cef_app->GetHudLayer()->Show();
        } else {
            inexor::ui::cef_app->GetHudLayer()->Hide();
        }
    }

void InexorHudLayer::Reload()
{
    std::string url = GetUrl();
    SetUrl(url);
}

void InexorHudLayer::Resize(int x, int y, int width, int height)
{
    if (is_visible && layer.get()) {
        spdlog::get("global")->info() << "Resize HUD layer: (" << x << ", " << y << ", " << width << ", " << height << ")";
        if (layer->GetInexorRenderHandler()->SetViewRect(x, y, width, height)) {
            layer->GetBrowser()->GetHost()->WasResized();
        }
    }
}

void InexorHudLayer::AutoResize(int width, int height)
{
    if (layer.get()) {
        if (width != layer->GetInexorRenderHandler()->GetViewWidth() || height != layer->GetInexorRenderHandler()->GetViewHeight()) {
            Resize(0, 0, width, height);
        }
    }
}

void InexorHudLayer::SetVisibility(bool _is_visible)
{
    if (_is_visible != GetVisibility()) {
        AbstractInexorLayerProvider::SetVisibility(_is_visible);
    }
}

void InexorHudLayer::SetAcceptingKeyInput(bool _is_accepting_key_input)
{
    if (_is_accepting_key_input != GetAcceptingKeyInput()) {
        AbstractInexorLayerProvider::SetAcceptingKeyInput(_is_accepting_key_input);
    }
}

void InexorHudLayer::SetAcceptingMouseInput(bool _is_accepting_mouse_input)
{
    if (_is_accepting_mouse_input != GetAcceptingMouseInput()) {
        AbstractInexorLayerProvider::SetAcceptingMouseInput(_is_accepting_mouse_input);
    }
}

void InexorHudLayer::InitializeContext()
{
}

bool InexorHudLayer::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorHudLayer::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorHudLayer::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

}
}
}
