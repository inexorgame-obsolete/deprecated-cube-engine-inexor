#pragma once

#include "inexor/fpsgame/fpsent.hpp"
#include "inexor/shared/cube_vector.hpp"

namespace game {
extern void showscores(bool on);
extern void getbestplayers(vector<fpsent *> &best);
extern void getbestteams(vector<const char *> &best);
}
