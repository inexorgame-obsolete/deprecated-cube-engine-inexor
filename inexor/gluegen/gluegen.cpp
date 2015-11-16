#include <iostream>
#include <string>
#include <algorithm>

#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>

#include "inexor/gluegen/cpp_parser.hpp"

using std::string;

int main(int argc, const char **argv) {
  struct {
    void shared_var(string cpp_type, string cpp_var, string tree_path) {
      std::cout
          << "(" << cpp_type << ") " << cpp_var
          << " " << tree_path << "\n";
    }
  } visitor;

  typedef std::vector<string> args_t;
  typedef typename args_t::iterator args_itr;

  args_t args(argv+1, argv+argc-1);
  auto div = boost::find(args, "--");

  inexor::rpc::gluegen::find_shared_decls(
      boost::iterator_range<args_itr>(div+1, args.end())
    , boost::iterator_range<args_itr>(args.begin(), div)
    , visitor);

  return 0;
}
