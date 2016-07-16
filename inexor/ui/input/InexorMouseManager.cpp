#include "inexor/ui/input/InexorMouseManager.hpp"

namespace inexor {
namespace ui {
namespace input {

void InexorMouseManager::InitializeContext()
{
}

bool InexorMouseManager::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorMouseManager::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorMouseManager::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

void InexorMouseManager::SendMouseMoveEvent(SDL_Event event)
{
    x = event.motion.x;
    y = event.motion.y;
    CefMouseEvent mouse_move_event;
    mouse_move_event.x = event.motion.x;
    mouse_move_event.y = event.motion.y;
    layer_manager->SendMouseMoveEvent(mouse_move_event, false);
}

void InexorMouseManager::SendMouseClickEvent(SDL_Event event)
{
    CefMouseEvent mouse_click_event;
    mouse_click_event.x = event.motion.x;
    mouse_click_event.y = event.motion.y;
    mouse_click_event.modifiers = 0;
    CefBrowserHost::MouseButtonType mouse_button_type = (event.button.button == 1 ? MBT_LEFT : ( event.button.button == 3 ? MBT_RIGHT : MBT_MIDDLE));
    layer_manager->SendMouseClickEvent(
        mouse_click_event,
        mouse_button_type,
        event.button.state != SDL_PRESSED,
        1
    );
}

void InexorMouseManager::SendMouseWheelEvent(SDL_Event event)
{
    CefMouseEvent mouse_wheel_event;
    mouse_wheel_event.x = event.motion.x;
    mouse_wheel_event.y = event.motion.y;
    mouse_wheel_event.modifiers = 1;
    layer_manager->SendMouseWheelEvent(
        mouse_wheel_event,
        event.wheel.x > 0 ? 20 : (event.wheel.x < 0 ? -20 : 0),
        event.wheel.y > 0 ? 20 : (event.wheel.y < 0 ? -20 : 0)
    );
}

}
}
}
