extern void logoutf(const char *fmt, ...);

#include <string>

#include "ceflayer.h"
#include "cefclienthandler.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"


InexorCefLayerManager::InexorCefLayerManager(int width, int height)
{
    SetScreenSize(width, height);
}

void InexorCefLayerManager::InitializeContext()
{
    context = CefV8Value::CreateObject(this);
    AddFunction("createLayer", this);
    AddFunction("showLayer", this);
    AddFunction("hideLayer", this);
    AddFunction("getLayers", this);
}

bool InexorCefLayerManager::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "createLayer") {
        if (arguments.size() == 2 && arguments[0]->IsString() && arguments[1]->IsString()) {
            CreateLayer(arguments[0]->GetStringValue().ToString(), arguments[1]->GetStringValue().ToString());
            return true;
        }
    } else if (name == "showLayer") {
        if (arguments.size() == 1 && arguments[0]->IsString()) {
            ShowLayer(arguments[0]->GetStringValue().ToString());
            return true;
        }
    } else if (name == "hideLayer") {
        if (arguments.size() == 1 && arguments[0]->IsString()) {
            HideLayer(arguments[0]->GetStringValue().ToString());
            return true;
        }
    } else if (name == "getLayers") {
        std::list<std::string> layer_names = GetLayers();
        retval = CefV8Value::CreateArray(layer_names.size());
        int i = 0;
        for(std::list<std::string>::iterator it = layer_names.begin(); it != layer_names.end(); ++it)
        {
            std::string layer_name = (*it);
            retval->SetValue(i, CefV8Value::CreateString(layer_name));
            i++;
        }
        return true;
    }
    return false;
}

bool InexorCefLayerManager::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorCefLayerManager::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

void InexorCefLayerManager::SetScreenSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

InexorCefLayer* InexorCefLayerManager::CreateLayer(std::string name, std::string url)
{
    return InexorCefLayerManager::CreateLayer(name, 0, 0, width, height, url);
}

InexorCefLayer* InexorCefLayerManager::CreateLayer(std::string name, int x, int y, int width, int height, std::string url)
{
    InexorCefLayer* layer = new InexorCefLayer(name, x, y, width, height, url);
    layers.push_back(layer);
    return layer;
}

InexorCefLayer* InexorCefLayerManager::GetLayer(std::string name)
{
    for(std::list<InexorCefLayer*>::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        InexorCefLayer* layer = (*it);
        if (layer->GetName() == name)
            return layer;
    }
    return NULL;
}

std::list<std::string> InexorCefLayerManager::GetLayers()
{
    std::list<std::string> _layers;
    for(std::list<InexorCefLayer*>::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        InexorCefLayer* layer = (*it);
        _layers.push_back(layer->GetName());
    }
    return _layers;
}

void InexorCefLayerManager::ShowLayer(std::string name)
{
    InexorCefLayer* layer = GetLayer(name);
    if (layer)
        layer->SetVisibility(true);
}

void InexorCefLayerManager::HideLayer(std::string name)
{
    InexorCefLayer* layer = GetLayer(name);
    if (layer)
        layer->SetVisibility(false);
}

void InexorCefLayerManager::RenderLayer(std::string name)
{
    InexorCefLayer* layer = GetLayer(name);
    if (layer)
        layer->GetRenderHandler()->Render();
}

void InexorCefLayerManager::Render()
{
    CEF_REQUIRE_UI_THREAD();
    for(std::list<InexorCefLayer*>::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        InexorCefLayer* layer = (*it);
        if (layer->IsVisible()) {
            layer->GetRenderHandler()->Render();
        }
    }
}

void InexorCefLayerManager::SendKeyEvent(CefKeyEvent event)
{
    for(std::list<InexorCefLayer*>::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        InexorCefLayer* layer = (*it);
        if (layer->IsVisible() && layer->IsAcceptingInput()) {
            layer->GetBrowser()->GetHost()->SendKeyEvent(event);
        }
    }
}

void InexorCefLayerManager::SendMouseClickEvent(const CefMouseEvent& event, CefBrowserHost::MouseButtonType type, bool mouseUp, int clickCount)
{
    for(std::list<InexorCefLayer*>::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        InexorCefLayer* layer = (*it);
        if (layer->IsVisible() && layer->IsAcceptingInput()) {
            layer->GetBrowser()->GetHost()->SendMouseClickEvent(event, type, mouseUp, clickCount);
        }
    }
}

void InexorCefLayerManager::SendMouseMoveEvent(const CefMouseEvent& event, bool mouseLeave)
{
    for(std::list<InexorCefLayer*>::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        InexorCefLayer* layer = (*it);
        if (layer->IsVisible() && layer->IsAcceptingInput()) {
            layer->GetBrowser()->GetHost()->SendMouseMoveEvent(event, mouseLeave);
        }
    }
}

void InexorCefLayerManager::SendMouseWheelEvent(const CefMouseEvent& event, int deltaX, int deltaY)
{
    for(std::list<InexorCefLayer*>::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        InexorCefLayer* layer = (*it);
        if (layer->IsVisible() && layer->IsAcceptingInput()) {
            layer->GetBrowser()->GetHost()->SendMouseWheelEvent(event, deltaX, deltaY);
        }
    }
}

InexorCefLayer::InexorCefLayer(std::string name, int x, int y, int width, int height, std::string url)
    : name(name),
      url(url),
      is_visible(false),
      is_accepting_input(false),
      has_focus(false)
{
    window_info.x = x;
    window_info.y = y;
    window_info.width = width;
    window_info.height = height;
    render_handler = new InexorCefRenderHandler(true, x, y, width, height);
    client_handler = new InexorCefClientHandler(render_handler);
    browser = CefBrowserHost::CreateBrowserSync(window_info, client_handler.get(), url, browser_settings, NULL);
    if (browser.get()) {
        logoutf("init: cef: created layer \"%s\"", name.c_str());
        browser->GetHost()->SendFocusEvent(has_focus);
    }
}

void InexorCefLayer::SetVisibility(bool is_visible)
{
	this->is_visible = is_visible;
	browser->GetHost()->SetWindowVisibility(is_visible);
	browser->GetHost()->WasHidden(!is_visible);
}

void InexorCefLayer::SetFocus(bool has_focus)
{
	this->has_focus = has_focus;
	browser->GetHost()->SendFocusEvent(has_focus);
}

void InexorCefLayer::SetIsAcceptingInput(bool is_accepting_input)
{
	this->is_accepting_input = is_accepting_input;
}
