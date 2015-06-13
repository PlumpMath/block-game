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

bool TestAddition() {
  const TestMatrix addend_0{
    1.0F, 2.0F, 3.0F,
    4.0F, 5.0F, 6.0F,
    7.0F, 8.0F, 9.0F
  };
  const TestMatrix addend_1{
    10.0F, 11.0F, 12.0F,
    13.0F, 14.0F, 15.0F,
    16.0F, 17.0F, 18.0F
  };
  const TestMatrix expected_sum{
    11.0F, 13.0F, 15.0F,
    17.0F, 19.0F, 21.0F,
    23.0F, 25.0F, 27.0F
  };

  const bool success{addend_0 + addend_1 == expected_sum};
  if (!success) {
    std::cerr << "addition operator failed: incorrect result" << std::endl;
  }
  return success;
}

bool TestSubtraction() {
  const TestMatrix minuend{
    11.0F, 13.0F, 15.0F,
    17.0F, 19.0F, 21.0F,
    23.0F, 25.0F, 27.0F
  };
  const TestMatrix subtrahend{
    1.0F, 2.0F, 3.0F,
    4.0F, 5.0F, 6.0F,
    7.0F, 8.0F, 9.0F
  };
  const TestMatrix expected_difference{
    10.0F, 11.0F, 12.0F,
    13.0F, 14.0F, 15.0F,
    16.0F, 17.0F, 18.0F
  };

  const bool success{minuend - subtrahend == expected_difference};
  if (!success) {
    std::cerr << "subtraction operator failed: incorrect result" << std::endl;
  }
  return success;
}

bool TestMultiplication() {
  const TestMatrix left{
    10.0F, 10.0F, 10.0F,
    10.0F, 0.0F, 0.0F,
    10.0F, 0.0F, 0.0F
  };
  const TestMatrix right{
    0.0F, 0.0F, 10.0F,
    0.0F, 0.0F, 10.0F,
    10.0F, 10.0F, 10.0F
  };
  const TestMatrix expected_product{
    100.0F, 100.0F, 300.0F,
    0.0F, 0.0F, 100.0F,
    0.0F, 0.0F, 100.0F
  };

  const bool success{left * right == expected_product};
  if (!success) {
    std::cerr << "multiplication operator failed: incorrect result" << std::endl;
  }
  return success;
}

bool TestAdditionAssignment() {
  TestMatrix original{
    1.0F, 2.0F, 3.0F,
    4.0F, 5.0F, 6.0F,
    7.0F, 8.0F, 9.0F
  };
  const TestMatrix addend{
    10.0F, 11.0F, 12.0F,
    13.0F, 14.0F, 15.0F,
    16.0F, 17.0F, 18.0F
  };
  const TestMatrix expected_sum{
    11.0F, 13.0F, 15.0F,
    17.0F, 19.0F, 21.0F,
    23.0F, 25.0F, 27.0F
  };

  const TestMatrix sum{original += addend};
  const bool success{original == expected_sum && sum == expected_sum};
  if (!success) {
    std::cerr << "addition assignment operator failed: incorrect result" << std::endl;
  }
  return success;
}

bool TestSubtractionAssignment() {
  TestMatrix original{
    11.0F, 13.0F, 15.0F,
    17.0F, 19.0F, 21.0F,
    23.0F, 25.0F, 27.0F
  };
  const TestMatrix subtrahend{
    1.0F, 2.0F, 3.0F,
    4.0F, 5.0F, 6.0F,
    7.0F, 8.0F, 9.0F
  };
  const TestMatrix expected_difference{
    10.0F, 11.0F, 12.0F,
    13.0F, 14.0F, 15.0F,
    16.0F, 17.0F, 18.0F
  };

  const TestMatrix difference{original -= subtrahend};
  const bool success{original == expected_difference && difference == expected_difference};
  if (!success) {
    std::cerr << "subtraction assignment operator failed: incorrect result" << std::endl;
  }
  return success;
}
}

int main() {
  bool success{true};

  Update(success, TestDefaultConstructor());
  Update(success, TestInitializerListConstructor());

  Update(success, TestEquality());
  Update(success, TestInequality());

  Update(success, TestAddition());
  Update(success, TestSubtraction());

  Update(success, TestMultiplication());

  Update(success, TestAdditionAssignment());
  Update(success, TestSubtractionAssignment());

  return lightest::ToExitStatus(success);
}
