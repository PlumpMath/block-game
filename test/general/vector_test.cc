#include <cstdlib>
#include <exception>
#include <iostream>

#include <json/json.h>

#include "general/vector.h"

namespace {
void TestDefaultConstructor(bool& success) {
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

void TestInitializerListConstructor(bool& success) {
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

void TestJSONConstructor(bool& success) {
  Json::Value value{Json::arrayValue};
  value.append(1.0F);
  value.append(2.0F);
  value.append(3.0F);
  value.append(4.0F);
  value.append(5.0F);
  value.append(6.0F);
  value.append(7.0F);
  value.append(8.0F);
  value.append(9.0F);
  value.append(10.0F);

  try {
    block_game::Vector<10> vector{value};
    for (size_t i{0}; i < 10; ++i) {
      if (vector[i] != value[i].asFloat()) {
        std::cerr << "JSON constructor failed: element " << i << " is " << vector[i] << " instead of " << value[i] << std::endl;
        success = false;
      }
    }
  } catch (const std::exception&) {
    std::cerr << "JSON constructor failed: exception thrown for valid input" << std::endl;
    success = false;
  }
}

void TestJSONConstructorNonArray(bool& success) {
  Json::Value value;

  bool exception_thrown{false};
  try {
    block_game::Vector<10> vector{value};
  } catch (const std::exception&) {
    exception_thrown = true;
  }
  if (!exception_thrown) {
    std::cerr << "JSON constructor failed: no exception thrown for non-array JSON value" << std::endl;
    success = false;
  }
}

void TestJSONConstructorMismatchedDimensions(Json::ArrayIndex num_dimensions, bool& success) {
  Json::Value value{Json::arrayValue};
  for (Json::ArrayIndex i{1}; i <= num_dimensions; ++i) {
    value.append(static_cast<float>(i));
  }

  bool exception_thrown{false};
  try {
    block_game::Vector<10> vector{value};
  } catch (const std::exception&) {
    exception_thrown = true;
  }
  if (!exception_thrown) {
    std::cerr << "JSON constructor failed: ";
    std::cerr << "no exception thrown for JSON value with ";
    std::cerr << value.size() << " dimensions instead of ";
    std::cerr << 10 << std::endl;
    success = false;
  }
}

void TestJSONConstructorTooFewDimensions(bool& success) {
  TestJSONConstructorMismatchedDimensions(5, success);
}

void TestJSONConstructorTooManyDimensions(bool& success) {
  TestJSONConstructorMismatchedDimensions(20, success);
}

void TestJSONConstructorNonNumericChild(bool& success) {
  Json::Value value{Json::arrayValue};
  value.resize(10);

  bool exception_thrown{false};
  try {
    block_game::Vector<10> vector{value};
  } catch (const std::exception&) {
    exception_thrown = true;
  }
  if (!exception_thrown) {
    std::cerr << "JSON constructor failed: no exception thrown for non-numeric JSON child value" << std::endl;
    success = false;
  }
}
}

int main() {
  bool success{true};
  TestDefaultConstructor(success);
  TestInitializerListConstructor(success);
  TestJSONConstructor(success);
  TestJSONConstructorNonArray(success);
  TestJSONConstructorTooFewDimensions(success);
  TestJSONConstructorTooManyDimensions(success);
  TestJSONConstructorNonNumericChild(success);
  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
