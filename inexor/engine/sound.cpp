// sound.cpp: basic positional sound using sdl_mixer

#include "inexor/engine/engine.hpp"
#include "inexor/filesystem/mediadirs.hpp"
#include "inexor/ui/screen/ScreenManager.hpp"
#include "inexor/util/Logging.hpp"

#include <string>


using namespace inexor::filesystem;
using namespace inexor::rendering::screen;

// #define MAXVOL MIX_MAX_VOLUME  // TODO Sound refractoring
#define MAXVOL 100

namespace inexor {
namespace sound {

bool nosound = true;

struct soundsample
{
    char *name;
    //Mix_Chunk *chunk;  // TODO Sound refractoring

    soundsample() : name(NULL)/*, chunk(NULL)*/ {}  // TODO Sound refractoring
    ~soundsample() { DELETEA(name); }

    void cleanup() { /*if(chunk) { Mix_FreeChunk(chunk); chunk = NULL; } */}  // TODO Sound refractoring
    bool load(bool msg = false);
};

struct soundslot
{
    soundsample *sample;
    int volume;
};

struct soundconfig
{
    int slots, numslots;
    int maxuses;

    bool hasslot(const soundslot *p, const vector<soundslot> &v) const
    {
        return p >= v.getbuf() + slots && p < v.getbuf() + slots+numslots && slots+numslots < v.length(); 
    }

    int chooseslot() const
    {
        return numslots > 1 ? slots + rnd(numslots) : slots;
    }
};

struct soundchannel
{
    int id;
    bool inuse;
    vec loc;
    soundslot *slot;
    extentity *ent;
    int radius, volume, pan, flags;
    bool dirty;

    soundchannel(int id) : id(id) { reset(); }

    bool hasloc() const { return loc.x >= -1e15f; }
    void clearloc() { loc = vec(-1e16f, -1e16f, -1e16f); }

    void reset()
    {
        inuse = false;
        clearloc();
        slot = NULL;
        ent = NULL;
        radius = 0;
        volume = -1;
        pan = -1;
        flags = 0;
        dirty = false;
    }
};
vector<soundchannel> channels;
int maxchannels = 0;

soundchannel &newchannel(int n, soundslot *slot, const vec *loc = NULL, extentity *ent = NULL, int flags = 0, int radius = 0)
{
    if(ent)
    {
        loc = &ent->o;
        ent->flags |= EF_SOUND;
    }
    while(!channels.inrange(n)) channels.add(channels.length());
    soundchannel &chan = channels[n];
    chan.reset();
    chan.inuse = true;
    if(loc) chan.loc = *loc;
    chan.slot = slot;
    chan.ent = ent;
    chan.flags = 0;
    chan.radius = radius;
    return chan;
}

void freechannel(int n)
{
    if(!channels.inrange(n) || !channels[n].inuse) return;
    soundchannel &chan = channels[n];
    chan.inuse = false;
    if(chan.ent) chan.ent->flags &= ~EF_SOUND;
}

void syncchannel(soundchannel &chan)
{
    if(!chan.dirty) return;
    //if(!Mix_FadingChannel(chan.id)) Mix_Volume(chan.id, chan.volume);
    //Mix_SetPanning(chan.id, 255-chan.pan, chan.pan);  // TODO Sound refractoring
    chan.dirty = false;
}

void stopchannels()
{
    loopv(channels)
    {
        soundchannel &chan = channels[i];
        if(!chan.inuse) continue;
        //Mix_HaltChannel(i);  // TODO Sound refractoring
        freechannel(i);
    }
}

VARFP(soundvol, 0, 255, 255, if(!soundvol) { stopchannels(); });
VARF(soundchans, 1, 32, 128, initwarning("sound configuration", INIT_RESET, CHANGE_SOUND));
VARF(soundfreq, 0, 44100, 44100, initwarning("sound configuration", INIT_RESET, CHANGE_SOUND));
VARF(soundbufferlen, 128, 1024, 4096, initwarning("sound configuration", INIT_RESET, CHANGE_SOUND));

void initsound()
{
    // TODO Sound refractoring
    //if(Mix_OpenAudio(soundfreq, MIX_DEFAULT_FORMAT, 2, soundbufferlen)<0)
    //{
    //    nosound = true;
    //    spdlog::get("global")->error("sound init failed (SDL_mixer): {}", Mix_GetError());
    //    return;
    //}
    //Mix_AllocateChannels(soundchans);
    maxchannels = soundchans;
    nosound = false;
}

// TODO Sound refractoring
//static Mix_Chunk *loadwav(const char *name)
//{
//    Mix_Chunk *c = Mix_LoadWAV(findfile(name, "rb"));
//    return c;
//}

bool soundsample::load(bool msg)
{
    //if(chunk) return true;  // TODO Sound refractoring
    if(!name[0]) return false;

    static const char * const exts[] = {"", ".ogg", ".flac", ".wav"};
    std::string filename;
    loopi(sizeof(exts) / sizeof(exts[0]))
    {
        getmediapath(filename, name, DIR_SOUND);
        filename += exts[i]; //append the extension
        if(msg && !i) renderprogress(0, filename.c_str());
        //chunk = loadwav(filename.c_str());  // TODO Sound refractoring
        //if(chunk) return true; // TODO Sound refractoring
    }

    spdlog::get("global")->warn("failed to load sound: {}", filename); // TODO: LOG_N_TIMES(1)
    return false;
}

static hashnameset<soundsample> samples;

static void cleanupsamples()
{
    enumerate(samples, soundsample, s, s.cleanup());
}

static struct soundtype
{
    vector<soundslot> slots;
    vector<soundconfig> configs;

