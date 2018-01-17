#pragma once

#include "inexor/fpsgame/fpsent.hpp"
// Moving platforms, obstacles (bomberman mode) and barels
#include "inexor/shared/cube_vector.hpp"  // for vector

struct fpsent;
struct physent;
struct vec;

namespace game {

struct movable;

extern vector<movable *> movables;

extern void clearmovables();
extern void stackmovable(movable *d, physent *o);
extern void updatemovables(int curtime);
extern void rendermovables();
extern void suicidemovable(movable *m);
extern void hitmovable(int damage, movable *m, fpsent *at, const vec &vel, int gun);
extern bool isobstaclealive(movable *m);

} // ns game
