#include "inexor/server/client_management.hpp"
#include "inexor/server/network_send.hpp"
#include "inexor/server/gamemode/gamemode_server.hpp"
#include "inexor/server/demos.hpp"
#include "inexor/network/legacy/crypto.hpp"
#include "inexor/network/legacy/cube_network.hpp"
#include "inexor/util/Logging.hpp"
#include "inexor/shared/cube.hpp"

namespace server {

extern ENetHost *serverhost;
extern void checkpausegame();

VARF(maxclients, 0, DEFAULTCLIENTS, MAXCLIENTS, {if(!maxclients) maxclients = DEFAULTCLIENTS;});
/// Max clients from same peer.
VARF(maxdupclients, 0, 0, MAXCLIENTS, {if(serverhost) serverhost->duplicatePeers = maxdupclients ? maxdupclients : MAXCLIENTS;});

/// The amount of people who can connect more than the actual specified max clients limit.
/// E.g. for people connecting as admin or with the password.
int reserveclients() { return 3; }

SVAR(serverpass, "");
SVAR(adminpass, "");
VARF(publicserver, 0, 0, 2, {
    switch(*publicserver)
    {
        case 0: default: mastermask = MM_PRIVSERV; break;
        case 1: mastermask = MM_PUBSERV; break;
        case 2: mastermask = MM_COOPSERV; break;
    }
});

/// TODO merge with clients or connects.
vector<client *> client_connections;

vector<clientinfo *> connects, clients, bots;

ENetPeer *getclientpeer(int i)
{
    return client_connections.inrange(i) && client_connections[i]->connected ? client_connections[i]->peer : nullptr;
}

uint getclientip(int n)
{
    return client_connections.inrange(n) && client_connections[n]->connected ? client_connections[n]->peer->address.host : 0;
}

/// Idk why client_connections.length isnt used here:
/// we try to avoid resetting the vector completely (probably an optimisation), but just free the buffers from it and set
/// the connection->connected to false and the next player joining fills the gap.. dunno, smells useless.
int client_count = 0;


bool has_clients() { return client_count != 0; }
// TODO: merge get_num_clients and numclients.. (maybe difference: connected vs not yet connected)?
// same as merging clientinfo with client_connection..
int get_num_clients() { return client_connections.length(); }

int numclients(int exclude, bool nospec, bool noai, bool priv)
{
    int n = 0;
    loopv(clients)
    {
        clientinfo *ci = clients[i];
        if(ci->clientnum==exclude) continue;
        if(nospec && ci->state.state==CS_SPECTATOR && !(priv && ci->privilege)) continue;
        if(noai && ci->state.aitype != AI_NONE) continue;
        n++;
    }
    return n;
}

clientinfo *get_client_info(int n, bool findbots) {
    if (n < MAXCLIENTS)
        return client_connections.inrange(n) && client_connections[n]->connected
               ? (clientinfo *) client_connections[n]->info : nullptr;
    if (!findbots) return nullptr;
    n -= MAXCLIENTS;
    return bots.inrange(n) ? bots[n] : NULL;
}

//// Name helpers
bool duplicatename(clientinfo *ci, const char *name)
{
    if(!name) name = ci->name;
    loopv(clients) if(clients[i]!=ci && !strcmp(name, clients[i]->name)) return true;
    return false;
}

const char *colorname(clientinfo *ci, const char *name)
{
    if(!name) name = ci->name;
    if(name[0] && !duplicatename(ci, name) && ci->state.aitype == AI_NONE) return name;
    static string cname[3];
    static int cidx = 0;
    cidx = (cidx+1)%3;
    formatstring(cname[cidx], ci->state.aitype == AI_NONE ? "%s %s(%d)%s" : "%s %s[%d]%s", name, COL_MAGENTA, ci->clientnum, COL_WHITE);
    return cname[cidx];
}

///// Bans
struct ban
{
    int time, expire;
    uint ip;
};

/// allowed IPs: mastermode locked allows some players to be unspectated immediately?
vector<uint> allowedips;
vector<ban> bannedips;

void addban(uint ip, int expire)
{
    allowedips.removeobj(ip);
    ban b;
    b.time = totalmillis;
    b.expire = totalmillis + expire;
    b.ip = ip;
    loopv(bannedips) if(bannedips[i].expire - b.expire > 0) { bannedips.insert(i, b); return; }
    bannedips.add(b);
}

void clearbans(clientinfo *actor)
{
    if(actor->privilege)
    {
        bannedips.shrink(0);
        sendservmsg("cleared all bans");
    }
}

// TODO: merge clientinfo and sendernum as soon as client_connections are gone
void change_mastermode(int mm, int sendernum, clientinfo *actor)
{
    if(actor->privilege && mm>=MM_OPEN && mm<=MM_PRIVATE)
    {
        if((actor->privilege>=PRIV_ADMIN) || (mastermask&(1<<mm)))
        {
            mastermode = mm;
            allowedips.shrink(0);
            if(mm>=MM_PRIVATE)
            {
                loopv(clients) allowedips.add(getclientip(clients[i]->clientnum));
            }
            sendf(-1, 1, "rii", N_MASTERMODE, mastermode);
            //sendservmsgf("mastermode is now %s (%d)", mastermodename(mastermode), mastermode);
        }
        else
        {
            defformatstring(s, "mastermode %d is disabled on this server", mm);
            sendf(sendernum, 1, "ris", N_SERVMSG, s);
        }
    }
}

void check_bans_expired()
{
    while(bannedips.length() && bannedips[0].expire-totalmillis <= 0) bannedips.remove(0);
}

void kickclients(uint ip, clientinfo *actor, int priv)
{
    loopvrev(clients)
    {
        clientinfo &c = *clients[i];
        if(c.state.aitype != AI_NONE || c.privilege >= PRIV_ADMIN) continue;
        if(actor && (c.privilege > priv || c.clientnum == actor->clientnum)) continue;
        if(getclientip(c.clientnum) == ip) disconnect_client(c.clientnum, DISC_KICK);
    }
}

bool trykick(clientinfo *ci, int victim, const char *reason, bool trial)
{
    int priv = ci->privilege;
    if((priv) && ci->clientnum!=victim)
    {
        clientinfo *vinfo = get_client_info(victim, false);
        if(vinfo && vinfo->connected && priv >= vinfo->privilege && vinfo->privilege < PRIV_ADMIN)
        {
            if(trial) return true;
            string kicker;
            copystring(kicker, colorname(ci));
            if(reason && reason[0]) sendservmsgf("%s kicked %s because: %s", kicker, colorname(vinfo), reason);
            else sendservmsgf("%s kicked %s", kicker, colorname(vinfo));
            uint ip = getclientip(victim);
            addban(ip, 4*60*60000);
            kickclients(ip, ci, priv);
        }
    }
    return false;
}

//// Global bans

vector<ipmask> gbans;

void cleargbans()
{
    gbans.shrink(0);
}

bool checkgban(uint ip)
{
    loopv(gbans) if(gbans[i].check(ip)) return true;
    return false;
}

void addgban(const char *name)
{
    ipmask ban;
    ban.parse(name);
    gbans.add(ban);

    loopvrev(clients)
    {
        clientinfo *ci = clients[i];
        if(ci->state.aitype != AI_NONE || ci->privilege >= PRIV_ADMIN) continue;
        if(checkgban(getclientip(ci->clientnum))) disconnect_client(ci->clientnum, DISC_IPBAN);
    }
}

int allowconnect(clientinfo *ci, const char *pwd = "")
{
    if(serverpass[0])
    {
        if(!checkpassword(ci->clientnum, ci->sessionid, serverpass, pwd)) return DISC_PASSWORD;
        return DISC_NONE;
    }
    if(adminpass[0] && checkpassword(ci->clientnum, ci->sessionid, adminpass, pwd)) return DISC_NONE;
    if(numclients(-1, false, true)>=maxclients) return DISC_MAXCLIENTS;
    uint ip = getclientip(ci->clientnum);
    loopv(bannedips) if(bannedips[i].ip==ip) return DISC_IPBAN;
    if(checkgban(ip)) return DISC_IPBAN;
    if(mastermode>=MM_PRIVATE && allowedips.find(ip)<0) return DISC_PRIVATE;
    return DISC_NONE;
}

int mastermode = MM_OPEN, mastermask = MM_PRIVSERV;

int get_mastermode_int()
{
    return serverpass[0] ? MM_PASSWORD : (mastermode || mastermask&MM_AUTOAPPROVE ? mastermode : MM_START);
}

void revokemaster(clientinfo *ci)
{
    ci->privilege = PRIV_NONE;
    if(ci->state.state==CS_SPECTATOR) aiman::removeai(ci);
}

bool setmaster(clientinfo *ci, bool val, const char *pass, bool force, bool trial)
{
    if(!val) return false;
    const char *name = "";

    bool haspass = adminpass[0] && checkpassword(ci->clientnum, ci->sessionid, adminpass, pass);
    int wantpriv = haspass ? PRIV_ADMIN : PRIV_MASTER;
    if(wantpriv <= ci->privilege) return true;
    else if(wantpriv <= PRIV_MASTER && !force)
    {
        if(ci->state.state==CS_SPECTATOR)
        {
            sendf(ci->clientnum, 1, "ris", N_SERVMSG, "Spectators may not claim master.");
            return false;
        }
        loopv(clients) if(ci!=clients[i] && clients[i]->privilege)
            {
                sendf(ci->clientnum, 1, "ris", N_SERVMSG, "Master is already claimed.");
                return false;
            }
        if(!(mastermask&MM_AUTOAPPROVE) && !ci->privilege)
        {
            sendf(ci->clientnum, 1, "ris", N_SERVMSG, "This server requires special permission to claim master.");
            return false;
        }
    }
    if(trial) return true;
    ci->privilege = wantpriv;
    name = privname(ci->privilege);

    bool hasmaster = false;
    loopv(clients) if(clients[i]->privilege >= PRIV_MASTER) hasmaster = true;
    if(!hasmaster)
    {
        mastermode = MM_OPEN;
        allowedips.shrink(0);
    }
    defformatstring(msg, "%s %s %s", colorname(ci), val ? "claimed" : "relinquished", name);
    packetbuf p(MAXTRANS, ENET_PACKET_FLAG_RELIABLE);
    putint(p, N_SERVMSG);
    sendstring(msg, p);
    putint(p, N_CURRENTMASTER);
    putint(p, mastermode);
    loopv(clients) if(clients[i]->privilege >= PRIV_MASTER)
        {
            putint(p, clients[i]->clientnum);
            putint(p, clients[i]->privilege);
        }
    putint(p, -1);
    sendpacket(-1, 1, p.finalize());
    checkpausegame();
    return true;
}

/// Save scores if client disconnects to restore it when he reconnects.
struct savedscore
{
    uint ip;
    string name;
    int maxhealth, frags, flags, deaths, teamkills, shotdamage, damage;
    int timeplayed;
    float effectiveness;
    int bombradius;
    int bombdelay;