    int findsound(const char *name, int vol)
    {
        loopv(configs)
        {
            soundconfig &s = configs[i];
            loopj(s.numslots)
            {
                soundslot &c = slots[s.slots+j];
                if(!strcmp(c.sample->name, name) && (!vol || c.volume==vol)) return i;
            }
        }
        return -1;
    }

    int addslot(const char *name, int vol)
    {
        soundsample *s = samples.access(name);
        if(!s)
        {
            char *n = newstring(name);
            s = &samples[n];
            s->name = n;
            //s->chunk = NULL; // TODO Sound refractoring
        }
        soundslot *oldslots = slots.getbuf();
        int oldlen = slots.length();
        soundslot &slot = slots.add();
        // soundslots.add() may relocate slot pointers
        if(slots.getbuf() != oldslots) loopv(channels)
        {
            soundchannel &chan = channels[i];
            if(chan.inuse && chan.slot >= oldslots && chan.slot < &oldslots[oldlen])
                chan.slot = &slots[chan.slot - oldslots];
        }
        slot.sample = s;
        slot.volume = vol ? vol : 100;
        return oldlen;
    }

    int addsound(const char *name, int vol, int maxuses = 0)
    {
        soundconfig &s = configs.add();
        s.slots = addslot(name, vol);
        s.numslots = 1;
        s.maxuses = maxuses;
        return configs.length()-1;
    }

    void addalt(const char *name, int vol)
    {
        if(configs.empty()) return;
        addslot(name, vol);
        configs.last().numslots++;
    }

    void clear()
    {
        slots.setsize(0);
        configs.setsize(0);
    }

    void reset()
    {
        loopv(channels)
        {
            soundchannel &chan = channels[i];
            if(chan.inuse && slots.inbuf(chan.slot))
            {
                //Mix_HaltChannel(i); // TODO Sound refractoring
                freechannel(i);
            }
        }
        clear();
    }

    void preloadsound(int n)
    {
        if(nosound || !configs.inrange(n)) return;
        soundconfig &config = configs[n];
        loopk(config.numslots) slots[config.slots+k].sample->load(true);
    }

