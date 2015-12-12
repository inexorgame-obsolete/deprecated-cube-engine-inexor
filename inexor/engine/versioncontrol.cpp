// versioncontrol.cpp: control the management of map versioning, merging and branching

#include "inexor/engine/engine.h"

/////////// version control //////////////
extern SharedVar<int> nompedit;
extern SharedVar<int> diffmode;


cube *refcubes = newcubes(F_SOLID);
cube *curcubes = newcubes(F_SOLID);

// alternative cubes used for diff between
// work cube is the one referencing the actual map we're working with.
// the current version and a reference are used to toggle between different options
struct altcubes
{
    cube *work;
    cube *cur;
    cube *ref;
    int r, size;      // r is the resolved indicator: 0 for unresolved, 1 for *cur, 2 for *ref;
    ivec pos;
};

std::vector<altcubes> diffs;

bool cube_equal(cube &a, cube &b)
{
    if (a.material != b.material) return false;
    loopi(6) if (a.texture[i] != b.texture[i]) return false;
    loopi(12) if (a.edges[i] != b.edges[i]) return false;
    return true;
}

std::vector<altcubes> cube_diff(cube &work, cube &cur, cube &ref, int size, ivec pos)
{
    std::vector<altcubes> diff, self;
    self.push_back({&work, &cur, &ref, 0, size, pos});

    if (!cur.children && ref.children)
    {
        if (isempty(cur)) cur.children = newcubes(F_EMPTY);
        else if (isentirelysolid(cur)) cur.children = newcubes(F_SOLID);
        else return self;

        loopi(8)
        {
            cur.children[i].material = cur.material;
            loopj(6) cur.children[i].texture[j] = cur.texture[j];
            loopj(12) cur.children[i].edges[j] = cur.edges[j];
        }
    }
    else if (cur.children && !ref.children)
    {
        if (isempty(ref)) ref.children = newcubes(F_EMPTY);
        else if (isentirelysolid(ref)) ref.children = newcubes(F_SOLID);
        else return self;

        loopi(8)
        {
            ref.children[i].material = ref.material;
            loopj(6) ref.children[i].texture[j] = ref.texture[j];
            loopj(12) ref.children[i].edges[j] = ref.edges[j];
        }
    }
    else if (!cube_equal(cur, ref)) return self;
 
    if (cur.children && ref.children)
    {
        loopi(8)
        {
            std::vector<altcubes> child_diff = cube_diff(work.children[i], cur.children[i], ref.children[i], size>>1, ivec(i, pos, size>>1));
            diff.insert(diff.end(), child_diff.begin(), child_diff.end());
        }
    }
    return diff;
}

void vc_commit()
{
    if (!diffmode)
    {
        loopi(8) copycube(worldroot[i], refcubes[i]);
        diffs.clear();
    }
    else
        conoutf(CON_INFO, "Cannot commit in diff mode. You need to either exit diff mode or resolve merge conflicts.");
}

int curconflict = -1;

void colordiffs()
{

    VSlot red, blue;
    red.changed = 1<<VSLOT_COLOR;
    red.colorscale = vec(1.0f, 0.0f, 0.0f);
    blue.changed = 1<<VSLOT_COLOR;
    blue.colorscale = vec(0.0f, 0.0f, 1.0f);

    VSlot *editred = remapvslot(1, 1, red);
    remappedvslots.setsize(0);
    VSlot *editblue = remapvslot(1, 1, blue);
    remappedvslots.setsize(0);
    
    loopi(diffs.size())
    {
        if (diffs[i].r == 0)
        {
            loopj(6)
                diffs[i].work->texture[j] = (i == curconflict) ? editred->index : editblue->index;
        }
    }
}

void selectdiff(int i)
{
    sel = selinfo();
    sel.o = diffs[i].pos;
    sel.s = ivec(1,1,1);
    sel.grid = sel.cxs = sel.cys = diffs[i].size;
}

void selectdiff(int i, block3 &b)
{
    b = block3();
    b.o = diffs[i].pos;
    b.s = ivec(1,1,1);
    b.grid = diffs[i].size;
}

void changeddiff(int i)
{
    block3 b;
    selectdiff(i, b);
    changed(b, false);
}

