#include <memory>                                     // for __shared_ptr

#include "include/base/cef_logging.h"                 // for COMPACT_GOOGLE_...
#include "include/base/cef_ref_counted.h"             // for scoped_refptr
#include "include/cef_browser.h"                      // for CefBrowser, Cef...
#include "include/cef_process_message.h"              // for CefProcessMessage
#include "include/cef_values.h"                       // for CefListValue
#include "include/wrapper/cef_helpers.h"              // for CEF_REQUIRE_REN...
#include "inexor/io/Logging.hpp"                      // for Log, Logger
#include "inexor/shared/command.hpp"                  // for VARFP
#include "inexor/ui/InexorCefApp.hpp"                 // for InexorCefApp
#include "inexor/ui/InexorRenderHandler.hpp"          // for InexorRenderHan...
#include "inexor/ui/layer/InexorAppLayer.hpp"
#include "inexor/ui/layer/InexorLayer.hpp"            // for InexorLayer

namespace inexor {
namespace ui {
namespace layer {

void update_app_layer();

VARFP(showapplayer, 0, 0, 1, update_app_layer());

void update_app_layer()
{
    if (showapplayer) {
        inexor::ui::cef_app->GetAppLayer()->Show();
    } else {
        inexor::ui::cef_app->GetAppLayer()->Hide();
    }
}

void InexorAppLayer::Reload()
{
    std::string url = GetUrl();
    SetUrl(url);
}

void InexorAppLayer::Resize(int x, int y, int width, int height)
{
    if (is_visible && layer.get()) {
        Log.ui->debug("Resize APP layer: ({0}x{1} at {2}, {3})", width, height, x, y);
        if (layer->GetInexorRenderHandler()->SetViewRect(x, y, width, height)) {
            layer->GetBrowser()->GetHost()->WasResized();
        }
    }
}

void InexorAppLayer::AutoResize(int width, int height)
{
    if (layer.get()) {
        if (width != layer->GetInexorRenderHandler()->GetViewWidth() || height != layer->GetInexorRenderHandler()->GetViewHeight()) {
            Resize(0, 0, width, height);
        }
    }
}

void InexorAppLayer::SetVisibility(bool _is_visible)
{
    if (_is_visible != GetVisibility()) {
        AbstractInexorLayerProvider::SetVisibility(_is_visible);
        FireUiEvent("isVisible", _is_visible);
    }
}

void InexorAppLayer::SetAcceptingKeyInput(bool _is_accepting_key_input)
{
    if (_is_accepting_key_input != GetAcceptingKeyInput()) {
        AbstractInexorLayerProvider::SetAcceptingKeyInput(_is_accepting_key_input);
        FireUiEvent("isAcceptingKeyInput", _is_accepting_key_input);
    }
}

void InexorAppLayer::SetAcceptingMouseInput(bool _is_accepting_mouse_input)
{
    if (_is_accepting_mouse_input != GetAcceptingMouseInput()) {
        AbstractInexorLayerProvider::SetAcceptingMouseInput(_is_accepting_mouse_input);
        FireUiEvent("isAcceptingMouseInput", _is_accepting_mouse_input);
    }
}

void InexorAppLayer::FireUiEvent(std::string name, bool value)
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

void InexorAppLayer::FireUiEvent(std::string name, std::string value)
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

void InexorAppLayer::InitializeContext()
{
}

bool InexorAppLayer::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorAppLayer::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorAppLayer::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

}
}
}
