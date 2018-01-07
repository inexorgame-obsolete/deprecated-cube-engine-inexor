#pragma once

#include "inexor/engine/octa.hpp"
#include "inexor/network/SharedVar.hpp"
#include "inexor/shared/cube_vector.hpp"
#include "inexor/shared/geom.hpp"

extern SharedVar<int> showmat;

extern int findmaterial(const char *name);
extern const char *findmaterialname(int mat);
extern const char *getmaterialdesc(int mat, const char *prefix = "");
extern void genmatsurfs(const cube &c, const ivec &co, int size, vector<materialsurface> &matsurfs);
extern void rendermatgrid(materialsurface *matbuf, int matsurfs);
extern int optimizematsurfs(materialsurface *matbuf, int matsurfs);
extern void setupmaterials(int start = 0, int len = 0);
extern void rendermaterials();
extern int visiblematerial(const cube &c, int orient, const ivec &co, int size, ushort matmask = MATF_VOLUME);

