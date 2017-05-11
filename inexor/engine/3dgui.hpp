#pragma once

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