// get the difference between the reference and the current state of the map
void vc_diff()
{
    // toggle diffmode
    diffmode = !diffmode;

    // going into diffmode
    if (diffmode)
    {
        // making a copy of the working tree to keep track of the "current" tree before diff
        loopi(8)
            copycube(worldroot[i], curcubes[i]);
        
        // TODO take into account already resolved diffs (could be an option)
        // reset diffs before getting the new ones
        diffs.clear();

        loopi(8)
        {
            std::vector<altcubes> d = cube_diff(worldroot[i], curcubes[i], refcubes[i], worldsize>>1, ivec(i, ivec(0,0,0), worldsize>>1));
            diffs.insert(diffs.end(), d.begin(), d.end());
        }

        conoutf(CON_INFO, "Number of diff cubes: %lu", diffs.size());

        conoutf(CON_INFO, "diffmode \fs\f1ON\fr");
        // show the smallest cubes that differ by reseting them to plain solid cubes
        loopi(diffs.size())
        {
            discardchildren(*diffs[i].work);
            freecubeext(*diffs[i].work);
            solidfaces(*diffs[i].work);
            loopj(6) diffs[i].work->texture[j] = 1;
        }
        colordiffs();
        loopi(diffs.size()) changeddiff(i);
    }
    else
    {
        conoutf(CON_INFO, "diffmode \fs\f1OFF\fr");

        // reset work to cur
        loopi(diffs.size())
        {
            if (diffs[i].r == 2)
                pastecube(*diffs[i].ref, *diffs[i].work);
            else    
                pastecube(*diffs[i].cur, *diffs[i].work);
            changeddiff(i);
        }
    }

    commitchanges(); // submit octree changes
}

void nextconflict()
{
    if (!diffmode) return;
    if (diffs.size() == 0)
    {
        curconflict = -1;
        conoutf(CON_INFO, "No more conflicts to resolve");
        return;
    }

    // rotate through conflicts
    curconflict++;

    bool allresolved = true;

    // find the first unresolved conflict
    loopi(diffs.size())
    {
        int j = (curconflict + i) % diffs.size();
        if (diffs[j].r == 0) {
            curconflict = j;
            allresolved = false;
            break;
        }
    }

    if (allresolved)
    {
        curconflict = -1;
        conoutf(CON_INFO, "No more conflicts to resolve");
        return;
    }
    else
    {
        colordiffs();
        loopi(diffs.size()) changeddiff(i);
        selectdiff(curconflict);
        commitchanges(); // submit octree changes
    }
}
COMMAND(nextconflict, "");

void resolve()
{
    if (!diffmode || curconflict < 0) return;

    altcubes ac = diffs[curconflict];

    switch (ac.r)
    {
        case 0:
        case 2:
            conoutf(CON_INFO, "current");
            diffs[curconflict].r = 1;
            pastecube(*ac.cur, *ac.work);
            break;
        case 1:
            conoutf(CON_INFO, "reference");
            diffs[curconflict].r = 2;
            pastecube(*ac.ref, *ac.work);
            break;   
    }

    selectdiff(curconflict);
    changed(sel, true);
}
COMMAND(resolve, "");

void diffpaste() {}
// Not working at the moment
// void diffpaste() {
//     if (curconflict < 0) return; 
//     if (diffs[curconflict].r == 0) return;

//     conoutf(CON_INFO, "pasting the current conflict");
    
//     block3 b;
//     selectdiff(curconflict, b);
//     pasteblock(b, sel, true);
// }

struct commit_metadata
{
    char author[16];
    char message[100];
    uint prevcommitcrc;
    int version;                           // any >8bit quantity is little endian
    // TODO timestamp

    commit_metadata(char *a, char *m, uint p) : prevcommitcrc(p)
    {
        std::strncpy(author, a, 15); // overflow safe
        author[15] = '\0';
        std::strncpy(message, m, 99); // overflow safe
        message[99] = '\0';
    }
};

struct cubepossize
{
    cube* c;
    ivec  p;
    int   s;
};

struct commit
{
    commit_metadata* cm;
    
    // content of the commit: either a snapshot (the whole octree) or a vector of diffs
    cube* snapshot = nullptr;
    std::vector<cubepossize> diffs;

    commit(commit_metadata* cm, cube* c) : cm(cm)
    {
        snapshot = newcubes(F_SOLID);
        loopi(8)
            copycube(worldroot[i], snapshot[i]);
    }
    commit(commit_metadata* cm, std::vector<cubepossize> d) : cm(cm), snapshot(NULL), diffs(d) {}

