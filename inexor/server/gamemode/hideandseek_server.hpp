#pragma once
#include <string.h>                                    // for strcmp

#include "inexor/gamemode/hideandseek_common.hpp"      // for TEAM_HIDE, TEA...
#include "inexor/server/client_management.hpp"         // for clientinfo (pt...
#include "inexor/server/gamemode/gamemode_server.hpp"  // for servmode
#include "inexor/shared/cube_vector.hpp"               // for vector
#include "inexor/shared/ents.hpp"                      // for ::CS_SPECTATOR

struct fpsent;
struct packetbuf;

#define ishider(ci) (strcmp(ci->team, TEAM_HIDE) == 0 && ci->state.state != CS_SPECTATOR ? true : false)
#define isseeker(ci) (strcmp(ci->team, TEAM_SEEK) == 0 && ci->state.state != CS_SPECTATOR ? true : false)

namespace server {

struct hideandseekservermode : servmode, hideandseekmode
{
    struct seekersinfo
    {
        int cn;
        bool freezed;
        seekersinfo(int cn_, bool freezed_) : cn(cn_), freezed(freezed_) {}
    };

    vector<seekersinfo*> seekersinfos;
    int lastupdatecheck;

    void setup() override;

    void initplayers();

    void initplayer(clientinfo *ci)
    {
        sethider(ci);
    }

    void initclient(clientinfo *ci, packetbuf &p, bool connecting) override
    {
        setseeker(ci);
    }

    void connected(clientinfo *ci) override
    {
        setseeker(ci);
    }

    void leavegame(clientinfo *ci, bool disconnecting) override;

    void cleanup() override
    {
        seekersinfos.deletecontents();
    }

    bool checkfinished();

    void update() override;

    void intermission() override
    {
    }

    void spawned(fpsent *d)
    {
    }

    bool canspawn(clientinfo *ci, bool connecting) override
    {
        return true;
    }

    bool canhit(clientinfo *target, clientinfo *actor) override;

    void died(clientinfo *target, clientinfo *actor) override;

    bool canchangeteam(clientinfo *ci, const char *oldteam, const char *newteam) override
    {
        return false;
    }

    void setseeker(clientinfo *ci);

    void sethider(clientinfo *ci);

    vector<clientinfo*> getactiveplayers();

    int getremaininghiders();

    bool isfreezed(clientinfo *ci);

    void setfreezedstate(clientinfo *ci, bool state);

    int getnonfreezedseekers();

    void announceseekers(char* msg);

    bool parse_network_message(int type, clientinfo *ci, clientinfo *cq, packetbuf &p) override
    {
        switch(type)
        {
            /*
            case N_RACEFINISH:
            {
            break;
            }
            */
            default: break;
        }
        return false;
    }
};




} // ns server
