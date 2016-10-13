#include <iostream>

#include "inexor/ui/InexorCefApp.hpp"

InexorCefApp::InexorCefApp(int width, int height)
{
    std::cerr << "init: cef: construct InexorCefApp (width: " << width << " height " << height << ")\n";

    context_manager = new InexorContextManager();

    layer_manager = new InexorLayerManager(width, height);
    context_manager->AddSubContext(layer_manager);

    mouse_manager = new InexorMouseManager(layer_manager, width, height);
    context_manager->AddSubContext(mouse_manager);

    keyboard_manager = new InexorKeyboardManager(layer_manager);
    context_manager->AddSubContext(keyboard_manager);

    SetScreenSize(width, height);

    std::string layer_name("ui");
    std::string layer_url("http://localhost:48702/treeui/");
    user_interface = new InexorUserInterface(layer_name, layer_url);
    user_interface->Show();

    context_manager->AddSubContext(user_interface);
    layer_manager->AddLayerProvider(user_interface);
}

void InexorCefApp::Destroy()
{
    layer_manager->DestroyLayers();
}

void InexorCefApp::SetScreenSize(int width, int height) {
    mouse_manager->SetScreenSize(width, height);
    layer_manager->SetScreenSize(width, height);
}

void InexorCefApp::OnContextInitialized()
{
    CEF_REQUIRE_UI_THREAD();
    layer_manager->InitializeLayers();
}

void InexorCefApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
    std::cerr << " ====================== InexorCefApp::OnContextCreated() Injecting inexor object into javascript context\n";
    CefRefPtr<CefV8Value> window_object = context->GetGlobal();
    context->GetGlobal()->SetValue(context_manager->GetContextName(), context_manager->GetContext(), V8_PROPERTY_ATTRIBUTE_NONE);
}

bool InexorCefApp::HandleSdlEvent(SDL_Event event) {
    // std::cerr << "InexorCefApp::HandleSdlEvent()\n";
    switch(event.type) {
        case SDL_TEXTINPUT:
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            GetKeyboardManager()->SendKeyEvent(event);
            return true;

        case SDL_MOUSEMOTION:
            GetMouseManager()->SendMouseMoveEvent(event);
            return true;

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            GetMouseManager()->SendMouseClickEvent(event);
            return true;

        case SDL_MOUSEWHEEL:
            GetMouseManager()->SendMouseWheelEvent(event);
            return true;

        default:
            return false;
    }
}
