#pragma once

#include <functional>
#include <string>
#include <regex>

#include <clang/AST/Decl.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>

#include <boost/range/algorithm.hpp>

#include "inexor/util.hpp"

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

/// Extract "named" annotations in the form:
///
/// ```
/// __attribute__(( annotate("Key=Value") )) int x;
/// ```
///
/// If there is no '=' sign, the Key is treted as empty and
/// the entire string will be passed as key.
///
/// @param r The annotations to check in
/// @param cb The callback that will be called for each
///   annotation we found. Can also abort the search by
///   returning false.
template<typename AnnotRange>
void extract_named_annotations(AnnotRange r
    , std::function<bool(std::string, std::string)> cb) {

    for (auto attr : r) {
        auto *annot = clang::cast<clang::AnnotateAttr>(attr);
        if (!annot) continue;

        auto cref = annot->getAnnotation();
        auto div = boost::find(cref, '=');

        bool abort;
        if (div == cref.end())
            abort = !cb("", std::string{cref.begin(), cref.end()});
        else
            abort = !cb(
                std::string{cref.begin(), div}
              , std::string{div + 1, cref.end()});

        if (abort) return;
    }
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
/// @param options The list of options to pass to clang++
/// @param sources The list of source files to search in
/// @param cb  Callback; the visitor to invoke when something is found
/// @tparam Visitor Must implement the same interface as SharedDeclVisitor
template<typename Visitor>
void find_shared_decls(const std::vector<std::string> &options, const std::vector<std::string> &sources, Visitor &cb__)
{

    // TODO: This is terrible; hack so we can pass this to the
    // InxVisitor; we should find something where we could
    // pass this along
    thread_local Visitor &cb = cb__;

    // TODO: This is all very
    struct InxVisitor : clang::RecursiveASTVisitor<InxVisitor>
    {
    public:

        bool VisitDecl(clang::Decl *x)
        {
            auto *xv = dynamic_cast<clang::VarDecl*>(x);
            if (!xv || xv->hasExternalStorage()) return true;
            const auto *bt = xv->getType().getTypePtrOrNull();
            if (!bt) return true;
            auto *tt = bt->getAs<clang::TemplateSpecializationType>();
            if (!tt) return true;
            auto *tmpl = tt->getTemplateName().getAsTemplateDecl();
            std::string tmpl_name = intern::canonical_decl(tmpl);
            if (tmpl_name != "::SharedVar" || !x->hasAttrs()) return true;

            std::string tree_path="";
            intern::extract_named_annotations(x->getAttrs(), [&tree_path] (std::string key, std::string val)
            {
                if (key == "SharedTree")
                {
                    tree_path = val;
                    return false;
                }
                return true;
            });

            cb.shared_var(
                tt->getArg(0).getAsType().getAsString(), // cpp type
                intern::canonical_decl(xv), // cpp canonical name
                tree_path
            );

            return true;
        }
    };

    struct InxASTConsumer : clang::ASTConsumer {
        InxVisitor ast_visitor;

        virtual void HandleTranslationUnit(clang::ASTContext &context) override
        {
            ast_visitor.TraverseDecl(context.getTranslationUnitDecl());
        }
    };

    struct InxFrontendAction : clang::ASTFrontendAction 
    {
        std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &CI, clang::StringRef file)
        {
            return std::unique_ptr<clang::ASTConsumer>{ new InxASTConsumer{} };
        }
    };

    llvm::cl::OptionCategory clang_category("inexor-tree-api-generator");
    clang::tooling::FixedCompilationDatabase cdb{ ".", options };
    clang::tooling::ClangTool tool{ cdb, sources };

    tool.run(clang::tooling::newFrontendActionFactory<InxFrontendAction>().get());
}

}
}
}
