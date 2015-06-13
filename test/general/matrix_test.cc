#include <cstdlib>

#include <lightest/lightest.h>

#include "block_game/general/matrix.h"

using lightest::Update;

namespace {
const size_t kTestOrder{3};
typedef block_game::Matrix<kTestOrder> TestMatrix;
}

int main() {
  bool success{true};
  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
