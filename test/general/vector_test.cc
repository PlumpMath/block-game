#include <cstdlib>
#include <iostream>

#include "general/vector.h"

namespace {
bool success{true};

void TestDefaultConstructor() {
  block_game::Vector<10> vector;
  float expected[10]{0.0F};
  for (size_t i{0}; i < 10; ++i) {
    if (vector[i] != expected[i]) {
      std::cerr << "default constructor failed: ";
      std::cerr << "element " << i << " is " << vector[i] << " instead of " << expected[i] << std::endl;
      success = false;
    }
  }
}

void TestInitializerListConstructor() {
  block_game::Vector<10> vector{1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F};
  float expected[]{1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F};
  for (size_t i{0}; i < 10; ++i) {
    if (vector[i] != expected[i]) {
      std::cerr << "initializer list constructor failed: ";
      std::cerr << "element " << i << " is " << vector[i] << " instead of " << expected[i] << std::endl;
      success = false;
    }
  }
}
}

int main() {
  TestDefaultConstructor();
  TestInitializerListConstructor();
  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
