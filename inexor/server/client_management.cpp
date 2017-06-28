#include "inexor/server/client_management.hpp"
#include "inexor/server/network_send.hpp"
#include "inexor/network/legacy/cube_network.hpp"
#include "inexor/shared/cube.hpp"

namespace server {

extern ENetHost *serverhost; // TODO

VARF(maxclients, 0, DEFAULTCLIENTS, MAXCLIENTS, {if(!maxclients) maxclients = DEFAULTCLIENTS;});
/// Max clients from same peer.
VARF(maxdupclients, 0, 0, MAXCLIENTS, {if(serverhost) serverhost->duplicatePeers = maxdupclients ? maxdupclients : MAXCLIENTS;});

vector<client *> client_connections;

ENetPeer *getclientpeer(int i)
{
    return client_connections.inrange(i) && client_connections[i]->connected ? client_connections[i]->peer : nullptr;
}

uint getclientip(int n)
{
    return client_connections.inrange(n) && client_connections[n]->connected ? client_connections[n]->peer->address.host : 0;
}

int client_count = 0;


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


void disconnect_client(int n, int reason)
{
    if(!client_connections.inrange(n)) return;
    enet_peer_disconnect(client_connections[n]->peer, reason);
    server::clientdisconnect(n);
    delete_client_connection(client_connections[n]);
    const char *msg = disconnectreason(reason);
    string s;
    if(msg) formatstring(s, "client (%s) disconnected because: %s", client_connections[n]->hostname, msg);
    else formatstring(s, "client (%s) disconnected", client_connections[n]->hostname);
    spdlog::get("global")->info(s);
    sendservmsg(s);
}

bool has_clients() { return client_count != 0; }
int get_num_clients() { return client_connections.length(); }

clientinfo *get_client_info(int n, bool findbots)
{
    if(n < MAXCLIENTS) 
        return client_connections.inrange(n) && client_connections[n]->connected ? (clientinfo *)client_connections[n]->info : nullptr;
    if(!findbots) return nullptr;
    n -= MAXCLIENTS;
    return bots.inrange(n) ? bots[n] : NULL;
}
} // ns server