    bool playing(const soundchannel &chan, const soundconfig &config) const
    {
        return chan.inuse && config.hasslot(chan.slot, slots);
    }
} gamesounds, mapsounds;

void registersound(char *name, int *vol) { intret(gamesounds.addsound(name, *vol, 0)); }
COMMAND(registersound, "si");

void mapsound(char *name, int *vol, int *maxuses) { intret(mapsounds.addsound(name, *vol, *maxuses < 0 ? 0 : max(1, *maxuses))); }
COMMAND(mapsound, "sii");

void altsound(char *name, int *vol) { gamesounds.addalt(name, *vol); }
COMMAND(altsound, "si");

void altmapsound(char *name, int *vol) { mapsounds.addalt(name, *vol); }
COMMAND(altmapsound, "si");

void soundreset()
{
    gamesounds.reset();
}
COMMAND(soundreset, "");

void mapsoundreset()
{
    mapsounds.reset();
}
COMMAND(mapsoundreset, "");

void resetchannels()
{
    loopv(channels) if(channels[i].inuse) freechannel(i);
    channels.shrink(0);
}

void clear_sound()
{
    closemumble();
    if(nosound) return;
    //stopmusic();  // TODO VARP shouldplaymusic

    cleanupsamples();
    gamesounds.clear();
    mapsounds.clear();
    samples.clear();
    //Mix_CloseAudio();  // TODO Sound refractoring
    resetchannels();
}

void stopmapsounds()
{
    loopv(channels) if(channels[i].inuse && channels[i].ent)
    {
     //   Mix_HaltChannel(i);  // TODO Sound refractoring
        freechannel(i);
    }
}

void clearmapsounds()
{
    stopmapsounds();
    mapsounds.clear();
}

void stopmapsound(extentity *e)
{
    loopv(channels)
    {
        soundchannel &chan = channels[i];
        if(chan.inuse && chan.ent == e)
        {
     //       Mix_HaltChannel(i);  // TODO Sound refractoring
            freechannel(i);
        }
    }
}

void checkmapsounds()
{
    const vector<extentity *> &ents = entities::getents();
    loopv(ents)
    {
        extentity &e = *ents[i];
        if(e.type!=ET_SOUND) continue;
        if(camera1->o.dist(e.o) < e.attr2)
        {
            if(!(e.flags&EF_SOUND)) playsound(e.attr1, NULL, &e, SND_MAP, -1);
        }
        else if(e.flags&EF_SOUND) stopmapsound(&e);
    }
}

VAR(stereo, 0, 1, 1);

VARP(maxsoundradius, 0, 340, 10000);

bool updatechannel(soundchannel &chan)
{
    if(!chan.slot) return false;
    int vol = soundvol, pan = 255 / 2;
    if(chan.hasloc())
    {
        vec v;
        float dist = chan.loc.dist(camera1->o, v);
        int rad = maxsoundradius;
        if(chan.ent)
        {
            rad = chan.ent->attr2;
            if(chan.ent->attr3)
            {
                rad -= chan.ent->attr3;
                dist -= chan.ent->attr3;
            }
        }
        else if(chan.radius > 0) rad = maxsoundradius ? min(maxsoundradius, chan.radius) : chan.radius;
        if(rad > 0) vol -= int(clamp(dist/rad, 0.0f, 1.0f)*soundvol); // simple mono distance attenuation
        if(stereo && (v.x != 0 || v.y != 0) && dist>0)
        {
            v.rotate_around_z(-camera1->yaw*RAD);
            pan = int(255.9f*(0.5f - 0.5f*v.x/v.magnitude2())); // range is from 0 (left) to 255 (right)
        }
    }
    vol = (vol*MAXVOL*chan.slot->volume)/255/255;
    vol = min(vol, MAXVOL);
    if(vol == chan.volume && pan == chan.pan) return false;
    chan.volume = vol;
    chan.pan = pan;
    chan.dirty = true;
    return true;
}

void reclaimchannels()
{
    loopv(channels)
    {
        soundchannel &chan = channels[i];
        //if(chan.inuse && !Mix_Playing(i)) freechannel(i); // TODO Sound refractoring
    }
}

void syncchannels()
{
    loopv(channels)
    {
        soundchannel &chan = channels[i];
        if(chan.inuse && chan.hasloc() && updatechannel(chan)) syncchannel(chan);
    }
}

void updatesounds()
{
    updatemumble();
    if(nosound) return;
    if(screen_manager.minimized) stopsounds();
    else
    {
        reclaimchannels();
        if(mainmenu) stopmapsounds();
        else checkmapsounds();
        syncchannels();
    }
    //if(music)
    //{
    //    if(!Mix_PlayingMusic()) musicdone(); // TODO sound VARP isplayingmusic? Or handle it completely on nodejs?
    //    else if(Mix_PausedMusic()) Mix_ResumeMusic();
    //}
}

VARP(maxsoundsatonce, 0, 7, 100);

VAR(dbgsound, 0, 0, 1);

void preloadsound(int n)
{
    gamesounds.preloadsound(n);
}

void preloadmapsound(int n)
{
    mapsounds.preloadsound(n);
}

void preloadmapsounds()
{
    const vector<extentity *> &ents = entities::getents();
    loopv(ents)
    {
        extentity &e = *ents[i];
        if(e.type==ET_SOUND) mapsounds.preloadsound(e.attr1);
    }
}

int playsound(int n, const vec *loc, extentity *ent, int flags, int loops, int fade, int chanid, int radius, int expire)
{
    if(nosound || !soundvol || screen_manager.minimized) return -1;

    soundtype &sounds = ent || flags&SND_MAP ? mapsounds : gamesounds;
    if(!sounds.configs.inrange(n)) { spdlog::get("global")->warn("unregistered sound: {}", n); return -1; } // TODO: LOG_N_TIMES(1)
    soundconfig &config = sounds.configs[n];

    if(loc && (maxsoundradius || radius > 0))
    {
        // cull sounds that are unlikely to be heard
        int rad = radius > 0 ? (maxsoundradius ? min(maxsoundradius, radius) : radius) : maxsoundradius;
        if(camera1->o.dist(*loc) > 1.5f*rad)
        {
            if(channels.inrange(chanid) && sounds.playing(channels[chanid], config))
            {
                //Mix_HaltChannel(chanid); // TODO Sound refractoring
                freechannel(chanid);
            }
            return -1;
        }
    }

    if(chanid < 0)
    {
        if(config.maxuses)
        {
            int uses = 0;
            loopv(channels) if(sounds.playing(channels[i], config) && ++uses >= config.maxuses) return -1;
        }

        // avoid bursts of sounds with heavy packetloss and in sp
        static int soundsatonce = 0, lastsoundmillis = 0;
        if(totalmillis == lastsoundmillis) soundsatonce++; else soundsatonce = 1;
        lastsoundmillis = totalmillis;
        if(maxsoundsatonce && soundsatonce > maxsoundsatonce) return -1;
    }

    if(channels.inrange(chanid))
    {
        soundchannel &chan = channels[chanid];
        if(sounds.playing(chan, config))
        {
            if(loc) chan.loc = *loc;
            else if(chan.hasloc()) chan.clearloc();
            return chanid;
        }
    }
    if(fade < 0) return -1;

    soundslot &slot = sounds.slots[config.chooseslot()];
    // if(!slot.sample->chunk && !slot.sample->load())  // TODO Sound refractoring
    {
        return -1;
    }

    if(dbgsound) spdlog::get("global")->debug("sound: {}", slot.sample->name);

    chanid = -1;
    loopv(channels) if(!channels[i].inuse) { chanid = i; break; }
    if(chanid < 0 && channels.length() < maxchannels) chanid = channels.length();
    if(chanid < 0) loopv(channels) if(!channels[i].volume) {/* Mix_HaltChannel(i); */freechannel(i); chanid = i; break; } // TODO Sound refractoring
    if(chanid < 0) return -1;

    soundchannel &chan = newchannel(chanid, &slot, loc, ent, flags, radius);
    updatechannel(chan);
    int playing = -1;
    //if(fade)  // TODO Sound refractoring
    //{
    //    Mix_Volume(chanid, chan.volume);
    //    playing = expire >= 0 ? Mix_FadeInChannelTimed(chanid, slot.sample->chunk, loops, fade, expire) : Mix_FadeInChannel(chanid, slot.sample->chunk, loops, fade);
    //}
    //else playing = expire >= 0 ? Mix_PlayChannelTimed(chanid, slot.sample->chunk, loops, expire) : Mix_PlayChannel(chanid, slot.sample->chunk, loops);
    if(playing >= 0) syncchannel(chan);
    else freechannel(chanid);
    return playing;
}

void stopsounds()
{
    loopv(channels) if(channels[i].inuse)
    {
        //Mix_HaltChannel(i);
        freechannel(i);
    }
}

bool stopsound(int n, int chanid, int fade)
{
    if(!gamesounds.configs.inrange(n) || !channels.inrange(chanid) || !channels[chanid].inuse || !gamesounds.playing(channels[chanid], gamesounds.configs[n])) return false;
    if(dbgsound) spdlog::get("global")->debug("stopsound: {}", channels[chanid].slot->sample->name);
    //if(!fade || !Mix_FadeOutChannel(chanid, fade)) // TODO Sound refractoring
    {
        //Mix_HaltChannel(chanid); // TODO Sound refractoring
        freechannel(chanid);
    }
    return true;
}

int playsoundname(const char *s, const vec *loc, int vol, int flags, int loops, int fade, int chanid, int radius, int expire)
{
    if(!vol) vol = 100;
    int id = gamesounds.findsound(s, vol);
    if(id < 0) id = gamesounds.addsound(s, vol);
    return playsound(id, loc, NULL, flags, loops, fade, chanid, radius, expire);
}

void sound(int *n) { playsound(*n); }
COMMAND(sound, "i");

void resetsound()
{
    clearchanges(CHANGE_SOUND);
    if(!nosound)
    {
        cleanupsamples();
    }
    initsound();
    resetchannels();
    if(nosound)
    {
        cleanupsamples();
        return;
    }
}

COMMAND(resetsound, "");

#ifdef WIN32

#include <wchar.h>

#else

#include <unistd.h>

#ifdef _POSIX_SHARED_MEMORY_OBJECTS
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <wchar.h>
#endif

#endif

#if defined(WIN32) || defined(_POSIX_SHARED_MEMORY_OBJECTS)
struct MumbleInfo
{
    int version, timestamp;
    vec pos, front, top;
    wchar_t name[256];
};
#endif

#ifdef WIN32
static HANDLE mumblelink = NULL;
static MumbleInfo *mumbleinfo = NULL;
#define VALID_MUMBLELINK (mumblelink && mumbleinfo)
#elif defined(_POSIX_SHARED_MEMORY_OBJECTS)
static int mumblelink = -1;
static MumbleInfo *mumbleinfo = (MumbleInfo *)-1;
#define VALID_MUMBLELINK (mumblelink >= 0 && mumbleinfo != (MumbleInfo *)-1)
#endif

#ifdef VALID_MUMBLELINK
VARFP(mumble, 0, 1, 1, { if(mumble) initmumble(); else closemumble(); });
#else
VARFP(mumble, 0, 0, 1, { if(mumble) initmumble(); else closemumble(); });
#endif

void initmumble()
{
    if(!mumble) return;
#ifdef VALID_MUMBLELINK
    if(VALID_MUMBLELINK) return;

    #ifdef WIN32
        mumblelink = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "MumbleLink");
        if(mumblelink)
        {
            mumbleinfo = (MumbleInfo *)MapViewOfFile(mumblelink, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MumbleInfo));
            if(mumbleinfo) wcsncpy(mumbleinfo->name, L"Inexor", 256);
        }
    #elif defined(_POSIX_SHARED_MEMORY_OBJECTS)
        defformatstring(shmname, "/MumbleLink.%d", getuid());
        mumblelink = shm_open(shmname, O_RDWR, 0);
        if(mumblelink >= 0)
        {
            mumbleinfo = (MumbleInfo *)mmap(NULL, sizeof(MumbleInfo), PROT_READ|PROT_WRITE, MAP_SHARED, mumblelink, 0);
            if(mumbleinfo != (MumbleInfo *)-1) wcsncpy(mumbleinfo->name, L"Inexor", 256);
        }
    #endif
    if(!VALID_MUMBLELINK) closemumble();
#else
    spdlog::get("global")->error("Mumble positional audio is not available on this platform.");
#endif
}

