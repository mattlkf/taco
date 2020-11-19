#include "test.h"
#include <stdio.h>

#include "taco/linalg.h"

using namespace taco;

void wait() {
  scanf("%*c");
}

// Note: run with ./bin/taco-test linalg.demo | sed -e/*linalg.demo*/\{ -e:1 -en\;b1 -e\} -ed
TEST(linalg, demo) {
  cout << "--- Starting demo (press ENTER to continue) ---" << endl;

  wait();

  cout << "--- Before constructing Matrices ---" << endl;
  Matrix<double> B("B", 2, 2, dense, dense);
  Matrix<double> C("C", 2, 2, dense, dense);
  Matrix<double> A("A", 2, 2, dense, dense);
  cout << "--- After constructing Matrices ---" << endl;

  wait();

  cout << "--- Before inserting ---" << endl;
  B.insert(0,0,2);
  B.insert(1,1,1);
  B.insert(0,1,2);

  C.insert(0,0,2);
  C.insert(1,1,2);
  cout << "--- After inserting ---" << endl;

  wait();

  cout << "--- Before an unassigned expression ---" << endl;
  B * C;
  cout << "--- After an unassigned expression ---" << endl;

  wait();

  cout << "--- Before Expression ---" << endl;
  A = B * C;
  cout << "--- After Expression ---" << endl;

  wait();

  cout << "--- Before getIndexAssignment on A ---" << endl;
  cout << A.getIndexAssignment() << endl;
  cout << "--- After getIndexAssignment on A ---" << endl;

  wait();

  cout << "--- Before printing A ---" << endl;
  cout << A << endl;
  cout << "--- After printing A ---" << endl;
}

TEST(linalg, matmul) {
  Matrix<double> B("B", 2, 2, dense, dense);
  Matrix<double> C("C", 2, 2, dense, dense);
  Matrix<double> A("A", 2, 2, dense, dense);

  cout << "--- Before inserting ---" << endl;
  B.insert(0,0,2);
  B.insert(1,1,1);
  B.insert(0,1,2);

  C.insert(0,0,2);
  C.insert(1,1,2);
  cout << "--- After inserting ---" << endl;

  cout << "--- Before Expression ---" << endl;
  A = B * C;
  cout << "--- After Expression ---" << endl;

  cout << "--- Before At ---" << endl;
  cout << "B(0,0): " << B.at(0,0) << endl;
  cout << "A(0,0): " << A.at(0,0) << endl;
  cout << "--- After At ---" << endl;

  cout << "--- Before Rewrite of A ---" << endl;
  A.rewrite();
  cout << "--- After Rewrite of A ---" << endl;

  cout << "--- Before At (A) ---" << endl;
  cout << "A(0,0): " << A.at(0,0) << endl;
  cout << "--- After At (A) ---" << endl;

  cout << "--- before cout of a ---" << endl;
  cout << A << endl;
  cout << "--- after cout of a ---" << endl;

  cout << "--- Before getIndexAssignment on A ---" << endl;
  cout << A.getIndexAssignment() << endl;
  cout << "--- After getIndexAssignment on A ---" << endl;

  ASSERT_EQ(A.at(0,0), 4);
  ASSERT_EQ(A.at(0,1), 4);
  ASSERT_EQ(A.at(1,0), 0);
  ASSERT_EQ(A.at(1,1), 2);

  // TODO: Support this style of accessing and querying the values, too
  /* map<vector<int>, double> vals = {{{0,0},4}, {{0,1},4}, {{1,1},2}}; */
  /* for (auto val = A.beginTyped<int>(); val != A.endTyped<int>(); ++val) { */
  /*   ASSERT_TRUE(util::contains(vals, val->first.toVector())); */
  /*   ASSERT_EQ(vals.at(val->first.toVector()), val->second); */
  /* } */

}

TEST(linalg, tensorbase) {
  Matrix<double> B("B", 2, 2, dense, dense);
  Matrix<double> C("C", 2, 2, dense, dense);
  Matrix<double> A("A", 2, 2, dense, dense);

  B.insert(0,0,1);
  B.insert(1,1,4);

  C.insert(0,1,2);
  C.insert(1,0,3);

  A = B + C;

  // Should be [1,2,3,4]
  cout << A << endl;
  
  cout << A.getIndexAssignment();

  ASSERT_EQ(A.at(0,0), 1);
  ASSERT_EQ(A.at(0,1), 2);
  ASSERT_EQ(A.at(1,0), 3);
  ASSERT_EQ(A.at(1,1), 4);
}

