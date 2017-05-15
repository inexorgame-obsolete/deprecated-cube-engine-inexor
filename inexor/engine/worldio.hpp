#pragma once
/// World input output: legacy serialisation of map files.

#include "inexor/shared/ents.hpp"
#include "inexor/shared/cube_vector.hpp"
#include "inexor/shared/cube_types.hpp"

extern bool load_world(const char *mname, const char *cname = nullptr);
extern bool save_world(const char *mname, bool nolms = false);
extern void getmapfilename(const char *fname, const char *cname, char *mapname);
extern uint getmapcrc();
extern void clearmapcrc();
extern bool loadents(const char *fname, vector<entity> &ents, uint *crc = nullptr);

