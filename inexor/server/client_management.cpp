#include "inexor/server/client_management.hpp"
#include "inexor/network/legacy/cube_network.hpp"
#include "inexor/shared/cube.hpp"

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
