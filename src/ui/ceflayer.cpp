extern void logoutf(const char *fmt, ...);

#include <string>

#include "ceflayer.h"
#include "cefclienthandler.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"


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
