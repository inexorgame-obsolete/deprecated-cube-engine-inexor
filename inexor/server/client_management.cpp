#include "inexor/server/client_management.hpp"
#include "inexor/server/network_send.hpp"
#include "inexor/network/legacy/cube_network.hpp"
#include "inexor/shared/cube.hpp"

vector<client *> clients;

extern ENetHost *serverhost; // TODO

VARF(maxclients, 0, DEFAULTCLIENTS, MAXCLIENTS, {if(!maxclients) maxclients = DEFAULTCLIENTS;});
/// Max clients from same peer.
VARF(maxdupclients, 0, 0, MAXCLIENTS, {if(serverhost) serverhost->duplicatePeers = maxdupclients ? maxdupclients : MAXCLIENTS;});

void *getclientinfo(int i) { return clients.inrange(i) && clients[i]->connected ? clients[i]->info : NULL; }
ENetPeer *getclientpeer(int i) { return clients.inrange(i) && clients[i]->connected ? clients[i]->peer : NULL; }
uint getclientip(int n) { return clients.inrange(n) && clients[n]->connected ? clients[n]->peer->address.host : 0; }

int client_count = 0;

bool has_clients() { return client_count != 0; }
int get_num_clients() { return clients.length(); }

client &addclient()
{
    client *c = NULL;
    loopv(clients) if(!clients[i]->connected)
    {
        c = clients[i];
        break;
    }
    if(!c)
    {
        c = new client;
        c->num = clients.length();
        clients.add(c);
    }
    c->info = server::newclientinfo();
    c->connected = true;
    client_count++;
    return *c;
}

void delclient(client *c)
{
    if(!c) return;
    if(!c->connected) return;
    c->connected = false;
    client_count--;
    if(c->peer) c->peer->data = NULL;
    c->peer = NULL;
    if(c->info)
    {
        server::deleteclientinfo(c->info);
        c->info = NULL;
    }
}

void disconnect_client(int n, int reason)
{
    if(!clients.inrange(n)) return;
    enet_peer_disconnect(clients[n]->peer, reason);
    server::clientdisconnect(n);
    delclient(clients[n]);
    const char *msg = disconnectreason(reason);
    string s;
    if(msg) formatstring(s, "client (%s) disconnected because: %s", clients[n]->hostname, msg);
    else formatstring(s, "client (%s) disconnected", clients[n]->hostname);
    spdlog::get("global")->info(s);
    sendservmsg(s);
}

namespace server {

    void *newclientinfo() { return new clientinfo; }
    void deleteclientinfo(void *ci) { delete (clientinfo *)ci; }

    clientinfo *getinfo(int n)
    {
        if(n < MAXCLIENTS) return (clientinfo *)getclientinfo(n);
        n -= MAXCLIENTS;
        return bots.inrange(n) ? bots[n] : NULL;
    }
}
