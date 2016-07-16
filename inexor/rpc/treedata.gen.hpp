// This file gets generated!
// Do not modify it directly but its corresponding template file instead! 

#pragma once

#include <unordered_map>

#include <boost/variant.hpp>
#include "inexor/rpc/treedata.gen.grpc.pb.h"

#include "inexor/rpc/SharedTree.hpp"
#include "inexor/rpc/RpcSubsystem.hpp"


// List of extern SharedVar declarations
namespace entities { 
    extern SharedVar<int> triggerstate;
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
namespace game { 
    extern SharedVar<int> skill;
 }
namespace game { 
    extern SharedVar<int> killsendsp;
 }
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


    extern SharedVar<int> optmats;


    extern SharedVar<int> showmat;


    extern SharedVar<int> glassenv;


    extern SharedVar<int> waterfallenv;


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


    extern SharedVar<int> dbgalias;


    extern SharedVar<int> showblobs;


    extern SharedVar<int> blobintensity;


    extern SharedVar<int> blobheight;


    extern SharedVar<int> blobfadelow;


    extern SharedVar<int> blobfadehigh;


    extern SharedVar<int> blobmargin;


    extern SharedVar<int> dbgblob;


    extern SharedVar<int> blobstattris;


    extern SharedVar<int> blobdyntris;


    extern SharedVar<int> savebak;


    extern SharedVar<int> dbgvars;


    extern SharedVar<int> reservevpparams;


    extern SharedVar<int> maxvsuniforms;


    extern SharedVar<int> maxfsuniforms;


    extern SharedVar<int> maxvaryings;


    extern SharedVar<int> dbgshader;


    extern SharedVar<int> dbgubo;


    extern SharedVar<int> shaderprecision;


    extern SharedVar<int> defershaders;


    extern SharedVar<int> shaderdetail;


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


    extern SharedVar<int> guiautotab;


    extern SharedVar<int> guiclicktab;


    extern SharedVar<int> guifadein;


    extern SharedVar<int> guipushdist;


    extern SharedVar<float> guisens;


    extern SharedVar<int> useguifollow;


    extern SharedVar<int> usegui2d;


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


    extern SharedVar<int> maxpvsblocker;


    extern SharedVar<int> pvsleafsize;


    extern SharedVar<int> pvsthreads;


    extern SharedVar<int> lockpvs;


    extern SharedVar<int> usepvs;


    extern SharedVar<int> usewaterpvs;


    extern SharedVar<int> mipvis;


    extern SharedVar<int> maxmerge;


    extern SharedVar<int> minface;


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


    extern SharedVar<int> maxdecaltris;


    extern SharedVar<int> decalfade;


    extern SharedVar<int> dbgdec;


    extern SharedVar<int> showdecals;


    extern SharedVar<int> maxdecaldistance;


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


    extern SharedVar<int> rate;


    extern SharedVar<int> throttle_interval;


    extern SharedVar<int> throttle_accel;


    extern SharedVar<int> throttle_decel;


    extern SharedVar<char *> connectname;


    extern SharedVar<int> connectport;


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


    extern SharedVar<int> dynentsize;


    extern SharedVar<int> maxroll;


    extern SharedVar<float> straferoll;


    extern SharedVar<float> faderoll;


    extern SharedVar<int> floatspeed;


    extern SharedVar<int> physinterp;


    extern SharedVar<int> lerpangle;


    extern SharedVar<int> lerpsubdiv;


    extern SharedVar<int> lerpsubdivsize;


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


    extern SharedVar<int> maxdynlights;


    extern SharedVar<int> dynlightdist;


    extern SharedVar<int> blendpaintmode;


    extern SharedVar<int> paintblendmapdelay;


    extern SharedVar<int> paintblendmapinterval;


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


    extern SharedVar<int> crosshairfx;


    extern SharedVar<int> crosshaircolors;


    extern SharedVar<char *> crosshairdir;


    extern SharedVar<int> wallclock;


    extern SharedVar<int> wallclock24;


    extern SharedVar<int> wallclocksecs;


    extern SharedVar<int> showfps;


    extern SharedVar<int> showfpsrange;


    extern SharedVar<int> showeditstats;


    extern SharedVar<int> statrate;


    extern SharedVar<float> conscale;


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

    extern SharedVar<int> debugvbo;


    extern SharedVar<int> maxvbosize;


    extern SharedVar<int> filltjoints;


    extern SharedVar<int> vafacemax;


    extern SharedVar<int> vafacemin;


    extern SharedVar<int> vacubesize;


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


    extern SharedVar<int> glaresize;


    extern SharedVar<int> glare;


    extern SharedVar<int> blurglare;


    extern SharedVar<int> blurglaresigma;


    extern SharedVar<int> debugglare;


    extern SharedVar<float> glarescale;


    extern SharedVar<int> compresspng;


    extern SharedVar<int> compresstga;


    extern SharedVar<int> screenshotformat;


    extern SharedVar<char *> screenshotdir;


    extern SharedVar<int> usedds;


    extern SharedVar<int> scaledds;


    extern SharedVar<int> autocompactvslots;


    extern SharedVar<int> dbgdds;


    extern SharedVar<int> envmapsize;


    extern SharedVar<int> envmapradius;


    extern SharedVar<int> aaenvmap;


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


    extern SharedVar<char *> mapdir;


    extern SharedVar<char *> texturedir;


    extern SharedVar<char *> skyboxdir;


    extern SharedVar<char *> interfacedir;


    extern SharedVar<char *> icondir;


    extern SharedVar<char *> sounddir;


    extern SharedVar<char *> musicdir;


    extern SharedVar<int> dbggz;


