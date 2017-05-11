#pragma once

#include "inexor/shared/ents.hpp"
#include "inexor/shared/geom.hpp"

enum
{
    PART_BLOOD = 0,
    PART_WATER,
    PART_SMOKE,
    PART_STEAM,
    PART_FLAME,
    PART_FIREBALL1, PART_FIREBALL2, PART_FIREBALL3,
    PART_STREAK, PART_LIGHTNING,
    PART_EXPLOSION, PART_EXPLOSION_BLUE,
    PART_SPARK, PART_EDIT,
    PART_SNOW,
    PART_MUZZLE_FLASH1, PART_MUZZLE_FLASH2, PART_MUZZLE_FLASH3,
    PART_HUD_ICON,
    PART_HUD_ICON_GREY,
    PART_TEXT,
    PART_METER, PART_METER_VS,
    PART_LENS_FLARE
};

extern bool canaddparticles();
extern void regular_particle_splash(int type, int num, int fade, const vec &p, int color = 0xFFFFFF, float size = 1.0f, int radius = 150, int gravity = 2, int delay = 0);
extern void regular_particle_flame(int type, const vec &p, float radius, float height, int color, int density = 3, float scale = 2.0f, float speed = 200.0f, float fade = 600.0f, int gravity = -15);
extern void particle_splash(int type, int num, int fade, const vec &p, int color = 0xFFFFFF, float size = 1.0f, int radius = 150, int gravity = 2);
extern void particle_trail(int type, int fade, const vec &from, const vec &to, int color = 0xFFFFFF, float size = 1.0f, int gravity = 20);
extern void particle_text(const vec &s, const char *t, int type, int fade = 2000, int color = 0xFFFFFF, float size = 2.0f, int gravity = 0);
extern void particle_textcopy(const vec &s, const char *t, int type, int fade = 2000, int color = 0xFFFFFF, float size = 2.0f, int gravity = 0);
extern void particle_icon(const vec &s, int ix, int iy, int type, int fade = 2000, int color = 0xFFFFFF, float size = 2.0f, int gravity = 0);
extern void particle_meter(const vec &s, float val, int type, int fade = 1, int color = 0xFFFFFF, int color2 = 0xFFFFF, float size = 2.0f);
extern void particle_flare(const vec &p, const vec &dest, int fade, int type, int color = 0xFFFFFF, float size = 0.28f, physent *owner = NULL);
extern void particle_fireball(const vec &dest, float max, int type, int fade = -1, int color = 0xFFFFFF, float size = 4.0f);
extern void removetrackedparticles(physent *owner = NULL);
