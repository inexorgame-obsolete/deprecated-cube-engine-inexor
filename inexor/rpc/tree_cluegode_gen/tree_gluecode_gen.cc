#include "clang/Driver/Options.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"

#include <iostream>

using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;

std::string canonical_decl(NamedDecl *d) {
  auto *dc = d->getDeclContext();
  auto *ns = dc->isNamespace()
      ? NamespaceDecl::castFromDeclContext(dc)
      : NULL;
  std::string sub = ns ? canonical_decl(ns) : "";
  return sub + "::" + d->getNameAsString();
}

class InxVisitor : public RecursiveASTVisitor<InxVisitor> {
public:
  bool VisitDecl(Decl *x) {
    auto *xv = dynamic_cast<VarDecl*>(x);
    if (!xv) return true;
    const auto *bt = xv->getType().getTypePtrOrNull();
    if (!bt) return true;
    auto *tt = bt->getAs<TemplateSpecializationType>();
    if (!tt) return true;
    auto *tmpl = tt->getTemplateName().getAsTemplateDecl();
    std::string tmpl_name = canonical_decl(tmpl);
    if (tmpl_name != "::SharedVar") return true;

    cout
      << "(" << tt->getArg(0).getAsType().getAsString() << ") "
      << canonical_decl(xv) << "\n";

    return true;
  }
};

class InxASTConsumer : public ASTConsumer {
public:
  InxVisitor visitor; // doesn't have to be private

  virtual void HandleTranslationUnit(ASTContext &context) {
    visitor.TraverseDecl(context.getTranslationUnitDecl());
  }
};

class InxFrontendAction : public ASTFrontendAction {
public:
  virtual std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef file) {
    return std::unique_ptr<ASTConsumer>{ new InxASTConsumer{} };
  }
};

int main(int argc, const char **argv) {
  llvm::cl::OptionCategory category("inexor-tree-api-generator");
  CommonOptionsParser op(argc, argv, category);

  ClangTool tool{ op.getCompilations(), op.getSourcePathList() };

  auto action_factory = newFrontendActionFactory<InxFrontendAction>();
  return tool.run(action_factory.get());
}
