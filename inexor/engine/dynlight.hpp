#pragma once

struct vtxarray;
// Dynlights (dynamic lights) are really primitive shaders which light up the near field
// area of the light source. It does not take into account occlusion.

extern void updatedynlights();
extern int finddynlights();
extern void calcdynlightmask(vtxarray *va);
extern int setdynlights(vtxarray *va);
