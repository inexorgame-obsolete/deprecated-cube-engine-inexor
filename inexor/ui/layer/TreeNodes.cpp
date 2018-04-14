#include "inexor/ui/layer/TreeNodes.hpp"
#include "inexor/network/SharedOptions.hpp"

namespace inexor { namespace ui {

SharedList<TreeNode> layers;


template<typename T>
class SHuVa {
private:
    typedef SHuVa<T> TMe;

    T value;
public:
    // Access

    T& operator *() { return value; }
    const T& operator *() const { return value; }
    T* operator ->() { return &value; }

    // Note: Let's see whether this causes too much problems
    operator T&() { return value; }

    // Proxies
    SHuVa(const T otr) : value(otr) {}
    SHuVa(const SHuVa<T> &otr) : value(otr.value) {}
    SHuVa(const SharedOption &a) : value(a.defval_int) {
    }

};

SHuVa<int> proxy_shared_var_attributes_int(const SharedOption &o) {
    SHuVa<int> i(o.defval_int);
    // i.onChange.connect(o.lambdas);
    return i;
}

class player_t {
public:
    SHuVa<int> name = proxy_shared_var_attributes_int(NoSync()|Persistent(false));
};

// alle elemente sollen connected werden
// ->
extern player_t connect_members_player_t(std::function<void(const int,  const int)> &&functor);
   player_t player = connect_members_player_t([](const int, const int) {
});


player_t connect_members_player_t(std::function<void(const int,  const int)> &&functor) {
    player_t p;
   // p.name.connect(functor);
  //  p.team.connect(functor);

}

} } // ns inexor::ui
