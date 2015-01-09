#include "cefapp.h"

InexorCefApp::InexorCefApp(int width, int height)
{
    mouse_manager = new InexorCefMouseManager();
    layer_manager = new InexorCefLayerManager(width, height);
    event_manager = new InexorCefEventManager();
    context = new InexorCefContext(layer_manager, event_manager, mouse_manager);
    SetScreenSize(width, height);
    mouse_manager->Show();
}

void InexorCefApp::Render()
{
    layer_manager->Render();
    mouse_manager->Render();
}

void InexorCefApp::SetScreenSize(int width, int height) {
    mouse_manager->SetMax(width, height);
    layer_manager->SetScreenSize(width, height);
}

void InexorCefApp::SendKeyEvent(CefKeyEvent event)
{
    layer_manager->SendKeyEvent(event);
}

void InexorCefApp::SendMouseClickEvent(const CefMouseEvent& event, CefBrowserHost::MouseButtonType type, bool mouseUp, int clickCount)
{
    layer_manager->SendMouseClickEvent(event, type, mouseUp, clickCount);
}

void InexorCefApp::SendMouseMoveEvent(const CefMouseEvent& event, bool mouseLeave)
{
    layer_manager->SendMouseMoveEvent(event, mouseLeave);
    mouse_manager->Update(event);
}

void InexorCefApp::SendMouseWheelEvent(const CefMouseEvent& event, int deltaX, int deltaY)
{
    layer_manager->SendMouseWheelEvent(event, deltaX, deltaY);
}

void InexorCefApp::OnContextInitialized()
{
    CEF_REQUIRE_UI_THREAD();
    // cefdebug("InexorCefApp::OnContextInitialized", "Create Layers");
    InexorCefLayer* layer2 = layer_manager->CreateLayer("menu-navigation", "http://gitdemo.inexor.org/menuprototype/");
    layer2->SetVisibility(true);
    layer2->SetIsAcceptingInput(true);
    layer2->SetFocus(true);
    InexorCefLayer* layer3 = layer_manager->CreateLayer("inexor-object", "http://gitdemo.inexor.org/inexor-object/");
    layer3->SetVisibility(true);
    layer3->SetIsAcceptingInput(true);
    layer3->SetFocus(true);
}

void InexorCefApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> browser_context)
{
    // cefdebug("InexorCefApp::OnContextCreated", "Injecting inexor object into javascript context");
    // only inject context if...
    browser_context->GetGlobal()->SetValue("inexor", context->GetContext(), V8_PROPERTY_ATTRIBUTE_NONE);
}