    void save(gamestate &gs)
    {
        maxhealth = gs.maxhealth;
        frags = gs.frags;
        flags = gs.flags;
        deaths = gs.deaths;
        teamkills = gs.teamkills;
        shotdamage = gs.shotdamage;
        damage = gs.damage;
        timeplayed = gs.timeplayed;
        effectiveness = gs.effectiveness;
        bombradius = gs.bombradius;
        bombdelay = gs.bombdelay;
    }

    void restore(gamestate &gs)
    {
        if(gs.health==gs.maxhealth) gs.health = maxhealth;
        gs.maxhealth = maxhealth;
        gs.frags = frags;
        gs.flags = flags;
        gs.deaths = deaths;
        gs.teamkills = teamkills;
        gs.shotdamage = shotdamage;
        gs.damage = damage;
        gs.timeplayed = timeplayed;
        gs.effectiveness = effectiveness;
        gs.bombradius = bombradius;
        gs.bombdelay = bombdelay;
    }
};

vector<savedscore> scores;

savedscore *findscore(clientinfo *ci, bool insert)
{
    uint ip = getclientip(ci->clientnum);
    if(!ip) return 0;
    if(!insert)
    {
        loopv(clients)
        {
            clientinfo *oi = clients[i];
            if(oi->clientnum != ci->clientnum && getclientip(oi->clientnum) == ip && !strcmp(oi->name, ci->name))
            {
                oi->state.timeplayed += lastmillis - oi->state.lasttimeplayed;
                oi->state.lasttimeplayed = lastmillis;
                static savedscore curscore;
                curscore.save(oi->state);
                return &curscore;
            }
        }
    }
    loopv(scores)
    {
        savedscore &sc = scores[i];
        if(sc.ip == ip && !strcmp(sc.name, ci->name)) return &sc;
    }
    if(!insert) return 0;
    savedscore &sc = scores.add();
    sc.ip = ip;
    copystring(sc.name, ci->name);
    return &sc;
}

void savescore(clientinfo *ci)
{
    savedscore *sc = findscore(ci, true);
    if(sc) sc->save(ci->state);
}

bool restorescore(clientinfo *ci)
{
    savedscore *sc = findscore(ci, false);
    if(sc)
    {
        sc->restore(ci->state);
        return true;
    }
    return false;
}

// new match: dont remember the old scores.
void resetdisconnectedplayerscores()
{
    scores.shrink(0);
}
///// Connect

extern SharedVar<char*> serverdesc;
extern SharedVar<char*> servermotd;

void sendservinfo(clientinfo *ci)
{
    sendf(ci->clientnum, 1, "ri5s", N_SERVINFO, ci->clientnum, PROTOCOL_VERSION, ci->sessionid, serverpass[0] ? 1 : 0, *serverdesc);
}


extern void choosemap(clientinfo *ci);

void sendresume(clientinfo *ci)
{
    gamestate &gs = ci->state;
    sendf(-1, 1, "ri7i9vi", N_RESUME, ci->clientnum,
          gs.state, gs.frags, gs.flags, gs.quadmillis,
          gs.deaths, gs.teamkills, gs.damage, gs.shotdamage,
          gs.lifesequence,
          gs.health, gs.maxhealth,
          gs.armour, gs.armourtype,
          gs.gunselect, GUN_PISTOL-GUN_SG+1, &gs.ammo[GUN_SG], -1);
}

extern void assign_team(clientinfo *ci);
extern void sendwelcome(clientinfo *ci);
extern void sendinitclient(clientinfo *ci);

bool player_connected(clientinfo *ci, const char *password)
{
    int disc = allowconnect(ci, password);
    if(disc != DISC_NONE) return false;

    if(m_demo) enddemoplayback();

    choosemap(ci);

    connects.removeobj(ci);
    clients.add(ci);

    ci->connected = true;
    ci->needclipboard = totalmillis ? totalmillis : 1;
    if(mastermode>=MM_LOCKED) ci->state.state = CS_SPECTATOR;
    ci->state.lasttimeplayed = lastmillis;

    assign_team(ci);

    sendwelcome(ci);
    if(restorescore(ci)) sendresume(ci);
    sendinitclient(ci);

    aiman::addclient(ci);

    if(m_demo) setupdemoplayback();

    if(servermotd[0]) sendf(ci->clientnum, 1, "ris", N_SERVMSG, *servermotd);
    return true;
}

client &add_client_connection()
{
    client *c = NULL;
    loopv(client_connections) if(!client_connections[i]->connected) // fill spaces
        {
            c = client_connections[i];
            break;
        }
    if(!c)
    {
        c = new client;
        c->num = client_connections.length();
        client_connections.add(c);
    }
    c->info = new clientinfo;
    c->connected = true;
    client_count++;
    return *c;
}

void delete_client_connection(client *c)
{
    if(!c) return;
    if(!c->connected) return;
    c->connected = false;
    client_count--;
    if(c->peer) c->peer->data = NULL;
    c->peer = NULL;
    if(c->info)
    {
        delete (clientinfo *)c->info;
        c->info = NULL;
    }
}


void noclients()
{
    bannedips.shrink(0);
    aiman::clearai();
}

int clientconnect(int n, uint ip)
{
    clientinfo *ci = get_client_info(n);
    ci->clientnum = ci->ownernum = n;
    ci->connectmillis = totalmillis;
    ci->sessionid = (rnd(0x1000000)*((totalmillis%10000)+1))&0xFFFFFF;

    connects.add(ci);
    sendservinfo(ci);
    return DISC_NONE;
}

void disconnect_client(int n, int reason)
{
    if(!client_connections.inrange(n)) return;
    enet_peer_disconnect(client_connections[n]->peer, reason);

    clientinfo *ci = get_client_info(n);
    if(!ci) return;
    if(ci->connected)
    {
        if(ci->privilege) setmaster(ci, false);
        if(smode) smode->leavegame(ci, true);
        ci->state.timeplayed += lastmillis - ci->state.lasttimeplayed;
        savescore(ci);
        sendf(-1, 1, "ri2", N_CDIS, n);
        clients.removeobj(ci);
        aiman::removeai(ci);
        if(!numclients(-1, false, true)) noclients(); // bans clear when server empties
        checkpausegame();
    }
    else connects.removeobj(ci);

    delete_client_connection(client_connections[n]);
    const char *msg = disconnectreason(reason);
    string s;
    if(msg) formatstring(s, "client (%s) disconnected because: %s", client_connections[n]->hostname, msg);
    else formatstring(s, "client (%s) disconnected", client_connections[n]->hostname);
    Log.std->info(s);
    sendservmsg(s);
}


void check_clients_timed_out()
{
    loopv(connects) if(totalmillis-connects[i]->connectmillis>15000) disconnect_client(connects[i]->clientnum, DISC_TIMEOUT);
}

} // ns server
