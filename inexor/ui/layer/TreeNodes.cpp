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
extern player_t connect_members_player_t(int); //std::function<void(const int,  const int)> &&functor);
player_t player = connect_members_player_t((NoSync()|Persistent(false)).defval_int);

// oder:
// SharedClass<player_t> player;
// -> Nein, extern SharedClass<player_t> player?

template<typename T>
struct SharedList {};
SharedList<int> IPs;

// Frage: Woher weiß tool, dass diese klasse markiert ist?
// Option A: iwas in initexpr (e.g. = <namens_prä>)
// Option B: ein kommentar davor (e.g. /// THIS_IS_SHARED: player
// Option C: SharedOptions sind argumente der funktion.

// Frage: wohin mit SharedOptions?
// Option A: Constructor  -> Schlecht für innerhalb einer Klassendefinition: Constructor der Klasse braucht extras
// Option B: Funktionsparameter der InitExpr -> Signalisiert nicht wirklich dass keine Logik erlaubt ist.
// -> B -> Problem: wie muss funktion genannt werden?
// -> keine vorgaben, irrelevant.


// Frage: wie SharedList als "is_sharedlist" markieren?
// Problemstellung: muss iwo in list definition markiert werden
//                  ist das wahr?
// Option A: marker iwo in class
// Option B: sharedclasses kriegen einfach so n marker "is_<class_name>"
//           ebenso dazu kommt ein marker is_<class_name>_<template_type> falls class templated ist.
//     -> SharedVar<T> ist keine SharedClass. Wieso? Weil dass das Ende ist, steckt nur n "char * buffer" member drin.
//      Ist SharedList<T> eine SharedClass? Steckt nur ein "std::vector<T> buffer" drin.
//      -> T ist nie C primitiv. Sondern C

//      Lösung: richtiges Ende markieren!

// sharedlist < S>                                  players/            is_sharedlist
//    - S = std::vector<Y>                          list_buffer         is_vector       collapsed path?
//        - Y = SharedVar<Z>                        list_entry -> /0/   is_sharedvar
//            - Z = int                             value               is_int          collapsed path? end of path?

// 1. bemerkung: für jede arg-layer vom template
//              -> entry kommt in "template_type" (plural later?)



// 2. bemerkung: partials sollten definiert werden können
        // 1. section ist "partials: { name, code  }"
        // 2. section ist "file: { filename, code }"


/*
// generiert:
// #include "file/of/player_t.hpp"
player_t connect_members_player_t(std::function<void(const int,  const int)> &&functor) {
    player_t p;
   // p.name.connect(functor);
  //  p.team.connect(functor);
}

void connect_synchro_functors(){
    // primitive_var.connect(functor(erstelle_message_setze_felder_sende_message)
    // list_var.on_add_function(
}

// Message -> change variables
void handle_index_player_t(int index, int msg) {
    // wenn index von "player":
    //   submsg = msg.submsg(index);
    //   setze_player_t_variables(submsg);
{{#variables}}
    case {{>index}}:
    {{#is_string}}
        {{name_cpp_full}}.setnosync(strdup(tree_event.{{name_unique}}().c_str()));
    {{/is_string}}
    {{^is_string}}
        {{name_cpp_full}}.setnosync(tree_event.{{name_unique}}());
    {{/is_string}}
    {{#is_class}}
        handle_index_{{class_name}}(index, msg);
    {{/is_class}}


    {{#is_shared_list}}
        {{#variables}} // the collapsed member (the buffer of the sharedlist<T> of type T)
            {{#is_class}}
                submsg = msg.submsg(index);
                handle_index_{{class_name}}(index, submsg);
            {{/is_class}}
        {{/variables}}
    {{/is_shared_list}}
        break;
{{/variables}}

}

void handle_index_TreeEvent(int index, int msg) {
    // wenn index von "player":
    //   submsg = msg.submsg(index);
    //   setze_player_t_variables(submsg);

}
        // Plugin Manager Core:
        // - Static or dynamic
        // - static get added to the proto file and a config file for a dynamic plugin?? or a name prefix (for detection)?
        // - a lot of stuff needs to be encompassed in classes so it is accessable from inside dynamic plugins
        // (which need dependency injection. Maybe also need dependency management)
        // - Special segment of proto indices is reserved for vanilla core (faster? is it worth it?)
        //   the rest is hashed by plugin name (java names)
        // On Flex side:
        // - Merge more than one proto together
        // - Also add plugins (each can specify the core or flex plugins it needs -> dependency management)

        Raus finden wie submsg in treevar (und index)
*/
} } // ns inexor::ui
