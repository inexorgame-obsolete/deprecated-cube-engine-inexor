#include "ceflayermanager.h"

InexorCefLayerManager::InexorCefLayerManager(int width, int height)
{
    SetScreenSize(width, height);
}

void InexorCefLayerManager::InitializeLayers()
{
    for(std::list<InexorCefLayerProvider*>::iterator it = layer_providers.begin(); it != layer_providers.end(); ++it)
    {
        InexorCefLayerProvider* layer_provider = (*it);
        InexorCefLayer* layer = CreateLayer(layer_provider->GetContextName(), layer_provider->GetUrl());
        layer->SetVisibility(layer_provider->GetVisibility());
        layer->SetIsAcceptingInput(layer_provider->GetAcceptingInput());
        layer->SetFocus(layer_provider->GetFocus());
        layer_provider->SetLayer(layer);
    }
}

void InexorCefLayerManager::DestroyLayers()
{
    logoutf("InexorCefLayerManager::DestroyLayers()");
    for(std::list<InexorCefLayer*>::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        (*it)->Destroy();
    }
}

void InexorCefLayerManager::AddLayerProvider(InexorCefLayerProvider* layer_provider) {
    layer_providers.push_back(layer_provider);
}

void InexorCefLayerManager::InitializeContext()
{
    CreateFunction("create", this);
    CreateFunction("show", this);
    CreateFunction("hide", this);
    CreateFunction("getLayerNames", this);
}

bool InexorCefLayerManager::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "create") {
        if (arguments.size() == 2 && arguments[0]->IsString() && arguments[1]->IsString()) {
            CreateLayer(arguments[0]->GetStringValue().ToString(), arguments[1]->GetStringValue().ToString());
            return true;
        }
    } else if (name == "show") {
        if (arguments.size() == 1 && arguments[0]->IsString()) {
            ShowLayer(arguments[0]->GetStringValue().ToString());
            return true;
        }
    } else if (name == "hide") {
        if (arguments.size() == 1 && arguments[0]->IsString()) {
            HideLayer(arguments[0]->GetStringValue().ToString());
            return true;
        }
    } else if (name == "getLayerNames") {
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
    logoutf("show layer %s", name.c_str());
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
