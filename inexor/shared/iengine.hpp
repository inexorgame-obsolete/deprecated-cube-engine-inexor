// the interface the game uses to access the engine
#pragma once

#include "inexor/network/SharedTree.hpp"
#include "inexor/network/legacy/game_types.hpp"
#include "inexor/util/legacy_time.hpp"

#include "inexor/engine/octaedit.hpp"
#include "inexor/physics/physics.hpp"


#include "inexor/texture/settexture.hpp"

// world
extern bool emptymap(int factor, bool force, const char *mname = "", bool usecfg = true);
extern bool enlargemap(bool force);
extern int findentity(int type, int index = 0, int attr1 = -1, int attr2 = -1);
extern void findents(int low, int high, bool notspawned, const vec &pos, const vec &radius, vector<int> &found);
extern extentity *newentity(bool local, const vec &o, int type, int v1, int v2, int v3, int v4, int v5, int &idx);
extern void attachentity(extentity &e);
extern bool modifyoctaent(int flags, int id);
extern void mpeditent(int i, const vec &o, int type, int attr1, int attr2, int attr3, int attr4, int attr5, bool local);

extern vec getselpos();
extern int getworldsize();
extern int getmapversion();
extern void renderentcone(const extentity &e, const vec &dir, float radius, float angle);
extern void renderentarrow(const extentity &e, const vec &dir, float radius);
extern void renderentattachment(const extentity &e);
extern void renderentsphere(const extentity &e, float radius);
extern void renderentring(const extentity &e, float radius, int axis = 0);

#include "inexor/io/Error.hpp"
#include "inexor/engine/rendertext.hpp"
#include "inexor/engine/dynlight.hpp"
#include "inexor/engine/rendergl.hpp"
#include "inexor/engine/decal.hpp"
#include "inexor/model/ragdoll.hpp"
#include "inexor/client/network.hpp"
