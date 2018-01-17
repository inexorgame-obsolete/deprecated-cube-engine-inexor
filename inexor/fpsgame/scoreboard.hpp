#pragma once

#include "inexor/shared/cube_vector.hpp"  // for vector

struct fpsent;

namespace game {
extern void showscores(bool on);
extern void getbestplayers(vector<fpsent *> &best);
extern void getbestteams(vector<const char *> &best);

extern void g3d_gamemenus();
}
