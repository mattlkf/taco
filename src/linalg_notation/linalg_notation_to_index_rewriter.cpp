//
// Created by Olivia Hsu on 11/10/20.
//
#include "taco/linalg_notation/linalg_notatation_to_index_rewriter.h"
#include "taco/linalg_notation/linalg_notation_nodes.h"
#include "taco/linalg_notation/linalg_notation_visitor.h"

using namespace std;

namespace taco {

class LinalgNotationToIndexRewriter::Visitor : public LinalgNotationVisitorStrict {
public:
  Visitor(LinalgNotationToIndexRewriter* rewriter) : rewriter(rewriter) {}
  IndexStmt rewrite(LinalgStmt stmt) {
    this->indexStmt = IndexStmt();
    LinalgStmtVisitorStrict::visit(stmt);
    return this->indexStmt;
  }
  IndexExpr lower(IndexExpr expr) {
    this->indexExpr = IndexExpr();
    LinalgExprVisitorStrict::visit(expr);
    return this->indexExpr;
  }
private:
  LinalgNotationToIndexRewriter* rewriter;
  IndexExpr indexExpr;
  IndexStmt indexStmt;
  using LinalgNotationVisitorStrict::visit;
  void visit(const LinalgVarNode* node)         {indexExpr = rewriter->rewriteVar(node)};
  void visit(const LinalgLiteralNode* node)     {indexExpr = rewriter->rewriteLiteral(node)};
  void visit(const LinalgNegNode* node)         {indexExpr = rewriter->rewriteNeg(node)};
  void visit(const LinalgAddNode* node)         {indexExpr = rewriter->rewriteAdd(node)};
  void visit(const LinalgSubNode* node)         {indexExpr = rewriter->rewriteSub(node)};
  void visit(const LinalgMatMulNode* node)      {indexExpr = rewriter->rewriteMatMul(node)};
  void visit(const LinalgElemMulNode* node)     {indexExpr = rewriter->rewriteElemMul(node)};
  void visit(const LinalgDivNode* node)         {indexExpr = rewriter->rewriteDiv(node)};
  void visit(const LinalgTransposeNode* node)   {indexExpr = rewriter->rewriteTranspose(node)};
  void visit(const LinalgAssignmentNode* node)  {indexStmt = rewriter->rewriteLinalgAssignment(node)};
};

IndexStmt LinalgNotationToIndexRewriter::rewrite(const LinalgStmt &expr) {
  if (!expr.defined())
    return IndexStmt();
  expr.accept(this);
  return indexNotation;
}

IndexExpr LinalgNotationToIndexRewriter::rewriteVar(const LinalgVarNode* op) {
  return IndexExpr();
}

void LinalgNotationToIndexRewriter::visit(const LinalgAssignmentNode* op) {
  os << op->lhs.getName() << " " << "= ";
  op->rhs.accept(this);
}

}