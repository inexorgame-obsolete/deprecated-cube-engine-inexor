#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>

#include "inexor/util/random.hpp"
#include "inexor/gluegen/tree.hpp"
#include "inexor/gluegen/generator_cpp_tree_adapter.hpp"

using boost::size;
using boost::begin;
using boost::end;
using boost::copy;
using boost::regex;
using boost::split_regex;
using boost::adaptors::sliced;

using std::string;
using std::vector;

namespace {

template<typename OStream, typename NSRange>
void enter_ns(OStream &s, const NSRange &ns) {
    for (auto &comp : ns) s << "\nnamespace " << comp << " {";
}

template<typename OStream, typename NSRange>
void leave_ns(OStream &s, const NSRange &ns) {
    for (size_t i=0; i<boost::size(ns); i++) s << "\n}";
}

template<typename Range>
auto initial(const Range &s) -> decltype(s | sliced(0, boost::size(s) - 1)) {
    return s | sliced(0, boost::size(s) - 1);
}

template<typename Range>
typename Range::value_type last(Range &s) {
    return *(s.begin() + (boost::size(s) - 1));
}

}

namespace inexor {
namespace rpc {
namespace gluegen {

void update_cpp_tree_server_impl(const string &header_path, const string &source_path, vector<ShTreeNode> &tree, const vector<string> &ns)
{
    std::ofstream h{header_path, std::ofstream::trunc};

    h << "#pragma once";

    enter_ns(h, ns);

    h << std::endl << "extern void dump(Global &);"
      << std::endl << std::endl;

    h << std::endl << "inline Global dump()"
      << std::endl << "{"
      << std::endl << "    Global r;"
      << std::endl << "    dump(r);"
      << std::endl << "    return r;"
      << std::endl << "}" << std::endl;

    leave_ns(h, ns);

    std::ofstream s{source_path, std::ofstream::trunc};

    for (auto &node : tree) {
        std::vector<std::string> nspath;
        split_regex(nspath, node.cpp_var, regex("::"));
        nspath.erase(nspath.begin()); // Workaround: remove :: root namespace

        enter_ns(s, initial(nspath));
        s << "\nextern " << node.type_lit << " " << last(nspath) << ";";
        leave_ns(s, initial(nspath));
    }

    enter_ns(s, ns);
    s << "\nvoid dump(Global &r) {";
    for (auto &node : tree)
        if (!node.mangled_path.empty())
          s << "\n  r.set_" << node.mangled_path << "(" << node.cpp_var << ");";
    s << "\n}";
    leave_ns(s, ns);
}

}
}
}
