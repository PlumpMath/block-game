#include <cstdlib>
#include <exception>
#include <iostream>

#include <json/json.h>
#include <lightest/lightest.h>

#include "block_game/general/vector.h"

using lightest::Update;

namespace {
const size_t kTestDimensions{3};
typedef block_game::Vector<kTestDimensions> TestVector;

bool TestDefaultConstructor() {
  const TestVector vector;
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
  const TestVector vector{1.0F, 2.0F, 3.0F};
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
    const TestVector vector{value};
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
    const TestVector vector{value};
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
    const TestVector vector{value};
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
    const TestVector vector{value};
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

bool TestEqualityTrue() {
  const TestVector vector_0{1.0F, 2.0F, 3.0F};
  const TestVector vector_1{1.0F, 2.0F, 3.0F};

  bool success{vector_0 == vector_1};
  if (!success) {
    std::cerr << "equality operator failed: comparison of equal Vector objects returns false" << std::endl;
  }
  return success;
}

bool TestEqualityFalse() {
  const TestVector vector_0{1.0F, 2.0F, 3.0F};
  const TestVector vector_1{3.0F, 2.0F, 1.0F};

  bool success{!(vector_0 == vector_1)};
  if (!success) {
    std::cerr << "equality operator failed: comparison of unequal Vector objects returns true" << std::endl;
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
  const TestVector vector_0{1.0F, 2.0F, 3.0F};
  const TestVector vector_1{3.0F, 2.0F, 1.0F};

  bool success{vector_0 != vector_1};
  if (!success) {
    std::cerr << "inequality operator failed: comparison of unequal Vector objects returns false" << std::endl;
  }
  return success;
}

bool TestInequalityFalse() {
  const TestVector vector_0{1.0F, 2.0F, 3.0F};
  const TestVector vector_1{1.0F, 2.0F, 3.0F};

  bool success{!(vector_0 != vector_1)};
  if (!success) {
    std::cerr << "inequality operator failed: comparison of equal Vector objects returns true" << std::endl;
  }
  return success;
}

bool TestInequality() {
  bool success{true};
  Update(success, TestInequalityTrue());
  Update(success, TestInequalityFalse());
  return success;
}

bool TestNegation() {
  const TestVector positive{1.0F, 2.0F, 3.0F};
  const TestVector expected_negative{-1.0F, -2.0F, -3.0F};

  bool success{-positive == expected_negative};
  if (!success) {
    std::cerr << "negation operator failed: incorrect result" << std::endl;
  }
  return success;
}

bool TestAddition() {
  const TestVector addend_0{1.0F, 2.0F, 3.0F};
  const TestVector addend_1{4.0F, 5.0F, 6.0F};
  const TestVector expected_sum{5.0F, 7.0F, 9.0F};

  bool success{addend_0 + addend_1 == expected_sum};
  if (!success) {
    std::cerr << "addition operator failed: incorrect result" << std::endl;
  }
  return success;
}

bool TestSubtraction() {
  const TestVector minuend{5.0F, 7.0F, 9.0F};
  const TestVector subtrahend{1.0F, 2.0F, 3.0F};
  const TestVector expected_difference{4.0F, 5.0F, 6.0F};

  bool success{minuend - subtrahend == expected_difference};
  if (!success) {
    std::cerr << "subtraction operator failed: incorrect result" << std::endl;
  }
  return success;
}

bool TestMultiplication() {
  const TestVector vector{1.0F, 2.0F, 3.0F};
  const float scalar{10.0F};
  const TestVector expected_product{10.0F, 20.0F, 30.0F};

  bool success{vector * scalar == expected_product};
  if (!success) {
    std::cerr << "multiplication operator failed: incorrect result" << std::endl;
  }
  return success;
}

bool TestDivision() {
  const TestVector vector{10.0F, 20.0F, 30.0F};
  const float scalar{10.0F};
  const TestVector expected_quotient{1.0F, 2.0F, 3.0F};

  bool success{vector / scalar == expected_quotient};
  if (!success) {
    std::cerr << "division operator failed: incorrect result" << std::endl;
  }
  return success;
}

bool TestAdditionAssignment() {
  TestVector original{1.0F, 2.0F, 3.0F};
  const TestVector addend{4.0F, 5.0F, 6.0F};
  const TestVector expected_sum{5.0F, 7.0F, 9.0F};

  const TestVector sum{original += addend};
  bool success{original == expected_sum && sum == expected_sum};
  if (!success) {
    std::cerr << "addition assignment operator failed: incorrect result" << std::endl;
  }
  return success;
}

bool TestSubtractionAssignment() {
  TestVector original{5.0F, 7.0F, 9.0F};
  const TestVector subtrahend{1.0F, 2.0F, 3.0F};
  const TestVector expected_difference{4.0F, 5.0F, 6.0F};

  const TestVector difference{original -= subtrahend};
  bool success{original == expected_difference && difference == expected_difference};
  if (!success) {
    std::cerr << "subtraction assignment operator failed: incorrect result" << std::endl;
  }
  return success;
}

bool TestMultiplicationAssignment() {
  TestVector original{1.0F, 2.0F, 3.0F};
  const float scalar{10.0F};
  const TestVector expected_product{10.0F, 20.0F, 30.0F};

  const TestVector product{original *= scalar};
  bool success{original == expected_product && product == expected_product};
  if (!success) {
    std::cerr << "multiplication assignment operator failed: incorrect result" << std::endl;
  }
  return success;
}

bool TestDivisionAssignment() {
  TestVector original{10.0F, 20.0F, 30.0F};
  const float scalar{10.0F};
  const TestVector expected_quotient{1.0F, 2.0F, 3.0F};

  const TestVector quotient{original /= scalar};
  bool success{original == expected_quotient && quotient == expected_quotient};
  if (!success) {
    std::cerr << "division assignment operator failed: incorrect result" << std::endl;
  }
  return success;
}

bool TestContainsZeroTrue() {
  const TestVector vector{1.0F, 0.0F, 1.0F};

  bool success{vector.ContainsZero()};
  if (!success) {
    std::cerr << "ContainsZero failed: returns false for a Vector containing zero" << std::endl;
  }
  return success;
}

bool TestContainsZeroFalse() {
  const TestVector vector{1.0F, 2.0F, 3.0F};

  bool success{!vector.ContainsZero()};
  if (!success) {
    std::cerr << "ContainsZero failed: returns true for a Vector not containing zero" << std::endl;
  }
  return success;
}

bool TestContainsZero() {
  bool success{true};
  Update(success, TestContainsZeroTrue());
  Update(success, TestContainsZeroFalse());
  return success;
}

bool TestIsInColorRangeTrue() {
  const TestVector vector{0.0F, 0.5F, 1.0F};

  bool success{vector.IsInColorRange()};
  if (!success) {
    std::cerr << "IsInColorRange failed: returns false for a Vector in color range" << std::endl;
  }
  return success;
}

bool TestIsInColorRangeTooSmall() {
  const TestVector vector{0.0F, -1.0F, -2.0F};

  bool success{!vector.IsInColorRange()};
  if (!success) {
    std::cerr << "IsInColorRange failed: returns true for a Vector with element smaller than color range" << std::endl;
  }
  return success;
}

bool TestIsInColorRangeTooLarge() {
  const TestVector vector{0.0F, 1.0F, 2.0F};

  bool success{!vector.IsInColorRange()};
  if (!success) {
    std::cerr << "IsInColorRange failed: returns true for a Vector with element larger than color range" << std::endl;
  }
  return success;
}

bool TestIsInColorRange() {
  bool success{true};
  Update(success, TestIsInColorRangeTrue());
  Update(success, TestIsInColorRangeTooSmall());
  Update(success, TestIsInColorRangeTooLarge());
  return success;
}

bool TestNonmemberMultiplication() {
  const float scalar{10.0F};
  const TestVector vector{1.0F, 2.0F, 3.0F};
  const TestVector expected_product{10.0F, 20.0F, 30.0F};

  bool success{scalar * vector == expected_product};
  if (!success) {
    std::cerr << "nonmember multiplication operator failed: incorrect result" << std::endl;
  }
  return success;
}

bool TestNonmemberDivision() {
  const float scalar{30.0F};
  const TestVector vector{2.0F, 3.0F, 5.0F};
  const TestVector expected_quotient{15.0F, 10.0F, 6.0F};

  bool success{scalar / vector == expected_quotient};
  if (!success) {
    std::cerr << "nonmember division operator failed: incorrect result" << std::endl;
  }
  return success;
}
}

int main() {
  bool success{true};

  Update(success, TestDefaultConstructor());
  Update(success, TestInitializerListConstructor());
  Update(success, TestJSONConstructor());

  Update(success, TestEquality());
  Update(success, TestInequality());

  Update(success, TestNegation());

  Update(success, TestAddition());
  Update(success, TestSubtraction());
  Update(success, TestMultiplication());
  Update(success, TestDivision());

  Update(success, TestAdditionAssignment());
  Update(success, TestSubtractionAssignment());
  Update(success, TestMultiplicationAssignment());
  Update(success, TestDivisionAssignment());

  Update(success, TestContainsZero());
  Update(success, TestIsInColorRange());

  Update(success, TestNonmemberMultiplication());
  Update(success, TestNonmemberDivision());

  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
