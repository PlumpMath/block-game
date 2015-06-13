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
}

int main() {
  bool success{true};

  Update(success, TestDefaultConstructor());

  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
