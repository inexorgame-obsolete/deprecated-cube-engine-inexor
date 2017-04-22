#pragma once

//namespace inexor { // we need to do it in global scope atm otherwise any cubescript declaration is broken TODO
//namespace rpc {

class SharedOption
{
public:
    friend SharedOption& operator|(SharedOption& first, const SharedOption& second) { return first; }
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
    // TODO add warning into gluegen
    /// Parse Template Data: Constructor arguments are data names, values get assigned in the place the constructor gets accessed.
    /// we need it for every possible 
    Range(int min = 0, int max = fu_cast<int>("{{index}}")) {}
    Range(float min = 0.0f, float max = fu_cast<float>("{{index}}")) {}

    const char *dummy_key1 = "dummy_value. min = {{min}} max = {{max}}";
    const char *dummy_key2 = "dummy_value";
    const char *dummy_key3 = "dummy_value";
};

// CustomXY are the hardest atm, since we need to override the build-tools behaviour (or we need to set the build tools defaults when customxy is missing)
// both ugly non-generic hacks.
class CustomPath : public SharedOption
{
public:
    /// !!! WARNING: either every or no arg can have a default value!!
    // TODO add warning into gluegen
    CustomPath(const char *path = "{{path}}") {}

    const char *proto_template = "(path)=\"{{path}}\"";
    const char *cpp_init_check_template = "send(path";
    const char *cpp_receive_template = "da";
    const char *cpp_send_template = "da";
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

//class Function : public SharedOption
//{
//public:
//    Function(std::function<void> predicate) {}
//
//    const char *cpp_receive_template = "da";
//};

