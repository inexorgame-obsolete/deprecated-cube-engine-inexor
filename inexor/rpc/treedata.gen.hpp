// This file gets generated!
// Do not modify it directly but its corresponding template file instead! 

#pragma once

#include <unordered_map>

#include <boost/variant.hpp>
#include "inexor/rpc/treedata.gen.grpc.pb.h"

#include "inexor/rpc/SharedTree.hpp"
#include "inexor/rpc/RpcSubsystem.hpp"


// List of extern SharedVar declarations

    extern SharedVar<int> guiautotab;


    extern SharedVar<int> guiclicktab;


    extern SharedVar<int> guifadein;


    extern SharedVar<int> guipushdist;


    extern SharedVar<float> guisens;


    extern SharedVar<int> useguifollow;


    extern SharedVar<int> usegui2d;


    extern SharedVar<int> blendpaintmode;


    extern SharedVar<int> paintblendmapdelay;


    extern SharedVar<int> paintblendmapinterval;


    extern SharedVar<int> showblobs;


    extern SharedVar<int> blobintensity;


    extern SharedVar<int> blobheight;


    extern SharedVar<int> blobfadelow;


    extern SharedVar<int> blobfadehigh;


    extern SharedVar<int> blobmargin;


    extern SharedVar<int> dbgblob;


    extern SharedVar<int> blobstattris;


    extern SharedVar<int> blobdyntris;


    extern SharedVar<int> rate;


    extern SharedVar<int> throttle_interval;


    extern SharedVar<int> throttle_accel;


    extern SharedVar<int> throttle_decel;


    extern SharedVar<char *> connectname;


    extern SharedVar<int> connectport;


    extern SharedVar<int> dbgalias;


    extern SharedVar<int> maxcon;


    extern SharedVar<int> confading;


    extern SharedVar<int> fullconsole;


    extern SharedVar<int> consize;


    extern SharedVar<int> miniconsize;


    extern SharedVar<int> miniconwidth;


    extern SharedVar<int> confade;


    extern SharedVar<int> miniconfade;


    extern SharedVar<int> fullconsize;


    extern SharedVar<int> confilter;


    extern SharedVar<int> fullconfilter;


    extern SharedVar<int> miniconfilter;


    extern SharedVar<int> maxhistory;


    extern SharedVar<int> maxdecaltris;


    extern SharedVar<int> decalfade;


    extern SharedVar<int> dbgdec;


    extern SharedVar<int> showdecals;


    extern SharedVar<int> maxdecaldistance;


    extern SharedVar<int> maxdynlights;


    extern SharedVar<int> dynlightdist;


    extern SharedVar<int> glaresize;


    extern SharedVar<int> glare;


    extern SharedVar<int> blurglare;


    extern SharedVar<int> blurglaresigma;


    extern SharedVar<int> debugglare;


    extern SharedVar<float> glarescale;


    extern SharedVar<int> grass;


    extern SharedVar<int> dbggrass;


    extern SharedVar<int> grassdist;


    extern SharedVar<float> grasstaper;


    extern SharedVar<float> grassstep;


    extern SharedVar<int> grassheight;


    extern SharedVar<int> grassanimmillis;


    extern SharedVar<float> grassanimscale;


    extern SharedVar<int> grassscale;


    extern SharedVar<float> grassalpha;


    extern SharedVar<int> lightprecision;


    extern SharedVar<int> lighterror;


    extern SharedVar<int> bumperror;


    extern SharedVar<int> lightlod;


    extern SharedVar<int> sunlightyaw;


    extern SharedVar<int> sunlightpitch;


    extern SharedVar<int> skytexturelight;


    extern SharedVar<int> lmshadows_;


    extern SharedVar<int> lmaa_;


    extern SharedVar<int> lerptjoints_;


    extern SharedVar<int> lmao_;


    extern SharedVar<int> lightcompress;


    extern SharedVar<int> ambientocclusion;


    extern SharedVar<float> ambientocclusionradius;


    extern SharedVar<int> debugao;


    extern SharedVar<int> blurlms;


    extern SharedVar<int> blurskylight;


    extern SharedVar<int> edgetolerance;


    extern SharedVar<int> adaptivesample;


    extern SharedVar<int> lightcachesize;


    extern SharedVar<int> lightthreads;


    extern SharedVar<int> patchnormals;


    extern SharedVar<int> fullbright;


    extern SharedVar<int> fullbrightlevel;


    extern SharedVar<int> roundlightmaptex;


    extern SharedVar<int> batchlightmaps;

namespace inexor { namespace rendering { namespace screen { 
    extern SharedVar<int> scr_w;
 } } }
namespace inexor { namespace rendering { namespace screen { 
    extern SharedVar<int> scr_h;
 } } }
namespace inexor { namespace rendering { namespace screen { 
    extern SharedVar<int> colorbits;
 } } }
namespace inexor { namespace rendering { namespace screen { 
    extern SharedVar<int> depthbits;
 } } }
namespace inexor { namespace rendering { namespace screen { 
    extern SharedVar<int> stencilbits;
 } } }
namespace inexor { namespace rendering { namespace screen { 
    extern SharedVar<int> vsync;
 } } }
namespace inexor { namespace rendering { namespace screen { 
    extern SharedVar<int> vsynctear;
 } } }

    extern SharedVar<int> fsaa;


    extern SharedVar<char *> background;


    extern SharedVar<char *> logo;


    extern SharedVar<int> userelativemouse;

namespace inexor { namespace rendering { namespace screen { 
    extern SharedVar<int> fullscreen;
 } } }
namespace inexor { namespace rendering { namespace screen { 
    extern SharedVar<int> gamma;
 } } }

    extern SharedVar<int> menufps;


    extern SharedVar<int> maxfps;


    extern SharedVar<int> clockerror;


    extern SharedVar<int> clockfix;


    extern SharedVar<int> numcpus;


    extern SharedVar<int> optmats;


    extern SharedVar<int> showmat;


    extern SharedVar<int> glassenv;


    extern SharedVar<int> waterfallenv;


    extern SharedVar<int> menudistance;


    extern SharedVar<int> menuautoclose;


    extern SharedVar<int> applydialog;


    extern SharedVar<int> mainmenu;


    extern SharedVar<int> dbgmovie;


    extern SharedVar<int> movieaccelblit;


    extern SharedVar<int> movieaccelyuv;


    extern SharedVar<int> movieaccel;


    extern SharedVar<int> moviesync;


    extern SharedVar<float> movieminquality;


    extern SharedVar<int> moview;


    extern SharedVar<int> movieh;


    extern SharedVar<int> moviefps;


    extern SharedVar<int> moviesound;


    extern SharedVar<int> lerpangle;


    extern SharedVar<int> lerpsubdiv;


    extern SharedVar<int> lerpsubdivsize;


    extern SharedVar<int> mipvis;


    extern SharedVar<int> maxmerge;


    extern SharedVar<int> minface;


    extern SharedVar<int> dragging;


    extern SharedVar<int> gridpower;


    extern SharedVar<int> passthroughsel;


    extern SharedVar<int> editing;


    extern SharedVar<int> selectcorners;


    extern SharedVar<int> hmapedit;


    extern SharedVar<int> gridlookup;


    extern SharedVar<int> passthroughcube;


    extern SharedVar<int> undomegs;


    extern SharedVar<int> nompedit;


    extern SharedVar<char *> prefabdir;


    extern SharedVar<int> brushx;


    extern SharedVar<int> brushy;


    extern SharedVar<int> invalidcubeguard;


    extern SharedVar<int> selectionsurf;


    extern SharedVar<int> usevdelta;


    extern SharedVar<int> allfaces;


    extern SharedVar<int> texguiwidth;


    extern SharedVar<int> texguiheight;


    extern SharedVar<int> texguitime;


    extern SharedVar<int> texgui2d;


    extern SharedVar<int> debugvbo;


    extern SharedVar<int> maxvbosize;


    extern SharedVar<int> filltjoints;


    extern SharedVar<int> vafacemax;


    extern SharedVar<int> vafacemin;


    extern SharedVar<int> vacubesize;


    extern SharedVar<int> dynentsize;


    extern SharedVar<int> maxroll;


    extern SharedVar<float> straferoll;


    extern SharedVar<float> faderoll;


    extern SharedVar<int> floatspeed;


    extern SharedVar<int> physinterp;


    extern SharedVar<int> maxpvsblocker;


    extern SharedVar<int> pvsleafsize;


    extern SharedVar<int> pvsthreads;


    extern SharedVar<int> lockpvs;


    extern SharedVar<int> usepvs;


    extern SharedVar<int> usewaterpvs;


    extern SharedVar<int> glversion;


    extern SharedVar<int> glslversion;


    extern SharedVar<int> ati_skybox_bug;


    extern SharedVar<int> ati_minmax_bug;


    extern SharedVar<int> ati_cubemap_bug;


    extern SharedVar<int> intel_vertexarray_bug;


    extern SharedVar<int> intel_mapbufferrange_bug;


    extern SharedVar<int> minimizetcusage;


    extern SharedVar<int> useubo;


    extern SharedVar<int> usetexcompress;


    extern SharedVar<int> rtscissor;


    extern SharedVar<int> blurtile;


    extern SharedVar<int> rtsharefb;


    extern SharedVar<int> dbgexts;


    extern SharedVar<int> wireframe;


    extern SharedVar<int> zoominvel;


    extern SharedVar<int> zoomoutvel;


    extern SharedVar<int> zoomfov;


    extern SharedVar<int> fov;


    extern SharedVar<int> followfov;


    extern SharedVar<int> avatarzoomfov;


    extern SharedVar<int> avatarfov;


    extern SharedVar<float> avatardepth;


    extern SharedVar<float> forceaspect;


    extern SharedVar<int> zoom;


    extern SharedVar<float> zoomsens;


    extern SharedVar<float> zoomaccel;


    extern SharedVar<int> zoomautosens;


    extern SharedVar<float> sensitivity;


    extern SharedVar<float> sensitivityscale;


    extern SharedVar<int> invmouse;


    extern SharedVar<float> mouseaccel;


    extern SharedVar<int> thirdperson;


    extern SharedVar<float> thirdpersondistance;


    extern SharedVar<float> thirdpersonup;


    extern SharedVar<float> thirdpersonside;


    extern SharedVar<float> nearplane;


    extern SharedVar<int> reflectclip;


    extern SharedVar<int> reflectclipavatar;


    extern SharedVar<float> polygonoffsetfactor;


    extern SharedVar<float> polygonoffsetunits;


    extern SharedVar<float> depthoffset;


    extern SharedVar<int> fog;


    extern SharedVar<int> skyboxglare;


    extern SharedVar<int> reflectmms;


    extern SharedVar<int> refractsky;


    extern SharedVar<int> modelpreviewfov;


    extern SharedVar<int> modelpreviewpitch;


    extern SharedVar<int> minimapheight;


    extern SharedVar<int> minimapclip;


    extern SharedVar<int> minimapsize;


    extern SharedVar<int> motionblur;


    extern SharedVar<int> motionblurmillis;


    extern SharedVar<float> motionblurscale;


    extern SharedVar<int> usedamagecompass;


    extern SharedVar<int> damagecompassfade;


    extern SharedVar<int> damagecompasssize;


    extern SharedVar<int> damagecompassalpha;


    extern SharedVar<int> damagecompassmin;


    extern SharedVar<int> damagecompassmax;


    extern SharedVar<int> damagescreen;


    extern SharedVar<int> damagescreenfactor;


    extern SharedVar<int> damagescreenalpha;


    extern SharedVar<int> damagescreenfade;


    extern SharedVar<int> damagescreenmin;


    extern SharedVar<int> damagescreenmax;


    extern SharedVar<int> hidestats;


    extern SharedVar<int> hidehud;


    extern SharedVar<int> crosshairsize;


    extern SharedVar<int> cursorsize;


    extern SharedVar<int> crosshairfx;


    extern SharedVar<int> crosshaircolors;


    extern SharedVar<char *> crosshairdir;


    extern SharedVar<char *> cursor;


    extern SharedVar<int> wallclock;


    extern SharedVar<int> wallclock24;


    extern SharedVar<int> wallclocksecs;


    extern SharedVar<int> showfps;


    extern SharedVar<int> showfpsrange;


    extern SharedVar<int> showeditstats;


    extern SharedVar<int> statrate;


    extern SharedVar<float> conscale;


    extern SharedVar<char *> modeldir;


    extern SharedVar<int> oqdynent;


    extern SharedVar<int> animationinterpolationtime;


    extern SharedVar<int> ragdolltimestepmin;


    extern SharedVar<int> ragdolltimestepmax;


    extern SharedVar<float> ragdollrotfric;


    extern SharedVar<float> ragdollrotfricstop;


    extern SharedVar<int> ragdollconstrain;


    extern SharedVar<float> ragdollbodyfric;


    extern SharedVar<float> ragdollbodyfricscale;


    extern SharedVar<float> ragdollwaterfric;


    extern SharedVar<float> ragdollgroundfric;


    extern SharedVar<float> ragdollairfric;


    extern SharedVar<float> ragdollunstick;


    extern SharedVar<int> ragdollexpireoffset;


    extern SharedVar<int> ragdollwaterexpireoffset;


    extern SharedVar<float> ragdolleyesmooth;


    extern SharedVar<int> ragdolleyesmoothmillis;


    extern SharedVar<int> envmapmodels;


    extern SharedVar<int> bumpmodels;


    extern SharedVar<int> fullbrightmodels;


    extern SharedVar<int> gpuskel;


    extern SharedVar<int> maxskelanimdata;


    extern SharedVar<int> testtags;


    extern SharedVar<int> showboundingbox;


    extern SharedVar<int> maxmodelradiusdistance;


    extern SharedVar<int> animoverride;


    extern SharedVar<int> testanims;


    extern SharedVar<int> testpitch;


    extern SharedVar<int> particlesize;


    extern SharedVar<int> emitmillis;


    extern SharedVar<int> showparticles;


    extern SharedVar<int> cullparticles;


    extern SharedVar<int> replayparticles;


    extern SharedVar<int> seedmillis;


    extern SharedVar<int> dbgpcull;


    extern SharedVar<int> dbgpseed;


    extern SharedVar<int> outlinemeters;


    extern SharedVar<int> depthfxfpscale;


    extern SharedVar<int> depthfxscale;


    extern SharedVar<int> depthfxblend;


    extern SharedVar<int> depthfxpartblend;


    extern SharedVar<int> depthfxmargin;


    extern SharedVar<int> depthfxbias;


    extern SharedVar<int> fpdepthfx;


    extern SharedVar<int> depthfxemuprecision;


    extern SharedVar<int> depthfxsize;


    extern SharedVar<int> depthfx;


    extern SharedVar<int> depthfxparts;


    extern SharedVar<int> blurdepthfx;


    extern SharedVar<int> blurdepthfxsigma;


    extern SharedVar<int> depthfxscissor;


    extern SharedVar<int> debugdepthfx;


    extern SharedVar<int> flarelights;


    extern SharedVar<int> flarecutoff;


    extern SharedVar<int> flaresize;


    extern SharedVar<int> lnjittermillis;


    extern SharedVar<int> lnjitterradius;


    extern SharedVar<float> lnjitterscale;


    extern SharedVar<int> lnscrollmillis;


    extern SharedVar<float> lnscrollscale;


    extern SharedVar<float> lnblendpower;


    extern SharedVar<int> maxparticles;


    extern SharedVar<int> fewparticles;


    extern SharedVar<int> particleglare;


    extern SharedVar<int> dbgparts;


    extern SharedVar<int> maxparticledistance;


    extern SharedVar<int> maxtrail;


    extern SharedVar<int> particletext;


    extern SharedVar<int> maxparticletextdistance;


    extern SharedVar<char *> skybox;


    extern SharedVar<int> skyboxcolour;


    extern SharedVar<float> spinsky;


    extern SharedVar<int> yawsky;


    extern SharedVar<char *> cloudbox;


    extern SharedVar<int> cloudboxcolour;


    extern SharedVar<float> cloudboxalpha;


    extern SharedVar<float> spinclouds;


    extern SharedVar<int> yawclouds;


    extern SharedVar<float> cloudclip;


    extern SharedVar<char *> cloudlayer;


    extern SharedVar<float> cloudoffsetx;


    extern SharedVar<float> cloudoffsety;


    extern SharedVar<float> cloudscrollx;


    extern SharedVar<float> cloudscrolly;


    extern SharedVar<float> cloudscale;


    extern SharedVar<float> spincloudlayer;


    extern SharedVar<int> yawcloudlayer;


    extern SharedVar<float> cloudheight;


    extern SharedVar<float> cloudfade;


    extern SharedVar<float> cloudalpha;


    extern SharedVar<int> cloudsubdiv;


    extern SharedVar<int> cloudcolour;


    extern SharedVar<float> fogdomeheight;


    extern SharedVar<float> fogdomemin;


    extern SharedVar<float> fogdomemax;


    extern SharedVar<int> fogdomecap;


    extern SharedVar<float> fogdomeclip;


    extern SharedVar<int> sparklyfix;


    extern SharedVar<int> showsky;


    extern SharedVar<int> clipsky;


    extern SharedVar<int> clampsky;


    extern SharedVar<int> fogdomeclouds;


    extern SharedVar<int> useskytexture;


    extern SharedVar<int> oqfrags;


    extern SharedVar<int> oqwait;


    extern SharedVar<int> oqmm;


    extern SharedVar<int> outline;


    extern SharedVar<int> outlinecolour;


    extern SharedVar<int> dtoutline;


    extern SharedVar<int> blendbrushcolor;


    extern SharedVar<int> oqdist;


    extern SharedVar<int> zpass;


    extern SharedVar<int> glowpass;


    extern SharedVar<int> envpass;


    extern SharedVar<int> batchgeom;


    extern SharedVar<char *> causticdir;


    extern SharedVar<int> causticscale;


    extern SharedVar<int> causticmillis;


    extern SharedVar<int> caustics;


    extern SharedVar<int> oqgeom;


    extern SharedVar<int> maxclients;


    extern SharedVar<int> maxdupclients;


    extern SharedVar<int> allowupdatemaster;


    extern SharedVar<char *> mastername;


    extern SharedVar<int> masterport;


    extern SharedVar<int> serveruprate;


    extern SharedVar<char *> serverip;


    extern SharedVar<int> serverport;


    extern SharedVar<int> searchlan;


    extern SharedVar<int> servpingrate;


    extern SharedVar<int> servpingdecay;


    extern SharedVar<int> maxservpings;


    extern SharedVar<int> autosortservers;


    extern SharedVar<int> autoupdateservers;


    extern SharedVar<int> reservevpparams;


    extern SharedVar<int> maxvsuniforms;


    extern SharedVar<int> maxfsuniforms;


    extern SharedVar<int> maxvaryings;


    extern SharedVar<int> dbgshader;


    extern SharedVar<int> dbgubo;


    extern SharedVar<int> shaderprecision;


    extern SharedVar<int> defershaders;


    extern SharedVar<int> shaderdetail;


    extern SharedVar<int> shadowmap;


    extern SharedVar<int> shadowmapsize;


    extern SharedVar<int> shadowmapradius;


    extern SharedVar<int> shadowmapheight;


    extern SharedVar<int> shadowmapdist;


    extern SharedVar<int> fpshadowmap;


    extern SharedVar<int> shadowmapprecision;


    extern SharedVar<int> shadowmapintensity;


    extern SharedVar<int> blurshadowmap;


    extern SharedVar<int> blursmsigma;


    extern SharedVar<int> shadowmapangle;


    extern SharedVar<int> shadowmapbias;


    extern SharedVar<int> shadowmappeelbias;


    extern SharedVar<int> smdepthpeel;


    extern SharedVar<int> smoothshadowmappeel;


    extern SharedVar<int> debugsm;

