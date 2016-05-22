#include <algorithm>
#include <fstream>
#include <functional>
#include <tuple>
#include <iostream>

#include <boost/spirit/include/karma.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/fusion/include/std_tuple.hpp>

#include "inexor/gluegen/generator_protoc.hpp"

namespace inexor {
namespace rpc {
namespace gluegen {

void update_protoc_file(
      const std::string &path
    , std::vector<ShTreeNode> &tree
    , const std::string &package) {

    /// Assign numbers to each of the fields

    using boost::adaptors::transformed;
    using std::function; // Finds the next index to use for not indexed fields: // The biggest used index plus one; we specifically do // not include unused index inbetween, because the could
    // be packets that have been deprecated
    // TODO: Use
    // https://github.com/ericniebler/range-v3/issues/255
    function<uint64_t(ShTreeNode&)> get_pidx = [](ShTreeNode&n) {
        return n.protoc_idx; };
    uint64_t idx_cnt = 1 + *boost::max_element( tree | transformed(get_pidx) );

    // Assign new indexes to each Node with unset index
    // TODO: Argh. Using ranges would be nicer
    for (auto &n : tree)
        if (n.protoc_idx == 0)
            n.protoc_idx = idx_cnt++;

    /// Declare the generator

    using boost::spirit::eol;           // end of line
    using boost::spirit::ascii::string;
    using boost::spirit::lit;
    using boost::spirit::long_long;

    // Indentation helpers (replace with special eol,
    // indend_, outdend_ and indend[...] directives)
    auto indent = "    ";

    // tuple(string type, mangled_name, index)
    auto var_gen = 
          indent 
          << string << " " << string       // type and name/submsg
          << " = " << long_long << ";"     // index
          << "  // " << string             // mangled name
          << eol;

    // range[tuple]
    auto protoc_gen =
               "package " << lit(package) << ";" << eol
          << eol
          << eol
          << "message Value {"
          << *var_gen
          << "}";

    // Format the data properly

    using boost::adaptors::filtered;
    using std::make_tuple;
    using std::tuple;

    // TODO: seriously, this syntax is terrible
    typedef tuple<std::string&, std::string&, int64_t, std::string&> ptup;
    function<bool(ShTreeNode&)> missing_paths = [](const ShTreeNode &n) {
        if (n.mangled_path.empty()) {
            std::cerr << "[WARNING] Missing path for " << n.cpp_var << "\n";
            return false;
        }
        return true;
    };
    function<ptup(ShTreeNode&)> mktup = [](ShTreeNode &n) {
        return ptup{
            n.protoc_lit
          , n.mangled_path
          , n.protoc_idx
          , n.cpp_var }; };
    auto data_gen = tree | filtered(missing_paths) | transformed(mktup);

    // TODO: Needed because format invokes size() on the
    // range; can we avoid this?
    std::vector<ptup> data(data_gen.begin(), data_gen.end());

    // Generate and write the code
    using boost::spirit::karma::format;

    std::ofstream sink{path, std::ofstream::trunc};
    sink << format(protoc_gen, data);
}


}
}
}
