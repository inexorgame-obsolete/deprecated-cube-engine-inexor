#pragma once

#include "inexor/fpsgame/fpsent.hpp"
#include "inexor/shared/cube_vector.hpp"
#include "inexor/shared/geom.hpp"
#include "inexor/shared/ents.hpp"

namespace game {

// TODO: actually this whole structure is not needed outside
struct projectile {
    vec dir, o, to, offset;
    float speed;
    fpsent *owner;
    int gun;
    bool local;
    int offsetmillis;
    int id;
    entitylight light;
};
extern vector<projectile> projs;

extern void clearprojectiles();

extern void renderprojectiles();

enum {
    BNC_GRENADE,
    BNC_BOMB,
    BNC_SPLINTER,
    BNC_GIBS,
    BNC_DEBRIS,
    BNC_BARRELDEBRIS
};

struct bouncer : physent {
    int lifetime, bounces;
    float lastyaw, roll;
    bool local;
    fpsent *owner;
    int bouncetype, variant;
    vec offset;
    int offsetmillis;
    int id;
    entitylight light;
    int generation;

    bouncer() : bounces(0), roll(0), variant(0) {
        type = ENT_BOUNCE;
    }
};

extern vector<bouncer *> bouncers;


extern void clearbouncers();

extern void renderbouncers();

extern void preloadbouncers();
} // ns game
