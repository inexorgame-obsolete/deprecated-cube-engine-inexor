#include "inexor/ui/InexorMouseManager.hpp"

void InexorMouseManager::InitializeContext()
{
    CreateFunction("show", this);
    CreateFunction("hide", this);
    CreateFunction("setTexture", this);
    CreateVariable("visible", true);
    CreateVariable("x", true);
    CreateVariable("y", true);
}

bool InexorMouseManager::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "show") {
        Show();
        return true;
    } else if (name == "hide") {
        Hide();
        return true;
    } else if (name == "setTexture") {
        if (arguments.size() == 2 && arguments[0]->IsString() && arguments[1]->IsInt()) {
            SetTexture(arguments[0]->GetStringValue().ToString(), arguments[1]->GetIntValue());
            return true;
        }
    }
    return false;
}

bool InexorMouseManager::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "visible") {
        return_value = CefV8Value::CreateBool(IsVisible());
        return true;
    } else if (name == "x") {
        return_value = CefV8Value::CreateInt(x);
        return true;
    } else if (name == "y") {
        return_value = CefV8Value::CreateInt(y);
        return true;
    }
    return false;
}

bool InexorMouseManager::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

void InexorMouseManager::Update(const CefMouseEvent& event) {
    x = event.x;
    y = event.y;
}

void InexorMouseManager::SetMax(int width, int height) {
    max_x = width;
    max_y = height;
};

void InexorMouseManager::SetTexture(std::string texture, int blendFunction)
{
    this->texture = texture;
    this->blendFunction = blendFunction;
}

void InexorMouseManager::Render()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float fx = (2.0f * ((float) x / (float) max_x)) - 1.0f;
    float fy = 1.0f -(2.0f * ((float) y / (float) max_y));
    float ratio = (float) max_x / (float) max_y;
    float gx = size;
    float gy = size * ratio;

    glBlendFunc(GL_ONE, blendFunction);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    // TODO: Read a texture
    // settexture(texture.c_str(), 3);

    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(fx, fy, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(fx + gx, fy, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(fx + gx, fy - gy, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(fx, fy - gy, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void InexorMouseManager::SendMouseMoveEvent(SDL_Event event)
{
    CefMouseEvent mouse_move_event;
    mouse_move_event.x = event.motion.x;
    mouse_move_event.y = event.motion.y;
    Update(mouse_move_event);
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