void closemumble()
{
#ifdef WIN32
    if(mumbleinfo) { UnmapViewOfFile(mumbleinfo); mumbleinfo = NULL; }
    if(mumblelink) { CloseHandle(mumblelink); mumblelink = NULL; }
#elif defined(_POSIX_SHARED_MEMORY_OBJECTS)
    if(mumbleinfo != (MumbleInfo *)-1) { munmap(mumbleinfo, sizeof(MumbleInfo)); mumbleinfo = (MumbleInfo *)-1; }
    if(mumblelink >= 0) { close(mumblelink); mumblelink = -1; }
#endif
}

static inline vec mumblevec(const vec &v, bool pos = false)
{
    // change from X left, Z up, Y forward to X right, Y up, Z forward
    // 8 cube units = 1 meter
    vec m(-v.x, v.z, v.y);
    if(pos) m.div(8);
    return m;
}

void updatemumble()
{
#ifdef VALID_MUMBLELINK
    if(!VALID_MUMBLELINK) return;

    static int timestamp = 0;

    mumbleinfo->version = 1;
    mumbleinfo->timestamp = ++timestamp;

    mumbleinfo->pos = mumblevec(player->o, true);
    mumbleinfo->front = mumblevec(vec(RAD*player->yaw, RAD*player->pitch));
    mumbleinfo->top = mumblevec(vec(RAD*player->yaw, RAD*(player->pitch+90)));
#endif
}

}
}
