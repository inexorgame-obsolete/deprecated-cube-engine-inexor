#pragma once

#include "inexor/texture/slot.hpp" // for Texture and Image and Slot
#include "inexor/shared/cube_formatting.hpp"

/// enumeration for icons
enum
{
    HICON_BLUE_ARMOUR = 0,
    HICON_GREEN_ARMOUR,
    HICON_YELLOW_ARMOUR,

    HICON_HEALTH,

    HICON_FIST,
    HICON_SG,
    HICON_CG,
    HICON_RL,
    HICON_RIFLE,
    HICON_GL,
    HICON_PISTOL,
    HICON_BOMB,

    HICON_QUAD,

    HICON_RED_FLAG,
    HICON_BLUE_FLAG,
    HICON_NEUTRAL_FLAG,

    HICON_TOKEN,

    // bomberman
    HICON_BOMBRADIUS,
    HICON_BOMBDELAY,

    HICON_X       = 20,
    HICON_Y       = 1650,
    HICON_TEXTY   = 1644,
    HICON_STEP    = 490,
    HICON_SIZE    = 120,
    HICON_SPACE   = 40
};

enum { G3D_DOWN = 1, G3D_UP = 2, G3D_PRESSED = 4, G3D_ROLLOVER = 8, G3D_DRAGGED = 16 };

enum { EDITORFOCUSED = 1, EDITORUSED, EDITORFOREVER };

struct g3d_gui
{
    virtual ~g3d_gui() {}

    virtual void start(int starttime, float basescale, int *tab = NULL, bool allowinput = true) = 0;
    virtual void end() = 0;

    virtual int text(const char *text, int color, const char *icon = NULL) = 0;
    int textf(const char *fmt, int color, const char *icon = NULL, ...) PRINTFARGS(2, 5)
    {
        defvformatstring(str, icon, fmt);
        return text(str, color, icon);
    }
    virtual int button(const char *text, int color, const char *icon = NULL) = 0;
    int buttonf(const char *fmt, int color, const char *icon = NULL, ...) PRINTFARGS(2, 5)
    {
        defvformatstring(str, icon, fmt);
        return button(str, color, icon);
    }
    virtual int title(const char *text, int color, const char *icon = NULL) = 0;
    int titlef(const char *fmt, int color, const char *icon = NULL, ...) PRINTFARGS(2, 5)
    {
        defvformatstring(str, icon, fmt);
        return title(str, color, icon);
    }
    virtual void background(int color, int parentw = 0, int parenth = 0) = 0;

    virtual void pushlist() {}
    virtual void poplist() {}

    virtual bool allowautotab(bool on) = 0;
    virtual bool shouldtab() { return false; }
    virtual void tab(const char *name = NULL, int color = 0) = 0;
    virtual int image(Texture *t, float scale, bool overlaid = false) = 0;
    virtual int texture(VSlot &vslot, float scale, bool overlaid = true) = 0;
    virtual int playerpreview(int model, int team, int weap, float scale, bool overlaid = false) { return 0; }
    virtual int modelpreview(const char *name, int anim, float scale, bool overlaid = false) { return 0; }
    virtual int prefabpreview(const char *prefab, const vec &color, float scale, bool overlaid = false) { return 0; }
    virtual void slider(int &val, int vmin, int vmax, int color, const char *label = NULL) = 0;
    virtual void separator() = 0;
    virtual void progress(float percent) = 0;
    virtual void strut(float size) = 0;
    virtual void space(float size) = 0;
    virtual void spring(int weight = 1) = 0;
    virtual void column(int col) = 0;
    virtual char *keyfield(const char *name, int color, int length, int height = 0, const char *initval = NULL, int initmode = EDITORFOCUSED) = 0;
    virtual char *field(const char *name, int color, int length, int height = 0, const char *initval = NULL, int initmode = EDITORFOCUSED) = 0;
    virtual void textbox(const char *text, int width, int height, int color = 0xFFFFFF) = 0;
    virtual bool mergehits(bool on) = 0;
};

struct g3d_callback
{
    virtual ~g3d_callback() {}

    int starttime();

    virtual void gui(g3d_gui &g, bool firstpass) = 0;
};

enum
{
    GUI_2D       = 1<<0,
    GUI_FOLLOW   = 1<<1,
    GUI_FORCE_2D = 1<<2,
    GUI_BOTTOM   = 1<<3
};

extern void g3d_addgui(g3d_callback *cb, vec &origin, int flags = 0);
extern bool g3d_movecursor(int dx, int dy);
extern void g3d_cursorpos(float &x, float &y);
extern void g3d_resetcursor();
extern void g3d_limitscale(float scale);


/// Bomberman: HUD announce effects
enum hudannounceeffects
{
    E_STATIC_CENTER = 0,
    E_STATIC_LEFT,
    E_STATIC_RIGHT,
    E_STATIC_TOP,
    E_STATIC_BOTTOM,
    E_FADE_LEFT_RIGHT,
    E_FADE_RIGHT_LEFT,
    E_FADE_TOP_BOTTOM,
    E_FADE_BOTTOM_TOP,
    E_ZOOM_IN,
    E_ZOOM_OUT,
    E_BLINK_CENTER
};


extern int hudannounce_begin;
extern int hudannounce_timeout;
extern int hudannounce_effect;
extern char* hudannounce_text;
