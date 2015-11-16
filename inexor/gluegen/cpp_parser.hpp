#ifndef INEXOR_RPC_GLUEGEN_CPP_PARSER_HEADER
#define INEXOR_RPC_GLUEGEN_CPP_PARSER_HEADER

#include <functional>
#include <string>

#include <clang/AST/Decl.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>

#include "inexor/util/util.h"

namespace inexor {
namespace rpc {
namespace gluegen {

namespace intern {

std::string canonical_decl(clang::NamedDecl *d) {
  auto *dc = d->getDeclContext();
  auto *ns = dc->isNamespace()
      ? clang::NamespaceDecl::castFromDeclContext(dc)
      : NULL;
  std::string sub = ns ? canonical_decl(ns) : "";
  return sub + "::" + d->getNameAsString();
}

} // ns intern

/// Basic no-op shared decl visitor for find_shared_decls
///
/// You can extend this class if you only care for a subset
/// of visitations
struct SharedDeclVisitor {
  /// Invoked for ans SharedVar found;
  ///
  /// @param cpp_type The c++ type of the variable
  /// @param cpp_var The canonical name of the variable (e.g. ::inexor::my_var)
  /// @param tree_path The path to the variable in inexor tree
  void shared_var(
      std::string cpp_type  INEXOR_ATTR_UNUSED
    , std::string cpp_var   INEXOR_ATTR_UNUSED
    , std::string tree_path INEXOR_ATTR_UNUSED) {}
};

/// Find all the Shared Declarations in a set of source files
///
/// At the moment this is any SharedVar declaration.
///
/// @param opt The list of options to pass to clang++
/// @param src The list of source files to search in
/// @param cb  Callback; the visitor to invoke when something is found
/// @tparam OptRange any Range (must define begin and end)
/// @tparam SourceRange any RangeA
/// @tparam Visitor Must implement the same interface as SharedDeclVisitor
template<typename OptRange, typename SourceRange, typename Visitor>
void find_shared_decls(
      const OptRange &opt
    , const SourceRange &src
    , Visitor &cb__) {

  // TODO: This is terrible; hack so we can pass this to the
  // InxVisitor; we should find something where we could
  // pass this along
  thread_local Visitor &cb = cb__;

  // TODO: This is all very
  struct InxVisitor : clang::RecursiveASTVisitor<InxVisitor> {
  public:
    bool VisitDecl(clang::Decl *x) {
      auto *xv = dynamic_cast<clang::VarDecl*>(x);
      if (!xv) return true;
      const auto *bt = xv->getType().getTypePtrOrNull();
      if (!bt) return true;
      auto *tt = bt->getAs<clang::TemplateSpecializationType>();
      if (!tt) return true;
      auto *tmpl = tt->getTemplateName().getAsTemplateDecl();
      std::string tmpl_name = intern::canonical_decl(tmpl);
      if (tmpl_name != "::SharedVar") return true;

      cb.shared_var(
          tt->getArg(0).getAsType().getAsString() // cpp type
        , intern::canonical_decl(xv) // cpp canonical name
        , "" // tree path
      );

      return true;
    }
  };

  struct InxASTConsumer : clang::ASTConsumer {
    InxVisitor ast_visitor;

    virtual void HandleTranslationUnit(clang::ASTContext &context) {
      ast_visitor.TraverseDecl(context.getTranslationUnitDecl());
    }
  };

  struct InxFrontendAction : clang::ASTFrontendAction {
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
          clang::CompilerInstance &CI INEXOR_ATTR_UNUSED
        , clang::StringRef file INEXOR_ATTR_UNUSED) {
      return std::unique_ptr<clang::ASTConsumer>{ new InxASTConsumer{} };
    }
  };

  // TODO: Damn llvm for their Array Ref requiring contiguous memory
  // (use an optimization for contiguous memory when we have the iterators)
  std::vector<std::string>
      opt_buf{ opt.begin(), opt.end() }
    , src_buf{ src.begin(), src.end() };

  llvm::cl::OptionCategory clang_category("inexor-tree-api-generator");
  clang::tooling::FixedCompilationDatabase cdb{ ".", opt_buf };
  clang::tooling::ClangTool tool{ cdb, src_buf };

  tool.run(clang::tooling::newFrontendActionFactory<InxFrontendAction>().get());
}

}
}
}

#endif
