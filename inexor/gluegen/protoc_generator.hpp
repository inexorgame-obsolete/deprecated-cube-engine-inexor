#ifndef INEXOR_RPC_GLUGEN_PROTOC_GENERATOR_HEADER
#define INEXOR_RPC_GLUGEN_PROTOC_GENERATOR_HEADER

#include <string>

#include "inexor/gluegen/tree.hpp"

namespace inexor {
namespace rpc {
namespace gluegen {

/// Takes an Inexor Shared Tree, assigns each Node
/// a protoc_idx and writes a protocol buffers protocol
/// description to the indicated file.
///
/// Later this should update the file instead of rewriting
/// it every time and read the existing protoc_idx'es from
/// the protocol file, that's why the indexes are assigned
/// in here
///
/// TODO: Use a range instead of the fixed ShTree
extern void update_protoc_file(const std::string &path, std::vector<ShTreeNode> &tree);

}
}
}

#endif
