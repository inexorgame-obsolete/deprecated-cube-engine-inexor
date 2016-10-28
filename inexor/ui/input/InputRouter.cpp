#include <boost/algorithm/clamp.hpp>

#include "InputRouter.hpp"
#include "inexor/ui/screen/ScreenManager.hpp"
#include "inexor/ui.hpp"

using namespace inexor::ui::screen;
using boost::algorithm::clamp;

// TODO: after refactoring there are still dependencies left
extern void quit();
extern size_t decodeutf8(unsigned char *dst, size_t dstlen, const unsigned char *src, size_t srclen, size_t *carry);
extern void processtextinput(const char *str, int len);
extern void processkey(int code, bool isdown);
extern bool g3d_movecursor(int dx, int dy);
extern void gl_resize();
extern void mousemove(int dx, int dy);
// ENDTODO

namespace inexor {
namespace ui {
namespace input {

InputRouter::InputRouter()
    : shouldgrab(false),
      grabinput(false),
      canrelativemouse(true),
      relativemouse(false),
      textinputmask(0),
      keyrepeatmask(0)
{
}

InputRouter::~InputRouter()
{
}

void InputRouter::keyrepeat(bool on, int mask)
{
    if (on) keyrepeatmask |= mask;
    else keyrepeatmask &= ~mask;
}

void InputRouter::textinput(bool on, int mask)
{
    if (on)
    {
        if (!textinputmask) SDL_StartTextInput();
        textinputmask |= mask;
    }
    else
    {
        textinputmask &= ~mask;
        if (!textinputmask) SDL_StopTextInput();
    }
}

void InputRouter::inputgrab()
{
    if (grabinput)
    {
        SDL_ShowCursor(SDL_FALSE);
        if (canrelativemouse && userelativemouse)
        {
            if (SDL_SetRelativeMouseMode(SDL_TRUE) >= 0)
            {
                SDL_SetWindowGrab(screen_manager.sdl_window, SDL_TRUE);
                relativemouse = true;
            }
            else
            {
                SDL_SetWindowGrab(screen_manager.sdl_window, SDL_FALSE);
                canrelativemouse = false;
                relativemouse = false;
            }
        }
    }
    else
    {
        SDL_ShowCursor(SDL_TRUE); // show OS cursor
        if (relativemouse)
        {
            SDL_SetWindowGrab(screen_manager.sdl_window, SDL_FALSE);
            SDL_SetRelativeMouseMode(SDL_FALSE);
            relativemouse = false;
        }
    }
    shouldgrab = false;
}

void InputRouter::set_grab_input(bool grab_input)
{
    this->grabinput = grab_input;
}

bool InputRouter::interceptkey(int sym)
{
    static int lastintercept = SDLK_UNKNOWN;
    int len = lastintercept == sym ? events.size() : 0;
    SDL_Event event;
    while (pollevent(event))
    {
        switch(event.type)
        {
            case SDL_MOUSEMOTION: break; /// ignore mouse motion events during loading processes
            default: pushevent(event); break;
        }
    }
    lastintercept = sym;
    if (sym != SDLK_UNKNOWN) for(int i = len; i < events.size(); i++)
    {
        if (events[i].type == SDL_KEYDOWN && events[i].key.keysym.sym == sym)
        {
            events.erase(events.begin()+i);
            return true;
        }
    }
    return false;
}

void InputRouter::ignoremousemotion()
{
    SDL_Event e;
    SDL_PumpEvents(); /// pumps the event loop, gathering events from the input devices.
    while (SDL_PeepEvents(&e, 1, SDL_GETEVENT, SDL_MOUSEMOTION, SDL_MOUSEMOTION)); /// check the event queue for messages and optionally return them
}

void InputRouter::checkinput()
{
    SDL_Event event;
    //int lasttype = 0, lastbut = 0;
    bool mousemoved = false;
    while (events.size() || pollevent(event))
    {
        if (events.size()) {
            event = events[0];
            events.erase(events.begin());
        }

        if (event.type == SDL_QUIT) {
            quit();
            return;
        }

        /*
        if (cef_app.get() && cef_app->GetAppLayer()->GetAcceptingInput()) {
            logoutf("checkinput() -> to CEF");
            bool handled = cef_app->HandleSdlEvent(event);
            if (handled) continue;
        }
        */

        if (inexor::ui::cef_app.get()) {
            inexor::ui::cef_app->HandleSdlEvent(event);
        }

        switch(event.type)
        {
            case SDL_TEXTINPUT:
            {
                static unsigned char buf[SDL_TEXTINPUTEVENT_TEXT_SIZE+1];
                int len = decodeutf8(buf, int(sizeof(buf)-1), (const unsigned char *)event.text.text, strlen(event.text.text));
                if (len > 0) { buf[len] = '\0'; processtextinput((const char *)buf, len); }
                break;
            }

            case SDL_KEYDOWN:
            case SDL_KEYUP:
                if (keyrepeatmask || !event.key.repeat)
                    processkey(event.key.keysym.sym, event.key.state==SDL_PRESSED);
                break;

            case SDL_WINDOWEVENT:
                switch(event.window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                        quit();
                        break;

                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        shouldgrab = true;
                        break;
                    case SDL_WINDOWEVENT_ENTER:
                    {
                        set_grab_input(true);
                        inputgrab();
                    }
                break;

                    case SDL_WINDOWEVENT_LEAVE:
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                    {
                        set_grab_input(false);
                        inputgrab();
                        break;
                    }
                    case SDL_WINDOWEVENT_MINIMIZED:
                        screen_manager.set_minimized(true);
                        break;

                    case SDL_WINDOWEVENT_MAXIMIZED:
                    case SDL_WINDOWEVENT_RESTORED:
                        screen_manager.set_minimized(false);
                        break;

                    case SDL_WINDOWEVENT_RESIZED:
                        break;

                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                    {
                        SDL_GetWindowSize(screen_manager.sdl_window, &(screen_manager.screenw), &(screen_manager.screenh));
                        if (!(SDL_GetWindowFlags(screen_manager.sdl_window) & SDL_WINDOW_FULLSCREEN))
                        {
                            scr_w = clamp(screen_manager.screenw, SCR_MINW, SCR_MAXW);
                            scr_h = clamp(screen_manager.screenh, SCR_MINH, SCR_MAXH);
                        }
                        gl_resize();
                    }
                        break;
                }
                break;

            case SDL_MOUSEMOTION:
                if (grabinput)
                {
                    int dx = event.motion.xrel, dy = event.motion.yrel;
                    checkmousemotion(dx, dy);
                    if (!g3d_movecursor(dx, dy)) mousemove(dx, dy);
                    mousemoved = true;
                }
                else if (shouldgrab)
                {
                    set_grab_input(true);
                    inputgrab();
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
#ifdef __linux__
   #define keycodeshift 0
#else
   #define keycodeshift 2*(event.button.button>=SDL_BUTTON_X1)
#endif
                processkey(-event.button.button - keycodeshift, event.button.state==SDL_PRESSED);
                break;

            case SDL_MOUSEWHEEL:
                if (event.wheel.y > 0) { processkey(-4, true); processkey(-4, false); }
                else if (event.wheel.y < 0) { processkey(-5, true); processkey(-5, false); }
                if (event.wheel.x > 0) { processkey(-35, true); processkey(-35, false); }
                else if (event.wheel.x < 0) { processkey(-36, true); processkey(-36, false); }
                break;
        }
    }
    if (mousemoved) resetmousemotion();

}

void InputRouter::pushevent(const SDL_Event &e)
{
    events.push_back(e);
}

bool InputRouter::filterevent(const SDL_Event &event)
{
    switch(event.type)
    {
        case SDL_MOUSEMOTION:
            if (grabinput && !relativemouse && !(SDL_GetWindowFlags(screen_manager.sdl_window) & SDL_WINDOW_FULLSCREEN))
            {
                if (event.motion.x == screen_manager.screenw / 2 && event.motion.y == screen_manager.screenh / 2)
                    return false;  // ignore any motion events generated by SDL_WarpMouse
                #ifdef __APPLE__
                if (event.motion.y == 0)
                    return false;  // let mac users drag windows via the title bar
                #endif
            }
            break;
    }
    return true;
}

bool InputRouter::pollevent(SDL_Event &event)
{
    while (SDL_PollEvent(&event))
    {
        if (filterevent(event)) return true;
    }
    return false;
}

void InputRouter::resetmousemotion()
{
    if (grabinput && !relativemouse && !(SDL_GetWindowFlags(screen_manager.sdl_window) & SDL_WINDOW_FULLSCREEN))
    {
        SDL_WarpMouseInWindow(screen_manager.sdl_window, screen_manager.screenw / 2, screen_manager.screenh / 2);
    }
}

void InputRouter::checkmousemotion(int &dx, int &dy)
{
    for (int i = 0; i < events.size(); i++)
    {
        SDL_Event &event = events[i];
        if (event.type != SDL_MOUSEMOTION)
        {
            if (i > 0) events.erase(events.begin()+i);
            return;
        }
        dx += event.motion.xrel;
        dy += event.motion.yrel;
    }
    events.clear();
    SDL_Event event;
    while (pollevent(event))
    {
        if (event.type != SDL_MOUSEMOTION)
        {
            events.push_back(event);
            return;
        }
        dx += event.motion.xrel;
        dy += event.motion.yrel;
    }
}

}
}
}