    ~commit()
    {
        diffs.clear();
        if (snapshot)
        {
            loopi (8) discardchildren(snapshot[i]);
            DELETEP(snapshot)
        }
    }
};

struct commit_header
{
    char magic[4] = {'C', 'M', 'T', 'H'};  // CMTH for .cmt header
    int version;                           // any >8bit quantity is little endian
    int headersize;                        // sizeof(header)
    uint prevcommitcrc;
    char author[16];
    char message[100];

    commit_header(const commit_metadata &cm) : version(cm.version), headersize(sizeof(commit_header)), prevcommitcrc(cm.prevcommitcrc)
    {
        std::strncpy(author, cm.author, 15); // overflow safe
        std::strncpy(message, cm.message, 99); // overflow safe
    }
};

static hashtable<commit, uint> vccommits;


void savecommit(commit_header hdr, commit cmt) {
// static string buf;
//     int format = -1, dirlen = 0;
//     copystring(buf, screenshotdir);
//         dirlen = strlen(buf);
//         if(buf[dirlen] != '/' && buf[dirlen] != '\\' && dirlen+1 < (int)sizeof(buf)) { buf[dirlen] = '/'; buf[dirlen+1] = '\0'; }
//         const char *dir = findfile(buf, "w");
//         if(!fileexists(dir, "w")) createdir(dir);
//     }
//     if(filename[0])
//     {
//         concatstring(buf, filename);
//         format = guessimageformat(buf, -1);
//     }
//     else
//     {
//         const char *sstime = gettimestr();
//         concatstring(buf, sstime);

//         const char *map = game::getclientmap()
    // defformatstring(filename, "%s/%s.obr", *prefabdir, name);
    // path(filename);
}
// void saveprefab(char *name)
// {
//     if(!name[0] || noedit(true) || (nompedit && multiplayer())) return;
//     prefab *b = prefabs.access(name);
//     if(!b)
//     {
//         b = &prefabs[name];
//         b->name = newstring(name);
//     }
//     if(b->copy) freeblock(b->copy);
//     protectsel(b->copy = blockcopy(block3(sel), sel.grid));
//     changed(sel);
//     defformatstring(filename, "%s/%s.obr", *prefabdir, name);
//     path(filename);
//     stream *f = opengzfile(filename, "wb");
//     if(!f) { conoutf(CON_ERROR, "could not write prefab to %s", filename); return; }
//     prefabheader hdr;
//     memcpy(hdr.magic, "OEBR", 4);
//     hdr.version = 0;
//     lilswap(&hdr.version, 1);
//     f->write(&hdr, sizeof(hdr));
//     streambuf<uchar> s(f);
//     if(!packblock(*b->copy, s)) { delete f; conoutf(CON_ERROR, "could not pack prefab %s", filename); return; }
//     delete f;
//     conoutf("wrote prefab file %s", filename);
// }

void savecommit(char *author, char *message, cube* snapshot)
{
    if(!author[0] || !message[0] || !snapshot || noedit(true) || (nompedit && multiplayer())) return;

    commit_metadata cmmd(author, message, 0 /* TODO */);
    commit_header hdr(cmmd);
    commit cmt(&cmmd, curcubes);

    savecommit(hdr, cmt);
}

void savecommit(char *author, char *message, std::vector<altcubes> diffs)
{
    if(!author[0] || !message[0] || !diffs.size() || noedit(true) || (nompedit && multiplayer())) return;

    commit_metadata cmmd(author, message, 0 /* TODO */);
    commit_header hdr(cmmd);

    std::vector<cubepossize> d;
    loopi(diffs.size())
    {
        // r == 0: possibly raise an error/abort commit
        if (diffs[i].r == 0) d.push_back({diffs[i].work, diffs[i].pos, diffs[i].size});
        if (diffs[i].r == 1) d.push_back({diffs[i].cur,  diffs[i].pos, diffs[i].size});
        if (diffs[i].r == 2) d.push_back({diffs[i].ref,  diffs[i].pos, diffs[i].size});
    }
    commit cmt(&cmmd, d);

    savecommit(hdr, cmt);
}



