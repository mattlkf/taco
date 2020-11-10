//
// Created by Olivia Hsu on 11/10/20.
//

#ifndef TACO_LINALG_NOTATATION_TO_INDEX_REWRITER_H
#define TACO_LINALG_NOTATATION_TO_INDEX_REWRITER_H

#include <ostream>
#include "taco/linalg_notation/linalg_notation_visitor.h"
#include "taco/index_notation/index_notation.h"

namespace taco {

class TensorVar;
class IndexVar;

class IndexStmt;
class Assignment;

class IndexExpr;
class Access;
class Literal;
class Neg;
class Add;
class Sub;
class Mul;
class Div;

class LinalgNotationToIndexRewriter : public util::Uncopyable {
public:
  LinalgNotationToIndexRewriter();
  ~LinalgNotationToIndexRewriter() = default;

  IndexStmt rewrite(const LinalgStmt &expr);

protected:
  IndexStmt rewriteLinalgAssignment(LinalgAssignment linalgAssignment);

  IndexExpr rewriteVar(LinalgVarNode* var);
  IndexExpr rewriteLiteral(LinalgLiteralNode* literal);
  IndexExpr rewriteNeg(LinalgNegNode* neg);
  IndexExpr rewriteAdd(LinalgAddNode* add);
  IndexExpr rewriteSub(LinalgSubNode* sub);
  IndexExpr rewriteMatMul(LinalgMatMulNode* matmul);
  IndexExpr rewriteElemMul(LinalgElemMulNode* elemmul);
  IndexExpr rewriteDiv(LinalgDivNode* div);
  IndexExpr rewriteTranspose(LinalgTransposeNode* transpose);

private:
  std::vector<IndexVar> active_indices;

  class Visitor;
  friend class Visitor;
  std::shared_ptr<Visitor> visitor;

};

}
#endif //TACO_LINALG_NOTATATION_TO_INDEX_REWRITER_H