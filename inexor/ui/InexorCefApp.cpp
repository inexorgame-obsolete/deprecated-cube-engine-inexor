#include "inexor/ui/InexorCefApp.hpp"

InexorCefApp::InexorCefApp(int width, int height)
{
    context_manager = new InexorContextManager();

    layer_manager = new InexorLayerManager(width, height);
    context_manager->AddSubContext(layer_manager);

    mouse_manager = new InexorMouseManager(layer_manager);
    context_manager->AddSubContext(mouse_manager);

    keyboard_manager = new InexorKeyboardManager(layer_manager);
    context_manager->AddSubContext(keyboard_manager);

    frame = new InexorFrame();
    context_manager->AddSubContext(frame);
    layer_manager->AddLayerProvider(frame);

    SetScreenSize(width, height);

    mouse_manager->Show();
}

void InexorCefApp::Destroy()
{
    layer_manager->DestroyLayers();
}

void InexorCefApp::Render()
{
    layer_manager->Render();
    if (HasFocus())
      mouse_manager->Render();
}

void InexorCefApp::SetScreenSize(int width, int height) {
    mouse_manager->SetMax(width, height);
    layer_manager->SetScreenSize(width, height);
}

void InexorCefApp::OnContextInitialized()
{
    CEF_REQUIRE_UI_THREAD();
    layer_manager->InitializeLayers();
}

void InexorCefApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> browser_context)
{
    // cefdebug("InexorCefApp::OnContextCreated", "Injecting inexor object into javascript context");
    browser_context->GetGlobal()->SetValue(context_manager->GetContextName(), context_manager->GetContext(), V8_PROPERTY_ATTRIBUTE_NONE);
}

bool InexorCefApp::HandleSdlEvent(SDL_Event event) {
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
