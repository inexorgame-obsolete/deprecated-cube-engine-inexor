#pragma once
#include "inexor/rpc/SharedVar.hpp"

/// All classes deriving from this class get detected by our reflection system InexorGlueGen.
class SharedClass
{
public:
    int id; // optional id in a SharedList
};

namespace inexor { namespace rendering {

class player : public SharedClass
{
public:
    player() : kills(0), deaths(0)
    {
        deaths = 0;
    }
    player(int kills)
        :
        kills(0)
        , deaths(0)
    {
    }

    player(const char *alpha);
    SharedVar<int> kills;
    SharedVar<int> deaths;
    class weapon : public SharedClass
    {
    public:
        weapon() : ammo(0) {}
        SharedVar<int> ammo;
    };
    //SharedList<weapon> weapons;
    weapon mainweapon;
};
} } // ns inexor::rendering