void loadcommit(uint crc)
{
//     if(!name[0] || noedit() || (nompedit && multiplayer())) return;
//     prefab *b = prefabs.access(name);
//     if(!b)
//     {
//         defformatstring(filename, "%s/%s.obr", *prefabdir, name);
//         path(filename);
//         stream *f = opengzfile(filename, "rb");
//         if(!f) { conoutf(CON_ERROR, "could not read prefab %s", filename); return; }
//         prefabheader hdr;
//         if(f->read(&hdr, sizeof(hdr)) != sizeof(prefabheader) || memcmp(hdr.magic, "OEBR", 4)) { delete f; conoutf(CON_ERROR, "prefab %s has malformatted header", filename); return; }
//         lilswap(&hdr.version, 1);
//         if(hdr.version != 0) { delete f; conoutf(CON_ERROR, "prefab %s uses unsupported version", filename); return; }
//         streambuf<uchar> s(f);
//         block3 *copy = NULL;
//         if(!unpackblock(copy, s)) { delete f; conoutf(CON_ERROR, "could not unpack prefab %s", filename); return; }
//         delete f;
//         b = &prefabs[name];
//         b->name = newstring(name);
//         b->copy = copy;
//     }
//     pasteblock(*b->copy, sel, true);
}

void applycommit(uint crc) {}

#define VERSION_CONTROL_COMMANDS_ARE "Version control commands are: \fs\f2help commit diff merge pull push log\fr"

void help(tagval *args, int numargs)
{
	if (numargs == 0)
	{
		conoutf(CON_INFO, VERSION_CONTROL_COMMANDS_ARE);
		conoutf(CON_INFO, "Type \fs\f2/vc help <command>\fr to find out more about a specific command.");
	}
	else
	{
		if (!strcmp(args[0].getstr(), "help"))
			conoutf(CON_INFO, "Type \fs\f2/vc help <command>\fr to find out more about a specific command.");
		else if (!strcmp(args[0].getstr(), "commit"))
			conoutf(CON_INFO, "Info about the commit command");
		else if (!strcmp(args[0].getstr(), "diff"))
			conoutf(CON_INFO, "Info about the diff command");
		else if (!strcmp(args[0].getstr(), "merge"))
			conoutf(CON_INFO, "Info about the diff command");
		else if (!strcmp(args[0].getstr(), "pull"))
			conoutf(CON_INFO, "Info about the pull command");
		else if (!strcmp(args[0].getstr(), "push"))
			conoutf(CON_INFO, "Info about the push command");
		else if (!strcmp(args[0].getstr(), "log"))
			conoutf(CON_INFO, "Info about the log command");
		else
			conoutf(CON_INFO, VERSION_CONTROL_COMMANDS_ARE);
	}
}

void commit(tagval *args, int numargs)
{
	conoutf(CON_INFO, "vc commit");
	vc_commit();
}

void diff(tagval *args, int numargs)
{
	conoutf(CON_INFO, "vc diff");
	vc_diff();
}

void merge(tagval *args, int numargs)
{
	conoutf(CON_INFO, "vc merge");
}

void pull(tagval *args, int numargs)
{
	conoutf(CON_INFO, "vc pull");
}

void push(tagval *args, int numargs)
{
	conoutf(CON_INFO, "vc push");
}

void log(tagval *args, int numargs)
{
	conoutf(CON_INFO, "vc log");
}

ICOMMAND(vc, "V", (tagval *args, int numargs),
{
	if (!editmode) conoutf(CON_INFO, "You need to be in edit mode to use version control.");
	else
	{
		if (numargs == 0) conoutf(CON_INFO, VERSION_CONTROL_COMMANDS_ARE);
		else if (!strcmp(args[0].getstr(), "help"))   help(args++, numargs--);
		else if (!strcmp(args[0].getstr(), "commit")) commit(args++, numargs--);
		else if (!strcmp(args[0].getstr(), "diff"))   diff(args++, numargs--);
		else if (!strcmp(args[0].getstr(), "merge"))  merge(args++, numargs--);
		else if (!strcmp(args[0].getstr(), "pull"))   pull(args++, numargs--);
		else if (!strcmp(args[0].getstr(), "push"))   push(args++, numargs--);
		else if (!strcmp(args[0].getstr(), "log"))    log(args++, numargs--);
		else conoutf(CON_INFO, "Version control command \fs\f3%s\fr not found.", args[0].getstr());
	}
});
