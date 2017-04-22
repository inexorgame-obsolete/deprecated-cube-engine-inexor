#pragma once
#include "inexor/network/SharedVar.hpp"
#include "inexor/network/SharedOptions.hpp"

/// All classes deriving from this class get detected by our reflection system InexorGlueGen.
class SharedClass
{
public:
    SharedClass() {}
    SharedClass(SharedOption p) {}
};

namespace inexor { namespace rendering {

class player : public SharedClass
{
public:
    player() : kills(0), deaths(0)
    {
    }
    player(int kills)
        :
        kills(0)
        , deaths(0)
    {
    }

    player(const char *alpha);
    player(const player &old) : kills(old.kills), deaths(old.deaths) // TODO: TELL PEOPLE THIS IS REQUIRED
    { }
    player operator=(const player &a)
    {
        return player(a);
    }

    SharedVar<int> kills;
    SharedVar<int> deaths;
    //class weapon : public SharedClass
    //{
    //public:
    //    weapon() : ammo(0) {}
    //    SharedVar<int> ammo;
    //};
    ////SharedList<weapon> weapons;
    //weapon mainweapon;
};
} } // ns inexor::rendering
