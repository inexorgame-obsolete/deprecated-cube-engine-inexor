#include "cefapp.h"

InexorCefApp::InexorCefApp(int width, int height)
{
    mouse_manager = new InexorCefMouseManager();
    layer_manager = new InexorCefLayerManager(width, height);
    event_manager = new InexorCefEventManager();
    console = new InexorCefConsole();
    menu = new InexorCefMenu();
    context_manager = new InexorCefContextManager();
    layer_manager->AddLayerProvider(console);
    layer_manager->AddLayerProvider(menu);
    context_manager->AddSubContext(layer_manager);
    context_manager->AddSubContext(event_manager);
    context_manager->AddSubContext(mouse_manager);
    context_manager->AddSubContext(console);
    context_manager->AddSubContext(menu);
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
    layer_manager->InitializeLayers();
}

void InexorCefApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> browser_context)
{
    // cefdebug("InexorCefApp::OnContextCreated", "Injecting inexor object into javascript context");
    browser_context->GetGlobal()->SetValue("inexor", context_manager->GetContext(), V8_PROPERTY_ATTRIBUTE_NONE);
}
