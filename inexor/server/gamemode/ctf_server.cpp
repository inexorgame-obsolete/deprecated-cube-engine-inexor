#include "inexor/server/gamemode/ctf_server.hpp"

namespace server {

VAR(ctftkpenalty, 0, 1, 1);

bool ctfservermode::addflag(int i, const vec &o, int team, int invistime)
{
    if(!ctfmode::addflag(i, o, team)) return false;
    flag &f = flags[i];
    f.invistime = invistime;
    return true;
}

void ctfservermode::died(clientinfo *ci, clientinfo *actor)
{
    dropflag(ci, ctftkpenalty && actor && actor != ci && isteam(actor->team, ci->team) ? actor : NULL);
    loopv(flags) if(flags[i].dropper == ci->clientnum) { flags[i].dropper = -1; flags[i].dropcount = 0; }
}

}