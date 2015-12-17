/// @file management of texture slots as visible ingame.
/// each texture slot can have multiple texture frames, of which currently only the first is used
/// additional frames can be used for various shaders

#ifndef INEXOR_TEX_SLOT_H
#define INEXOR_TEX_SLOT_H

struct Slot;

enum
{
    VSLOT_SHPARAM = 0,
    VSLOT_SCALE,
    VSLOT_ROTATION,
    VSLOT_OFFSET,
    VSLOT_SCROLL,
    VSLOT_LAYER,
    VSLOT_ALPHA,
    VSLOT_COLOR,
    VSLOT_NUM
};

struct VSlot
{
    Slot *slot;
    VSlot *next;
    int index, changed;
    vector<SlotShaderParam> params;
    bool linked;
    float scale;
    int rotation;
    ivec2 offset;
    vec2 scroll;
    int layer;
    float alphafront, alphaback;
    vec colorscale;
    vec glowcolor;

    VSlot(Slot *slot = NULL, int index = -1) : slot(slot), next(NULL), index(index), changed(0)
    {
        reset();
        if(slot) addvariant(slot);
    }

    void addvariant(Slot *slot);

    void reset()
    {
        params.shrink(0);
        linked = false;
        scale = 1;
        rotation = 0;
        offset = ivec2(0, 0);
        scroll = vec2(0, 0);
        layer = 0;
        alphafront = 0.5f;
        alphaback = 0;
        colorscale = vec(1, 1, 1);
        glowcolor = vec(1, 1, 1);
    }

    void cleanup()
    {
        linked = false;
    }
};

struct Slot
{
    struct Tex
    {
        int type;
        Texture *t;
        string name;
        int combined;
    };

    int index;
    vector<Tex> sts;
    Shader *shader;
    vector<SlotShaderParam> params;
    VSlot *variants;
    bool loaded;
    uint texmask;
    char *autograss;
    Texture *grasstex, *thumbnail;
    char *layermaskname;
    int layermaskmode;
    float layermaskscale;
    ImageData *layermask;

    Slot(int index = -1) : index(index), variants(NULL), autograss(NULL), layermaskname(NULL), layermask(NULL) { reset(); }

    void reset()
    {
        sts.shrink(0);
        shader = NULL;
        params.shrink(0);
        loaded = false;
        texmask = 0;
        DELETEA(autograss);
        grasstex = NULL;
        thumbnail = NULL;
        DELETEA(layermaskname);
        layermaskmode = 0;
        layermaskscale = 1;
        if(layermask) DELETEP(layermask);
    }

    void cleanup()
    {
        loaded = false;
        grasstex = NULL;
        thumbnail = NULL;
        loopv(sts)
        {
            Tex &t = sts[i];
            t.t = NULL;
            t.combined = -1;
        }
    }

    Slot &load(bool msg, bool forceload);
    Texture *loadthumbnail();
};

inline void VSlot::addvariant(Slot *slot)
{
    if(!slot->variants) slot->variants = this;
    else
    {
        VSlot *prev = slot->variants;
        while(prev->next) prev = prev->next;
        prev->next = this;
    }
}

struct MSlot : Slot, VSlot
{
    MSlot() : VSlot(this) {}

    void reset()
    {
        Slot::reset();
        VSlot::reset();
    }

    void cleanup()
    {
        Slot::cleanup();
        VSlot::cleanup();
    }
};

extern void loadlayermasks();

extern void clearslots();
extern void cleanupslots();
extern void cleanupvslots();
extern void cleanupmaterialslots();

extern void propagatevslot(VSlot *root, int changed);
extern void texturereset(int first, int num = 0);

extern MSlot &lookupmaterialslot(int slot, bool load = true);
extern Slot &lookupslot(int slot, bool load = true);
extern VSlot &lookupvslot(int slot, bool load = true);
extern VSlot *emptyvslot(Slot &owner);

extern VSlot *editvslot(const VSlot &src, const VSlot &delta);
extern void mergevslot(VSlot &dst, const VSlot &src, const VSlot &delta);

extern void compactvslots(cube *c, int n = 8);
extern void compactvslot(int &index);
extern void compactvslot(VSlot &vs);
extern int compactvslots();

extern void packvslot(vector<uchar> &buf, const VSlot &src);
extern bool unpackvslot(ucharbuf &buf, VSlot &dst, bool delta);

extern vector<Slot *> slots;
extern vector<VSlot *> vslots;

#endif //INEXOR_TEX_SLOT_H
