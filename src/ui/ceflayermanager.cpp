#include "ceflayermanager.h"

InexorCefLayerManager::InexorCefLayerManager(int width, int height)
{
    SetScreenSize(width, height);
}

void InexorCefLayerManager::InitializeLayers()
{
    for(std::list<CefRefPtr<InexorCefLayerProvider> >::iterator it = layer_providers.begin(); it != layer_providers.end(); ++it)
    {
        CefRefPtr<InexorCefLayerProvider> layer_provider = (*it);
        CefRefPtr<InexorCefLayer> layer = CreateLayer(layer_provider->GetContextName(), layer_provider->GetUrl());
        layer->SetVisibility(layer_provider->GetVisibility());
        layer->SetIsAcceptingInput(layer_provider->GetAcceptingInput());
        layer->SetFocus(layer_provider->GetFocus());
        layer_provider->SetLayer(layer);
    }
}

void InexorCefLayerManager::DestroyLayers()
{
    logoutf("InexorCefLayerManager::DestroyLayers()");
    for(std::list<CefRefPtr<InexorCefLayer> >::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        (*it)->Destroy();
    }
}

void InexorCefLayerManager::AddLayerProvider(CefRefPtr<InexorCefLayerProvider> layer_provider) {
    layer_providers.push_back(layer_provider);
}

void InexorCefLayerManager::InitializeContext()
{
    CreateFunction("create", this);
    CreateFunction("show", this);
    CreateFunction("hide", this);
    CreateFunction("bringToFront", this);
    CreateFunction("sendToBack", this);
    CreateFunction("bringForward", this);
    CreateFunction("sendBackward", this);
    CreateFunction("getLayerNames", this);
    CreateFunction("copy", this);
    CreateFunction("paste", this);
    CreateFunction("cut", this);
    CreateFunction("showDevTools", this);
}

