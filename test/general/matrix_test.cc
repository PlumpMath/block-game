#include <cstdlib>
#include <iostream>

#include <lightest/lightest.h>

#include "block_game/general/matrix.h"

using lightest::Update;

namespace {
const size_t kTestOrder{3};
typedef block_game::Matrix<kTestOrder> TestMatrix;

bool TestDefaultConstructor() {
  const TestMatrix matrix;
  const float expected[kTestOrder][kTestOrder]{
    {1.0F, 0.0F, 0.0F},
    {0.0F, 1.0F, 0.0F},
    {0.0F, 0.0F, 1.0F}
  };

  bool success{true};
  for (size_t i{0}; i < kTestOrder; ++i) {
    for (size_t j{0}; j < kTestOrder; ++j) {
      if (matrix[i][j] != expected[i][j]) {
        std::cerr << "default constructor failed: ";
        std::cerr << "element [" << i << "][" << j << "] is " << matrix[i][j] << " instead of " << expected[i][j] << std::endl;
        success = false;
      }
    }
  }
  return success;
}

bool TestInitializerListConstructor() {
  const TestMatrix matrix{
    9.0F, 8.0F, 7.0F,
    6.0F, 5.0F, 4.0F,
    3.0F, 2.0F, 1.0F
  };
  const float expected[kTestOrder][kTestOrder]{
    {9.0F, 8.0F, 7.0F},
    {6.0F, 5.0F, 4.0F},
    {3.0F, 2.0F, 1.0F}
  };

  bool success{true};
  for (size_t i{0}; i < kTestOrder; ++i) {
    for (size_t j{0}; j < kTestOrder; ++j) {
      if (matrix[i][j] != expected[i][j]) {
        std::cerr << "initializer list constructor failed: ";
        std::cerr << "element [" << i << "][" << j << "] is " << matrix[i][j] << " instead of " << expected[i][j] << std::endl;
        success = false;
      }
    }
  }
  return success;
}

bool TestEqualityTrue() {
  const TestMatrix matrix_0;
  const TestMatrix matrix_1;

  const bool success{matrix_0 == matrix_1};
  if (!success) {
    std::cerr << "equality operator failed: comparison of equal Matrix objects returns false" << std::endl;
  }
  return success;
}

bool TestEqualityFalse() {
  const TestMatrix matrix_0;
  TestMatrix matrix_1;
  matrix_1[1][1] = 0.0F;

  const bool success{!(matrix_0 == matrix_1)};
  if (!success) {
    std::cerr << "equality operator failed: comparison of unequal Matrix objects returns true" << std::endl;
  }
  return success;
}

bool TestEquality() {
  bool success{true};
  Update(success, TestEqualityTrue());
  Update(success, TestEqualityFalse());
  return success;
}

bool TestInequalityTrue() {
  const TestMatrix matrix_0;
  TestMatrix matrix_1;
  matrix_1[1][1] = 0.0F;

  const bool success{matrix_0 != matrix_1};
  if (!success) {
    std::cerr << "inequality operator failed: comparison of unequal Matrix objects returns false" << std::endl;
  }
  return success;
}

bool TestInequalityFalse() {
  const TestMatrix matrix_0;
  const TestMatrix matrix_1;

  const bool success{!(matrix_0 != matrix_1)};
  if (!success) {
    std::cerr << "inequality operator failed: comparison of equal Matrix objects returns true" << std::endl;
  }
  return success;
}

bool TestInequality() {
  bool success{true};
  Update(success, TestInequalityTrue());
  Update(success, TestInequalityFalse());
  return success;
}
}

int main() {
  bool success{true};

  Update(success, TestDefaultConstructor());
  Update(success, TestInitializerListConstructor());

  Update(success, TestEquality());
  Update(success, TestInequality());

  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
