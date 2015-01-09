#include "cefmouse.h"

void InexorCefMouseManager::InitializeContext()
{
    CreateFunction("show", this);
    CreateFunction("hide", this);
    CreateFunction("setTexture", this);
    CreateVariable("visible", true);
    CreateVariable("x", true);
    CreateVariable("y", true);
}

bool InexorCefMouseManager::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "show") {
        Show();
        return true;
    } else if (name == "fire") {
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

bool InexorCefMouseManager::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
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

bool InexorCefMouseManager::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

void InexorCefMouseManager::Update(const CefMouseEvent& event) {
    x = event.x;
    y = event.y;
}

void InexorCefMouseManager::SetMax(int width, int height) {
    max_x = width;
    max_y = height;
};

void InexorCefMouseManager::SetTexture(std::string texture, int blendFunction)
{
    this->texture = texture;
    this->blendFunction = blendFunction;
}

void InexorCefMouseManager::Render()
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

    settexture(texture.c_str(), 3);

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