    extern SharedVar<int> dbgzip;



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
        ::entities::triggerstate.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__entities_triggerstate(newvalue);
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
        ::dbgalias.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__dbgalias(newvalue);
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
        ::inexor::rendering::screen::scr_w.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_rendering_screen_scr_w(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::rendering::screen::scr_h.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_rendering_screen_scr_h(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::rendering::screen::colorbits.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_rendering_screen_colorbits(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::rendering::screen::depthbits.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_rendering_screen_depthbits(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::rendering::screen::stencilbits.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_rendering_screen_stencilbits(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::rendering::screen::vsync.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_rendering_screen_vsync(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::rendering::screen::vsynctear.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_rendering_screen_vsynctear(newvalue);
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
                val.set__inexor_rendering_screen_fullscreen(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::rendering::screen::gamma.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_rendering_screen_gamma(newvalue);
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
        ::inexor::sound::soundvol.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_sound_soundvol(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::musicvol.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_sound_musicvol(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::soundchans.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_sound_soundchans(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::soundfreq.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_sound_soundfreq(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::soundbufferlen.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_sound_soundbufferlen(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::stereo.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_sound_stereo(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::maxsoundradius.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_sound_maxsoundradius(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::maxsoundsatonce.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_sound_maxsoundsatonce(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::dbgsound.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_sound_dbgsound(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
        ::inexor::sound::mumble.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__inexor_sound_mumble(newvalue);
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
        ::autocompactvslots.onChange.connect([](const int oldvalue, const int newvalue)
            {
                inexor::tree::TreeNodeChanged val;
                val.set__autocompactvslots(newvalue);
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

    }

    void syncall()
    {
        // TODO: Dont call by type but by reference if not a ptr: *or& -> {cpp_observer_type}
        ::entities::triggerstate.sync();
        ::game::maxdebris.sync();
        ::game::maxbarreldebris.sync();
        ::game::blood.sync();
        ::game::muzzleflash.sync();
        ::game::muzzlelight.sync();
        ::game::bombcolliderad.sync();
        ::game::bombbarrier.sync();
        ::game::skill.sync();
        ::game::killsendsp.sync();
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
        ::optmats.sync();
        ::showmat.sync();
        ::glassenv.sync();
        ::waterfallenv.sync();
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
        ::dbgalias.sync();
        ::showblobs.sync();
        ::blobintensity.sync();
        ::blobheight.sync();
        ::blobfadelow.sync();
        ::blobfadehigh.sync();
        ::blobmargin.sync();
        ::dbgblob.sync();
        ::blobstattris.sync();
        ::blobdyntris.sync();
        ::savebak.sync();
        ::dbgvars.sync();
        ::reservevpparams.sync();
        ::maxvsuniforms.sync();
        ::maxfsuniforms.sync();
        ::maxvaryings.sync();
        ::dbgshader.sync();
        ::dbgubo.sync();
        ::shaderprecision.sync();
        ::defershaders.sync();
        ::shaderdetail.sync();
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
        ::guiautotab.sync();
        ::guiclicktab.sync();
        ::guifadein.sync();
        ::guipushdist.sync();
        ::guisens.sync();
        ::useguifollow.sync();
        ::usegui2d.sync();
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
        ::maxpvsblocker.sync();
        ::pvsleafsize.sync();
        ::pvsthreads.sync();
        ::lockpvs.sync();
        ::usepvs.sync();
        ::usewaterpvs.sync();
        ::mipvis.sync();
        ::maxmerge.sync();
        ::minface.sync();
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
        ::maxdecaltris.sync();
        ::decalfade.sync();
        ::dbgdec.sync();
        ::showdecals.sync();
        ::maxdecaldistance.sync();
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
        ::rate.sync();
        ::throttle_interval.sync();
        ::throttle_accel.sync();
        ::throttle_decel.sync();
        ::connectname.sync();
        ::connectport.sync();
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
        ::dynentsize.sync();
        ::maxroll.sync();
        ::straferoll.sync();
        ::faderoll.sync();
        ::floatspeed.sync();
        ::physinterp.sync();
        ::lerpangle.sync();
        ::lerpsubdiv.sync();
        ::lerpsubdivsize.sync();
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
        ::maxdynlights.sync();
        ::dynlightdist.sync();
        ::blendpaintmode.sync();
        ::paintblendmapdelay.sync();
        ::paintblendmapinterval.sync();
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
        ::crosshairfx.sync();
        ::crosshaircolors.sync();
        ::crosshairdir.sync();
        ::wallclock.sync();
        ::wallclock24.sync();
        ::wallclocksecs.sync();
        ::showfps.sync();
        ::showfpsrange.sync();
        ::showeditstats.sync();
        ::statrate.sync();
        ::conscale.sync();
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
        ::debugvbo.sync();
        ::maxvbosize.sync();
        ::filltjoints.sync();
        ::vafacemax.sync();
        ::vafacemin.sync();
        ::vacubesize.sync();
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
        ::glaresize.sync();
        ::glare.sync();
        ::blurglare.sync();
        ::blurglaresigma.sync();
        ::debugglare.sync();
        ::glarescale.sync();
        ::compresspng.sync();
        ::compresstga.sync();
        ::screenshotformat.sync();
        ::screenshotdir.sync();
        ::usedds.sync();
        ::scaledds.sync();
        ::autocompactvslots.sync();
        ::dbgdds.sync();
        ::envmapsize.sync();
        ::envmapradius.sync();
        ::aaenvmap.sync();
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
        ::mapdir.sync();
        ::texturedir.sync();
        ::skyboxdir.sync();
        ::interfacedir.sync();
        ::icondir.sync();
        ::sounddir.sync();
        ::musicdir.sync();
        ::dbggz.sync();
        ::dbgzip.sync();

    }

    /// (proto)index -> pointer to the to-be-updated-variable.
    const std::unordered_map<int64, boost::variant<SharedVar<char *>*, SharedVar<int>*, SharedVar<float>*>> cppvar_pointer_map
    {
        // { index, pointer_to_the_changed_var (see net2maintupel::ptr2var) }
        { 1, &::entities::triggerstate },
        { 2, &::game::maxdebris },
        { 3, &::game::maxbarreldebris },
        { 4, &::game::blood },
        { 5, &::game::muzzleflash },
        { 6, &::game::muzzlelight },
        { 7, &::game::bombcolliderad },
        { 8, &::game::bombbarrier },
        { 9, &::game::skill },
        { 10, &::game::killsendsp },
        { 11, &::ai::aidebug },
        { 12, &::ai::aiforcegun },
        { 13, &::ai::showwaypoints },
        { 14, &::ai::showwaypointsradius },
        { 15, &::game::minradarscale },
        { 16, &::game::maxradarscale },
        { 17, &::game::radarteammates },
        { 18, &::game::minimapalpha },
        { 19, &::game::radardir },
        { 20, &::game::capturetether },
        { 21, &::game::autorepammo },
        { 22, &::game::basenumbers },
        { 23, &::game::showbombs },
        { 24, &::game::showbombradius },
        { 25, &::game::showbombdelay },
        { 26, &::game::showminimapobstacles },
        { 27, &::game::deadpush },
        { 28, &::game::autoauth },
        { 29, &::game::smoothmove },
        { 30, &::game::smoothdist },
        { 31, &::game::slowmosp },
        { 32, &::game::spawnwait },
        { 33, &::game::hitsound },
        { 34, &::game::deathscore },
        { 35, &::game::teamcolorfrags },
        { 36, &::game::showmodeinfo },
        { 37, &::game::teamcolortext },
        { 38, &::game::ammohud },
        { 39, &::game::teamcrosshair },
        { 40, &::game::hitcrosshair },
        { 41, &::server::lockmaprotation },
        { 42, &::server::maxdemos },
        { 43, &::server::maxdemosize },
        { 44, &::server::restrictdemos },
        { 45, &::server::restrictpausegame },
        { 46, &::server::restrictgamespeed },
        { 47, &::server::restrictpersistteams },
        { 48, &::server::serverdesc },
        { 49, &::server::serverpass },
        { 50, &::server::adminpass },
        { 51, &::server::publicserver },
        { 52, &::server::servermotd },
        { 53, &::server::spectatemodifiedmap },
        { 54, &::server::ctftkpenalty },
        { 55, &::server::serverauth },
        { 56, &::server::modifiedmapspectator },
        { 57, &::server::extinfoip },
        { 58, &::server::aiman::botlimit },
        { 59, &::server::aiman::serverbotbalance },
        { 60, &::ai::dropwaypoints },
        { 61, &::game::ragdoll },
        { 62, &::game::ragdollmillis },
        { 63, &::game::ragdollfade },
        { 64, &::game::playermodel },
        { 65, &::game::forceplayermodels },
        { 66, &::game::hidedead },
        { 67, &::game::testquad },
        { 68, &::game::testarmour },
        { 69, &::game::testteam },
        { 70, &::game::teamskins },
        { 71, &::game::hudgun },
        { 72, &::game::hudgunsway },
        { 73, &::game::teamhudguns },
        { 74, &::game::chainsawhudgun },
        { 75, &::game::testhudgun },
        { 76, &::game::swaystep },
        { 77, &::game::swayside },
        { 78, &::game::swayup },
        { 79, &::game::hudgunsdir },
        { 80, &::game::scoreboard2d },
        { 81, &::game::showservinfo },
        { 82, &::game::showclientnum },
        { 83, &::game::showpj },
        { 84, &::game::showping },
        { 85, &::game::showspectators },
        { 86, &::game::showflags },
        { 87, &::game::showfrags },
        { 88, &::game::showaccuracy },
        { 89, &::game::highlightscore },
        { 90, &::game::showconnecting },
        { 91, &::game::showscoreboard },
        { 92, &::oqfrags },
        { 93, &::oqwait },
        { 94, &::oqmm },
        { 95, &::outline },
        { 96, &::outlinecolour },
        { 97, &::dtoutline },
        { 98, &::blendbrushcolor },
        { 99, &::oqdist },
        { 100, &::zpass },
        { 101, &::glowpass },
        { 102, &::envpass },
        { 103, &::batchgeom },
        { 104, &::causticdir },
        { 105, &::causticscale },
        { 106, &::causticmillis },
        { 107, &::caustics },
        { 108, &::oqgeom },
        { 109, &::optmats },
        { 110, &::showmat },
        { 111, &::glassenv },
        { 112, &::waterfallenv },
        { 113, &::lightprecision },
        { 114, &::lighterror },
        { 115, &::bumperror },
        { 116, &::lightlod },
        { 117, &::sunlightyaw },
        { 118, &::sunlightpitch },
        { 119, &::skytexturelight },
        { 120, &::lmshadows_ },
        { 121, &::lmaa_ },
        { 122, &::lerptjoints_ },
        { 123, &::lmao_ },
        { 124, &::lightcompress },
        { 125, &::ambientocclusion },
        { 126, &::ambientocclusionradius },
        { 127, &::debugao },
        { 128, &::blurlms },
        { 129, &::blurskylight },
        { 130, &::edgetolerance },
        { 131, &::adaptivesample },
        { 132, &::lightcachesize },
        { 133, &::lightthreads },
        { 134, &::patchnormals },
        { 135, &::fullbright },
        { 136, &::fullbrightlevel },
        { 137, &::roundlightmaptex },
        { 138, &::batchlightmaps },
        { 139, &::dragging },
        { 140, &::gridpower },
        { 141, &::passthroughsel },
        { 142, &::editing },
        { 143, &::selectcorners },
        { 144, &::hmapedit },
        { 145, &::gridlookup },
        { 146, &::passthroughcube },
        { 147, &::undomegs },
        { 148, &::nompedit },
        { 149, &::prefabdir },
        { 150, &::brushx },
        { 151, &::brushy },
        { 152, &::invalidcubeguard },
        { 153, &::selectionsurf },
        { 154, &::usevdelta },
        { 155, &::allfaces },
        { 156, &::texguiwidth },
        { 157, &::texguiheight },
        { 158, &::texguitime },
        { 159, &::texgui2d },
        { 160, &::dbgalias },
        { 161, &::showblobs },
        { 162, &::blobintensity },
        { 163, &::blobheight },
        { 164, &::blobfadelow },
        { 165, &::blobfadehigh },
        { 166, &::blobmargin },
        { 167, &::dbgblob },
        { 168, &::blobstattris },
        { 169, &::blobdyntris },
        { 170, &::savebak },
        { 171, &::dbgvars },
        { 172, &::reservevpparams },
        { 173, &::maxvsuniforms },
        { 174, &::maxfsuniforms },
        { 175, &::maxvaryings },
        { 176, &::dbgshader },
        { 177, &::dbgubo },
        { 178, &::shaderprecision },
        { 179, &::defershaders },
        { 180, &::shaderdetail },
        { 181, &::skybox },
        { 182, &::skyboxcolour },
        { 183, &::spinsky },
        { 184, &::yawsky },
        { 185, &::cloudbox },
        { 186, &::cloudboxcolour },
        { 187, &::cloudboxalpha },
        { 188, &::spinclouds },
        { 189, &::yawclouds },
        { 190, &::cloudclip },
        { 191, &::cloudlayer },
        { 192, &::cloudoffsetx },
        { 193, &::cloudoffsety },
        { 194, &::cloudscrollx },
        { 195, &::cloudscrolly },
        { 196, &::cloudscale },
        { 197, &::spincloudlayer },
        { 198, &::yawcloudlayer },
        { 199, &::cloudheight },
        { 200, &::cloudfade },
        { 201, &::cloudalpha },
        { 202, &::cloudsubdiv },
        { 203, &::cloudcolour },
        { 204, &::fogdomeheight },
        { 205, &::fogdomemin },
        { 206, &::fogdomemax },
        { 207, &::fogdomecap },
        { 208, &::fogdomeclip },
        { 209, &::sparklyfix },
        { 210, &::showsky },
        { 211, &::clipsky },
        { 212, &::clampsky },
        { 213, &::fogdomeclouds },
        { 214, &::useskytexture },
        { 215, &::guiautotab },
        { 216, &::guiclicktab },
        { 217, &::guifadein },
        { 218, &::guipushdist },
        { 219, &::guisens },
        { 220, &::useguifollow },
        { 221, &::usegui2d },
        { 222, &::grass },
        { 223, &::dbggrass },
        { 224, &::grassdist },
        { 225, &::grasstaper },
        { 226, &::grassstep },
        { 227, &::grassheight },
        { 228, &::grassanimmillis },
        { 229, &::grassanimscale },
        { 230, &::grassscale },
        { 231, &::grassalpha },
        { 232, &::modeldir },
        { 233, &::oqdynent },
        { 234, &::animationinterpolationtime },
        { 235, &::ragdolltimestepmin },
        { 236, &::ragdolltimestepmax },
        { 237, &::ragdollrotfric },
        { 238, &::ragdollrotfricstop },
        { 239, &::ragdollconstrain },
        { 240, &::ragdollbodyfric },
        { 241, &::ragdollbodyfricscale },
        { 242, &::ragdollwaterfric },
        { 243, &::ragdollgroundfric },
        { 244, &::ragdollairfric },
        { 245, &::ragdollunstick },
        { 246, &::ragdollexpireoffset },
        { 247, &::ragdollwaterexpireoffset },
        { 248, &::ragdolleyesmooth },
        { 249, &::ragdolleyesmoothmillis },
        { 250, &::envmapmodels },
        { 251, &::bumpmodels },
        { 252, &::fullbrightmodels },
        { 253, &::gpuskel },
        { 254, &::maxskelanimdata },
        { 255, &::testtags },
        { 256, &::showboundingbox },
        { 257, &::maxmodelradiusdistance },
        { 258, &::animoverride },
        { 259, &::testanims },
        { 260, &::testpitch },
        { 261, &::maxpvsblocker },
        { 262, &::pvsleafsize },
        { 263, &::pvsthreads },
        { 264, &::lockpvs },
        { 265, &::usepvs },
        { 266, &::usewaterpvs },
        { 267, &::mipvis },
        { 268, &::maxmerge },
        { 269, &::minface },
        { 270, &::waterreflect },
        { 271, &::waterrefract },
        { 272, &::waterenvmap },
        { 273, &::waterfallrefract },
        { 274, &::watersubdiv },
        { 275, &::waterlod },
        { 276, &::vertwater },
        { 277, &::reflectdist },
        { 278, &::waterfog },
        { 279, &::waterspec },
        { 280, &::water2fog },
        { 281, &::water2spec },
        { 282, &::water3fog },
        { 283, &::water3spec },
        { 284, &::water4fog },
        { 285, &::water4spec },
        { 286, &::lavafog },
        { 287, &::lava2fog },
        { 288, &::lava3fog },
        { 289, &::lava4fog },
        { 290, &::oqwater },
        { 291, &::waterfade },
        { 292, &::reflectsize },
        { 293, &::maxreflect },
        { 294, &::maskreflect },
        { 295, &::reflectscissor },
        { 296, &::reflectvfc },
        { 297, &::refractclear },
        { 298, &::maxdecaltris },
        { 299, &::decalfade },
        { 300, &::dbgdec },
        { 301, &::showdecals },
        { 302, &::maxdecaldistance },
        { 303, &::shadowmap },
        { 304, &::shadowmapsize },
        { 305, &::shadowmapradius },
        { 306, &::shadowmapheight },
        { 307, &::shadowmapdist },
        { 308, &::fpshadowmap },
        { 309, &::shadowmapprecision },
        { 310, &::shadowmapintensity },
        { 311, &::blurshadowmap },
        { 312, &::blursmsigma },
        { 313, &::shadowmapangle },
        { 314, &::shadowmapbias },
        { 315, &::shadowmappeelbias },
        { 316, &::smdepthpeel },
        { 317, &::smoothshadowmappeel },
        { 318, &::debugsm },
        { 319, &::inexor::rendering::screen::scr_w },
        { 320, &::inexor::rendering::screen::scr_h },
        { 321, &::inexor::rendering::screen::colorbits },
        { 322, &::inexor::rendering::screen::depthbits },
        { 323, &::inexor::rendering::screen::stencilbits },
        { 324, &::inexor::rendering::screen::vsync },
        { 325, &::inexor::rendering::screen::vsynctear },
        { 326, &::fsaa },
        { 327, &::background },
        { 328, &::logo },
        { 329, &::userelativemouse },
        { 330, &::inexor::rendering::screen::fullscreen },
        { 331, &::inexor::rendering::screen::gamma },
        { 332, &::menufps },
        { 333, &::maxfps },
        { 334, &::clockerror },
        { 335, &::clockfix },
        { 336, &::numcpus },
        { 337, &::rate },
        { 338, &::throttle_interval },
        { 339, &::throttle_accel },
        { 340, &::throttle_decel },
        { 341, &::connectname },
        { 342, &::connectport },
        { 343, &::maxcon },
        { 344, &::confading },
        { 345, &::fullconsole },
        { 346, &::consize },
        { 347, &::miniconsize },
        { 348, &::miniconwidth },
        { 349, &::confade },
        { 350, &::miniconfade },
        { 351, &::fullconsize },
        { 352, &::confilter },
        { 353, &::fullconfilter },
        { 354, &::miniconfilter },
        { 355, &::maxhistory },
        { 356, &::dynentsize },
        { 357, &::maxroll },
        { 358, &::straferoll },
        { 359, &::faderoll },
        { 360, &::floatspeed },
        { 361, &::physinterp },
        { 362, &::lerpangle },
        { 363, &::lerpsubdiv },
        { 364, &::lerpsubdivsize },
        { 365, &::menudistance },
        { 366, &::menuautoclose },
        { 367, &::applydialog },
        { 368, &::mainmenu },
        { 369, &::dbgmovie },
        { 370, &::movieaccelblit },
        { 371, &::movieaccelyuv },
        { 372, &::movieaccel },
        { 373, &::moviesync },
        { 374, &::movieminquality },
        { 375, &::moview },
        { 376, &::movieh },
        { 377, &::moviefps },
        { 378, &::moviesound },
        { 379, &::maxdynlights },
        { 380, &::dynlightdist },
        { 381, &::blendpaintmode },
        { 382, &::paintblendmapdelay },
        { 383, &::paintblendmapinterval },
        { 384, &::glversion },
        { 385, &::glslversion },
        { 386, &::ati_skybox_bug },
        { 387, &::ati_minmax_bug },
        { 388, &::ati_cubemap_bug },
        { 389, &::intel_vertexarray_bug },
        { 390, &::intel_mapbufferrange_bug },
        { 391, &::minimizetcusage },
        { 392, &::useubo },
        { 393, &::usetexcompress },
        { 394, &::rtscissor },
        { 395, &::blurtile },
        { 396, &::rtsharefb },
        { 397, &::dbgexts },
        { 398, &::wireframe },
        { 399, &::zoominvel },
        { 400, &::zoomoutvel },
        { 401, &::zoomfov },
        { 402, &::fov },
        { 403, &::followfov },
        { 404, &::avatarzoomfov },
        { 405, &::avatarfov },
        { 406, &::avatardepth },
        { 407, &::forceaspect },
        { 408, &::zoom },
        { 409, &::zoomsens },
        { 410, &::zoomaccel },
        { 411, &::zoomautosens },
        { 412, &::sensitivity },
        { 413, &::sensitivityscale },
        { 414, &::invmouse },
        { 415, &::mouseaccel },
        { 416, &::thirdperson },
        { 417, &::thirdpersondistance },
        { 418, &::thirdpersonup },
        { 419, &::thirdpersonside },
        { 420, &::nearplane },
        { 421, &::reflectclip },
        { 422, &::reflectclipavatar },
        { 423, &::polygonoffsetfactor },
        { 424, &::polygonoffsetunits },
        { 425, &::depthoffset },
        { 426, &::fog },
        { 427, &::skyboxglare },
        { 428, &::reflectmms },
        { 429, &::refractsky },
        { 430, &::modelpreviewfov },
        { 431, &::modelpreviewpitch },
        { 432, &::minimapheight },
        { 433, &::minimapclip },
        { 434, &::minimapsize },
        { 435, &::motionblur },
        { 436, &::motionblurmillis },
        { 437, &::motionblurscale },
        { 438, &::usedamagecompass },
        { 439, &::damagecompassfade },
        { 440, &::damagecompasssize },
        { 441, &::damagecompassalpha },
        { 442, &::damagecompassmin },
        { 443, &::damagecompassmax },
        { 444, &::damagescreen },
        { 445, &::damagescreenfactor },
        { 446, &::damagescreenalpha },
        { 447, &::damagescreenfade },
        { 448, &::damagescreenmin },
        { 449, &::damagescreenmax },
        { 450, &::hidestats },
        { 451, &::hidehud },
        { 452, &::crosshairsize },
        { 453, &::crosshairfx },
        { 454, &::crosshaircolors },
        { 455, &::crosshairdir },
        { 456, &::wallclock },
        { 457, &::wallclock24 },
        { 458, &::wallclocksecs },
        { 459, &::showfps },
        { 460, &::showfpsrange },
        { 461, &::showeditstats },
        { 462, &::statrate },
        { 463, &::conscale },
        { 464, &::mapversion },
        { 465, &::worldscale },
        { 466, &::worldsize },
        { 467, &::maptitle },
        { 468, &::octaentsize },
        { 469, &::entselradius },
        { 470, &::entediting },
        { 471, &::attachradius },
        { 472, &::entselsnap },
        { 473, &::entmovingshadow },
        { 474, &::showentradius },
        { 475, &::entitysurf },
        { 476, &::entautoviewdist },
        { 477, &::entdrop },
        { 478, &::maxclients },
        { 479, &::maxdupclients },
        { 480, &::allowupdatemaster },
        { 481, &::mastername },
        { 482, &::masterport },
        { 483, &::serveruprate },
        { 484, &::serverip },
        { 485, &::serverport },
        { 486, &::searchlan },
        { 487, &::servpingrate },
        { 488, &::servpingdecay },
        { 489, &::maxservpings },
        { 490, &::autosortservers },
        { 491, &::autoupdateservers },
        { 492, &::inexor::sound::soundvol },
        { 493, &::inexor::sound::musicvol },
        { 494, &::inexor::sound::soundchans },
        { 495, &::inexor::sound::soundfreq },
        { 496, &::inexor::sound::soundbufferlen },
        { 497, &::inexor::sound::stereo },
        { 498, &::inexor::sound::maxsoundradius },
        { 499, &::inexor::sound::maxsoundsatonce },
        { 500, &::inexor::sound::dbgsound },
        { 501, &::inexor::sound::mumble },
        { 502, &::debugvbo },
        { 503, &::maxvbosize },
        { 504, &::filltjoints },
        { 505, &::vafacemax },
        { 506, &::vafacemin },
        { 507, &::vacubesize },
        { 508, &::particlesize },
        { 509, &::emitmillis },
        { 510, &::showparticles },
        { 511, &::cullparticles },
        { 512, &::replayparticles },
        { 513, &::seedmillis },
        { 514, &::dbgpcull },
        { 515, &::dbgpseed },
        { 516, &::outlinemeters },
        { 517, &::depthfxfpscale },
        { 518, &::depthfxscale },
        { 519, &::depthfxblend },
        { 520, &::depthfxpartblend },
        { 521, &::depthfxmargin },
        { 522, &::depthfxbias },
        { 523, &::fpdepthfx },
        { 524, &::depthfxemuprecision },
        { 525, &::depthfxsize },
        { 526, &::depthfx },
        { 527, &::depthfxparts },
        { 528, &::blurdepthfx },
        { 529, &::blurdepthfxsigma },
        { 530, &::depthfxscissor },
        { 531, &::debugdepthfx },
        { 532, &::flarelights },
        { 533, &::flarecutoff },
        { 534, &::flaresize },
        { 535, &::lnjittermillis },
        { 536, &::lnjitterradius },
        { 537, &::lnjitterscale },
        { 538, &::lnscrollmillis },
        { 539, &::lnscrollscale },
        { 540, &::lnblendpower },
        { 541, &::maxparticles },
        { 542, &::fewparticles },
        { 543, &::particleglare },
        { 544, &::dbgparts },
        { 545, &::maxparticledistance },
        { 546, &::maxtrail },
        { 547, &::particletext },
        { 548, &::maxparticletextdistance },
        { 549, &::glaresize },
        { 550, &::glare },
        { 551, &::blurglare },
        { 552, &::blurglaresigma },
        { 553, &::debugglare },
        { 554, &::glarescale },
        { 555, &::compresspng },
        { 556, &::compresstga },
        { 557, &::screenshotformat },
        { 558, &::screenshotdir },
        { 559, &::usedds },
        { 560, &::scaledds },
        { 561, &::autocompactvslots },
        { 562, &::dbgdds },
        { 563, &::envmapsize },
        { 564, &::envmapradius },
        { 565, &::aaenvmap },
        { 566, &::hwtexsize },
        { 567, &::hwcubetexsize },
        { 568, &::hwmaxaniso },
        { 569, &::maxtexsize },
        { 570, &::reducefilter },
        { 571, &::texreduce },
        { 572, &::trilinear },
        { 573, &::bilinear },
        { 574, &::aniso },
        { 575, &::texcompress },
        { 576, &::texcompressquality },
        { 577, &::usenp2 },
        { 578, &::mapdir },
        { 579, &::texturedir },
        { 580, &::skyboxdir },
        { 581, &::interfacedir },
        { 582, &::icondir },
        { 583, &::sounddir },
        { 584, &::musicdir },
        { 585, &::dbggz },
        { 586, &::dbgzip },
    
    };

    /// (proto)index -> Data type (cpp_type_t)
    const std::unordered_map<int64, int> index_to_type_map
    {
        // { index, enum_type(string=0,float=1,int=2) }
        { 1, 2 },  // /entities/triggerstate, int
        { 2, 2 },  // /game/maxdebris, int
        { 3, 2 },  // /game/maxbarreldebris, int
        { 4, 2 },  // /game/blood, int
        { 5, 2 },  // /game/muzzleflash, int
        { 6, 2 },  // /game/muzzlelight, int
        { 7, 2 },  // /game/bombcolliderad, int
        { 8, 2 },  // /game/bombbarrier, int
        { 9, 2 },  // /game/skill, int
        { 10, 2 },  // /game/killsendsp, int
        { 11, 2 },  // /ai/aidebug, int
        { 12, 2 },  // /ai/aiforcegun, int
        { 13, 2 },  // /ai/showwaypoints, int
        { 14, 2 },  // /ai/showwaypointsradius, int
        { 15, 2 },  // /game/minradarscale, int
        { 16, 2 },  // /game/maxradarscale, int
        { 17, 2 },  // /game/radarteammates, int
        { 18, 1 },  // /game/minimapalpha, float
        { 19, 0 },  // /game/radardir, char *
        { 20, 2 },  // /game/capturetether, int
        { 21, 2 },  // /game/autorepammo, int
        { 22, 2 },  // /game/basenumbers, int
        { 23, 2 },  // /game/showbombs, int
        { 24, 2 },  // /game/showbombradius, int
        { 25, 2 },  // /game/showbombdelay, int
        { 26, 2 },  // /game/showminimapobstacles, int
        { 27, 2 },  // /game/deadpush, int
        { 28, 2 },  // /game/autoauth, int
        { 29, 2 },  // /game/smoothmove, int
        { 30, 2 },  // /game/smoothdist, int
        { 31, 2 },  // /game/slowmosp, int
        { 32, 2 },  // /game/spawnwait, int
        { 33, 2 },  // /game/hitsound, int
        { 34, 2 },  // /game/deathscore, int
        { 35, 2 },  // /game/teamcolorfrags, int
        { 36, 2 },  // /game/showmodeinfo, int
        { 37, 2 },  // /game/teamcolortext, int
        { 38, 2 },  // /game/ammohud, int
        { 39, 2 },  // /game/teamcrosshair, int
        { 40, 2 },  // /game/hitcrosshair, int
        { 41, 2 },  // /server/lockmaprotation, int
        { 42, 2 },  // /server/maxdemos, int
        { 43, 2 },  // /server/maxdemosize, int
        { 44, 2 },  // /server/restrictdemos, int
        { 45, 2 },  // /server/restrictpausegame, int
        { 46, 2 },  // /server/restrictgamespeed, int
        { 47, 2 },  // /server/restrictpersistteams, int
        { 48, 0 },  // /server/serverdesc, char *
        { 49, 0 },  // /server/serverpass, char *
        { 50, 0 },  // /server/adminpass, char *
        { 51, 2 },  // /server/publicserver, int
        { 52, 0 },  // /server/servermotd, char *
        { 53, 2 },  // /server/spectatemodifiedmap, int
        { 54, 2 },  // /server/ctftkpenalty, int
        { 55, 0 },  // /server/serverauth, char *
        { 56, 2 },  // /server/modifiedmapspectator, int
        { 57, 2 },  // /server/extinfoip, int
        { 58, 2 },  // /server/aiman/botlimit, int
        { 59, 2 },  // /server/aiman/serverbotbalance, int
        { 60, 2 },  // /ai/dropwaypoints, int
        { 61, 2 },  // /game/ragdoll, int
        { 62, 2 },  // /game/ragdollmillis, int
        { 63, 2 },  // /game/ragdollfade, int
        { 64, 2 },  // /game/playermodel, int
        { 65, 2 },  // /game/forceplayermodels, int
        { 66, 2 },  // /game/hidedead, int
        { 67, 2 },  // /game/testquad, int
        { 68, 2 },  // /game/testarmour, int
        { 69, 2 },  // /game/testteam, int
        { 70, 2 },  // /game/teamskins, int
        { 71, 2 },  // /game/hudgun, int
        { 72, 2 },  // /game/hudgunsway, int
        { 73, 2 },  // /game/teamhudguns, int
        { 74, 2 },  // /game/chainsawhudgun, int
        { 75, 2 },  // /game/testhudgun, int
        { 76, 1 },  // /game/swaystep, float
        { 77, 1 },  // /game/swayside, float
        { 78, 1 },  // /game/swayup, float
        { 79, 0 },  // /game/hudgunsdir, char *
        { 80, 2 },  // /game/scoreboard2d, int
        { 81, 2 },  // /game/showservinfo, int
        { 82, 2 },  // /game/showclientnum, int
        { 83, 2 },  // /game/showpj, int
        { 84, 2 },  // /game/showping, int
        { 85, 2 },  // /game/showspectators, int
        { 86, 2 },  // /game/showflags, int
        { 87, 2 },  // /game/showfrags, int
        { 88, 2 },  // /game/showaccuracy, int
        { 89, 2 },  // /game/highlightscore, int
        { 90, 2 },  // /game/showconnecting, int
        { 91, 2 },  // /game/showscoreboard, int
        { 92, 2 },  // /oqfrags, int
        { 93, 2 },  // /oqwait, int
        { 94, 2 },  // /oqmm, int
        { 95, 2 },  // /outline, int
        { 96, 2 },  // /outlinecolour, int
        { 97, 2 },  // /dtoutline, int
        { 98, 2 },  // /blendbrushcolor, int
        { 99, 2 },  // /oqdist, int
        { 100, 2 },  // /zpass, int
        { 101, 2 },  // /glowpass, int
        { 102, 2 },  // /envpass, int
        { 103, 2 },  // /batchgeom, int
        { 104, 0 },  // /causticdir, char *
        { 105, 2 },  // /causticscale, int
        { 106, 2 },  // /causticmillis, int
        { 107, 2 },  // /caustics, int
        { 108, 2 },  // /oqgeom, int
        { 109, 2 },  // /optmats, int
        { 110, 2 },  // /showmat, int
        { 111, 2 },  // /glassenv, int
        { 112, 2 },  // /waterfallenv, int
        { 113, 2 },  // /lightprecision, int
        { 114, 2 },  // /lighterror, int
        { 115, 2 },  // /bumperror, int
        { 116, 2 },  // /lightlod, int
        { 117, 2 },  // /sunlightyaw, int
        { 118, 2 },  // /sunlightpitch, int
        { 119, 2 },  // /skytexturelight, int
        { 120, 2 },  // /lmshadows_, int
        { 121, 2 },  // /lmaa_, int
        { 122, 2 },  // /lerptjoints_, int
        { 123, 2 },  // /lmao_, int
        { 124, 2 },  // /lightcompress, int
        { 125, 2 },  // /ambientocclusion, int
        { 126, 1 },  // /ambientocclusionradius, float
        { 127, 2 },  // /debugao, int
        { 128, 2 },  // /blurlms, int
        { 129, 2 },  // /blurskylight, int
        { 130, 2 },  // /edgetolerance, int
        { 131, 2 },  // /adaptivesample, int
        { 132, 2 },  // /lightcachesize, int
        { 133, 2 },  // /lightthreads, int
        { 134, 2 },  // /patchnormals, int
        { 135, 2 },  // /fullbright, int
        { 136, 2 },  // /fullbrightlevel, int
        { 137, 2 },  // /roundlightmaptex, int
        { 138, 2 },  // /batchlightmaps, int
        { 139, 2 },  // /dragging, int
        { 140, 2 },  // /gridpower, int
        { 141, 2 },  // /passthroughsel, int
        { 142, 2 },  // /editing, int
        { 143, 2 },  // /selectcorners, int
        { 144, 2 },  // /hmapedit, int
        { 145, 2 },  // /gridlookup, int
        { 146, 2 },  // /passthroughcube, int
        { 147, 2 },  // /undomegs, int
        { 148, 2 },  // /nompedit, int
        { 149, 0 },  // /prefabdir, char *
        { 150, 2 },  // /brushx, int
        { 151, 2 },  // /brushy, int
        { 152, 2 },  // /invalidcubeguard, int
        { 153, 2 },  // /selectionsurf, int
        { 154, 2 },  // /usevdelta, int
        { 155, 2 },  // /allfaces, int
        { 156, 2 },  // /texguiwidth, int
        { 157, 2 },  // /texguiheight, int
        { 158, 2 },  // /texguitime, int
        { 159, 2 },  // /texgui2d, int
        { 160, 2 },  // /dbgalias, int
        { 161, 2 },  // /showblobs, int
        { 162, 2 },  // /blobintensity, int
        { 163, 2 },  // /blobheight, int
        { 164, 2 },  // /blobfadelow, int
        { 165, 2 },  // /blobfadehigh, int
        { 166, 2 },  // /blobmargin, int
        { 167, 2 },  // /dbgblob, int
        { 168, 2 },  // /blobstattris, int
        { 169, 2 },  // /blobdyntris, int
        { 170, 2 },  // /savebak, int
        { 171, 2 },  // /dbgvars, int
        { 172, 2 },  // /reservevpparams, int
        { 173, 2 },  // /maxvsuniforms, int
        { 174, 2 },  // /maxfsuniforms, int
        { 175, 2 },  // /maxvaryings, int
        { 176, 2 },  // /dbgshader, int
        { 177, 2 },  // /dbgubo, int
        { 178, 2 },  // /shaderprecision, int
        { 179, 2 },  // /defershaders, int
        { 180, 2 },  // /shaderdetail, int
        { 181, 0 },  // /skybox, char *
        { 182, 2 },  // /skyboxcolour, int
        { 183, 1 },  // /spinsky, float
        { 184, 2 },  // /yawsky, int
        { 185, 0 },  // /cloudbox, char *
        { 186, 2 },  // /cloudboxcolour, int
        { 187, 1 },  // /cloudboxalpha, float
        { 188, 1 },  // /spinclouds, float
        { 189, 2 },  // /yawclouds, int
        { 190, 1 },  // /cloudclip, float
        { 191, 0 },  // /cloudlayer, char *
        { 192, 1 },  // /cloudoffsetx, float
        { 193, 1 },  // /cloudoffsety, float
        { 194, 1 },  // /cloudscrollx, float
        { 195, 1 },  // /cloudscrolly, float
        { 196, 1 },  // /cloudscale, float
        { 197, 1 },  // /spincloudlayer, float
        { 198, 2 },  // /yawcloudlayer, int
        { 199, 1 },  // /cloudheight, float
        { 200, 1 },  // /cloudfade, float
        { 201, 1 },  // /cloudalpha, float
        { 202, 2 },  // /cloudsubdiv, int
        { 203, 2 },  // /cloudcolour, int
        { 204, 1 },  // /fogdomeheight, float
        { 205, 1 },  // /fogdomemin, float
        { 206, 1 },  // /fogdomemax, float
        { 207, 2 },  // /fogdomecap, int
        { 208, 1 },  // /fogdomeclip, float
        { 209, 2 },  // /sparklyfix, int
        { 210, 2 },  // /showsky, int
        { 211, 2 },  // /clipsky, int
        { 212, 2 },  // /clampsky, int
        { 213, 2 },  // /fogdomeclouds, int
        { 214, 2 },  // /useskytexture, int
        { 215, 2 },  // /guiautotab, int
        { 216, 2 },  // /guiclicktab, int
        { 217, 2 },  // /guifadein, int
        { 218, 2 },  // /guipushdist, int
        { 219, 1 },  // /guisens, float
        { 220, 2 },  // /useguifollow, int
        { 221, 2 },  // /usegui2d, int
        { 222, 2 },  // /grass, int
        { 223, 2 },  // /dbggrass, int
        { 224, 2 },  // /grassdist, int
        { 225, 1 },  // /grasstaper, float
        { 226, 1 },  // /grassstep, float
        { 227, 2 },  // /grassheight, int
        { 228, 2 },  // /grassanimmillis, int
        { 229, 1 },  // /grassanimscale, float
        { 230, 2 },  // /grassscale, int
        { 231, 1 },  // /grassalpha, float
        { 232, 0 },  // /modeldir, char *
        { 233, 2 },  // /oqdynent, int
        { 234, 2 },  // /animationinterpolationtime, int
        { 235, 2 },  // /ragdolltimestepmin, int
        { 236, 2 },  // /ragdolltimestepmax, int
        { 237, 1 },  // /ragdollrotfric, float
        { 238, 1 },  // /ragdollrotfricstop, float
        { 239, 2 },  // /ragdollconstrain, int
        { 240, 1 },  // /ragdollbodyfric, float
        { 241, 1 },  // /ragdollbodyfricscale, float
        { 242, 1 },  // /ragdollwaterfric, float
        { 243, 1 },  // /ragdollgroundfric, float
        { 244, 1 },  // /ragdollairfric, float
        { 245, 1 },  // /ragdollunstick, float
        { 246, 2 },  // /ragdollexpireoffset, int
        { 247, 2 },  // /ragdollwaterexpireoffset, int
        { 248, 1 },  // /ragdolleyesmooth, float
        { 249, 2 },  // /ragdolleyesmoothmillis, int
        { 250, 2 },  // /envmapmodels, int
        { 251, 2 },  // /bumpmodels, int
        { 252, 2 },  // /fullbrightmodels, int
        { 253, 2 },  // /gpuskel, int
        { 254, 2 },  // /maxskelanimdata, int
        { 255, 2 },  // /testtags, int
        { 256, 2 },  // /showboundingbox, int
        { 257, 2 },  // /maxmodelradiusdistance, int
        { 258, 2 },  // /animoverride, int
        { 259, 2 },  // /testanims, int
        { 260, 2 },  // /testpitch, int
        { 261, 2 },  // /maxpvsblocker, int
        { 262, 2 },  // /pvsleafsize, int
        { 263, 2 },  // /pvsthreads, int
        { 264, 2 },  // /lockpvs, int
        { 265, 2 },  // /usepvs, int
        { 266, 2 },  // /usewaterpvs, int
        { 267, 2 },  // /mipvis, int
        { 268, 2 },  // /maxmerge, int
        { 269, 2 },  // /minface, int
        { 270, 2 },  // /waterreflect, int
        { 271, 2 },  // /waterrefract, int
        { 272, 2 },  // /waterenvmap, int
        { 273, 2 },  // /waterfallrefract, int
        { 274, 2 },  // /watersubdiv, int
        { 275, 2 },  // /waterlod, int
        { 276, 2 },  // /vertwater, int
        { 277, 2 },  // /reflectdist, int
        { 278, 2 },  // /waterfog, int
        { 279, 2 },  // /waterspec, int
        { 280, 2 },  // /water2fog, int
        { 281, 2 },  // /water2spec, int
        { 282, 2 },  // /water3fog, int
        { 283, 2 },  // /water3spec, int
        { 284, 2 },  // /water4fog, int
        { 285, 2 },  // /water4spec, int
        { 286, 2 },  // /lavafog, int
        { 287, 2 },  // /lava2fog, int
        { 288, 2 },  // /lava3fog, int
        { 289, 2 },  // /lava4fog, int
        { 290, 2 },  // /oqwater, int
        { 291, 2 },  // /waterfade, int
        { 292, 2 },  // /reflectsize, int
        { 293, 2 },  // /maxreflect, int
        { 294, 2 },  // /maskreflect, int
        { 295, 2 },  // /reflectscissor, int
        { 296, 2 },  // /reflectvfc, int
        { 297, 2 },  // /refractclear, int
        { 298, 2 },  // /maxdecaltris, int
        { 299, 2 },  // /decalfade, int
        { 300, 2 },  // /dbgdec, int
        { 301, 2 },  // /showdecals, int
        { 302, 2 },  // /maxdecaldistance, int
        { 303, 2 },  // /shadowmap, int
        { 304, 2 },  // /shadowmapsize, int
        { 305, 2 },  // /shadowmapradius, int
        { 306, 2 },  // /shadowmapheight, int
        { 307, 2 },  // /shadowmapdist, int
        { 308, 2 },  // /fpshadowmap, int
        { 309, 2 },  // /shadowmapprecision, int
        { 310, 2 },  // /shadowmapintensity, int
        { 311, 2 },  // /blurshadowmap, int
        { 312, 2 },  // /blursmsigma, int
        { 313, 2 },  // /shadowmapangle, int
        { 314, 2 },  // /shadowmapbias, int
        { 315, 2 },  // /shadowmappeelbias, int
        { 316, 2 },  // /smdepthpeel, int
        { 317, 2 },  // /smoothshadowmappeel, int
        { 318, 2 },  // /debugsm, int
        { 319, 2 },  // /inexor/rendering/screen/scr_w, int
        { 320, 2 },  // /inexor/rendering/screen/scr_h, int
        { 321, 2 },  // /inexor/rendering/screen/colorbits, int
        { 322, 2 },  // /inexor/rendering/screen/depthbits, int
        { 323, 2 },  // /inexor/rendering/screen/stencilbits, int
        { 324, 2 },  // /inexor/rendering/screen/vsync, int
        { 325, 2 },  // /inexor/rendering/screen/vsynctear, int
        { 326, 2 },  // /fsaa, int
        { 327, 0 },  // /background, char *
        { 328, 0 },  // /logo, char *
        { 329, 2 },  // /userelativemouse, int
        { 330, 2 },  // /inexor/rendering/screen/fullscreen, int
        { 331, 2 },  // /inexor/rendering/screen/gamma, int
        { 332, 2 },  // /menufps, int
        { 333, 2 },  // /maxfps, int
        { 334, 2 },  // /clockerror, int
        { 335, 2 },  // /clockfix, int
        { 336, 2 },  // /numcpus, int
        { 337, 2 },  // /rate, int
        { 338, 2 },  // /throttle_interval, int
        { 339, 2 },  // /throttle_accel, int
        { 340, 2 },  // /throttle_decel, int
        { 341, 0 },  // /connectname, char *
        { 342, 2 },  // /connectport, int
        { 343, 2 },  // /maxcon, int
        { 344, 2 },  // /confading, int
        { 345, 2 },  // /fullconsole, int
        { 346, 2 },  // /consize, int
        { 347, 2 },  // /miniconsize, int
        { 348, 2 },  // /miniconwidth, int
        { 349, 2 },  // /confade, int
        { 350, 2 },  // /miniconfade, int
        { 351, 2 },  // /fullconsize, int
        { 352, 2 },  // /confilter, int
        { 353, 2 },  // /fullconfilter, int
        { 354, 2 },  // /miniconfilter, int
        { 355, 2 },  // /maxhistory, int
        { 356, 2 },  // /dynentsize, int
        { 357, 2 },  // /maxroll, int
        { 358, 1 },  // /straferoll, float
        { 359, 1 },  // /faderoll, float
        { 360, 2 },  // /floatspeed, int
        { 361, 2 },  // /physinterp, int
        { 362, 2 },  // /lerpangle, int
        { 363, 2 },  // /lerpsubdiv, int
        { 364, 2 },  // /lerpsubdivsize, int
        { 365, 2 },  // /menudistance, int
        { 366, 2 },  // /menuautoclose, int
        { 367, 2 },  // /applydialog, int
        { 368, 2 },  // /mainmenu, int
        { 369, 2 },  // /dbgmovie, int
        { 370, 2 },  // /movieaccelblit, int
        { 371, 2 },  // /movieaccelyuv, int
        { 372, 2 },  // /movieaccel, int
        { 373, 2 },  // /moviesync, int
        { 374, 1 },  // /movieminquality, float
        { 375, 2 },  // /moview, int
        { 376, 2 },  // /movieh, int
        { 377, 2 },  // /moviefps, int
        { 378, 2 },  // /moviesound, int
        { 379, 2 },  // /maxdynlights, int
        { 380, 2 },  // /dynlightdist, int
        { 381, 2 },  // /blendpaintmode, int
        { 382, 2 },  // /paintblendmapdelay, int
        { 383, 2 },  // /paintblendmapinterval, int
        { 384, 2 },  // /glversion, int
        { 385, 2 },  // /glslversion, int
        { 386, 2 },  // /ati_skybox_bug, int
        { 387, 2 },  // /ati_minmax_bug, int
        { 388, 2 },  // /ati_cubemap_bug, int
        { 389, 2 },  // /intel_vertexarray_bug, int
        { 390, 2 },  // /intel_mapbufferrange_bug, int
        { 391, 2 },  // /minimizetcusage, int
        { 392, 2 },  // /useubo, int
        { 393, 2 },  // /usetexcompress, int
        { 394, 2 },  // /rtscissor, int
        { 395, 2 },  // /blurtile, int
        { 396, 2 },  // /rtsharefb, int
        { 397, 2 },  // /dbgexts, int
        { 398, 2 },  // /wireframe, int
        { 399, 2 },  // /zoominvel, int
        { 400, 2 },  // /zoomoutvel, int
        { 401, 2 },  // /zoomfov, int
        { 402, 2 },  // /fov, int
        { 403, 2 },  // /followfov, int
        { 404, 2 },  // /avatarzoomfov, int
        { 405, 2 },  // /avatarfov, int
        { 406, 1 },  // /avatardepth, float
        { 407, 1 },  // /forceaspect, float
        { 408, 2 },  // /zoom, int
        { 409, 1 },  // /zoomsens, float
        { 410, 1 },  // /zoomaccel, float
        { 411, 2 },  // /zoomautosens, int
        { 412, 1 },  // /sensitivity, float
        { 413, 1 },  // /sensitivityscale, float
        { 414, 2 },  // /invmouse, int
        { 415, 1 },  // /mouseaccel, float
        { 416, 2 },  // /thirdperson, int
        { 417, 1 },  // /thirdpersondistance, float
        { 418, 1 },  // /thirdpersonup, float
        { 419, 1 },  // /thirdpersonside, float
        { 420, 1 },  // /nearplane, float
        { 421, 2 },  // /reflectclip, int
        { 422, 2 },  // /reflectclipavatar, int
        { 423, 1 },  // /polygonoffsetfactor, float
        { 424, 1 },  // /polygonoffsetunits, float
        { 425, 1 },  // /depthoffset, float
        { 426, 2 },  // /fog, int
        { 427, 2 },  // /skyboxglare, int
        { 428, 2 },  // /reflectmms, int
        { 429, 2 },  // /refractsky, int
        { 430, 2 },  // /modelpreviewfov, int
        { 431, 2 },  // /modelpreviewpitch, int
        { 432, 2 },  // /minimapheight, int
        { 433, 2 },  // /minimapclip, int
        { 434, 2 },  // /minimapsize, int
        { 435, 2 },  // /motionblur, int
        { 436, 2 },  // /motionblurmillis, int
        { 437, 1 },  // /motionblurscale, float
        { 438, 2 },  // /usedamagecompass, int
        { 439, 2 },  // /damagecompassfade, int
        { 440, 2 },  // /damagecompasssize, int
        { 441, 2 },  // /damagecompassalpha, int
        { 442, 2 },  // /damagecompassmin, int
        { 443, 2 },  // /damagecompassmax, int
        { 444, 2 },  // /damagescreen, int
        { 445, 2 },  // /damagescreenfactor, int
        { 446, 2 },  // /damagescreenalpha, int
        { 447, 2 },  // /damagescreenfade, int
        { 448, 2 },  // /damagescreenmin, int
        { 449, 2 },  // /damagescreenmax, int
        { 450, 2 },  // /hidestats, int
        { 451, 2 },  // /hidehud, int
        { 452, 2 },  // /crosshairsize, int
        { 453, 2 },  // /crosshairfx, int
        { 454, 2 },  // /crosshaircolors, int
        { 455, 0 },  // /crosshairdir, char *
        { 456, 2 },  // /wallclock, int
        { 457, 2 },  // /wallclock24, int
        { 458, 2 },  // /wallclocksecs, int
        { 459, 2 },  // /showfps, int
        { 460, 2 },  // /showfpsrange, int
        { 461, 2 },  // /showeditstats, int
        { 462, 2 },  // /statrate, int
        { 463, 1 },  // /conscale, float
        { 464, 2 },  // /mapversion, int
        { 465, 2 },  // /worldscale, int
        { 466, 2 },  // /worldsize, int
        { 467, 0 },  // /maptitle, char *
        { 468, 2 },  // /octaentsize, int
        { 469, 2 },  // /entselradius, int
        { 470, 2 },  // /entediting, int
        { 471, 2 },  // /attachradius, int
        { 472, 2 },  // /entselsnap, int
        { 473, 2 },  // /entmovingshadow, int
        { 474, 2 },  // /showentradius, int
        { 475, 2 },  // /entitysurf, int
        { 476, 2 },  // /entautoviewdist, int
        { 477, 2 },  // /entdrop, int
        { 478, 2 },  // /maxclients, int
        { 479, 2 },  // /maxdupclients, int
        { 480, 2 },  // /allowupdatemaster, int
        { 481, 0 },  // /mastername, char *
        { 482, 2 },  // /masterport, int
        { 483, 2 },  // /serveruprate, int
        { 484, 0 },  // /serverip, char *
        { 485, 2 },  // /serverport, int
        { 486, 2 },  // /searchlan, int
        { 487, 2 },  // /servpingrate, int
        { 488, 2 },  // /servpingdecay, int
        { 489, 2 },  // /maxservpings, int
        { 490, 2 },  // /autosortservers, int
        { 491, 2 },  // /autoupdateservers, int
        { 492, 2 },  // /inexor/sound/soundvol, int
        { 493, 2 },  // /inexor/sound/musicvol, int
        { 494, 2 },  // /inexor/sound/soundchans, int
        { 495, 2 },  // /inexor/sound/soundfreq, int
        { 496, 2 },  // /inexor/sound/soundbufferlen, int
        { 497, 2 },  // /inexor/sound/stereo, int
        { 498, 2 },  // /inexor/sound/maxsoundradius, int
        { 499, 2 },  // /inexor/sound/maxsoundsatonce, int
        { 500, 2 },  // /inexor/sound/dbgsound, int
        { 501, 2 },  // /inexor/sound/mumble, int
        { 502, 2 },  // /debugvbo, int
        { 503, 2 },  // /maxvbosize, int
        { 504, 2 },  // /filltjoints, int
        { 505, 2 },  // /vafacemax, int
        { 506, 2 },  // /vafacemin, int
        { 507, 2 },  // /vacubesize, int
        { 508, 2 },  // /particlesize, int
        { 509, 2 },  // /emitmillis, int
        { 510, 2 },  // /showparticles, int
        { 511, 2 },  // /cullparticles, int
        { 512, 2 },  // /replayparticles, int
        { 513, 2 },  // /seedmillis, int
        { 514, 2 },  // /dbgpcull, int
        { 515, 2 },  // /dbgpseed, int
        { 516, 2 },  // /outlinemeters, int
        { 517, 2 },  // /depthfxfpscale, int
        { 518, 2 },  // /depthfxscale, int
        { 519, 2 },  // /depthfxblend, int
        { 520, 2 },  // /depthfxpartblend, int
        { 521, 2 },  // /depthfxmargin, int
        { 522, 2 },  // /depthfxbias, int
        { 523, 2 },  // /fpdepthfx, int
        { 524, 2 },  // /depthfxemuprecision, int
        { 525, 2 },  // /depthfxsize, int
        { 526, 2 },  // /depthfx, int
        { 527, 2 },  // /depthfxparts, int
        { 528, 2 },  // /blurdepthfx, int
        { 529, 2 },  // /blurdepthfxsigma, int
        { 530, 2 },  // /depthfxscissor, int
        { 531, 2 },  // /debugdepthfx, int
        { 532, 2 },  // /flarelights, int
        { 533, 2 },  // /flarecutoff, int
        { 534, 2 },  // /flaresize, int
        { 535, 2 },  // /lnjittermillis, int
        { 536, 2 },  // /lnjitterradius, int
        { 537, 1 },  // /lnjitterscale, float
        { 538, 2 },  // /lnscrollmillis, int
        { 539, 1 },  // /lnscrollscale, float
        { 540, 1 },  // /lnblendpower, float
        { 541, 2 },  // /maxparticles, int
        { 542, 2 },  // /fewparticles, int
        { 543, 2 },  // /particleglare, int
        { 544, 2 },  // /dbgparts, int
        { 545, 2 },  // /maxparticledistance, int
        { 546, 2 },  // /maxtrail, int
        { 547, 2 },  // /particletext, int
        { 548, 2 },  // /maxparticletextdistance, int
        { 549, 2 },  // /glaresize, int
        { 550, 2 },  // /glare, int
        { 551, 2 },  // /blurglare, int
        { 552, 2 },  // /blurglaresigma, int
        { 553, 2 },  // /debugglare, int
        { 554, 1 },  // /glarescale, float
        { 555, 2 },  // /compresspng, int
        { 556, 2 },  // /compresstga, int
        { 557, 2 },  // /screenshotformat, int
        { 558, 0 },  // /screenshotdir, char *
        { 559, 2 },  // /usedds, int
        { 560, 2 },  // /scaledds, int
        { 561, 2 },  // /autocompactvslots, int
        { 562, 2 },  // /dbgdds, int
        { 563, 2 },  // /envmapsize, int
        { 564, 2 },  // /envmapradius, int
        { 565, 2 },  // /aaenvmap, int
        { 566, 2 },  // /hwtexsize, int
        { 567, 2 },  // /hwcubetexsize, int
        { 568, 2 },  // /hwmaxaniso, int
        { 569, 2 },  // /maxtexsize, int
        { 570, 2 },  // /reducefilter, int
        { 571, 2 },  // /texreduce, int
        { 572, 2 },  // /trilinear, int
        { 573, 2 },  // /bilinear, int
        { 574, 2 },  // /aniso, int
        { 575, 2 },  // /texcompress, int
        { 576, 2 },  // /texcompressquality, int
        { 577, 2 },  // /usenp2, int
        { 578, 0 },  // /mapdir, char *
        { 579, 0 },  // /texturedir, char *
        { 580, 0 },  // /skyboxdir, char *
        { 581, 0 },  // /interfacedir, char *
        { 582, 0 },  // /icondir, char *
        { 583, 0 },  // /sounddir, char *
        { 584, 0 },  // /musicdir, char *
        { 585, 2 },  // /dbggz, int
        { 586, 2 },  // /dbgzip, int
    
    };

} client_treedata;

} } // namespace inexor::rpc