bool InexorCefLayerManager::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "create") {
        if (arguments.size() == 2 && arguments[0]->IsString() && arguments[1]->IsString()) {
            _CreateLayer(arguments[0]->GetStringValue().ToString(), arguments[1]->GetStringValue().ToString());
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
    } else if (name == "bringToFront") {
        if (arguments.size() == 1 && arguments[0]->IsString()) {
            BringToFront(arguments[0]->GetStringValue().ToString());
            return true;
        }
    } else if (name == "sendToBack") {
        if (arguments.size() == 1 && arguments[0]->IsString()) {
            SendToBack(arguments[0]->GetStringValue().ToString());
            return true;
        }
    } else if (name == "bringForward") {
        if (arguments.size() == 1 && arguments[0]->IsString()) {
            BringForward(arguments[0]->GetStringValue().ToString());
            return true;
        }
    } else if (name == "sendBackward") {
        if (arguments.size() == 1 && arguments[0]->IsString()) {
            SendBackward(arguments[0]->GetStringValue().ToString());
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
    } else if (name == "copy") {
        if (arguments.size() == 1 && arguments[0]->IsString()) {
            if (LayerExists(name))
                GetLayer(name)->Copy();
            return true;
        }
    } else if (name == "paste") {
        if (arguments.size() == 1 && arguments[0]->IsString()) {
            if (LayerExists(name))
                GetLayer(name)->Paste();
            return true;
        }
    } else if (name == "cut") {
        if (arguments.size() == 1 && arguments[0]->IsString()) {
            if (LayerExists(name))
                GetLayer(name)->Cut();
            return true;
        }
    } else if (name == "showDevTools") {
        if (arguments.size() == 1 && arguments[0]->IsString()) {
            std::string name = arguments[0]->GetStringValue().ToString();
            if (LayerExists(name))
                GetLayer(name)->ShowDevTools();
            return true;
        }
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

void InexorCefLayerManager::_CreateLayer(std::string name, std::string url)
{
    if (!CefCurrentlyOn(TID_UI)) {
        CefPostTask(TID_UI, NewCefRunnableMethod(this, &InexorCefLayerManager::_CreateLayer, name, url));
    } else {
        CEF_REQUIRE_UI_THREAD();
        CefRefPtr<InexorCefLayer> layer = InexorCefLayerManager::CreateLayer(name, 0, 0, width, height, url);
        layer->SetFocus(true);
        layer->SetVisibility(true);
        layer->SetIsAcceptingInput(true);
    }
}

CefRefPtr<InexorCefLayer> InexorCefLayerManager::CreateLayer(std::string name, std::string url)
{
    return InexorCefLayerManager::CreateLayer(name, 0, 0, width, height, url);
}

CefRefPtr<InexorCefLayer> InexorCefLayerManager::CreateLayer(std::string name, int x, int y, int width, int height, std::string url)
{
    CefRefPtr<InexorCefLayer> layer = new InexorCefLayer(name, x, y, width, height, url);
    layers.push_back(layer);
    return layer;
}

CefRefPtr<InexorCefLayer> InexorCefLayerManager::GetLayer(std::string name)
{
    for(std::list<CefRefPtr<InexorCefLayer> >::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        CefRefPtr<InexorCefLayer> layer = (*it);
        if (layer->GetName() == name)
            return layer;
    }
    return NULL;
}

/**
 * Returns an iterator instance pointing to the layer element with the given
 * name. If no element was found, the iterator points to end() which means
 * there is no layer with the given name.
 */
std::list<CefRefPtr<InexorCefLayer> >::iterator InexorCefLayerManager::GetIterator(std::string name)
{
    std::list<CefRefPtr<InexorCefLayer> >::iterator it = layers.begin();
    for(it = layers.begin(); it != layers.end(); ++it)
    {
        CefRefPtr<InexorCefLayer> layer = (*it);
        if (layer->GetName() == name)
            break;
    }
    return it;
}

bool InexorCefLayerManager::LayerExists(std::string name)
{
    return GetIterator(name) != layers.end();
}

std::list<std::string> InexorCefLayerManager::GetLayers()
{
    std::list<std::string> _layers;
    for(std::list<CefRefPtr<InexorCefLayer> >::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        CefRefPtr<InexorCefLayer> layer = (*it);
        _layers.push_back(layer->GetName());
    }
    return _layers;
}

void InexorCefLayerManager::ShowLayer(std::string name)
{
    logoutf("show layer %s", name.c_str());
    CefRefPtr<InexorCefLayer> layer = GetLayer(name);
    if (layer.get())
        layer->SetVisibility(true);
}

void InexorCefLayerManager::HideLayer(std::string name)
{
    CefRefPtr<InexorCefLayer> layer = GetLayer(name);
    if (layer.get())
        layer->SetVisibility(false);
}

void InexorCefLayerManager::BringToFront(std::string name)
{
    std::list<CefRefPtr<InexorCefLayer> >::iterator it = GetIterator(name);
    if (it != layers.end())
        layers.splice(layers.begin(), layers, it);
}

void InexorCefLayerManager::SendToBack(std::string name)
{
    std::list<CefRefPtr<InexorCefLayer> >::iterator it = GetIterator(name);
    if (it != layers.end())
        layers.splice(layers.end(), layers, it);
}

void InexorCefLayerManager::BringForward(std::string name)
{
    std::list<CefRefPtr<InexorCefLayer> >::iterator it = GetIterator(name);
    // name exists and not already on front
    if (it != layers.end() && it != layers.begin()) {
        std::list<CefRefPtr<InexorCefLayer> >::iterator it2 = it;
        --it2;
        layers.splice(it2, layers, it);
    }
}

void InexorCefLayerManager::SendBackward(std::string name)
{
    std::list<CefRefPtr<InexorCefLayer> >::iterator it = GetIterator(name);
    // name exists and not already on back
    std::list<CefRefPtr<InexorCefLayer> >::iterator it_back = layers.end();
    if (it != layers.end() && it != --it_back) {
        std::list<CefRefPtr<InexorCefLayer> >::iterator it2 = it;
        ++it2;
        layers.splice(it2, layers, it);
    }
}

void InexorCefLayerManager::RenderLayer(std::string name)
{
    CefRefPtr<InexorCefLayer> layer = GetLayer(name);
    if (layer.get())
        layer->Render();
}

void InexorCefLayerManager::Render()
{
    CEF_REQUIRE_UI_THREAD();
    // Render from back to front
    for(std::list<CefRefPtr<InexorCefLayer> >::reverse_iterator it = layers.rbegin(); it != layers.rend(); ++it)
    {
        CefRefPtr<InexorCefLayer> layer = (*it);
        if (layer.get() && layer->IsVisible()) {
            layer->Render();
        }
    }
}

void InexorCefLayerManager::SendKeyEvent(CefKeyEvent event)
{
    for(std::list<CefRefPtr<InexorCefLayer> >::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        CefRefPtr<InexorCefLayer> layer = (*it);
        if (layer.get() && layer->IsVisible() && layer->IsAcceptingInput()) {
            layer->GetBrowser()->GetHost()->SendKeyEvent(event);
        }
    }
}

void InexorCefLayerManager::SendMouseClickEvent(const CefMouseEvent& event, CefBrowserHost::MouseButtonType type, bool mouseUp, int clickCount)
{
    for(std::list<CefRefPtr<InexorCefLayer> >::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        CefRefPtr<InexorCefLayer> layer = (*it);
        if (layer.get() && layer->IsVisible() && layer->IsAcceptingInput()) {
            layer->GetBrowser()->GetHost()->SendMouseClickEvent(event, type, mouseUp, clickCount);
        }
    }
}

void InexorCefLayerManager::SendMouseMoveEvent(const CefMouseEvent& event, bool mouseLeave)
{
    for(std::list<CefRefPtr<InexorCefLayer> >::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        CefRefPtr<InexorCefLayer> layer = (*it);
        if (layer.get() && layer->IsVisible() && layer->IsAcceptingInput()) {
            layer->GetBrowser()->GetHost()->SendMouseMoveEvent(event, mouseLeave);
        }
    }
}

void InexorCefLayerManager::SendMouseWheelEvent(const CefMouseEvent& event, int deltaX, int deltaY)
{
    for(std::list<CefRefPtr<InexorCefLayer> >::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        CefRefPtr<InexorCefLayer> layer = (*it);
        if (layer.get() && layer->IsVisible() && layer->IsAcceptingInput()) {
            layer->GetBrowser()->GetHost()->SendMouseWheelEvent(event, deltaX, deltaY);
        }
    }
}
