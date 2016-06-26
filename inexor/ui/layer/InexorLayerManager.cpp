#include <iostream>

#include "inexor/ui/layer/InexorLayerManager.hpp"

namespace inexor {
namespace ui {
namespace layer {

InexorLayerManager::InexorLayerManager(int width, int height)
{
    SetScreenSize(width, height);
}

void InexorLayerManager::InitializeLayers()
{
    for(std::list<CefRefPtr<InexorLayerProvider> >::iterator it = layer_providers.begin(); it != layer_providers.end(); ++it)
    {
        CefRefPtr<InexorLayerProvider> layer_provider = (*it);
        InitializeLayer(layer_provider);
    }
}

void InexorLayerManager::InitializeLayer(CefRefPtr<InexorLayerProvider> layer_provider)
{
    std::cerr << "InexorLayerManager::InitializeLayer()\n  name: " << layer_provider->GetLayerName() << "\n  url: " << layer_provider->GetUrl() << "\n";
    CefRefPtr<InexorLayer> layer = CreateLayer(layer_provider->GetLayerName(), layer_provider->GetUrl());
    layer->SetVisibility(layer_provider->GetVisibility());
    layer->SetIsAcceptingKeyInput(layer_provider->GetAcceptingKeyInput());
    layer->SetIsAcceptingMouseInput(layer_provider->GetAcceptingMouseInput());
    layer_provider->SetLayer(layer);
}

void InexorLayerManager::DestroyLayers()
{
    spdlog::get("global")->debug() << "InexorLayerManager::DestroyLayers()";
    for(std::list<CefRefPtr<InexorLayer> >::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        CefRefPtr<InexorLayer> layer = (*it);
        if (layer.get()) {
            layer->Destroy();
        }
    }
}

void InexorLayerManager::AddLayerProvider(CefRefPtr<InexorLayerProvider> layer_provider) {
    layer_providers.push_back(layer_provider);
}

void InexorLayerManager::InitializeContext()
{
}

bool InexorLayerManager::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorLayerManager::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorLayerManager::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

void InexorLayerManager::SetScreenSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

void InexorLayerManager::_CreateLayer(std::string name, std::string url)
{
    if (!CefCurrentlyOn(TID_UI)) {
        CefPostTask(TID_UI, NewCefRunnableMethod(this, &InexorLayerManager::_CreateLayer, name, url));
    } else {
        CEF_REQUIRE_UI_THREAD();
        CefRefPtr<InexorLayer> layer = InexorLayerManager::CreateLayer(name, 0, 0, width, height, url);
        layer->SetVisibility(true);
        layer->SetIsAcceptingKeyInput(true);
        layer->SetIsAcceptingMouseInput(true);
    }
}

CefRefPtr<InexorLayer> InexorLayerManager::CreateLayer(std::string name, std::string url)
{
    return InexorLayerManager::CreateLayer(name, 0, 0, width, height, url);
}

CefRefPtr<InexorLayer> InexorLayerManager::CreateLayer(std::string name, int x, int y, int width, int height, std::string url)
{
    CefRefPtr<InexorLayer> layer = new InexorLayer(name, x, y, width, height, url);
    layers.push_back(layer);
    return layer;
}

CefRefPtr<InexorLayer> InexorLayerManager::GetLayer(std::string name)
{
    for(std::list<CefRefPtr<InexorLayer> >::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        CefRefPtr<InexorLayer> layer = (*it);
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
std::list<CefRefPtr<InexorLayer> >::iterator InexorLayerManager::GetIterator(std::string name)
{
    std::list<CefRefPtr<InexorLayer> >::iterator it = layers.begin();
    for(it = layers.begin(); it != layers.end(); ++it)
    {
        CefRefPtr<InexorLayer> layer = (*it);
        if (layer->GetName() == name)
            break;
    }
    return it;
}

bool InexorLayerManager::LayerExists(std::string name)
{
    return GetIterator(name) != layers.end();
}

std::list<std::string> InexorLayerManager::GetLayers()
{
    std::list<std::string> _layers;
    for(std::list<CefRefPtr<InexorLayer> >::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        CefRefPtr<InexorLayer> layer = (*it);
        _layers.push_back(layer->GetName());
    }
    return _layers;
}

void InexorLayerManager::ShowLayer(std::string name)
{
    spdlog::get("global")->debug("show layer {}", name);
    CefRefPtr<InexorLayer> layer = GetLayer(name);
    if (layer.get())
        layer->SetVisibility(true);
}

void InexorLayerManager::HideLayer(std::string name)
{
    spdlog::get("global")->debug("hide layer {}", name);
    CefRefPtr<InexorLayer> layer = GetLayer(name);
    if (layer.get())
        layer->SetVisibility(false);
}

void InexorLayerManager::BringToFront(std::string name)
{
    std::list<CefRefPtr<InexorLayer> >::iterator it = GetIterator(name);
    if (it != layers.end())
        layers.splice(layers.begin(), layers, it);
}

void InexorLayerManager::SendToBack(std::string name)
{
    std::list<CefRefPtr<InexorLayer> >::iterator it = GetIterator(name);
    if (it != layers.end())
        layers.splice(layers.end(), layers, it);
}

void InexorLayerManager::BringForward(std::string name)
{
    std::list<CefRefPtr<InexorLayer> >::iterator it = GetIterator(name);
    // name exists and not already on front
    if (it != layers.end() && it != layers.begin()) {
        std::list<CefRefPtr<InexorLayer> >::iterator it2 = it;
        --it2;
        layers.splice(it2, layers, it);
    }
}

void InexorLayerManager::SendBackward(std::string name)
{
    std::list<CefRefPtr<InexorLayer> >::iterator it = GetIterator(name);
    // name exists and not already on back
    std::list<CefRefPtr<InexorLayer> >::iterator it_back = layers.end();
    if (it != layers.end() && it != --it_back) {
        std::list<CefRefPtr<InexorLayer> >::iterator it2 = it;
        ++it2;
        layers.splice(it2, layers, it);
    }
}

/*
void InexorLayerManager::RenderLayer(std::string name)
{
    CefRefPtr<InexorLayer> layer = GetLayer(name);
    if (layer.get())
        layer->Render();
}

void InexorLayerManager::Render()
{
    CEF_REQUIRE_UI_THREAD();
    // Render from back to front
    for(std::list<CefRefPtr<InexorLayer> >::reverse_iterator it = layers.rbegin(); it != layers.rend(); ++it)
    {
        CefRefPtr<InexorLayer> layer = (*it);
        if (layer.get() && layer->IsVisible()) {
            layer->Render();
        }
    }
}
*/

void InexorLayerManager::SendKeyEvent(CefKeyEvent event)
{
    for(std::list<CefRefPtr<InexorLayer> >::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        CefRefPtr<InexorLayer> layer = (*it);
        if (layer.get() && layer->IsAcceptingKeyInput()) {
            // std::cerr << "layer->GetBrowser()->GetHost()->SendKeyEvent() -> " << layer->GetName() << "\n";
            layer->GetBrowser()->GetHost()->SendKeyEvent(event);
        }
    }
}

void InexorLayerManager::SendMouseClickEvent(const CefMouseEvent& event, CefBrowserHost::MouseButtonType type, bool mouseUp, int clickCount)
{
    for(std::list<CefRefPtr<InexorLayer> >::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        CefRefPtr<InexorLayer> layer = (*it);
        if (layer.get() && layer->IsAcceptingMouseInput()) {
            // std::cerr << "layer->GetBrowser()->GetHost()->SendMouseClickEvent() -> " << layer->GetName() << "\n";
            layer->GetBrowser()->GetHost()->SendMouseClickEvent(event, type, mouseUp, clickCount);
        }
    }
}

void InexorLayerManager::SendMouseMoveEvent(const CefMouseEvent& event, bool mouseLeave)
{
    for(std::list<CefRefPtr<InexorLayer> >::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        CefRefPtr<InexorLayer> layer = (*it);
        if (layer.get() && layer->IsAcceptingMouseInput()) {
            // std::cerr << "layer->GetBrowser()->GetHost()->SendMouseMoveEvent() -> " << layer->GetName() << "\n";
            layer->GetBrowser()->GetHost()->SendMouseMoveEvent(event, mouseLeave);
        }
    }
}

void InexorLayerManager::SendMouseWheelEvent(const CefMouseEvent& event, int deltaX, int deltaY)
{
    for(std::list<CefRefPtr<InexorLayer> >::iterator it = layers.begin(); it != layers.end(); ++it)
    {
        CefRefPtr<InexorLayer> layer = (*it);
        if (layer.get() && layer->IsAcceptingMouseInput()) {
            // std::cerr << "layer->GetBrowser()->GetHost()->SendMouseWheelEvent() -> " << layer->GetName() << "\n";
            layer->GetBrowser()->GetHost()->SendMouseWheelEvent(event, deltaX, deltaY);
        }
    }
}

}
}
}
