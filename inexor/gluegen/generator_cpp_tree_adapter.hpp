#pragma once

namespace inexor {
namespace rpc {
namespace gluegen {

void update_cpp_tree_server_impl(
      const std::string &header_path
    , const std::string &source_path
    , std::vector<ShTreeNode> &tree
    , const std::vector<std::string> &ns);

}
}
}