namespace inexor { namespace sound { 
    extern SharedVar<int> soundvol;
 } }
namespace inexor { namespace sound { 
    extern SharedVar<int> musicvol;
 } }
namespace inexor { namespace sound { 
    extern SharedVar<int> soundchans;
 } }
namespace inexor { namespace sound { 
    extern SharedVar<int> soundfreq;
 } }
namespace inexor { namespace sound { 
    extern SharedVar<int> soundbufferlen;
 } }
namespace inexor { namespace sound { 
    extern SharedVar<int> stereo;
 } }
namespace inexor { namespace sound { 
    extern SharedVar<int> maxsoundradius;
 } }
namespace inexor { namespace sound { 
    extern SharedVar<int> maxsoundsatonce;
 } }
namespace inexor { namespace sound { 
    extern SharedVar<int> dbgsound;
 } }
namespace inexor { namespace sound { 
    extern SharedVar<int> mumble;
 } }

    extern SharedVar<int> waterreflect;


    extern SharedVar<int> waterrefract;


    extern SharedVar<int> waterenvmap;


    extern SharedVar<int> waterfallrefract;


    extern SharedVar<int> watersubdiv;


    extern SharedVar<int> waterlod;


    extern SharedVar<int> vertwater;


    extern SharedVar<int> reflectdist;


    extern SharedVar<int> waterfog;


    extern SharedVar<int> waterspec;


    extern SharedVar<int> water2fog;


    extern SharedVar<int> water2spec;


    extern SharedVar<int> water3fog;


    extern SharedVar<int> water3spec;


    extern SharedVar<int> water4fog;


    extern SharedVar<int> water4spec;


    extern SharedVar<int> lavafog;


    extern SharedVar<int> lava2fog;


    extern SharedVar<int> lava3fog;


    extern SharedVar<int> lava4fog;


    extern SharedVar<int> oqwater;


    extern SharedVar<int> waterfade;


    extern SharedVar<int> reflectsize;


    extern SharedVar<int> maxreflect;


    extern SharedVar<int> maskreflect;


    extern SharedVar<int> reflectscissor;


    extern SharedVar<int> reflectvfc;


    extern SharedVar<int> refractclear;


    extern SharedVar<int> mapversion;


    extern SharedVar<int> worldscale;


    extern SharedVar<int> worldsize;


    extern SharedVar<char *> maptitle;


    extern SharedVar<int> octaentsize;


    extern SharedVar<int> entselradius;


    extern SharedVar<int> entediting;


    extern SharedVar<int> attachradius;


    extern SharedVar<int> entselsnap;


    extern SharedVar<int> entmovingshadow;


    extern SharedVar<int> showentradius;


    extern SharedVar<int> entitysurf;


    extern SharedVar<int> entautoviewdist;


    extern SharedVar<int> entdrop;


    extern SharedVar<int> savebak;


    extern SharedVar<int> dbgvars;


    extern SharedVar<char *> mapdir;


    extern SharedVar<char *> texturedir;


    extern SharedVar<char *> skyboxdir;


    extern SharedVar<char *> interfacedir;


    extern SharedVar<char *> icondir;


    extern SharedVar<char *> sounddir;


    extern SharedVar<char *> musicdir;

namespace ai { 
    extern SharedVar<int> aidebug;
 }
namespace ai { 
    extern SharedVar<int> aiforcegun;
 }
namespace ai { 
    extern SharedVar<int> showwaypoints;
 }
namespace ai { 
    extern SharedVar<int> showwaypointsradius;
 }
namespace game { 
    extern SharedVar<int> minradarscale;
 }
namespace game { 
    extern SharedVar<int> maxradarscale;
 }
namespace game { 
    extern SharedVar<int> radarteammates;
 }
namespace game { 
    extern SharedVar<float> minimapalpha;
 }
namespace game { 
    extern SharedVar<char *> radardir;
 }
namespace game { 
    extern SharedVar<int> capturetether;
 }
namespace game { 
    extern SharedVar<int> autorepammo;
 }
namespace game { 
    extern SharedVar<int> basenumbers;
 }
namespace game { 
    extern SharedVar<int> showbombs;
 }
namespace game { 
    extern SharedVar<int> showbombradius;
 }
namespace game { 
    extern SharedVar<int> showbombdelay;
 }
namespace game { 
    extern SharedVar<int> showminimapobstacles;
 }
namespace game { 
    extern SharedVar<int> deadpush;
 }
namespace game { 
    extern SharedVar<int> autoauth;
 }
namespace entities { 
    extern SharedVar<int> triggerstate;
 }
namespace game { 
    extern SharedVar<int> smoothmove;
 }
namespace game { 
    extern SharedVar<int> smoothdist;
 }
namespace game { 
    extern SharedVar<int> slowmosp;
 }
namespace game { 
    extern SharedVar<int> spawnwait;
 }
namespace game { 
    extern SharedVar<int> hitsound;
 }
namespace game { 
    extern SharedVar<int> deathscore;
 }
namespace game { 
    extern SharedVar<int> teamcolorfrags;
 }
namespace game { 
    extern SharedVar<int> showmodeinfo;
 }
namespace game { 
    extern SharedVar<int> teamcolortext;
 }
namespace game { 
    extern SharedVar<int> ammohud;
 }
namespace game { 
    extern SharedVar<int> teamcrosshair;
 }
namespace game { 
    extern SharedVar<int> hitcrosshair;
 }
namespace game { 
    extern SharedVar<int> skill;
 }
namespace game { 
    extern SharedVar<int> killsendsp;
 }
namespace game { 
    extern SharedVar<int> ragdoll;
 }
namespace game { 
    extern SharedVar<int> ragdollmillis;
 }
namespace game { 
    extern SharedVar<int> ragdollfade;
 }
namespace game { 
    extern SharedVar<int> playermodel;
 }
namespace game { 
    extern SharedVar<int> forceplayermodels;
 }
namespace game { 
    extern SharedVar<int> hidedead;
 }
namespace game { 
    extern SharedVar<int> testquad;
 }
namespace game { 
    extern SharedVar<int> testarmour;
 }
namespace game { 
    extern SharedVar<int> testteam;
 }
namespace game { 
    extern SharedVar<int> teamskins;
 }
namespace game { 
    extern SharedVar<int> hudgun;
 }
namespace game { 
    extern SharedVar<int> hudgunsway;
 }
namespace game { 
    extern SharedVar<int> teamhudguns;
 }
namespace game { 
    extern SharedVar<int> chainsawhudgun;
 }
namespace game { 
    extern SharedVar<int> testhudgun;
 }
namespace game { 
    extern SharedVar<float> swaystep;
 }
namespace game { 
    extern SharedVar<float> swayside;
 }
namespace game { 
    extern SharedVar<float> swayup;
 }
namespace game { 
    extern SharedVar<char *> hudgunsdir;
 }
namespace game { 
    extern SharedVar<int> scoreboard2d;
 }
namespace game { 
    extern SharedVar<int> showservinfo;
 }
namespace game { 
    extern SharedVar<int> showclientnum;
 }
namespace game { 
    extern SharedVar<int> showpj;
 }
namespace game { 
    extern SharedVar<int> showping;
 }
namespace game { 
    extern SharedVar<int> showspectators;
 }
namespace game { 
    extern SharedVar<int> showflags;
 }
namespace game { 
    extern SharedVar<int> showfrags;
 }
namespace game { 
    extern SharedVar<int> showaccuracy;
 }
namespace game { 
    extern SharedVar<int> highlightscore;
 }
namespace game { 
    extern SharedVar<int> showconnecting;
 }
namespace game { 
    extern SharedVar<int> showscoreboard;
 }
namespace server { 
    extern SharedVar<int> lockmaprotation;
 }
namespace server { 
    extern SharedVar<int> maxdemos;
 }
namespace server { 
    extern SharedVar<int> maxdemosize;
 }
namespace server { 
    extern SharedVar<int> restrictdemos;
 }
namespace server { 
    extern SharedVar<int> restrictpausegame;
 }
namespace server { 
    extern SharedVar<int> restrictgamespeed;
 }
namespace server { 
    extern SharedVar<int> restrictpersistteams;
 }
namespace server { 
    extern SharedVar<char *> serverdesc;
 }
namespace server { 
    extern SharedVar<char *> serverpass;
 }
namespace server { 
    extern SharedVar<char *> adminpass;
 }
namespace server { 
    extern SharedVar<int> publicserver;
 }
namespace server { 
    extern SharedVar<char *> servermotd;
 }
namespace server { 
    extern SharedVar<int> spectatemodifiedmap;
 }
namespace server { 
    extern SharedVar<int> ctftkpenalty;
 }
namespace server { 
    extern SharedVar<char *> serverauth;
 }
namespace server { 
    extern SharedVar<int> modifiedmapspectator;
 }
namespace server { 
    extern SharedVar<int> extinfoip;
 }
namespace server { namespace aiman { 
    extern SharedVar<int> botlimit;
 } }
namespace server { namespace aiman { 
    extern SharedVar<int> serverbotbalance;
 } }
namespace ai { 
    extern SharedVar<int> dropwaypoints;
 }
namespace game { 
    extern SharedVar<int> maxdebris;
 }
namespace game { 
    extern SharedVar<int> maxbarreldebris;
 }
namespace game { 
    extern SharedVar<int> blood;
 }
namespace game { 
    extern SharedVar<int> muzzleflash;
 }
namespace game { 
    extern SharedVar<int> muzzlelight;
 }
namespace game { 
    extern SharedVar<int> bombcolliderad;
 }
namespace game { 
    extern SharedVar<int> bombbarrier;
 }

    extern SharedVar<int> dbggz;


    extern SharedVar<int> dbgzip;


    extern SharedVar<int> dbgdds;


    extern SharedVar<int> envmapsize;


    extern SharedVar<int> envmapradius;


    extern SharedVar<int> aaenvmap;


    extern SharedVar<int> compresspng;


    extern SharedVar<int> compresstga;


    extern SharedVar<int> screenshotformat;


    extern SharedVar<char *> screenshotdir;


    extern SharedVar<int> autocompactvslots;


    extern SharedVar<int> hwtexsize;


    extern SharedVar<int> hwcubetexsize;


    extern SharedVar<int> hwmaxaniso;


    extern SharedVar<int> maxtexsize;


    extern SharedVar<int> reducefilter;


    extern SharedVar<int> texreduce;


    extern SharedVar<int> trilinear;


    extern SharedVar<int> bilinear;


    extern SharedVar<int> aniso;


    extern SharedVar<int> texcompress;


    extern SharedVar<int> texcompressquality;


    extern SharedVar<int> usenp2;


    extern SharedVar<int> usedds;


    extern SharedVar<int> scaledds;



namespace inexor { namespace rpc {

/// Known C++ SharedVar types
enum cpp_type_t
{
    t_cstring = 0,
    t_float,
    t_int
};

class treedata {
  public:

    void connectall()
    {
        // TODO: Dont call by type but by reference if not a ptr: *or& -> {cpp_observer_type}
        ::guiautotab.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__guiautotab(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::guiclicktab.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__guiclicktab(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::guifadein.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__guifadein(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::guipushdist.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__guipushdist(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::guisens.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__guisens(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::useguifollow.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__useguifollow(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::usegui2d.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__usegui2d(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blendpaintmode.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blendpaintmode(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::paintblendmapdelay.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__paintblendmapdelay(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::paintblendmapinterval.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__paintblendmapinterval(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::showblobs.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__showblobs(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blobintensity.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blobintensity(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blobheight.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blobheight(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blobfadelow.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blobfadelow(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blobfadehigh.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blobfadehigh(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blobmargin.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blobmargin(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dbgblob.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dbgblob(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blobstattris.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blobstattris(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blobdyntris.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blobdyntris(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::rate.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__rate(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::throttle_interval.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__throttle_interval(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::throttle_accel.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__throttle_accel(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::throttle_decel.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__throttle_decel(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::connectname.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__connectname(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::connectport.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__connectport(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dbgalias.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dbgalias(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxcon.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxcon(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::confading.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__confading(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fullconsole.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fullconsole(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::consize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__consize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::miniconsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__miniconsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::miniconwidth.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__miniconwidth(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::confade.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__confade(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::miniconfade.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__miniconfade(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fullconsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fullconsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::confilter.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__confilter(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fullconfilter.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fullconfilter(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::miniconfilter.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__miniconfilter(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxhistory.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxhistory(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxdecaltris.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxdecaltris(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::decalfade.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__decalfade(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dbgdec.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dbgdec(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::showdecals.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__showdecals(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxdecaldistance.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxdecaldistance(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxdynlights.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxdynlights(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dynlightdist.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dynlightdist(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::glaresize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__glaresize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::glare.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__glare(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blurglare.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blurglare(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blurglaresigma.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blurglaresigma(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::debugglare.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__debugglare(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::glarescale.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__glarescale(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::grass.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__grass(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dbggrass.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dbggrass(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::grassdist.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__grassdist(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::grasstaper.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__grasstaper(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::grassstep.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__grassstep(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::grassheight.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__grassheight(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::grassanimmillis.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__grassanimmillis(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::grassanimscale.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__grassanimscale(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::grassscale.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__grassscale(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::grassalpha.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__grassalpha(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lightprecision.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lightprecision(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lighterror.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lighterror(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::bumperror.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__bumperror(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lightlod.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lightlod(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::sunlightyaw.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__sunlightyaw(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::sunlightpitch.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__sunlightpitch(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::skytexturelight.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__skytexturelight(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lmshadows_.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lmshadows_(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lmaa_.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lmaa_(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lerptjoints_.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lerptjoints_(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lmao_.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lmao_(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lightcompress.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lightcompress(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ambientocclusion.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ambientocclusion(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ambientocclusionradius.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ambientocclusionradius(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::debugao.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__debugao(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blurlms.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blurlms(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blurskylight.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blurskylight(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::edgetolerance.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__edgetolerance(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::adaptivesample.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__adaptivesample(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lightcachesize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lightcachesize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lightthreads.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lightthreads(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::patchnormals.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__patchnormals(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fullbright.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fullbright(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fullbrightlevel.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fullbrightlevel(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::roundlightmaptex.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__roundlightmaptex(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::batchlightmaps.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__batchlightmaps(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::rendering::screen::scr_w.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__rendering_screen_scr_w(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::rendering::screen::scr_h.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__rendering_screen_scr_h(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::rendering::screen::colorbits.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__rendering_screen_colorbits(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::rendering::screen::depthbits.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__rendering_screen_depthbits(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::rendering::screen::stencilbits.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__rendering_screen_stencilbits(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::rendering::screen::vsync.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__rendering_screen_vsync(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::rendering::screen::vsynctear.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__rendering_screen_vsynctear(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fsaa.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fsaa(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::background.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__background(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::logo.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__logo(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::userelativemouse.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__userelativemouse(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::rendering::screen::fullscreen.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__rendering_screen_fullscreen(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::rendering::screen::gamma.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__rendering_screen_gamma(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::menufps.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__menufps(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxfps.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxfps(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::clockerror.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__clockerror(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::clockfix.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__clockfix(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::numcpus.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__numcpus(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::optmats.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__optmats(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::showmat.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__showmat(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::glassenv.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__glassenv(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::waterfallenv.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__waterfallenv(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::menudistance.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__menudistance(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::menuautoclose.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__menuautoclose(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::applydialog.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__applydialog(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::mainmenu.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__mainmenu(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dbgmovie.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dbgmovie(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::movieaccelblit.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__movieaccelblit(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::movieaccelyuv.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__movieaccelyuv(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::movieaccel.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__movieaccel(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::moviesync.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__moviesync(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::movieminquality.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__movieminquality(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::moview.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__moview(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::movieh.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__movieh(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::moviefps.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__moviefps(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::moviesound.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__moviesound(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lerpangle.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lerpangle(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lerpsubdiv.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lerpsubdiv(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lerpsubdivsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lerpsubdivsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::mipvis.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__mipvis(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxmerge.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxmerge(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::minface.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__minface(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dragging.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dragging(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::gridpower.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__gridpower(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::passthroughsel.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__passthroughsel(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::editing.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__editing(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::selectcorners.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__selectcorners(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::hmapedit.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__hmapedit(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::gridlookup.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__gridlookup(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::passthroughcube.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__passthroughcube(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::undomegs.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__undomegs(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::nompedit.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__nompedit(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::prefabdir.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__prefabdir(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::brushx.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__brushx(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::brushy.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__brushy(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::invalidcubeguard.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__invalidcubeguard(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::selectionsurf.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__selectionsurf(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::usevdelta.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__usevdelta(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::allfaces.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__allfaces(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::texguiwidth.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__texguiwidth(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::texguiheight.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__texguiheight(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::texguitime.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__texguitime(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::texgui2d.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__texgui2d(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::debugvbo.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__debugvbo(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxvbosize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxvbosize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::filltjoints.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__filltjoints(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::vafacemax.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__vafacemax(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::vafacemin.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__vafacemin(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::vacubesize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__vacubesize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dynentsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dynentsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxroll.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxroll(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::straferoll.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__straferoll(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::faderoll.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__faderoll(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::floatspeed.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__floatspeed(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::physinterp.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__physinterp(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxpvsblocker.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxpvsblocker(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::pvsleafsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__pvsleafsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::pvsthreads.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__pvsthreads(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lockpvs.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lockpvs(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::usepvs.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__usepvs(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::usewaterpvs.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__usewaterpvs(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::glversion.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__glversion(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::glslversion.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__glslversion(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ati_skybox_bug.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ati_skybox_bug(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ati_minmax_bug.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ati_minmax_bug(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ati_cubemap_bug.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ati_cubemap_bug(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::intel_vertexarray_bug.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__intel_vertexarray_bug(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::intel_mapbufferrange_bug.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__intel_mapbufferrange_bug(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::minimizetcusage.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__minimizetcusage(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::useubo.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__useubo(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::usetexcompress.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__usetexcompress(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::rtscissor.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__rtscissor(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blurtile.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blurtile(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::rtsharefb.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__rtsharefb(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dbgexts.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dbgexts(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::wireframe.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__wireframe(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::zoominvel.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__zoominvel(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::zoomoutvel.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__zoomoutvel(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::zoomfov.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__zoomfov(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fov.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fov(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::followfov.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__followfov(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::avatarzoomfov.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__avatarzoomfov(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::avatarfov.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__avatarfov(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::avatardepth.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__avatardepth(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::forceaspect.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__forceaspect(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::zoom.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__zoom(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::zoomsens.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__zoomsens(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::zoomaccel.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__zoomaccel(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::zoomautosens.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__zoomautosens(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::sensitivity.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__sensitivity(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::sensitivityscale.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__sensitivityscale(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::invmouse.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__invmouse(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::mouseaccel.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__mouseaccel(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::thirdperson.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__thirdperson(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::thirdpersondistance.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__thirdpersondistance(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::thirdpersonup.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__thirdpersonup(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::thirdpersonside.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__thirdpersonside(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::nearplane.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__nearplane(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::reflectclip.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__reflectclip(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::reflectclipavatar.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__reflectclipavatar(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::polygonoffsetfactor.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__polygonoffsetfactor(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::polygonoffsetunits.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__polygonoffsetunits(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::depthoffset.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__depthoffset(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fog.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fog(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::skyboxglare.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__skyboxglare(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::reflectmms.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__reflectmms(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::refractsky.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__refractsky(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::modelpreviewfov.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__modelpreviewfov(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::modelpreviewpitch.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__modelpreviewpitch(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::minimapheight.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__minimapheight(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::minimapclip.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__minimapclip(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::minimapsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__minimapsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::motionblur.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__motionblur(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::motionblurmillis.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__motionblurmillis(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::motionblurscale.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__motionblurscale(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::usedamagecompass.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__usedamagecompass(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::damagecompassfade.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__damagecompassfade(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::damagecompasssize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__damagecompasssize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::damagecompassalpha.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__damagecompassalpha(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::damagecompassmin.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__damagecompassmin(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::damagecompassmax.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__damagecompassmax(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::damagescreen.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__damagescreen(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::damagescreenfactor.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__damagescreenfactor(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::damagescreenalpha.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__damagescreenalpha(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::damagescreenfade.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__damagescreenfade(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::damagescreenmin.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__damagescreenmin(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::damagescreenmax.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__damagescreenmax(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::hidestats.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__hidestats(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::hidehud.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__hidehud(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::crosshairsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__crosshairsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cursorsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cursorsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::crosshairfx.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__crosshairfx(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::crosshaircolors.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__crosshaircolors(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::crosshairdir.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__crosshairdir(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cursor.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cursor(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::wallclock.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__wallclock(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::wallclock24.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__wallclock24(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::wallclocksecs.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__wallclocksecs(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::showfps.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__showfps(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::showfpsrange.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__showfpsrange(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::showeditstats.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__showeditstats(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::statrate.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__statrate(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::conscale.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__conscale(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::modeldir.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__modeldir(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::oqdynent.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__oqdynent(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::animationinterpolationtime.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__animationinterpolationtime(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ragdolltimestepmin.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ragdolltimestepmin(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ragdolltimestepmax.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ragdolltimestepmax(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ragdollrotfric.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ragdollrotfric(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ragdollrotfricstop.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ragdollrotfricstop(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ragdollconstrain.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ragdollconstrain(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ragdollbodyfric.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ragdollbodyfric(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ragdollbodyfricscale.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ragdollbodyfricscale(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ragdollwaterfric.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ragdollwaterfric(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ragdollgroundfric.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ragdollgroundfric(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ragdollairfric.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ragdollairfric(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ragdollunstick.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ragdollunstick(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ragdollexpireoffset.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ragdollexpireoffset(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ragdollwaterexpireoffset.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ragdollwaterexpireoffset(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ragdolleyesmooth.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ragdolleyesmooth(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ragdolleyesmoothmillis.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ragdolleyesmoothmillis(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::envmapmodels.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__envmapmodels(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::bumpmodels.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__bumpmodels(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fullbrightmodels.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fullbrightmodels(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::gpuskel.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__gpuskel(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxskelanimdata.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxskelanimdata(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::testtags.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__testtags(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::showboundingbox.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__showboundingbox(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxmodelradiusdistance.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxmodelradiusdistance(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::animoverride.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__animoverride(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::testanims.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__testanims(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::testpitch.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__testpitch(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::particlesize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__particlesize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::emitmillis.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__emitmillis(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::showparticles.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__showparticles(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cullparticles.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cullparticles(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::replayparticles.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__replayparticles(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::seedmillis.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__seedmillis(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dbgpcull.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dbgpcull(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dbgpseed.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dbgpseed(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::outlinemeters.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__outlinemeters(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::depthfxfpscale.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__depthfxfpscale(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::depthfxscale.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__depthfxscale(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::depthfxblend.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__depthfxblend(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::depthfxpartblend.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__depthfxpartblend(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::depthfxmargin.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__depthfxmargin(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::depthfxbias.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__depthfxbias(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fpdepthfx.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fpdepthfx(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::depthfxemuprecision.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__depthfxemuprecision(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::depthfxsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__depthfxsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::depthfx.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__depthfx(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::depthfxparts.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__depthfxparts(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blurdepthfx.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blurdepthfx(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blurdepthfxsigma.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blurdepthfxsigma(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::depthfxscissor.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__depthfxscissor(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::debugdepthfx.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__debugdepthfx(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::flarelights.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__flarelights(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::flarecutoff.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__flarecutoff(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::flaresize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__flaresize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lnjittermillis.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lnjittermillis(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lnjitterradius.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lnjitterradius(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lnjitterscale.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lnjitterscale(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lnscrollmillis.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lnscrollmillis(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lnscrollscale.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lnscrollscale(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lnblendpower.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lnblendpower(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxparticles.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxparticles(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fewparticles.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fewparticles(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::particleglare.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__particleglare(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dbgparts.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dbgparts(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxparticledistance.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxparticledistance(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxtrail.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxtrail(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::particletext.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__particletext(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxparticletextdistance.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxparticletextdistance(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::skybox.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__skybox(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::skyboxcolour.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__skyboxcolour(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::spinsky.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__spinsky(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::yawsky.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__yawsky(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cloudbox.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cloudbox(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cloudboxcolour.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cloudboxcolour(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cloudboxalpha.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cloudboxalpha(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::spinclouds.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__spinclouds(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::yawclouds.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__yawclouds(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cloudclip.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cloudclip(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cloudlayer.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cloudlayer(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cloudoffsetx.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cloudoffsetx(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cloudoffsety.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cloudoffsety(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cloudscrollx.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cloudscrollx(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cloudscrolly.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cloudscrolly(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cloudscale.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cloudscale(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::spincloudlayer.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__spincloudlayer(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::yawcloudlayer.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__yawcloudlayer(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cloudheight.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cloudheight(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cloudfade.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cloudfade(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cloudalpha.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cloudalpha(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cloudsubdiv.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cloudsubdiv(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::cloudcolour.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__cloudcolour(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fogdomeheight.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fogdomeheight(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fogdomemin.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fogdomemin(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fogdomemax.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fogdomemax(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fogdomecap.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fogdomecap(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fogdomeclip.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fogdomeclip(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::sparklyfix.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__sparklyfix(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::showsky.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__showsky(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::clipsky.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__clipsky(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::clampsky.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__clampsky(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fogdomeclouds.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fogdomeclouds(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::useskytexture.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__useskytexture(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::oqfrags.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__oqfrags(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::oqwait.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__oqwait(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::oqmm.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__oqmm(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::outline.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__outline(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::outlinecolour.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__outlinecolour(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dtoutline.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dtoutline(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blendbrushcolor.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blendbrushcolor(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::oqdist.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__oqdist(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::zpass.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__zpass(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::glowpass.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__glowpass(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::envpass.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__envpass(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::batchgeom.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__batchgeom(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::causticdir.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__causticdir(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::causticscale.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__causticscale(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::causticmillis.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__causticmillis(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::caustics.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__caustics(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::oqgeom.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__oqgeom(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxclients.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxclients(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxdupclients.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxdupclients(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::allowupdatemaster.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__allowupdatemaster(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::mastername.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__mastername(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::masterport.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__masterport(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::serveruprate.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__serveruprate(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::serverip.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__serverip(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::serverport.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__serverport(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::searchlan.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__searchlan(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::servpingrate.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__servpingrate(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::servpingdecay.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__servpingdecay(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxservpings.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxservpings(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::autosortservers.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__autosortservers(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::autoupdateservers.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__autoupdateservers(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::reservevpparams.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__reservevpparams(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxvsuniforms.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxvsuniforms(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxfsuniforms.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxfsuniforms(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxvaryings.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxvaryings(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dbgshader.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dbgshader(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dbgubo.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dbgubo(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::shaderprecision.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__shaderprecision(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::defershaders.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__defershaders(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::shaderdetail.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__shaderdetail(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::shadowmap.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__shadowmap(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::shadowmapsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__shadowmapsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::shadowmapradius.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__shadowmapradius(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::shadowmapheight.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__shadowmapheight(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::shadowmapdist.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__shadowmapdist(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::fpshadowmap.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__fpshadowmap(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::shadowmapprecision.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__shadowmapprecision(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::shadowmapintensity.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__shadowmapintensity(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blurshadowmap.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blurshadowmap(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::blursmsigma.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__blursmsigma(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::shadowmapangle.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__shadowmapangle(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::shadowmapbias.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__shadowmapbias(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::shadowmappeelbias.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__shadowmappeelbias(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::smdepthpeel.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__smdepthpeel(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::smoothshadowmappeel.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__smoothshadowmappeel(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::debugsm.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__debugsm(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::soundvol.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__sound_soundvol(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::musicvol.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__sound_musicvol(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::soundchans.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__sound_soundchans(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::soundfreq.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__sound_soundfreq(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::soundbufferlen.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__sound_soundbufferlen(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::stereo.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__sound_stereo(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::maxsoundradius.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__sound_maxsoundradius(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::maxsoundsatonce.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__sound_maxsoundsatonce(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::dbgsound.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__sound_dbgsound(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::mumble.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__sound_mumble(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::waterreflect.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__waterreflect(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::waterrefract.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__waterrefract(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::waterenvmap.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__waterenvmap(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::waterfallrefract.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__waterfallrefract(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::watersubdiv.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__watersubdiv(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::waterlod.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__waterlod(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::vertwater.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__vertwater(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::reflectdist.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__reflectdist(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::waterfog.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__waterfog(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::waterspec.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__waterspec(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::water2fog.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__water2fog(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::water2spec.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__water2spec(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::water3fog.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__water3fog(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::water3spec.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__water3spec(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::water4fog.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__water4fog(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::water4spec.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__water4spec(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lavafog.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lavafog(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lava2fog.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lava2fog(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lava3fog.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lava3fog(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::lava4fog.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__lava4fog(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::oqwater.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__oqwater(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::waterfade.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__waterfade(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::reflectsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__reflectsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxreflect.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxreflect(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maskreflect.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maskreflect(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::reflectscissor.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__reflectscissor(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::reflectvfc.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__reflectvfc(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::refractclear.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__refractclear(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::mapversion.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__mapversion(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::worldscale.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__worldscale(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::worldsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__worldsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maptitle.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maptitle(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::octaentsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__octaentsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::entselradius.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__entselradius(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::entediting.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__entediting(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::attachradius.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__attachradius(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::entselsnap.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__entselsnap(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::entmovingshadow.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__entmovingshadow(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::showentradius.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__showentradius(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::entitysurf.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__entitysurf(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::entautoviewdist.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__entautoviewdist(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::entdrop.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__entdrop(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::savebak.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__savebak(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dbgvars.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dbgvars(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::mapdir.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__mapdir(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::texturedir.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__texturedir(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::skyboxdir.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__skyboxdir(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::interfacedir.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__interfacedir(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::icondir.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__icondir(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::sounddir.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__sounddir(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::musicdir.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__musicdir(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ai::aidebug.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ai_aidebug(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ai::aiforcegun.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ai_aiforcegun(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ai::showwaypoints.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ai_showwaypoints(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ai::showwaypointsradius.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ai_showwaypointsradius(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::minradarscale.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_minradarscale(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::maxradarscale.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_maxradarscale(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::radarteammates.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_radarteammates(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::minimapalpha.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_minimapalpha(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::radardir.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_radardir(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::capturetether.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_capturetether(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::autorepammo.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_autorepammo(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::basenumbers.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_basenumbers(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::showbombs.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_showbombs(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::showbombradius.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_showbombradius(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::showbombdelay.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_showbombdelay(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::showminimapobstacles.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_showminimapobstacles(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::deadpush.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_deadpush(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::autoauth.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_autoauth(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::entities::triggerstate.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__entities_triggerstate(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::smoothmove.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_smoothmove(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::smoothdist.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_smoothdist(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::slowmosp.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_slowmosp(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::spawnwait.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_spawnwait(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::hitsound.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_hitsound(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::deathscore.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_deathscore(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::teamcolorfrags.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_teamcolorfrags(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::showmodeinfo.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_showmodeinfo(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::teamcolortext.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_teamcolortext(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::ammohud.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_ammohud(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::teamcrosshair.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_teamcrosshair(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::hitcrosshair.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_hitcrosshair(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::skill.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_skill(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::killsendsp.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_killsendsp(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::ragdoll.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_ragdoll(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::ragdollmillis.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_ragdollmillis(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::ragdollfade.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_ragdollfade(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::playermodel.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_playermodel(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::forceplayermodels.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_forceplayermodels(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::hidedead.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_hidedead(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::testquad.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_testquad(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::testarmour.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_testarmour(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::testteam.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_testteam(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::teamskins.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_teamskins(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::hudgun.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_hudgun(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::hudgunsway.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_hudgunsway(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::teamhudguns.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_teamhudguns(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::chainsawhudgun.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_chainsawhudgun(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::testhudgun.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_testhudgun(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::swaystep.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_swaystep(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::swayside.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_swayside(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::swayup.onChange.connect([](const float oldvalue, const float newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_swayup(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::hudgunsdir.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_hudgunsdir(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::scoreboard2d.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_scoreboard2d(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::showservinfo.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_showservinfo(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::showclientnum.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_showclientnum(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::showpj.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_showpj(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::showping.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_showping(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::showspectators.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_showspectators(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::showflags.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_showflags(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::showfrags.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_showfrags(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::showaccuracy.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_showaccuracy(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::highlightscore.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_highlightscore(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::showconnecting.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_showconnecting(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::showscoreboard.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_showscoreboard(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::lockmaprotation.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_lockmaprotation(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::maxdemos.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_maxdemos(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::maxdemosize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_maxdemosize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::restrictdemos.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_restrictdemos(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::restrictpausegame.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_restrictpausegame(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::restrictgamespeed.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_restrictgamespeed(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::restrictpersistteams.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_restrictpersistteams(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::serverdesc.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_serverdesc(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::serverpass.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_serverpass(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::adminpass.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_adminpass(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::publicserver.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_publicserver(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::servermotd.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_servermotd(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::spectatemodifiedmap.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_spectatemodifiedmap(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::ctftkpenalty.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_ctftkpenalty(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::serverauth.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_serverauth(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::modifiedmapspectator.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_modifiedmapspectator(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::extinfoip.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_extinfoip(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::aiman::botlimit.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_aiman_botlimit(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::server::aiman::serverbotbalance.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__server_aiman_serverbotbalance(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::ai::dropwaypoints.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__ai_dropwaypoints(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::maxdebris.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_maxdebris(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::maxbarreldebris.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_maxbarreldebris(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::blood.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_blood(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::muzzleflash.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_muzzleflash(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::muzzlelight.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_muzzlelight(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::bombcolliderad.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_bombcolliderad(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::game::bombbarrier.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__game_bombbarrier(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dbggz.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dbggz(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dbgzip.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dbgzip(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::dbgdds.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dbgdds(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::envmapsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__envmapsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::envmapradius.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__envmapradius(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::aaenvmap.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__aaenvmap(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::compresspng.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__compresspng(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::compresstga.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__compresstga(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::screenshotformat.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__screenshotformat(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::screenshotdir.onChange.connect([](const char * oldvalue, const char * newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__screenshotdir(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::autocompactvslots.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__autocompactvslots(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::hwtexsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__hwtexsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::hwcubetexsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__hwcubetexsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::hwmaxaniso.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__hwmaxaniso(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::maxtexsize.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__maxtexsize(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::reducefilter.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__reducefilter(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::texreduce.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__texreduce(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::trilinear.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__trilinear(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::bilinear.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__bilinear(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::aniso.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__aniso(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::texcompress.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__texcompress(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::texcompressquality.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__texcompressquality(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::usenp2.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__usenp2(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::usedds.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__usedds(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::scaledds.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__scaledds(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );

    }

    void syncall()
    {
        // TODO: Dont call by type but by reference if not a ptr: *or& -> {cpp_observer_type}
        ::guiautotab.sync();
        ::guiclicktab.sync();
        ::guifadein.sync();
        ::guipushdist.sync();
        ::guisens.sync();
        ::useguifollow.sync();
        ::usegui2d.sync();
        ::blendpaintmode.sync();
        ::paintblendmapdelay.sync();
        ::paintblendmapinterval.sync();
        ::showblobs.sync();
        ::blobintensity.sync();
        ::blobheight.sync();
        ::blobfadelow.sync();
        ::blobfadehigh.sync();
        ::blobmargin.sync();
        ::dbgblob.sync();
        ::blobstattris.sync();
        ::blobdyntris.sync();
        ::rate.sync();
        ::throttle_interval.sync();
        ::throttle_accel.sync();
        ::throttle_decel.sync();
        ::connectname.sync();
        ::connectport.sync();
        ::dbgalias.sync();
        ::maxcon.sync();
        ::confading.sync();
        ::fullconsole.sync();
        ::consize.sync();
        ::miniconsize.sync();
        ::miniconwidth.sync();
        ::confade.sync();
        ::miniconfade.sync();
        ::fullconsize.sync();
        ::confilter.sync();
        ::fullconfilter.sync();
        ::miniconfilter.sync();
        ::maxhistory.sync();
        ::maxdecaltris.sync();
        ::decalfade.sync();
        ::dbgdec.sync();
        ::showdecals.sync();
        ::maxdecaldistance.sync();
        ::maxdynlights.sync();
        ::dynlightdist.sync();
        ::glaresize.sync();
        ::glare.sync();
        ::blurglare.sync();
        ::blurglaresigma.sync();
        ::debugglare.sync();
        ::glarescale.sync();
        ::grass.sync();
        ::dbggrass.sync();
        ::grassdist.sync();
        ::grasstaper.sync();
        ::grassstep.sync();
        ::grassheight.sync();
        ::grassanimmillis.sync();
        ::grassanimscale.sync();
        ::grassscale.sync();
        ::grassalpha.sync();
        ::lightprecision.sync();
        ::lighterror.sync();
        ::bumperror.sync();
        ::lightlod.sync();
        ::sunlightyaw.sync();
        ::sunlightpitch.sync();
        ::skytexturelight.sync();
        ::lmshadows_.sync();
        ::lmaa_.sync();
        ::lerptjoints_.sync();
        ::lmao_.sync();
        ::lightcompress.sync();
        ::ambientocclusion.sync();
        ::ambientocclusionradius.sync();
        ::debugao.sync();
        ::blurlms.sync();
        ::blurskylight.sync();
        ::edgetolerance.sync();
        ::adaptivesample.sync();
        ::lightcachesize.sync();
        ::lightthreads.sync();
        ::patchnormals.sync();
        ::fullbright.sync();
        ::fullbrightlevel.sync();
        ::roundlightmaptex.sync();
        ::batchlightmaps.sync();
        ::inexor::rendering::screen::scr_w.sync();
        ::inexor::rendering::screen::scr_h.sync();
        ::inexor::rendering::screen::colorbits.sync();
        ::inexor::rendering::screen::depthbits.sync();
        ::inexor::rendering::screen::stencilbits.sync();
        ::inexor::rendering::screen::vsync.sync();
        ::inexor::rendering::screen::vsynctear.sync();
        ::fsaa.sync();
        ::background.sync();
        ::logo.sync();
        ::userelativemouse.sync();
        ::inexor::rendering::screen::fullscreen.sync();
        ::inexor::rendering::screen::gamma.sync();
        ::menufps.sync();
        ::maxfps.sync();
        ::clockerror.sync();
        ::clockfix.sync();
        ::numcpus.sync();
        ::optmats.sync();
        ::showmat.sync();
        ::glassenv.sync();
        ::waterfallenv.sync();
        ::menudistance.sync();
        ::menuautoclose.sync();
        ::applydialog.sync();
        ::mainmenu.sync();
        ::dbgmovie.sync();
        ::movieaccelblit.sync();
        ::movieaccelyuv.sync();
        ::movieaccel.sync();
        ::moviesync.sync();
        ::movieminquality.sync();
        ::moview.sync();
        ::movieh.sync();
        ::moviefps.sync();
        ::moviesound.sync();
        ::lerpangle.sync();
        ::lerpsubdiv.sync();
        ::lerpsubdivsize.sync();
        ::mipvis.sync();
        ::maxmerge.sync();
        ::minface.sync();
        ::dragging.sync();
        ::gridpower.sync();
        ::passthroughsel.sync();
        ::editing.sync();
        ::selectcorners.sync();
        ::hmapedit.sync();
        ::gridlookup.sync();
        ::passthroughcube.sync();
        ::undomegs.sync();
        ::nompedit.sync();
        ::prefabdir.sync();
        ::brushx.sync();
        ::brushy.sync();
        ::invalidcubeguard.sync();
        ::selectionsurf.sync();
        ::usevdelta.sync();
        ::allfaces.sync();
        ::texguiwidth.sync();
        ::texguiheight.sync();
        ::texguitime.sync();
        ::texgui2d.sync();
        ::debugvbo.sync();
        ::maxvbosize.sync();
        ::filltjoints.sync();
        ::vafacemax.sync();
        ::vafacemin.sync();
        ::vacubesize.sync();
        ::dynentsize.sync();
        ::maxroll.sync();
        ::straferoll.sync();
        ::faderoll.sync();
        ::floatspeed.sync();
        ::physinterp.sync();
        ::maxpvsblocker.sync();
        ::pvsleafsize.sync();
        ::pvsthreads.sync();
        ::lockpvs.sync();
        ::usepvs.sync();
        ::usewaterpvs.sync();
        ::glversion.sync();
        ::glslversion.sync();
        ::ati_skybox_bug.sync();
        ::ati_minmax_bug.sync();
        ::ati_cubemap_bug.sync();
        ::intel_vertexarray_bug.sync();
        ::intel_mapbufferrange_bug.sync();
        ::minimizetcusage.sync();
        ::useubo.sync();
        ::usetexcompress.sync();
        ::rtscissor.sync();
        ::blurtile.sync();
        ::rtsharefb.sync();
        ::dbgexts.sync();
        ::wireframe.sync();
        ::zoominvel.sync();
        ::zoomoutvel.sync();
        ::zoomfov.sync();
        ::fov.sync();
        ::followfov.sync();
        ::avatarzoomfov.sync();
        ::avatarfov.sync();
        ::avatardepth.sync();
        ::forceaspect.sync();
        ::zoom.sync();
        ::zoomsens.sync();
        ::zoomaccel.sync();
        ::zoomautosens.sync();
        ::sensitivity.sync();
        ::sensitivityscale.sync();
        ::invmouse.sync();
        ::mouseaccel.sync();
        ::thirdperson.sync();
        ::thirdpersondistance.sync();
        ::thirdpersonup.sync();
        ::thirdpersonside.sync();
        ::nearplane.sync();
        ::reflectclip.sync();
        ::reflectclipavatar.sync();
        ::polygonoffsetfactor.sync();
        ::polygonoffsetunits.sync();
        ::depthoffset.sync();
        ::fog.sync();
        ::skyboxglare.sync();
        ::reflectmms.sync();
        ::refractsky.sync();
        ::modelpreviewfov.sync();
        ::modelpreviewpitch.sync();
        ::minimapheight.sync();
        ::minimapclip.sync();
        ::minimapsize.sync();
        ::motionblur.sync();
        ::motionblurmillis.sync();
        ::motionblurscale.sync();
        ::usedamagecompass.sync();
        ::damagecompassfade.sync();
        ::damagecompasssize.sync();
        ::damagecompassalpha.sync();
        ::damagecompassmin.sync();
        ::damagecompassmax.sync();
        ::damagescreen.sync();
        ::damagescreenfactor.sync();
        ::damagescreenalpha.sync();
        ::damagescreenfade.sync();
        ::damagescreenmin.sync();
        ::damagescreenmax.sync();
        ::hidestats.sync();
        ::hidehud.sync();
        ::crosshairsize.sync();
        ::cursorsize.sync();
        ::crosshairfx.sync();
        ::crosshaircolors.sync();
        ::crosshairdir.sync();
        ::cursor.sync();
        ::wallclock.sync();
        ::wallclock24.sync();
        ::wallclocksecs.sync();
        ::showfps.sync();
        ::showfpsrange.sync();
        ::showeditstats.sync();
        ::statrate.sync();
        ::conscale.sync();
        ::modeldir.sync();
        ::oqdynent.sync();
        ::animationinterpolationtime.sync();
        ::ragdolltimestepmin.sync();
        ::ragdolltimestepmax.sync();
        ::ragdollrotfric.sync();
        ::ragdollrotfricstop.sync();
        ::ragdollconstrain.sync();
        ::ragdollbodyfric.sync();
        ::ragdollbodyfricscale.sync();
        ::ragdollwaterfric.sync();
        ::ragdollgroundfric.sync();
        ::ragdollairfric.sync();
        ::ragdollunstick.sync();
        ::ragdollexpireoffset.sync();
        ::ragdollwaterexpireoffset.sync();
        ::ragdolleyesmooth.sync();
        ::ragdolleyesmoothmillis.sync();
        ::envmapmodels.sync();
        ::bumpmodels.sync();
        ::fullbrightmodels.sync();
        ::gpuskel.sync();
        ::maxskelanimdata.sync();
        ::testtags.sync();
        ::showboundingbox.sync();
        ::maxmodelradiusdistance.sync();
        ::animoverride.sync();
        ::testanims.sync();
        ::testpitch.sync();
        ::particlesize.sync();
        ::emitmillis.sync();
        ::showparticles.sync();
        ::cullparticles.sync();
        ::replayparticles.sync();
        ::seedmillis.sync();
        ::dbgpcull.sync();
        ::dbgpseed.sync();
        ::outlinemeters.sync();
        ::depthfxfpscale.sync();
        ::depthfxscale.sync();
        ::depthfxblend.sync();
        ::depthfxpartblend.sync();
        ::depthfxmargin.sync();
        ::depthfxbias.sync();
        ::fpdepthfx.sync();
        ::depthfxemuprecision.sync();
        ::depthfxsize.sync();
        ::depthfx.sync();
        ::depthfxparts.sync();
        ::blurdepthfx.sync();
        ::blurdepthfxsigma.sync();
        ::depthfxscissor.sync();
        ::debugdepthfx.sync();
        ::flarelights.sync();
        ::flarecutoff.sync();
        ::flaresize.sync();
        ::lnjittermillis.sync();
        ::lnjitterradius.sync();
        ::lnjitterscale.sync();
        ::lnscrollmillis.sync();
        ::lnscrollscale.sync();
        ::lnblendpower.sync();
        ::maxparticles.sync();
        ::fewparticles.sync();
        ::particleglare.sync();
        ::dbgparts.sync();
        ::maxparticledistance.sync();
        ::maxtrail.sync();
        ::particletext.sync();
        ::maxparticletextdistance.sync();
        ::skybox.sync();
        ::skyboxcolour.sync();
        ::spinsky.sync();
        ::yawsky.sync();
        ::cloudbox.sync();
        ::cloudboxcolour.sync();
        ::cloudboxalpha.sync();
        ::spinclouds.sync();
        ::yawclouds.sync();
        ::cloudclip.sync();
        ::cloudlayer.sync();
        ::cloudoffsetx.sync();
        ::cloudoffsety.sync();
        ::cloudscrollx.sync();
        ::cloudscrolly.sync();
        ::cloudscale.sync();
        ::spincloudlayer.sync();
        ::yawcloudlayer.sync();
        ::cloudheight.sync();
        ::cloudfade.sync();
        ::cloudalpha.sync();
        ::cloudsubdiv.sync();
        ::cloudcolour.sync();
        ::fogdomeheight.sync();
        ::fogdomemin.sync();
        ::fogdomemax.sync();
        ::fogdomecap.sync();
        ::fogdomeclip.sync();
        ::sparklyfix.sync();
        ::showsky.sync();
        ::clipsky.sync();
        ::clampsky.sync();
        ::fogdomeclouds.sync();
        ::useskytexture.sync();
        ::oqfrags.sync();
        ::oqwait.sync();
        ::oqmm.sync();
        ::outline.sync();
        ::outlinecolour.sync();
        ::dtoutline.sync();
        ::blendbrushcolor.sync();
        ::oqdist.sync();
        ::zpass.sync();
        ::glowpass.sync();
        ::envpass.sync();
        ::batchgeom.sync();
        ::causticdir.sync();
        ::causticscale.sync();
        ::causticmillis.sync();
        ::caustics.sync();
        ::oqgeom.sync();
        ::maxclients.sync();
        ::maxdupclients.sync();
        ::allowupdatemaster.sync();
        ::mastername.sync();
        ::masterport.sync();
        ::serveruprate.sync();
        ::serverip.sync();
        ::serverport.sync();
        ::searchlan.sync();
        ::servpingrate.sync();
        ::servpingdecay.sync();
        ::maxservpings.sync();
        ::autosortservers.sync();
        ::autoupdateservers.sync();
        ::reservevpparams.sync();
        ::maxvsuniforms.sync();
        ::maxfsuniforms.sync();
        ::maxvaryings.sync();
        ::dbgshader.sync();
        ::dbgubo.sync();
        ::shaderprecision.sync();
        ::defershaders.sync();
        ::shaderdetail.sync();
        ::shadowmap.sync();
        ::shadowmapsize.sync();
        ::shadowmapradius.sync();
        ::shadowmapheight.sync();
        ::shadowmapdist.sync();
        ::fpshadowmap.sync();
        ::shadowmapprecision.sync();
        ::shadowmapintensity.sync();
        ::blurshadowmap.sync();
        ::blursmsigma.sync();
        ::shadowmapangle.sync();
        ::shadowmapbias.sync();
        ::shadowmappeelbias.sync();
        ::smdepthpeel.sync();
        ::smoothshadowmappeel.sync();
        ::debugsm.sync();
        ::inexor::sound::soundvol.sync();
        ::inexor::sound::musicvol.sync();
        ::inexor::sound::soundchans.sync();
        ::inexor::sound::soundfreq.sync();
        ::inexor::sound::soundbufferlen.sync();
        ::inexor::sound::stereo.sync();
        ::inexor::sound::maxsoundradius.sync();
        ::inexor::sound::maxsoundsatonce.sync();
        ::inexor::sound::dbgsound.sync();
        ::inexor::sound::mumble.sync();
        ::waterreflect.sync();
        ::waterrefract.sync();
        ::waterenvmap.sync();
        ::waterfallrefract.sync();
        ::watersubdiv.sync();
        ::waterlod.sync();
        ::vertwater.sync();
        ::reflectdist.sync();
        ::waterfog.sync();
        ::waterspec.sync();
        ::water2fog.sync();
        ::water2spec.sync();
        ::water3fog.sync();
        ::water3spec.sync();
        ::water4fog.sync();
        ::water4spec.sync();
        ::lavafog.sync();
        ::lava2fog.sync();
        ::lava3fog.sync();
        ::lava4fog.sync();
        ::oqwater.sync();
        ::waterfade.sync();
        ::reflectsize.sync();
        ::maxreflect.sync();
        ::maskreflect.sync();
        ::reflectscissor.sync();
        ::reflectvfc.sync();
        ::refractclear.sync();
        ::mapversion.sync();
        ::worldscale.sync();
        ::worldsize.sync();
        ::maptitle.sync();
        ::octaentsize.sync();
        ::entselradius.sync();
        ::entediting.sync();
        ::attachradius.sync();
        ::entselsnap.sync();
        ::entmovingshadow.sync();
        ::showentradius.sync();
        ::entitysurf.sync();
        ::entautoviewdist.sync();
        ::entdrop.sync();
        ::savebak.sync();
        ::dbgvars.sync();
        ::mapdir.sync();
        ::texturedir.sync();
        ::skyboxdir.sync();
        ::interfacedir.sync();
        ::icondir.sync();
        ::sounddir.sync();
        ::musicdir.sync();
        ::ai::aidebug.sync();
        ::ai::aiforcegun.sync();
        ::ai::showwaypoints.sync();
        ::ai::showwaypointsradius.sync();
        ::game::minradarscale.sync();
        ::game::maxradarscale.sync();
        ::game::radarteammates.sync();
        ::game::minimapalpha.sync();
        ::game::radardir.sync();
        ::game::capturetether.sync();
        ::game::autorepammo.sync();
        ::game::basenumbers.sync();
        ::game::showbombs.sync();
        ::game::showbombradius.sync();
        ::game::showbombdelay.sync();
        ::game::showminimapobstacles.sync();
        ::game::deadpush.sync();
        ::game::autoauth.sync();
        ::entities::triggerstate.sync();
        ::game::smoothmove.sync();
        ::game::smoothdist.sync();
        ::game::slowmosp.sync();
        ::game::spawnwait.sync();
        ::game::hitsound.sync();
        ::game::deathscore.sync();
        ::game::teamcolorfrags.sync();
        ::game::showmodeinfo.sync();
        ::game::teamcolortext.sync();
        ::game::ammohud.sync();
        ::game::teamcrosshair.sync();
        ::game::hitcrosshair.sync();
        ::game::skill.sync();
        ::game::killsendsp.sync();
        ::game::ragdoll.sync();
        ::game::ragdollmillis.sync();
        ::game::ragdollfade.sync();
        ::game::playermodel.sync();
        ::game::forceplayermodels.sync();
        ::game::hidedead.sync();
        ::game::testquad.sync();
        ::game::testarmour.sync();
        ::game::testteam.sync();
        ::game::teamskins.sync();
        ::game::hudgun.sync();
        ::game::hudgunsway.sync();
        ::game::teamhudguns.sync();
        ::game::chainsawhudgun.sync();
        ::game::testhudgun.sync();
        ::game::swaystep.sync();
        ::game::swayside.sync();
        ::game::swayup.sync();
        ::game::hudgunsdir.sync();
        ::game::scoreboard2d.sync();
        ::game::showservinfo.sync();
        ::game::showclientnum.sync();
        ::game::showpj.sync();
        ::game::showping.sync();
        ::game::showspectators.sync();
        ::game::showflags.sync();
        ::game::showfrags.sync();
        ::game::showaccuracy.sync();
        ::game::highlightscore.sync();
        ::game::showconnecting.sync();
        ::game::showscoreboard.sync();
        ::server::lockmaprotation.sync();
        ::server::maxdemos.sync();
        ::server::maxdemosize.sync();
        ::server::restrictdemos.sync();
        ::server::restrictpausegame.sync();
        ::server::restrictgamespeed.sync();
        ::server::restrictpersistteams.sync();
        ::server::serverdesc.sync();
        ::server::serverpass.sync();
        ::server::adminpass.sync();
        ::server::publicserver.sync();
        ::server::servermotd.sync();
        ::server::spectatemodifiedmap.sync();
        ::server::ctftkpenalty.sync();
        ::server::serverauth.sync();
        ::server::modifiedmapspectator.sync();
        ::server::extinfoip.sync();
        ::server::aiman::botlimit.sync();
        ::server::aiman::serverbotbalance.sync();
        ::ai::dropwaypoints.sync();
        ::game::maxdebris.sync();
        ::game::maxbarreldebris.sync();
        ::game::blood.sync();
        ::game::muzzleflash.sync();
        ::game::muzzlelight.sync();
        ::game::bombcolliderad.sync();
        ::game::bombbarrier.sync();
        ::dbggz.sync();
        ::dbgzip.sync();
        ::dbgdds.sync();
        ::envmapsize.sync();
        ::envmapradius.sync();
        ::aaenvmap.sync();
        ::compresspng.sync();
        ::compresstga.sync();
        ::screenshotformat.sync();
        ::screenshotdir.sync();
        ::autocompactvslots.sync();
        ::hwtexsize.sync();
        ::hwcubetexsize.sync();
        ::hwmaxaniso.sync();
        ::maxtexsize.sync();
        ::reducefilter.sync();
        ::texreduce.sync();
        ::trilinear.sync();
        ::bilinear.sync();
        ::aniso.sync();
        ::texcompress.sync();
        ::texcompressquality.sync();
        ::usenp2.sync();
        ::usedds.sync();
        ::scaledds.sync();

    }

    /// (proto)index -> pointer to the to-be-updated-variable.
    const std::unordered_map<int64, boost::variant<SharedVar<char *>*, SharedVar<int>*, SharedVar<float>*>> cppvar_pointer_map
    {
        // { index, pointer_to_the_changed_var (see net2maintupel::ptr2var) }
        { 1, &::guiautotab },
        { 2, &::guiclicktab },
        { 3, &::guifadein },
        { 4, &::guipushdist },
        { 5, &::guisens },
        { 6, &::useguifollow },
        { 7, &::usegui2d },
        { 8, &::blendpaintmode },
        { 9, &::paintblendmapdelay },
        { 10, &::paintblendmapinterval },
        { 11, &::showblobs },
        { 12, &::blobintensity },
        { 13, &::blobheight },
        { 14, &::blobfadelow },
        { 15, &::blobfadehigh },
        { 16, &::blobmargin },
        { 17, &::dbgblob },
        { 18, &::blobstattris },
        { 19, &::blobdyntris },
        { 20, &::rate },
        { 21, &::throttle_interval },
        { 22, &::throttle_accel },
        { 23, &::throttle_decel },
        { 24, &::connectname },
        { 25, &::connectport },
        { 26, &::dbgalias },
        { 27, &::maxcon },
        { 28, &::confading },
        { 29, &::fullconsole },
        { 30, &::consize },
        { 31, &::miniconsize },
        { 32, &::miniconwidth },
        { 33, &::confade },
        { 34, &::miniconfade },
        { 35, &::fullconsize },
        { 36, &::confilter },
        { 37, &::fullconfilter },
        { 38, &::miniconfilter },
        { 39, &::maxhistory },
        { 40, &::maxdecaltris },
        { 41, &::decalfade },
        { 42, &::dbgdec },
        { 43, &::showdecals },
        { 44, &::maxdecaldistance },
        { 45, &::maxdynlights },
        { 46, &::dynlightdist },
        { 47, &::glaresize },
        { 48, &::glare },
        { 49, &::blurglare },
        { 50, &::blurglaresigma },
        { 51, &::debugglare },
        { 52, &::glarescale },
        { 53, &::grass },
        { 54, &::dbggrass },
        { 55, &::grassdist },
        { 56, &::grasstaper },
        { 57, &::grassstep },
        { 58, &::grassheight },
        { 59, &::grassanimmillis },
        { 60, &::grassanimscale },
        { 61, &::grassscale },
        { 62, &::grassalpha },
        { 63, &::lightprecision },
        { 64, &::lighterror },
        { 65, &::bumperror },
        { 66, &::lightlod },
        { 67, &::sunlightyaw },
        { 68, &::sunlightpitch },
        { 69, &::skytexturelight },
        { 70, &::lmshadows_ },
        { 71, &::lmaa_ },
        { 72, &::lerptjoints_ },
        { 73, &::lmao_ },
        { 74, &::lightcompress },
        { 75, &::ambientocclusion },
        { 76, &::ambientocclusionradius },
        { 77, &::debugao },
        { 78, &::blurlms },
        { 79, &::blurskylight },
        { 80, &::edgetolerance },
        { 81, &::adaptivesample },
        { 82, &::lightcachesize },
        { 83, &::lightthreads },
        { 84, &::patchnormals },
        { 85, &::fullbright },
        { 86, &::fullbrightlevel },
        { 87, &::roundlightmaptex },
        { 88, &::batchlightmaps },
        { 89, &::inexor::rendering::screen::scr_w },
        { 90, &::inexor::rendering::screen::scr_h },
        { 91, &::inexor::rendering::screen::colorbits },
        { 92, &::inexor::rendering::screen::depthbits },
        { 93, &::inexor::rendering::screen::stencilbits },
        { 94, &::inexor::rendering::screen::vsync },
        { 95, &::inexor::rendering::screen::vsynctear },
        { 96, &::fsaa },
        { 97, &::background },
        { 98, &::logo },
        { 99, &::userelativemouse },
        { 100, &::inexor::rendering::screen::fullscreen },
        { 101, &::inexor::rendering::screen::gamma },
        { 102, &::menufps },
        { 103, &::maxfps },
        { 104, &::clockerror },
        { 105, &::clockfix },
        { 106, &::numcpus },
        { 107, &::optmats },
        { 108, &::showmat },
        { 109, &::glassenv },
        { 110, &::waterfallenv },
        { 111, &::menudistance },
        { 112, &::menuautoclose },
        { 113, &::applydialog },
        { 114, &::mainmenu },
        { 115, &::dbgmovie },
        { 116, &::movieaccelblit },
        { 117, &::movieaccelyuv },
        { 118, &::movieaccel },
        { 119, &::moviesync },
        { 120, &::movieminquality },
        { 121, &::moview },
        { 122, &::movieh },
        { 123, &::moviefps },
        { 124, &::moviesound },
        { 125, &::lerpangle },
        { 126, &::lerpsubdiv },
        { 127, &::lerpsubdivsize },
        { 128, &::mipvis },
        { 129, &::maxmerge },
        { 130, &::minface },
        { 131, &::dragging },
        { 132, &::gridpower },
        { 133, &::passthroughsel },
        { 134, &::editing },
        { 135, &::selectcorners },
        { 136, &::hmapedit },
        { 137, &::gridlookup },
        { 138, &::passthroughcube },
        { 139, &::undomegs },
        { 140, &::nompedit },
        { 141, &::prefabdir },
        { 142, &::brushx },
        { 143, &::brushy },
        { 144, &::invalidcubeguard },
        { 145, &::selectionsurf },
        { 146, &::usevdelta },
        { 147, &::allfaces },
        { 148, &::texguiwidth },
        { 149, &::texguiheight },
        { 150, &::texguitime },
        { 151, &::texgui2d },
        { 152, &::debugvbo },
        { 153, &::maxvbosize },
        { 154, &::filltjoints },
        { 155, &::vafacemax },
        { 156, &::vafacemin },
        { 157, &::vacubesize },
        { 158, &::dynentsize },
        { 159, &::maxroll },
        { 160, &::straferoll },
        { 161, &::faderoll },
        { 162, &::floatspeed },
        { 163, &::physinterp },
        { 164, &::maxpvsblocker },
        { 165, &::pvsleafsize },
        { 166, &::pvsthreads },
        { 167, &::lockpvs },
        { 168, &::usepvs },
        { 169, &::usewaterpvs },
        { 170, &::glversion },
        { 171, &::glslversion },
        { 172, &::ati_skybox_bug },
        { 173, &::ati_minmax_bug },
        { 174, &::ati_cubemap_bug },
        { 175, &::intel_vertexarray_bug },
        { 176, &::intel_mapbufferrange_bug },
        { 177, &::minimizetcusage },
        { 178, &::useubo },
        { 179, &::usetexcompress },
        { 180, &::rtscissor },
        { 181, &::blurtile },
        { 182, &::rtsharefb },
        { 183, &::dbgexts },
        { 184, &::wireframe },
        { 185, &::zoominvel },
        { 186, &::zoomoutvel },
        { 187, &::zoomfov },
        { 188, &::fov },
        { 189, &::followfov },
        { 190, &::avatarzoomfov },
        { 191, &::avatarfov },
        { 192, &::avatardepth },
        { 193, &::forceaspect },
        { 194, &::zoom },
        { 195, &::zoomsens },
        { 196, &::zoomaccel },
        { 197, &::zoomautosens },
        { 198, &::sensitivity },
        { 199, &::sensitivityscale },
        { 200, &::invmouse },
        { 201, &::mouseaccel },
        { 202, &::thirdperson },
        { 203, &::thirdpersondistance },
        { 204, &::thirdpersonup },
        { 205, &::thirdpersonside },
        { 206, &::nearplane },
        { 207, &::reflectclip },
        { 208, &::reflectclipavatar },
        { 209, &::polygonoffsetfactor },
        { 210, &::polygonoffsetunits },
        { 211, &::depthoffset },
        { 212, &::fog },
        { 213, &::skyboxglare },
        { 214, &::reflectmms },
        { 215, &::refractsky },
        { 216, &::modelpreviewfov },
        { 217, &::modelpreviewpitch },
        { 218, &::minimapheight },
        { 219, &::minimapclip },
        { 220, &::minimapsize },
        { 221, &::motionblur },
        { 222, &::motionblurmillis },
        { 223, &::motionblurscale },
        { 224, &::usedamagecompass },
        { 225, &::damagecompassfade },
        { 226, &::damagecompasssize },
        { 227, &::damagecompassalpha },
        { 228, &::damagecompassmin },
        { 229, &::damagecompassmax },
        { 230, &::damagescreen },
        { 231, &::damagescreenfactor },
        { 232, &::damagescreenalpha },
        { 233, &::damagescreenfade },
        { 234, &::damagescreenmin },
        { 235, &::damagescreenmax },
        { 236, &::hidestats },
        { 237, &::hidehud },
        { 238, &::crosshairsize },
        { 239, &::cursorsize },
        { 240, &::crosshairfx },
        { 241, &::crosshaircolors },
        { 242, &::crosshairdir },
        { 243, &::cursor },
        { 244, &::wallclock },
        { 245, &::wallclock24 },
        { 246, &::wallclocksecs },
        { 247, &::showfps },
        { 248, &::showfpsrange },
        { 249, &::showeditstats },
        { 250, &::statrate },
        { 251, &::conscale },
        { 252, &::modeldir },
        { 253, &::oqdynent },
        { 254, &::animationinterpolationtime },
        { 255, &::ragdolltimestepmin },
        { 256, &::ragdolltimestepmax },
        { 257, &::ragdollrotfric },
        { 258, &::ragdollrotfricstop },
        { 259, &::ragdollconstrain },
        { 260, &::ragdollbodyfric },
        { 261, &::ragdollbodyfricscale },
        { 262, &::ragdollwaterfric },
        { 263, &::ragdollgroundfric },
        { 264, &::ragdollairfric },
        { 265, &::ragdollunstick },
        { 266, &::ragdollexpireoffset },
        { 267, &::ragdollwaterexpireoffset },
        { 268, &::ragdolleyesmooth },
        { 269, &::ragdolleyesmoothmillis },
        { 270, &::envmapmodels },
        { 271, &::bumpmodels },
        { 272, &::fullbrightmodels },
        { 273, &::gpuskel },
        { 274, &::maxskelanimdata },
        { 275, &::testtags },
        { 276, &::showboundingbox },
        { 277, &::maxmodelradiusdistance },
        { 278, &::animoverride },
        { 279, &::testanims },
        { 280, &::testpitch },
        { 281, &::particlesize },
        { 282, &::emitmillis },
        { 283, &::showparticles },
        { 284, &::cullparticles },
        { 285, &::replayparticles },
        { 286, &::seedmillis },
        { 287, &::dbgpcull },
        { 288, &::dbgpseed },
        { 289, &::outlinemeters },
        { 290, &::depthfxfpscale },
        { 291, &::depthfxscale },
        { 292, &::depthfxblend },
        { 293, &::depthfxpartblend },
        { 294, &::depthfxmargin },
        { 295, &::depthfxbias },
        { 296, &::fpdepthfx },
        { 297, &::depthfxemuprecision },
        { 298, &::depthfxsize },
        { 299, &::depthfx },
        { 300, &::depthfxparts },
        { 301, &::blurdepthfx },
        { 302, &::blurdepthfxsigma },
        { 303, &::depthfxscissor },
        { 304, &::debugdepthfx },
        { 305, &::flarelights },
        { 306, &::flarecutoff },
        { 307, &::flaresize },
        { 308, &::lnjittermillis },
        { 309, &::lnjitterradius },
        { 310, &::lnjitterscale },
        { 311, &::lnscrollmillis },
        { 312, &::lnscrollscale },
        { 313, &::lnblendpower },
        { 314, &::maxparticles },
        { 315, &::fewparticles },
        { 316, &::particleglare },
        { 317, &::dbgparts },
        { 318, &::maxparticledistance },
        { 319, &::maxtrail },
        { 320, &::particletext },
        { 321, &::maxparticletextdistance },
        { 322, &::skybox },
        { 323, &::skyboxcolour },
        { 324, &::spinsky },
        { 325, &::yawsky },
        { 326, &::cloudbox },
        { 327, &::cloudboxcolour },
        { 328, &::cloudboxalpha },
        { 329, &::spinclouds },
        { 330, &::yawclouds },
        { 331, &::cloudclip },
        { 332, &::cloudlayer },
        { 333, &::cloudoffsetx },
        { 334, &::cloudoffsety },
        { 335, &::cloudscrollx },
        { 336, &::cloudscrolly },
        { 337, &::cloudscale },
        { 338, &::spincloudlayer },
        { 339, &::yawcloudlayer },
        { 340, &::cloudheight },
        { 341, &::cloudfade },
        { 342, &::cloudalpha },
        { 343, &::cloudsubdiv },
        { 344, &::cloudcolour },
        { 345, &::fogdomeheight },
        { 346, &::fogdomemin },
        { 347, &::fogdomemax },
        { 348, &::fogdomecap },
        { 349, &::fogdomeclip },
        { 350, &::sparklyfix },
        { 351, &::showsky },
        { 352, &::clipsky },
        { 353, &::clampsky },
        { 354, &::fogdomeclouds },
        { 355, &::useskytexture },
        { 356, &::oqfrags },
        { 357, &::oqwait },
        { 358, &::oqmm },
        { 359, &::outline },
        { 360, &::outlinecolour },
        { 361, &::dtoutline },
        { 362, &::blendbrushcolor },
        { 363, &::oqdist },
        { 364, &::zpass },
        { 365, &::glowpass },
        { 366, &::envpass },
        { 367, &::batchgeom },
        { 368, &::causticdir },
        { 369, &::causticscale },
        { 370, &::causticmillis },
        { 371, &::caustics },
        { 372, &::oqgeom },
        { 373, &::maxclients },
        { 374, &::maxdupclients },
        { 375, &::allowupdatemaster },
        { 376, &::mastername },
        { 377, &::masterport },
        { 378, &::serveruprate },
        { 379, &::serverip },
        { 380, &::serverport },
        { 381, &::searchlan },
        { 382, &::servpingrate },
        { 383, &::servpingdecay },
        { 384, &::maxservpings },
        { 385, &::autosortservers },
        { 386, &::autoupdateservers },
        { 387, &::reservevpparams },
        { 388, &::maxvsuniforms },
        { 389, &::maxfsuniforms },
        { 390, &::maxvaryings },
        { 391, &::dbgshader },
        { 392, &::dbgubo },
        { 393, &::shaderprecision },
        { 394, &::defershaders },
        { 395, &::shaderdetail },
        { 396, &::shadowmap },
        { 397, &::shadowmapsize },
        { 398, &::shadowmapradius },
        { 399, &::shadowmapheight },
        { 400, &::shadowmapdist },
        { 401, &::fpshadowmap },
        { 402, &::shadowmapprecision },
        { 403, &::shadowmapintensity },
        { 404, &::blurshadowmap },
        { 405, &::blursmsigma },
        { 406, &::shadowmapangle },
        { 407, &::shadowmapbias },
        { 408, &::shadowmappeelbias },
        { 409, &::smdepthpeel },
        { 410, &::smoothshadowmappeel },
        { 411, &::debugsm },
        { 412, &::inexor::sound::soundvol },
        { 413, &::inexor::sound::musicvol },
        { 414, &::inexor::sound::soundchans },
        { 415, &::inexor::sound::soundfreq },
        { 416, &::inexor::sound::soundbufferlen },
        { 417, &::inexor::sound::stereo },
        { 418, &::inexor::sound::maxsoundradius },
        { 419, &::inexor::sound::maxsoundsatonce },
        { 420, &::inexor::sound::dbgsound },
        { 421, &::inexor::sound::mumble },
        { 422, &::waterreflect },
        { 423, &::waterrefract },
        { 424, &::waterenvmap },
        { 425, &::waterfallrefract },
        { 426, &::watersubdiv },
        { 427, &::waterlod },
        { 428, &::vertwater },
        { 429, &::reflectdist },
        { 430, &::waterfog },
        { 431, &::waterspec },
        { 432, &::water2fog },
        { 433, &::water2spec },
        { 434, &::water3fog },
        { 435, &::water3spec },
        { 436, &::water4fog },
        { 437, &::water4spec },
        { 438, &::lavafog },
        { 439, &::lava2fog },
        { 440, &::lava3fog },
        { 441, &::lava4fog },
        { 442, &::oqwater },
        { 443, &::waterfade },
        { 444, &::reflectsize },
        { 445, &::maxreflect },
        { 446, &::maskreflect },
        { 447, &::reflectscissor },
        { 448, &::reflectvfc },
        { 449, &::refractclear },
        { 450, &::mapversion },
        { 451, &::worldscale },
        { 452, &::worldsize },
        { 453, &::maptitle },
        { 454, &::octaentsize },
        { 455, &::entselradius },
        { 456, &::entediting },
        { 457, &::attachradius },
        { 458, &::entselsnap },
        { 459, &::entmovingshadow },
        { 460, &::showentradius },
        { 461, &::entitysurf },
        { 462, &::entautoviewdist },
        { 463, &::entdrop },
        { 464, &::savebak },
        { 465, &::dbgvars },
        { 466, &::mapdir },
        { 467, &::texturedir },
        { 468, &::skyboxdir },
        { 469, &::interfacedir },
        { 470, &::icondir },
        { 471, &::sounddir },
        { 472, &::musicdir },
        { 473, &::ai::aidebug },
        { 474, &::ai::aiforcegun },
        { 475, &::ai::showwaypoints },
        { 476, &::ai::showwaypointsradius },
        { 477, &::game::minradarscale },
        { 478, &::game::maxradarscale },
        { 479, &::game::radarteammates },
        { 480, &::game::minimapalpha },
        { 481, &::game::radardir },
        { 482, &::game::capturetether },
        { 483, &::game::autorepammo },
        { 484, &::game::basenumbers },
        { 485, &::game::showbombs },
        { 486, &::game::showbombradius },
        { 487, &::game::showbombdelay },
        { 488, &::game::showminimapobstacles },
        { 489, &::game::deadpush },
        { 490, &::game::autoauth },
        { 491, &::entities::triggerstate },
        { 492, &::game::smoothmove },
        { 493, &::game::smoothdist },
        { 494, &::game::slowmosp },
        { 495, &::game::spawnwait },
        { 496, &::game::hitsound },
        { 497, &::game::deathscore },
        { 498, &::game::teamcolorfrags },
        { 499, &::game::showmodeinfo },
        { 500, &::game::teamcolortext },
        { 501, &::game::ammohud },
        { 502, &::game::teamcrosshair },
        { 503, &::game::hitcrosshair },
        { 504, &::game::skill },
        { 505, &::game::killsendsp },
        { 506, &::game::ragdoll },
        { 507, &::game::ragdollmillis },
        { 508, &::game::ragdollfade },
        { 509, &::game::playermodel },
        { 510, &::game::forceplayermodels },
        { 511, &::game::hidedead },
        { 512, &::game::testquad },
        { 513, &::game::testarmour },
        { 514, &::game::testteam },
        { 515, &::game::teamskins },
        { 516, &::game::hudgun },
        { 517, &::game::hudgunsway },
        { 518, &::game::teamhudguns },
        { 519, &::game::chainsawhudgun },
        { 520, &::game::testhudgun },
        { 521, &::game::swaystep },
        { 522, &::game::swayside },
        { 523, &::game::swayup },
        { 524, &::game::hudgunsdir },
        { 525, &::game::scoreboard2d },
        { 526, &::game::showservinfo },
        { 527, &::game::showclientnum },
        { 528, &::game::showpj },
        { 529, &::game::showping },
        { 530, &::game::showspectators },
        { 531, &::game::showflags },
        { 532, &::game::showfrags },
        { 533, &::game::showaccuracy },
        { 534, &::game::highlightscore },
        { 535, &::game::showconnecting },
        { 536, &::game::showscoreboard },
        { 537, &::server::lockmaprotation },
        { 538, &::server::maxdemos },
        { 539, &::server::maxdemosize },
        { 540, &::server::restrictdemos },
        { 541, &::server::restrictpausegame },
        { 542, &::server::restrictgamespeed },
        { 543, &::server::restrictpersistteams },
        { 544, &::server::serverdesc },
        { 545, &::server::serverpass },
        { 546, &::server::adminpass },
        { 547, &::server::publicserver },
        { 548, &::server::servermotd },
        { 549, &::server::spectatemodifiedmap },
        { 550, &::server::ctftkpenalty },
        { 551, &::server::serverauth },
        { 552, &::server::modifiedmapspectator },
        { 553, &::server::extinfoip },
        { 554, &::server::aiman::botlimit },
        { 555, &::server::aiman::serverbotbalance },
        { 556, &::ai::dropwaypoints },
        { 557, &::game::maxdebris },
        { 558, &::game::maxbarreldebris },
        { 559, &::game::blood },
        { 560, &::game::muzzleflash },
        { 561, &::game::muzzlelight },
        { 562, &::game::bombcolliderad },
        { 563, &::game::bombbarrier },
        { 564, &::dbggz },
        { 565, &::dbgzip },
        { 566, &::dbgdds },
        { 567, &::envmapsize },
        { 568, &::envmapradius },
        { 569, &::aaenvmap },
        { 570, &::compresspng },
        { 571, &::compresstga },
        { 572, &::screenshotformat },
        { 573, &::screenshotdir },
        { 574, &::autocompactvslots },
        { 575, &::hwtexsize },
        { 576, &::hwcubetexsize },
        { 577, &::hwmaxaniso },
        { 578, &::maxtexsize },
        { 579, &::reducefilter },
        { 580, &::texreduce },
        { 581, &::trilinear },
        { 582, &::bilinear },
        { 583, &::aniso },
        { 584, &::texcompress },
        { 585, &::texcompressquality },
        { 586, &::usenp2 },
        { 587, &::usedds },
        { 588, &::scaledds },
    
    };

    /// (proto)index -> Data type (cpp_type_t)
    const std::unordered_map<int64, int> index_to_type_map
    {
        // { index, enum_type(string=0,float=1,int=2) }
        { 1, 2 },  // /guiautotab, int
        { 2, 2 },  // /guiclicktab, int
        { 3, 2 },  // /guifadein, int
        { 4, 2 },  // /guipushdist, int
        { 5, 1 },  // /guisens, float
        { 6, 2 },  // /useguifollow, int
        { 7, 2 },  // /usegui2d, int
        { 8, 2 },  // /blendpaintmode, int
        { 9, 2 },  // /paintblendmapdelay, int
        { 10, 2 },  // /paintblendmapinterval, int
        { 11, 2 },  // /showblobs, int
        { 12, 2 },  // /blobintensity, int
        { 13, 2 },  // /blobheight, int
        { 14, 2 },  // /blobfadelow, int
        { 15, 2 },  // /blobfadehigh, int
        { 16, 2 },  // /blobmargin, int
        { 17, 2 },  // /dbgblob, int
        { 18, 2 },  // /blobstattris, int
        { 19, 2 },  // /blobdyntris, int
        { 20, 2 },  // /rate, int
        { 21, 2 },  // /throttle_interval, int
        { 22, 2 },  // /throttle_accel, int
        { 23, 2 },  // /throttle_decel, int
        { 24, 0 },  // /connectname, char *
        { 25, 2 },  // /connectport, int
        { 26, 2 },  // /dbgalias, int
        { 27, 2 },  // /maxcon, int
        { 28, 2 },  // /confading, int
        { 29, 2 },  // /fullconsole, int
        { 30, 2 },  // /consize, int
        { 31, 2 },  // /miniconsize, int
        { 32, 2 },  // /miniconwidth, int
        { 33, 2 },  // /confade, int
        { 34, 2 },  // /miniconfade, int
        { 35, 2 },  // /fullconsize, int
        { 36, 2 },  // /confilter, int
        { 37, 2 },  // /fullconfilter, int
        { 38, 2 },  // /miniconfilter, int
        { 39, 2 },  // /maxhistory, int
        { 40, 2 },  // /maxdecaltris, int
        { 41, 2 },  // /decalfade, int
        { 42, 2 },  // /dbgdec, int
        { 43, 2 },  // /showdecals, int
        { 44, 2 },  // /maxdecaldistance, int
        { 45, 2 },  // /maxdynlights, int
        { 46, 2 },  // /dynlightdist, int
        { 47, 2 },  // /glaresize, int
        { 48, 2 },  // /glare, int
        { 49, 2 },  // /blurglare, int
        { 50, 2 },  // /blurglaresigma, int
        { 51, 2 },  // /debugglare, int
        { 52, 1 },  // /glarescale, float
        { 53, 2 },  // /grass, int
        { 54, 2 },  // /dbggrass, int
        { 55, 2 },  // /grassdist, int
        { 56, 1 },  // /grasstaper, float
        { 57, 1 },  // /grassstep, float
        { 58, 2 },  // /grassheight, int
        { 59, 2 },  // /grassanimmillis, int
        { 60, 1 },  // /grassanimscale, float
        { 61, 2 },  // /grassscale, int
        { 62, 1 },  // /grassalpha, float
        { 63, 2 },  // /lightprecision, int
        { 64, 2 },  // /lighterror, int
        { 65, 2 },  // /bumperror, int
        { 66, 2 },  // /lightlod, int
        { 67, 2 },  // /sunlightyaw, int
        { 68, 2 },  // /sunlightpitch, int
        { 69, 2 },  // /skytexturelight, int
        { 70, 2 },  // /lmshadows_, int
        { 71, 2 },  // /lmaa_, int
        { 72, 2 },  // /lerptjoints_, int
        { 73, 2 },  // /lmao_, int
        { 74, 2 },  // /lightcompress, int
        { 75, 2 },  // /ambientocclusion, int
        { 76, 1 },  // /ambientocclusionradius, float
        { 77, 2 },  // /debugao, int
        { 78, 2 },  // /blurlms, int
        { 79, 2 },  // /blurskylight, int
        { 80, 2 },  // /edgetolerance, int
        { 81, 2 },  // /adaptivesample, int
        { 82, 2 },  // /lightcachesize, int
        { 83, 2 },  // /lightthreads, int
        { 84, 2 },  // /patchnormals, int
        { 85, 2 },  // /fullbright, int
        { 86, 2 },  // /fullbrightlevel, int
        { 87, 2 },  // /roundlightmaptex, int
        { 88, 2 },  // /batchlightmaps, int
        { 89, 2 },  // /rendering/screen/scr_w, int
        { 90, 2 },  // /rendering/screen/scr_h, int
        { 91, 2 },  // /rendering/screen/colorbits, int
        { 92, 2 },  // /rendering/screen/depthbits, int
        { 93, 2 },  // /rendering/screen/stencilbits, int
        { 94, 2 },  // /rendering/screen/vsync, int
        { 95, 2 },  // /rendering/screen/vsynctear, int
        { 96, 2 },  // /fsaa, int
        { 97, 0 },  // /background, char *
        { 98, 0 },  // /logo, char *
        { 99, 2 },  // /userelativemouse, int
        { 100, 2 },  // /rendering/screen/fullscreen, int
        { 101, 2 },  // /rendering/screen/gamma, int
        { 102, 2 },  // /menufps, int
        { 103, 2 },  // /maxfps, int
        { 104, 2 },  // /clockerror, int
        { 105, 2 },  // /clockfix, int
        { 106, 2 },  // /numcpus, int
        { 107, 2 },  // /optmats, int
        { 108, 2 },  // /showmat, int
        { 109, 2 },  // /glassenv, int
        { 110, 2 },  // /waterfallenv, int
        { 111, 2 },  // /menudistance, int
        { 112, 2 },  // /menuautoclose, int
        { 113, 2 },  // /applydialog, int
        { 114, 2 },  // /mainmenu, int
        { 115, 2 },  // /dbgmovie, int
        { 116, 2 },  // /movieaccelblit, int
        { 117, 2 },  // /movieaccelyuv, int
        { 118, 2 },  // /movieaccel, int
        { 119, 2 },  // /moviesync, int
        { 120, 1 },  // /movieminquality, float
        { 121, 2 },  // /moview, int
        { 122, 2 },  // /movieh, int
        { 123, 2 },  // /moviefps, int
        { 124, 2 },  // /moviesound, int
        { 125, 2 },  // /lerpangle, int
        { 126, 2 },  // /lerpsubdiv, int
        { 127, 2 },  // /lerpsubdivsize, int
        { 128, 2 },  // /mipvis, int
        { 129, 2 },  // /maxmerge, int
        { 130, 2 },  // /minface, int
        { 131, 2 },  // /dragging, int
        { 132, 2 },  // /gridpower, int
        { 133, 2 },  // /passthroughsel, int
        { 134, 2 },  // /editing, int
        { 135, 2 },  // /selectcorners, int
        { 136, 2 },  // /hmapedit, int
        { 137, 2 },  // /gridlookup, int
        { 138, 2 },  // /passthroughcube, int
        { 139, 2 },  // /undomegs, int
        { 140, 2 },  // /nompedit, int
        { 141, 0 },  // /prefabdir, char *
        { 142, 2 },  // /brushx, int
        { 143, 2 },  // /brushy, int
        { 144, 2 },  // /invalidcubeguard, int
        { 145, 2 },  // /selectionsurf, int
        { 146, 2 },  // /usevdelta, int
        { 147, 2 },  // /allfaces, int
        { 148, 2 },  // /texguiwidth, int
        { 149, 2 },  // /texguiheight, int
        { 150, 2 },  // /texguitime, int
        { 151, 2 },  // /texgui2d, int
        { 152, 2 },  // /debugvbo, int
        { 153, 2 },  // /maxvbosize, int
        { 154, 2 },  // /filltjoints, int
        { 155, 2 },  // /vafacemax, int
        { 156, 2 },  // /vafacemin, int
        { 157, 2 },  // /vacubesize, int
        { 158, 2 },  // /dynentsize, int
        { 159, 2 },  // /maxroll, int
        { 160, 1 },  // /straferoll, float
        { 161, 1 },  // /faderoll, float
        { 162, 2 },  // /floatspeed, int
        { 163, 2 },  // /physinterp, int
        { 164, 2 },  // /maxpvsblocker, int
        { 165, 2 },  // /pvsleafsize, int
        { 166, 2 },  // /pvsthreads, int
        { 167, 2 },  // /lockpvs, int
        { 168, 2 },  // /usepvs, int
        { 169, 2 },  // /usewaterpvs, int
        { 170, 2 },  // /glversion, int
        { 171, 2 },  // /glslversion, int
        { 172, 2 },  // /ati_skybox_bug, int
        { 173, 2 },  // /ati_minmax_bug, int
        { 174, 2 },  // /ati_cubemap_bug, int
        { 175, 2 },  // /intel_vertexarray_bug, int
        { 176, 2 },  // /intel_mapbufferrange_bug, int
        { 177, 2 },  // /minimizetcusage, int
        { 178, 2 },  // /useubo, int
        { 179, 2 },  // /usetexcompress, int
        { 180, 2 },  // /rtscissor, int
        { 181, 2 },  // /blurtile, int
        { 182, 2 },  // /rtsharefb, int
        { 183, 2 },  // /dbgexts, int
        { 184, 2 },  // /wireframe, int
        { 185, 2 },  // /zoominvel, int
        { 186, 2 },  // /zoomoutvel, int
        { 187, 2 },  // /zoomfov, int
        { 188, 2 },  // /fov, int
        { 189, 2 },  // /followfov, int
        { 190, 2 },  // /avatarzoomfov, int
        { 191, 2 },  // /avatarfov, int
        { 192, 1 },  // /avatardepth, float
        { 193, 1 },  // /forceaspect, float
        { 194, 2 },  // /zoom, int
        { 195, 1 },  // /zoomsens, float
        { 196, 1 },  // /zoomaccel, float
        { 197, 2 },  // /zoomautosens, int
        { 198, 1 },  // /sensitivity, float
        { 199, 1 },  // /sensitivityscale, float
        { 200, 2 },  // /invmouse, int
        { 201, 1 },  // /mouseaccel, float
        { 202, 2 },  // /thirdperson, int
        { 203, 1 },  // /thirdpersondistance, float
        { 204, 1 },  // /thirdpersonup, float
        { 205, 1 },  // /thirdpersonside, float
        { 206, 1 },  // /nearplane, float
        { 207, 2 },  // /reflectclip, int
        { 208, 2 },  // /reflectclipavatar, int
        { 209, 1 },  // /polygonoffsetfactor, float
        { 210, 1 },  // /polygonoffsetunits, float
        { 211, 1 },  // /depthoffset, float
        { 212, 2 },  // /fog, int
        { 213, 2 },  // /skyboxglare, int
        { 214, 2 },  // /reflectmms, int
        { 215, 2 },  // /refractsky, int
        { 216, 2 },  // /modelpreviewfov, int
        { 217, 2 },  // /modelpreviewpitch, int
        { 218, 2 },  // /minimapheight, int
        { 219, 2 },  // /minimapclip, int
        { 220, 2 },  // /minimapsize, int
        { 221, 2 },  // /motionblur, int
        { 222, 2 },  // /motionblurmillis, int
        { 223, 1 },  // /motionblurscale, float
        { 224, 2 },  // /usedamagecompass, int
        { 225, 2 },  // /damagecompassfade, int
        { 226, 2 },  // /damagecompasssize, int
        { 227, 2 },  // /damagecompassalpha, int
        { 228, 2 },  // /damagecompassmin, int
        { 229, 2 },  // /damagecompassmax, int
        { 230, 2 },  // /damagescreen, int
        { 231, 2 },  // /damagescreenfactor, int
        { 232, 2 },  // /damagescreenalpha, int
        { 233, 2 },  // /damagescreenfade, int
        { 234, 2 },  // /damagescreenmin, int
        { 235, 2 },  // /damagescreenmax, int
        { 236, 2 },  // /hidestats, int
        { 237, 2 },  // /hidehud, int
        { 238, 2 },  // /crosshairsize, int
        { 239, 2 },  // /cursorsize, int
        { 240, 2 },  // /crosshairfx, int
        { 241, 2 },  // /crosshaircolors, int
        { 242, 0 },  // /crosshairdir, char *
        { 243, 0 },  // /cursor, char *
        { 244, 2 },  // /wallclock, int
        { 245, 2 },  // /wallclock24, int
        { 246, 2 },  // /wallclocksecs, int
        { 247, 2 },  // /showfps, int
        { 248, 2 },  // /showfpsrange, int
        { 249, 2 },  // /showeditstats, int
        { 250, 2 },  // /statrate, int
        { 251, 1 },  // /conscale, float
        { 252, 0 },  // /modeldir, char *
        { 253, 2 },  // /oqdynent, int
        { 254, 2 },  // /animationinterpolationtime, int
        { 255, 2 },  // /ragdolltimestepmin, int
        { 256, 2 },  // /ragdolltimestepmax, int
        { 257, 1 },  // /ragdollrotfric, float
        { 258, 1 },  // /ragdollrotfricstop, float
        { 259, 2 },  // /ragdollconstrain, int
        { 260, 1 },  // /ragdollbodyfric, float
        { 261, 1 },  // /ragdollbodyfricscale, float
        { 262, 1 },  // /ragdollwaterfric, float
        { 263, 1 },  // /ragdollgroundfric, float
        { 264, 1 },  // /ragdollairfric, float
        { 265, 1 },  // /ragdollunstick, float
        { 266, 2 },  // /ragdollexpireoffset, int
        { 267, 2 },  // /ragdollwaterexpireoffset, int
        { 268, 1 },  // /ragdolleyesmooth, float
        { 269, 2 },  // /ragdolleyesmoothmillis, int
        { 270, 2 },  // /envmapmodels, int
        { 271, 2 },  // /bumpmodels, int
        { 272, 2 },  // /fullbrightmodels, int
        { 273, 2 },  // /gpuskel, int
        { 274, 2 },  // /maxskelanimdata, int
        { 275, 2 },  // /testtags, int
        { 276, 2 },  // /showboundingbox, int
        { 277, 2 },  // /maxmodelradiusdistance, int
        { 278, 2 },  // /animoverride, int
        { 279, 2 },  // /testanims, int
        { 280, 2 },  // /testpitch, int
        { 281, 2 },  // /particlesize, int
        { 282, 2 },  // /emitmillis, int
        { 283, 2 },  // /showparticles, int
        { 284, 2 },  // /cullparticles, int
        { 285, 2 },  // /replayparticles, int
        { 286, 2 },  // /seedmillis, int
        { 287, 2 },  // /dbgpcull, int
        { 288, 2 },  // /dbgpseed, int
        { 289, 2 },  // /outlinemeters, int
        { 290, 2 },  // /depthfxfpscale, int
        { 291, 2 },  // /depthfxscale, int
        { 292, 2 },  // /depthfxblend, int
        { 293, 2 },  // /depthfxpartblend, int
        { 294, 2 },  // /depthfxmargin, int
        { 295, 2 },  // /depthfxbias, int
        { 296, 2 },  // /fpdepthfx, int
        { 297, 2 },  // /depthfxemuprecision, int
        { 298, 2 },  // /depthfxsize, int
        { 299, 2 },  // /depthfx, int
        { 300, 2 },  // /depthfxparts, int
        { 301, 2 },  // /blurdepthfx, int
        { 302, 2 },  // /blurdepthfxsigma, int
        { 303, 2 },  // /depthfxscissor, int
        { 304, 2 },  // /debugdepthfx, int
        { 305, 2 },  // /flarelights, int
        { 306, 2 },  // /flarecutoff, int
        { 307, 2 },  // /flaresize, int
        { 308, 2 },  // /lnjittermillis, int
        { 309, 2 },  // /lnjitterradius, int
        { 310, 1 },  // /lnjitterscale, float
        { 311, 2 },  // /lnscrollmillis, int
        { 312, 1 },  // /lnscrollscale, float
        { 313, 1 },  // /lnblendpower, float
        { 314, 2 },  // /maxparticles, int
        { 315, 2 },  // /fewparticles, int
        { 316, 2 },  // /particleglare, int
        { 317, 2 },  // /dbgparts, int
        { 318, 2 },  // /maxparticledistance, int
        { 319, 2 },  // /maxtrail, int
        { 320, 2 },  // /particletext, int
        { 321, 2 },  // /maxparticletextdistance, int
        { 322, 0 },  // /skybox, char *
        { 323, 2 },  // /skyboxcolour, int
        { 324, 1 },  // /spinsky, float
        { 325, 2 },  // /yawsky, int
        { 326, 0 },  // /cloudbox, char *
        { 327, 2 },  // /cloudboxcolour, int
        { 328, 1 },  // /cloudboxalpha, float
        { 329, 1 },  // /spinclouds, float
        { 330, 2 },  // /yawclouds, int
        { 331, 1 },  // /cloudclip, float
        { 332, 0 },  // /cloudlayer, char *
        { 333, 1 },  // /cloudoffsetx, float
        { 334, 1 },  // /cloudoffsety, float
        { 335, 1 },  // /cloudscrollx, float
        { 336, 1 },  // /cloudscrolly, float
        { 337, 1 },  // /cloudscale, float
        { 338, 1 },  // /spincloudlayer, float
        { 339, 2 },  // /yawcloudlayer, int
        { 340, 1 },  // /cloudheight, float
        { 341, 1 },  // /cloudfade, float
        { 342, 1 },  // /cloudalpha, float
        { 343, 2 },  // /cloudsubdiv, int
        { 344, 2 },  // /cloudcolour, int
        { 345, 1 },  // /fogdomeheight, float
        { 346, 1 },  // /fogdomemin, float
        { 347, 1 },  // /fogdomemax, float
        { 348, 2 },  // /fogdomecap, int
        { 349, 1 },  // /fogdomeclip, float
        { 350, 2 },  // /sparklyfix, int
        { 351, 2 },  // /showsky, int
        { 352, 2 },  // /clipsky, int
        { 353, 2 },  // /clampsky, int
        { 354, 2 },  // /fogdomeclouds, int
        { 355, 2 },  // /useskytexture, int
        { 356, 2 },  // /oqfrags, int
        { 357, 2 },  // /oqwait, int
        { 358, 2 },  // /oqmm, int
        { 359, 2 },  // /outline, int
        { 360, 2 },  // /outlinecolour, int
        { 361, 2 },  // /dtoutline, int
        { 362, 2 },  // /blendbrushcolor, int
        { 363, 2 },  // /oqdist, int
        { 364, 2 },  // /zpass, int
        { 365, 2 },  // /glowpass, int
        { 366, 2 },  // /envpass, int
        { 367, 2 },  // /batchgeom, int
        { 368, 0 },  // /causticdir, char *
        { 369, 2 },  // /causticscale, int
        { 370, 2 },  // /causticmillis, int
        { 371, 2 },  // /caustics, int
        { 372, 2 },  // /oqgeom, int
        { 373, 2 },  // /maxclients, int
        { 374, 2 },  // /maxdupclients, int
        { 375, 2 },  // /allowupdatemaster, int
        { 376, 0 },  // /mastername, char *
        { 377, 2 },  // /masterport, int
        { 378, 2 },  // /serveruprate, int
        { 379, 0 },  // /serverip, char *
        { 380, 2 },  // /serverport, int
        { 381, 2 },  // /searchlan, int
        { 382, 2 },  // /servpingrate, int
        { 383, 2 },  // /servpingdecay, int
        { 384, 2 },  // /maxservpings, int
        { 385, 2 },  // /autosortservers, int
        { 386, 2 },  // /autoupdateservers, int
        { 387, 2 },  // /reservevpparams, int
        { 388, 2 },  // /maxvsuniforms, int
        { 389, 2 },  // /maxfsuniforms, int
        { 390, 2 },  // /maxvaryings, int
        { 391, 2 },  // /dbgshader, int
        { 392, 2 },  // /dbgubo, int
        { 393, 2 },  // /shaderprecision, int
        { 394, 2 },  // /defershaders, int
        { 395, 2 },  // /shaderdetail, int
        { 396, 2 },  // /shadowmap, int
        { 397, 2 },  // /shadowmapsize, int
        { 398, 2 },  // /shadowmapradius, int
        { 399, 2 },  // /shadowmapheight, int
        { 400, 2 },  // /shadowmapdist, int
        { 401, 2 },  // /fpshadowmap, int
        { 402, 2 },  // /shadowmapprecision, int
        { 403, 2 },  // /shadowmapintensity, int
        { 404, 2 },  // /blurshadowmap, int
        { 405, 2 },  // /blursmsigma, int
        { 406, 2 },  // /shadowmapangle, int
        { 407, 2 },  // /shadowmapbias, int
        { 408, 2 },  // /shadowmappeelbias, int
        { 409, 2 },  // /smdepthpeel, int
        { 410, 2 },  // /smoothshadowmappeel, int
        { 411, 2 },  // /debugsm, int
        { 412, 2 },  // /sound/soundvol, int
        { 413, 2 },  // /sound/musicvol, int
        { 414, 2 },  // /sound/soundchans, int
        { 415, 2 },  // /sound/soundfreq, int
        { 416, 2 },  // /sound/soundbufferlen, int
        { 417, 2 },  // /sound/stereo, int
        { 418, 2 },  // /sound/maxsoundradius, int
        { 419, 2 },  // /sound/maxsoundsatonce, int
        { 420, 2 },  // /sound/dbgsound, int
        { 421, 2 },  // /sound/mumble, int
        { 422, 2 },  // /waterreflect, int
        { 423, 2 },  // /waterrefract, int
        { 424, 2 },  // /waterenvmap, int
        { 425, 2 },  // /waterfallrefract, int
        { 426, 2 },  // /watersubdiv, int
        { 427, 2 },  // /waterlod, int
        { 428, 2 },  // /vertwater, int
        { 429, 2 },  // /reflectdist, int
        { 430, 2 },  // /waterfog, int
        { 431, 2 },  // /waterspec, int
        { 432, 2 },  // /water2fog, int
        { 433, 2 },  // /water2spec, int
        { 434, 2 },  // /water3fog, int
        { 435, 2 },  // /water3spec, int
        { 436, 2 },  // /water4fog, int
        { 437, 2 },  // /water4spec, int
        { 438, 2 },  // /lavafog, int
        { 439, 2 },  // /lava2fog, int
        { 440, 2 },  // /lava3fog, int
        { 441, 2 },  // /lava4fog, int
        { 442, 2 },  // /oqwater, int
        { 443, 2 },  // /waterfade, int
        { 444, 2 },  // /reflectsize, int
        { 445, 2 },  // /maxreflect, int
        { 446, 2 },  // /maskreflect, int
        { 447, 2 },  // /reflectscissor, int
        { 448, 2 },  // /reflectvfc, int
        { 449, 2 },  // /refractclear, int
        { 450, 2 },  // /mapversion, int
        { 451, 2 },  // /worldscale, int
        { 452, 2 },  // /worldsize, int
        { 453, 0 },  // /maptitle, char *
        { 454, 2 },  // /octaentsize, int
        { 455, 2 },  // /entselradius, int
        { 456, 2 },  // /entediting, int
        { 457, 2 },  // /attachradius, int
        { 458, 2 },  // /entselsnap, int
        { 459, 2 },  // /entmovingshadow, int
        { 460, 2 },  // /showentradius, int
        { 461, 2 },  // /entitysurf, int
        { 462, 2 },  // /entautoviewdist, int
        { 463, 2 },  // /entdrop, int
        { 464, 2 },  // /savebak, int
        { 465, 2 },  // /dbgvars, int
        { 466, 0 },  // /mapdir, char *
        { 467, 0 },  // /texturedir, char *
        { 468, 0 },  // /skyboxdir, char *
        { 469, 0 },  // /interfacedir, char *
        { 470, 0 },  // /icondir, char *
        { 471, 0 },  // /sounddir, char *
        { 472, 0 },  // /musicdir, char *
        { 473, 2 },  // /ai/aidebug, int
        { 474, 2 },  // /ai/aiforcegun, int
        { 475, 2 },  // /ai/showwaypoints, int
        { 476, 2 },  // /ai/showwaypointsradius, int
        { 477, 2 },  // /game/minradarscale, int
        { 478, 2 },  // /game/maxradarscale, int
        { 479, 2 },  // /game/radarteammates, int
        { 480, 1 },  // /game/minimapalpha, float
        { 481, 0 },  // /game/radardir, char *
        { 482, 2 },  // /game/capturetether, int
        { 483, 2 },  // /game/autorepammo, int
        { 484, 2 },  // /game/basenumbers, int
        { 485, 2 },  // /game/showbombs, int
        { 486, 2 },  // /game/showbombradius, int
        { 487, 2 },  // /game/showbombdelay, int
        { 488, 2 },  // /game/showminimapobstacles, int
        { 489, 2 },  // /game/deadpush, int
        { 490, 2 },  // /game/autoauth, int
        { 491, 2 },  // /entities/triggerstate, int
        { 492, 2 },  // /game/smoothmove, int
        { 493, 2 },  // /game/smoothdist, int
        { 494, 2 },  // /game/slowmosp, int
        { 495, 2 },  // /game/spawnwait, int
        { 496, 2 },  // /game/hitsound, int
        { 497, 2 },  // /game/deathscore, int
        { 498, 2 },  // /game/teamcolorfrags, int
        { 499, 2 },  // /game/showmodeinfo, int
        { 500, 2 },  // /game/teamcolortext, int
        { 501, 2 },  // /game/ammohud, int
        { 502, 2 },  // /game/teamcrosshair, int
        { 503, 2 },  // /game/hitcrosshair, int
        { 504, 2 },  // /game/skill, int
        { 505, 2 },  // /game/killsendsp, int
        { 506, 2 },  // /game/ragdoll, int
        { 507, 2 },  // /game/ragdollmillis, int
        { 508, 2 },  // /game/ragdollfade, int
        { 509, 2 },  // /game/playermodel, int
        { 510, 2 },  // /game/forceplayermodels, int
        { 511, 2 },  // /game/hidedead, int
        { 512, 2 },  // /game/testquad, int
        { 513, 2 },  // /game/testarmour, int
        { 514, 2 },  // /game/testteam, int
        { 515, 2 },  // /game/teamskins, int
        { 516, 2 },  // /game/hudgun, int
        { 517, 2 },  // /game/hudgunsway, int
        { 518, 2 },  // /game/teamhudguns, int
        { 519, 2 },  // /game/chainsawhudgun, int
        { 520, 2 },  // /game/testhudgun, int
        { 521, 1 },  // /game/swaystep, float
        { 522, 1 },  // /game/swayside, float
        { 523, 1 },  // /game/swayup, float
        { 524, 0 },  // /game/hudgunsdir, char *
        { 525, 2 },  // /game/scoreboard2d, int
        { 526, 2 },  // /game/showservinfo, int
        { 527, 2 },  // /game/showclientnum, int
        { 528, 2 },  // /game/showpj, int
        { 529, 2 },  // /game/showping, int
        { 530, 2 },  // /game/showspectators, int
        { 531, 2 },  // /game/showflags, int
        { 532, 2 },  // /game/showfrags, int
        { 533, 2 },  // /game/showaccuracy, int
        { 534, 2 },  // /game/highlightscore, int
        { 535, 2 },  // /game/showconnecting, int
        { 536, 2 },  // /game/showscoreboard, int
        { 537, 2 },  // /server/lockmaprotation, int
        { 538, 2 },  // /server/maxdemos, int
        { 539, 2 },  // /server/maxdemosize, int
        { 540, 2 },  // /server/restrictdemos, int
        { 541, 2 },  // /server/restrictpausegame, int
        { 542, 2 },  // /server/restrictgamespeed, int
        { 543, 2 },  // /server/restrictpersistteams, int
        { 544, 0 },  // /server/serverdesc, char *
        { 545, 0 },  // /server/serverpass, char *
        { 546, 0 },  // /server/adminpass, char *
        { 547, 2 },  // /server/publicserver, int
        { 548, 0 },  // /server/servermotd, char *
        { 549, 2 },  // /server/spectatemodifiedmap, int
        { 550, 2 },  // /server/ctftkpenalty, int
        { 551, 0 },  // /server/serverauth, char *
        { 552, 2 },  // /server/modifiedmapspectator, int
        { 553, 2 },  // /server/extinfoip, int
        { 554, 2 },  // /server/aiman/botlimit, int
        { 555, 2 },  // /server/aiman/serverbotbalance, int
        { 556, 2 },  // /ai/dropwaypoints, int
        { 557, 2 },  // /game/maxdebris, int
        { 558, 2 },  // /game/maxbarreldebris, int
        { 559, 2 },  // /game/blood, int
        { 560, 2 },  // /game/muzzleflash, int
        { 561, 2 },  // /game/muzzlelight, int
        { 562, 2 },  // /game/bombcolliderad, int
        { 563, 2 },  // /game/bombbarrier, int
        { 564, 2 },  // /dbggz, int
        { 565, 2 },  // /dbgzip, int
        { 566, 2 },  // /dbgdds, int
        { 567, 2 },  // /envmapsize, int
        { 568, 2 },  // /envmapradius, int
        { 569, 2 },  // /aaenvmap, int
        { 570, 2 },  // /compresspng, int
        { 571, 2 },  // /compresstga, int
        { 572, 2 },  // /screenshotformat, int
        { 573, 0 },  // /screenshotdir, char *
        { 574, 2 },  // /autocompactvslots, int
        { 575, 2 },  // /hwtexsize, int
        { 576, 2 },  // /hwcubetexsize, int
        { 577, 2 },  // /hwmaxaniso, int
        { 578, 2 },  // /maxtexsize, int
        { 579, 2 },  // /reducefilter, int
        { 580, 2 },  // /texreduce, int
        { 581, 2 },  // /trilinear, int
        { 582, 2 },  // /bilinear, int
        { 583, 2 },  // /aniso, int
        { 584, 2 },  // /texcompress, int
        { 585, 2 },  // /texcompressquality, int
        { 586, 2 },  // /usenp2, int
        { 587, 2 },  // /usedds, int
        { 588, 2 },  // /scaledds, int
    
    };

} client_treedata;

} } // namespace inexor::rpc