TEST(linalg, matvec_mul) {
  Vector<double> x("x", 2, dense);
  Vector<double> b("b", 2, dense);
  Matrix<double> A("A", 2, 2, dense, dense);

  b.insert(0,2);
  b.insert(1,1);

  A.insert(0,0,1);
  A.insert(0,1,3);
  A.insert(1,1,2);

  x = A*b;

  ASSERT_EQ(x.at(0), 5);
  ASSERT_EQ(x.at(1), 2);

  // Should be [5,2]
  cout << x << endl;

  cout << x.getIndexAssignment();
}

TEST(linalg, vecmat_mul) {
  Vector<double> x("x", 2, dense, false);
  Vector<double> b("b", 2, dense, false);
  Matrix<double> A("A", 2, 2, dense, dense);

  b.insert(0,3);
  b.insert(1,-2);

  A.insert(0,0,5);
  A.insert(0,1,2);
  A.insert(1,0,-1);

  // Should be [17, 6]
  x = b * A;

  ASSERT_EQ(x.at(0), 17);
  ASSERT_EQ(x.at(1), 6);

  cout << x << endl;

  cout << x.getIndexAssignment();
}

TEST(linalg, inner_mul) {
  Scalar<double> x("x", true);
  Vector<double> b("b", 2, dense, false);
  Vector<double> a("a", 2, dense, true);

  b.insert(0,2);
  b.insert(1,3);

  a.insert(0,-3);
  a.insert(1,5);

  x = b * a;

  // Should be 9
  cout << x << endl;

  cout << x.getIndexAssignment();


  ASSERT_TRUE(1);
}

TEST(linalg, outer_mul) {
  Matrix<double> X("X", 2, 2, dense, dense);
  Vector<double> b("b", 2, dense, false);
  Vector<double> a("a", 2, dense, true);

  b.insert(0,2);
  b.insert(1,3);

  a.insert(0,-3);
  a.insert(1,5);

  X = a * b;

  // Should be [-6,-9,10,15]
  cout << X << endl;

  cout << X.getIndexAssignment();

  cout << X;

  ASSERT_TRUE(1);
}

TEST(linalg, rowvec_transpose) {
  Vector<double> b("b", 2, dense, false);
  Matrix<double> A("A", 2, 2, dense, dense);
  Scalar<double> a("a", true);

  b.insert(0,2);
  b.insert(1,5);

  A.insert(0,0,1);
  A.insert(0,1,2);
  A.insert(1,1,4);

  a = transpose(transpose(b) * A * b);

  // Should be 124
  cout << a << endl;

  cout << a.getIndexAssignment();

  ASSERT_TRUE(1);
}

TEST(linalg, tensorapi) {
  cout << "--- Beginning of TensorAPI test ---" << endl;
  Tensor<double> a({2,2}, dense);
  Tensor<double> b({2,3}, dense);
  Tensor<double> c({3,2}, dense);

  cout << "--- Initialized Tensors ---" << endl;

  b(0,0) = 2;
  b(1,1) = 1;
  b(0,1) = 2;

  cout << "--- Initializing c ---" << endl;

  c(0,0) = 2;
  c(1,1) = 2;

  cout << "--- Declaring IndexVars ---" << endl;

  IndexVar i,j,k;

  // The original
  /* a(i,j) = b(i,k) * c(k,j); */

  // The broken-up version
  cout << "--- Creating operand IndexExprs ---" << endl;

  IndexExpr tc = c(k,j);
  IndexExpr tb = b(i,k);

  cout << "Pre-assignment" << endl;
  a(i,j) = tb * tc;
  cout << "Post-assignment" << endl;

  /* cout << a << endl; */
}

TEST(linalg, complex_expr) {
  Matrix<double> A("A", 2, 2, dense, dense);
  Matrix<double> B("B", 2, 2, dense, dense);
  Matrix<double> C("C", 2, 2, dense, dense);
  Matrix<double> D("D", 2, 2, dense, dense);
  Matrix<double> E("D", 2, 2, dense, dense);

  A = E*elemMul(B+C, D);

  cout << A << endl;

  cout << A.getIndexAssignment();

  ASSERT_TRUE(1);
}
