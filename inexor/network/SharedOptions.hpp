#pragma once

//namespace inexor { // we need to do it in global scope atm otherwise any cubescript declaration is broken TODO
//namespace rpc {
#include <type_traits>

class SharedOption
{
public:
    int defval_int = 0;
    float defval_float = 0.0f;
    const char *defval_cstring = nullptr;

    /// The Operator | lets us chain more than one SharedOption together.
    /// Since SharedOptions are used for constructing the SharedVars, the default value will be passed on to the
    /// resulting SharedOption.
    friend SharedOption& operator|(SharedOption &&first, const SharedOption &&second)
    {
        if(second.defval_int != 0) first.defval_int = second.defval_int;
        if(second.defval_float != 0.0f) first.defval_float = second.defval_float;
        if(second.defval_cstring != nullptr) first.defval_cstring = second.defval_cstring;
        return first;
    }
};

/// The fuck you cast does nothing expect silencing warnings when doing forbidden casts.
/// @warning its totally not functional (and even worse it only works for numeric types).
template<typename S>
class fu_cast
{
public:
    fu_cast(const char *input) {}
    operator S() { return 0; }
};

class Range : public SharedOption
{
public:
    /// !!! WARNING: both constructor args need to be named the same!!
    /// !!! WARNING: either every or no arg can have a default value!!
    // TODO add warning into gluegen


    /// Parse Template Data: Constructor arguments are data names, values get assigned in the place the constructor gets accessed.
    /// we need it for every possible argument type.
    Range(int min = 0, int max = fu_cast<int>("{{index}}")) {}
    Range(float min = 0.0f, float max = fu_cast<float>("{{index}}")) {}

    const char *proto_template = "(min)={{min}}, (max)={{max}}";
};

// CustomXY are the hardest atm, since we need to override the build-tools behaviour (or we need to set the build tools defaults when customxy is missing)
// both ugly non-generic hacks.
class CustomPath : public SharedOption
{
public:
    CustomPath(const char *path = "{{path}}") {}

    const char *proto_template = "(path)=\"{{path}}\"";
};

class NoSync : public SharedOption
{
public:
    NoSync() {}

    const char *cpp_receive_template = "return;";
    const char *cpp_send_template = "return;";
};

// TODO respect default initializer ispersistent = false
class Persistent : public SharedOption
{
public:
    Persistent(bool ispersistent) {}

    const char *proto_template = "da";
    const char *cpp_receive_template = "da";
    const char *cpp_send_template = "da";
};

class Default : public  SharedOption
{
public:
    Default(const int val = 0) {defval_int = val;}
    Default(const float val = 0.0f) { defval_float = val; }
    Default(const char *val = "") { defval_cstring = val; }

    const char *default_value = "{{val}}";
};

//class Function : public SharedOption
//{
//public:
//    Function(std::function<void> predicate) {}
//
//    const char *cpp_receive_template = "da";
//};

