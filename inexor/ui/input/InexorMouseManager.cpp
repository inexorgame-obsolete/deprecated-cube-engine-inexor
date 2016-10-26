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

void InexorMouseManager::SendMouseMoveEvent(SDL_Event &e)
{
    x = e.motion.x;
    y = e.motion.y;
    CefMouseEvent mouse_move_event;
    mouse_move_event.x = e.motion.x;
    mouse_move_event.y = e.motion.y;
    layer_manager->SendMouseMoveEvent(mouse_move_event, false);
}

void InexorMouseManager::SendMouseClickEvent(SDL_Event &e)
{
    CefMouseEvent mouse_click_event;
    mouse_click_event.x = e.motion.x;
    mouse_click_event.y = e.motion.y;
    mouse_click_event.modifiers = 0;
    CefBrowserHost::MouseButtonType mouse_button_type = (e.button.button == 1 ? MBT_LEFT : ( e.button.button == 3 ? MBT_RIGHT : MBT_MIDDLE));
    layer_manager->SendMouseClickEvent(
        mouse_click_event,
        mouse_button_type,
        e.button.state != SDL_PRESSED,
        1
    );
}

void InexorMouseManager::SendMouseWheelEvent(SDL_Event &e)
{
    CefMouseEvent mouse_wheel_event;
    int delta_x = e.wheel.x;
    int delta_y = e.wheel.y;
    if(e.wheel.direction == SDL_MOUSEWHEEL_FLIPPED)
        delta_y *= -1;
    else
        delta_x *= -1;
    layer_manager->SendMouseWheelEvent(mouse_wheel_event, delta_x * 40, delta_y * 40); // TODO: get rid of *20, but make it resolution relative
}

}
}
}
