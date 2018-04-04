#pragma once

#include "inexor/network/SharedTree.hpp"

namespace inexor { namespace ui {

class TreeNodes : public SharedClass {
public:
    TreeNodes() : url(""), name(""), visible(0), x(0), y(0), width(0), height(0), mouse_accept_input(0), keyboard_accept_input(0)
    {
    }

    SharedVar<char *> url;
    SharedVar<char *> name;
    SharedVar<int> visible;
    SharedVar<int> x;
    SharedVar<int> y;
    SharedVar<int> width;
    SharedVar<int> height;
    SharedVar<int> mouse_accept_input;
    SharedVar<int> keyboard_accept_input;
};

extern SharedList<TreeNodes> layers;
} } // ns inexor::ui
