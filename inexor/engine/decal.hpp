#pragma once

// Decals are used to temporarily blend over the texture of a wall/model because of some past event.
// Could get superseeded by a background world loader/updater.

extern void initdecals();
extern void cleardecals();
extern void renderdecals(bool mainpass = false);
