#include <cstdlib>
#include <exception>
#include <iostream>

#include <json/json.h>

#include "general/vector.h"

namespace {
void Update(bool& success, bool test_result) {
  if (!test_result) {
    success = false;
  }
}

const size_t kTestDimensions{3};

bool TestDefaultConstructor() {
  const block_game::Vector<kTestDimensions> vector;
  float expected[kTestDimensions]{0.0F};

  bool success{true};
  for (size_t i{0}; i < kTestDimensions; ++i) {
    if (vector[i] != expected[i]) {
      std::cerr << "default constructor failed: ";
      std::cerr << "element " << i << " is " << vector[i] << " instead of " << expected[i] << std::endl;
      success = false;
    }
  }
  return success;
}

bool TestInitializerListConstructor() {
  const block_game::Vector<kTestDimensions> vector{1.0F, 2.0F, 3.0F};
  const float expected[]{1.0F, 2.0F, 3.0F};

  bool success{true};
  for (size_t i{0}; i < kTestDimensions; ++i) {
    if (vector[i] != expected[i]) {
      std::cerr << "initializer list constructor failed: ";
      std::cerr << "element " << i << " is " << vector[i] << " instead of " << expected[i] << std::endl;
      success = false;
    }
  }
  return success;
}

bool TestJSONConstructorNominal() {
  Json::Value value{Json::arrayValue};
  for (size_t i{1}; i <= kTestDimensions; ++i) {
    value.append(static_cast<float>(i));
  }

  bool success{true};
  try {
    const block_game::Vector<kTestDimensions> vector{value};
    for (size_t i{0}; i < kTestDimensions; ++i) {
      if (vector[i] != value[i].asFloat()) {
        std::cerr << "JSON constructor failed: element " << i << " is " << vector[i] << " instead of " << value[i] << std::endl;
        success = false;
      }
    }
  } catch (const std::exception&) {
    std::cerr << "JSON constructor failed: exception thrown for valid input" << std::endl;
    success = false;
  }
  return success;
}

bool TestJSONConstructorNonArray() {
  Json::Value value;

  bool success{true};
  bool exception_thrown{false};
  try {
    const block_game::Vector<kTestDimensions> vector{value};
  } catch (const std::exception&) {
    exception_thrown = true;
  }
  if (!exception_thrown) {
    std::cerr << "JSON constructor failed: no exception thrown for non-array JSON value" << std::endl;
    success = false;
  }
  return success;
}

bool TestJSONConstructorMismatchedDimensions(Json::ArrayIndex num_dimensions) {
  Json::Value value{Json::arrayValue};
  for (Json::ArrayIndex i{1}; i <= num_dimensions; ++i) {
    value.append(static_cast<float>(i));
  }

  bool success{true};
  bool exception_thrown{false};
  try {
    const block_game::Vector<kTestDimensions> vector{value};
  } catch (const std::exception&) {
    exception_thrown = true;
  }
  if (!exception_thrown) {
    std::cerr << "JSON constructor failed: ";
    std::cerr << "no exception thrown for JSON value with ";
    std::cerr << value.size() << " dimensions instead of ";
    std::cerr << kTestDimensions << std::endl;
    success = false;
  }
  return success;
}

bool TestJSONConstructorTooFewDimensions() {
  return TestJSONConstructorMismatchedDimensions(kTestDimensions - 1);
}

bool TestJSONConstructorTooManyDimensions() {
  return TestJSONConstructorMismatchedDimensions(kTestDimensions + 1);
}

bool TestJSONConstructorNonNumericChild() {
  Json::Value value{Json::arrayValue};
  value.resize(kTestDimensions);

  bool success{true};
  bool exception_thrown{false};
  try {
    const block_game::Vector<kTestDimensions> vector{value};
  } catch (const std::exception&) {
    exception_thrown = true;
  }
  if (!exception_thrown) {
    std::cerr << "JSON constructor failed: no exception thrown for non-numeric JSON child value" << std::endl;
    success = false;
  }
  return success;
}

bool TestJSONConstructor() {
  bool success{true};
  Update(success, TestJSONConstructorNominal());
  Update(success, TestJSONConstructorNonArray());
  Update(success, TestJSONConstructorTooFewDimensions());
  Update(success, TestJSONConstructorTooManyDimensions());
  Update(success, TestJSONConstructorNonNumericChild());
  return success;
}

bool TestEqualsTrue() {
  const block_game::Vector<kTestDimensions> vector_0{1.0F, 2.0F, 3.0F};
  const block_game::Vector<kTestDimensions> vector_1{1.0F, 2.0F, 3.0F};

  if (vector_0 == vector_1) {
    return true;
  } else {
    std::cerr << "== operator failed: comparison of equal Vector objects returns false" << std::endl;
    return false;
  }
}

bool TestEqualsFalse() {
  const block_game::Vector<kTestDimensions> vector_0{1.0F, 2.0F, 3.0F};
  const block_game::Vector<kTestDimensions> vector_1{3.0F, 2.0F, 1.0F};

  if (vector_0 == vector_1) {
    std::cerr << "== operator failed: comparison of unequal Vector objects returns true" << std::endl;
    return false;
  } else {
    return true;
  }
}

bool TestEquals() {
  bool success{true};
  Update(success, TestEqualsTrue());
  Update(success, TestEqualsFalse());
  return success;
}

bool TestNotEqualsTrue() {
  const block_game::Vector<kTestDimensions> vector_0{1.0F, 2.0F, 3.0F};
  const block_game::Vector<kTestDimensions> vector_1{3.0F, 2.0F, 1.0F};

  if (vector_0 != vector_1) {
    return true;
  } else {
    std::cerr << "!= operator failed: comparison of unequal Vector objects returns false" << std::endl;
    return false;
  }
}

bool TestNotEqualsFalse() {
  const block_game::Vector<kTestDimensions> vector_0{1.0F, 2.0F, 3.0F};
  const block_game::Vector<kTestDimensions> vector_1{1.0F, 2.0F, 3.0F};

  if (vector_0 != vector_1) {
    std::cerr << "!= operator failed: comparison of equal Vector objects returns true" << std::endl;
    return false;
  } else {
    return true;
  }
}

bool TestNotEquals() {
  bool success{true};
  Update(success, TestNotEqualsTrue());
  Update(success, TestNotEqualsFalse());
  return success;
}

bool TestNegative() {
  const block_game::Vector<kTestDimensions> positive{1.0F, 2.0F, 3.0F};
  const block_game::Vector<kTestDimensions> negative{-1.0F, -2.0F, -3.0F};

  if (-positive == negative) {
    return true;
  } else {
    std::cerr << "unary - operator failed: incorrect result" << std::endl;
    return false;
  }
}

bool TestPlus() {
  const block_game::Vector<kTestDimensions> addend_0{1.0F, 2.0F, 3.0F};
  const block_game::Vector<kTestDimensions> addend_1{4.0F, 5.0F, 6.0F};
  const block_game::Vector<kTestDimensions> expected_sum{5.0F, 7.0F, 9.0F};

  if (addend_0 + addend_1 == expected_sum) {
    return true;
  } else {
    std::cerr << "+ operator failed: incorrect result" << std::endl;
    return false;
  }
}
}

int main() {
  bool success{true};
  Update(success, TestDefaultConstructor());
  Update(success, TestInitializerListConstructor());
  Update(success, TestJSONConstructor());
  Update(success, TestEquals());
  Update(success, TestNotEquals());
  Update(success, TestNegative());
  Update(success, TestPlus());
  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
