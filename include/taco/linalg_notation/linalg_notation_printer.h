#ifndef TACO_LINALG_NOTATION_PRINTER_H
#define TACO_LINALG_NOTATION_PRINTER_H

#include <ostream>
#include "taco/linalg_notation/linalg_notation_visitor.h"

namespace taco {

class LinalgNotationPrinter : public LinalgExprVisitorStrict {
public:
  LinalgNotationPrinter(std::ostream& os);

  void print(const LinalgExpr& expr);

  using LinalgExprVisitorStrict::visit;

  // Scalar Expressions
  void visit(const VarNode*);
  void visit(const LiteralNode*);
  void visit(const NegNode*);
  void visit(const AddNode*);
  void visit(const SubNode*);
  void visit(const MatMulNode*);
  void visit(const ElemMulNode*);
  void visit(const DivNode*);
  void visit(const TransposeNode*);

private:
  std::ostream& os;

  enum class Precedence {
    ACCESS = 2,
    VAR = 2,
    FUNC = 2,
    NEG = 3,
    TRANSPOSE = 3,
    MATMUL = 5,
    ELEMMUL = 5,
    DIV = 5,
    ADD = 6,
    SUB = 6,
    TOP = 20
  };
  Precedence parentPrecedence;

  template <typename Node> void visitBinary(Node op, Precedence p);
};

}
#endif //TACO_LINALG_NOTATION_PRINTER_H