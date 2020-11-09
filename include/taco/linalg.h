#ifndef TACO_LINALG_H
#define TACO_LINALG_H

#include "taco/type.h"
#include "taco/tensor.h"
#include "taco/format.h"

#include "taco/linalg_notation/linalg_notation.h"
#include "taco/linalg_notation/linalg_notation_nodes.h"
#include "taco/linalg_notation/linalg_notation_printer.h"


namespace taco {

class LinalgBase : public LinalgExpr {
protected:
  std::string name;
  Type tensorType;

  // The associated tensor
  TensorBase *tbase;

  LinalgAssignment assignment;
  IndexStmt indexAssignment;

  int idxcount;

  IndexExpr rewrite(LinalgExpr linalg, std::vector<IndexVar> indices);
  IndexVar getUniqueIndex();
  std::vector<IndexVar> getUniqueIndices(size_t order);
public:
  LinalgBase(std::string name, Type tensorType);
  LinalgBase(std::string name, Type tensorType, Format format);
  LinalgBase(std::string name, Type tensorType, Datatype dtype, std::vector<size_t> dims, Format format);
  /// [LINALG NOTATION]
  LinalgAssignment operator=(const LinalgExpr& expr);
  const LinalgAssignment getAssignment() const;
  const IndexStmt getIndexAssignment() const;

  // TODO: remove
  void ping() {
    std::cout << name << ".ping()" << std::endl;
  }
  IndexStmt rewrite();

  typedef LinalgVarNode Node;
  /* LinalgBase operator=(LinalgExpr) { */
  /*   return (LinalgBase)LinalgExpr; */
  /* } */
};

std::ostream& operator<<(std::ostream& os, const LinalgBase& linalg);
IndexExpr rewrite(LinalgExpr linalg, std::vector<IndexVar>);
IndexStmt rewrite(LinalgStmt linalg);

// ------------------------------------------------------------
// Matrix class
// ------------------------------------------------------------

template <typename CType>
class Matrix : public LinalgBase {
public:
  explicit Matrix(std::string name);
  Matrix(std::string name, size_t dim1, size_t dim2);
  Matrix(std::string name, std::vector<size_t> dimensions);
  Matrix(std::string name, size_t dim1, size_t dim2, Format format);
  Matrix(std::string name, std::vector<size_t> dimensions, Format format);
  Matrix(std::string name, size_t dim1, size_t dim2, ModeFormat format1, ModeFormat format2);
  Matrix(std::string name, Type tensorType);
  Matrix(std::string name, Type tensorType, Format format);
  LinalgAssignment operator=(const LinalgExpr& expr) {
    return LinalgBase::operator=(expr);
  }

  // Support some Read methods
  CType at(int coord_x, int coord_y);

};

// ------------------------------------------------------------
// Matrix template method implementations
// ------------------------------------------------------------

template <typename CType>
Matrix<CType>::Matrix(std::string name) : LinalgBase(name, Type(type<CType>(), {42, 42})) {}
template <typename CType>
Matrix<CType>::Matrix(std::string name, std::vector<size_t> dimensions) : LinalgBase(name, Type(type<CType>(), dimensions)) {}
template <typename CType>
Matrix<CType>::Matrix(std::string name, size_t dim1, size_t dim2) : LinalgBase(name, Type(type<CType>(), {dim1, dim2})) {}
template <typename CType>
Matrix<CType>::Matrix(std::string name, size_t dim1, size_t dim2, Format format) :
  LinalgBase(name, Type(type<CType>(), {dim1, dim2}), format) {}
template <typename CType>
Matrix<CType>::Matrix(std::string name, std::vector<size_t> dimensions, Format format) :
  LinalgBase(name, Type(type<CType>(), dimensions), format) {}
template <typename CType>
Matrix<CType>::Matrix(std::string name, size_t dim1, size_t dim2, ModeFormat format1, ModeFormat format2) :
  LinalgBase(name, Type(type<CType>(), {dim1, dim2}), Format({format1, format2})) {}
template <typename CType>
Matrix<CType>::Matrix(std::string name, Type tensorType) : LinalgBase(name, tensorType) {}
template <typename CType>
Matrix<CType>::Matrix(std::string name, Type tensorType, Format format) : LinalgBase(name, tensorType, format) {}

// Definition of Read methods
template <typename CType>
CType Matrix<CType>::at(int coord_x, int coord_y) {
  std::cout << "Name: " << name << std::endl;
  std::cout << tbase << std::endl;
  std::cout << "Matrix found a TBase " << tbase->getName() << std::endl;
  std::cout << "Will print a coordinate" << std::endl;


  // Check if this LinalgBase holds an assignment
  if (this->assignment.ptr != NULL) {
    std::cout << "This matrix is the result of an assignment" << std::endl;
  }

  return tbase->at<CType>({coord_x, coord_y});
}
// ------------------------------------------------------------
// Vector class
// ------------------------------------------------------------

template <typename CType>
class Vector : public LinalgBase {
  std::string name;
  Datatype ctype;
public:
  explicit Vector(std::string name);
  Vector(std::string name, size_t dim);
  Vector(std::string name, size_t dim, Format format);
  Vector(std::string name, size_t dim, ModeFormat format);
  Vector(std::string name, Type type, Format format);
  Vector(std::string name, Type type, ModeFormat format);
  LinalgAssignment operator=(const LinalgExpr& expr) {
    return LinalgBase::operator=(expr);
  }
};

// ------------------------------------------------------------
// Vector template method implementations
// ------------------------------------------------------------

template <typename CType>
Vector<CType>::Vector(std::string name) : LinalgBase(name, Type(type<CType>(), {42})) {}
template <typename CType>
Vector<CType>::Vector(std::string name, size_t dim) : LinalgBase(name, Type(type<CType>(), {dim})) {}
template <typename CType>
Vector<CType>::Vector(std::string name, size_t dim, Format format) : LinalgBase(name, Type(type<CType>(), {dim}), format) {}
template <typename CType>
Vector<CType>::Vector(std::string name, size_t dim, ModeFormat format) :
  LinalgBase(name, Type(type<CType>(), {dim}), Format(format)) {}
template <typename CType>
Vector<CType>::Vector(std::string name, Type type, Format format) :
  LinalgBase(name, type, format) {}
template <typename CType>
Vector<CType>::Vector(std::string name, Type type, ModeFormat format) :
  LinalgBase(name, type, Format(format)) {}
}
#endif