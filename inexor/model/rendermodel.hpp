#pragma once
#include "inexor/shared/cube_types.hpp"   // for string
#include "inexor/shared/cube_vector.hpp"  // for vector
#include "inexor/model/model.hpp"

struct model;
struct occludequery;

struct mapmodelinfo { string name; model *m; };

extern void findanims(const char *pattern, vector<int> &anims);
extern mapmodelinfo *getmminfo(int i);
extern void startmodelquery(occludequery *query);
extern void endmodelquery();

extern void preloadusedmapmodels(bool msg = false, bool bih = false);

static inline model *loadmapmodel(int n)
{
    extern vector<mapmodelinfo> mapmodels;
    if(mapmodels.inrange(n))
    {
        model *m = mapmodels[n].m;
        return m ? m : loadmodel(nullptr, n);
    }
    return nullptr;
}
