#include "cefapp.h"

InexorCefApp::InexorCefApp(int width, int height)
{
    mouse = new InexorCefMouse();
    layer_manager = new InexorCefLayerManager(width, height);
    context = new InexorCefContext(layer_manager);
    SetScreenSize(width, height);
    mouse->Show();
}

void InexorCefApp::Render()
{
    layer_manager->Render();
    mouse->Render();
}

void InexorCefApp::SetScreenSize(int width, int height) {
    mouse->SetMax(width, height);
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
    mouse->Update(event);
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
