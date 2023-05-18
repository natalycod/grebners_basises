#include <gtest/gtest.h>

#include "grebner_basises/rational.hpp"

namespace {

testing::AssertionResult RationalEq(const Rational& a, const Rational& b) {
  if (a.GetNumerator() == b.GetNumerator() && a.GetDenumerator() == b.GetDenumerator()) {
    return testing::AssertionSuccess();
  }
  return testing::AssertionFailure() << a.ToString() << " is not equal to " << b.ToString();
}

testing::AssertionResult SumEq(const Rational& a, const Rational& b, const Rational& c) {
  Rational result = a + b;
  return RationalEq(result, c);
}

testing::AssertionResult DiffEq(const Rational& a, const Rational& b, const Rational& c) {
  Rational result = a - b;
  return RationalEq(result, c);
}

testing::AssertionResult MultEq(const Rational& a, const Rational& b, const Rational& c) {
  Rational result = a * b;
  return RationalEq(result, c);
}

testing::AssertionResult DivEq(const Rational& a, const Rational& b, const Rational& c) {
  Rational result = a / b;
  return RationalEq(result, c);
}
}

TEST(Rational, EmptyConstructor) {
  Rational x;
  EXPECT_EQ(x.GetNumerator(), 0);
  EXPECT_EQ(x.GetDenumerator(), 1);
}

TEST(Rational, OneNumberConstructor) {
  Rational x(3);
  EXPECT_EQ(x.GetNumerator(), 3);
  EXPECT_EQ(x.GetDenumerator(), 1);
}

TEST(Rational, TwoNumberConstructor) {
  Rational x(5, 7);
  EXPECT_EQ(x.GetNumerator(), 5);
  EXPECT_EQ(x.GetDenumerator(), 7);
}

TEST(Rational, TwoNumberConstructorSimplify) {
  Rational x(4, 6);
  EXPECT_EQ(x.GetNumerator(), 2);
  EXPECT_EQ(x.GetDenumerator(), 3);
}

TEST(Rational, Negative) {
  EXPECT_TRUE(RationalEq(-Rational(11, 15), {-11, 15}));
  EXPECT_TRUE(RationalEq(-Rational(-5, 7), {5, 7}));
}

TEST(Rational, Add) {
  EXPECT_TRUE(SumEq({1, 5}, {2, 5}, {3, 5}));
  EXPECT_TRUE(SumEq({1, 6}, {2, 6}, {1, 2}));
  EXPECT_TRUE(SumEq({2, 5}, {3, 2}, {19, 10}));
  EXPECT_TRUE(SumEq({1, 6}, {1, 9}, {5, 18}));
  EXPECT_TRUE(SumEq({-1, 7}, {3, 7}, {2, 7}));
  EXPECT_TRUE(SumEq({1, 7}, {-3, 7}, {-2, 7}));
}

TEST(Rational, Subtract) {
  EXPECT_TRUE(DiffEq({5, 7}, {3, 7}, {2, 7}));
  EXPECT_TRUE(DiffEq({5, 7}, {3, 7}, {2, 7}));
  EXPECT_TRUE(DiffEq({1, 2}, {1, 6}, {1, 3}));
  EXPECT_TRUE(DiffEq({1, 6}, {1, 2}, {-1, 3}));
}

TEST(Rational, Multiply) {
  EXPECT_TRUE(MultEq({2, 3}, {3, 5}, {6, 15}));     // no reduction
  EXPECT_TRUE(MultEq({2, 3}, {3, 2}, {1, 1}));      // full reduction
  EXPECT_TRUE(MultEq({3, 10}, {4, 15}, {2, 25}));   // partial reduction
  EXPECT_TRUE(MultEq({1, 2}, {-1, 3}, {-1, 6}));    // one negative
  EXPECT_TRUE(MultEq({-5, 6}, {-1, 3}, {5, 18}));   // two negatives
  EXPECT_TRUE(MultEq({0, 1}, {1, 3}, {0, 1}));      // zero
}

TEST(Rational, Divide) {
  EXPECT_TRUE(DivEq({1, 3}, {1, 2}, {2, 3}));       // no reduction
  EXPECT_TRUE(DivEq({3, 2}, {3, 2}, {1, 1}));       // full reduction
  EXPECT_TRUE(DivEq({3, 10}, {15, 4}, {2, 25}));    // partial reduction
  EXPECT_TRUE(DivEq({-1, 2}, {1, 3}, {-3, 2}));     // first negative
  EXPECT_TRUE(DivEq({1, 2}, {-1, 3}, {-3, 2}));     // second negative
  EXPECT_TRUE(DivEq({-1, 2}, {-1, 3}, {3, 2}));     // two negatives
  EXPECT_TRUE(DivEq({0, 1}, {1, 3}, {0, 1}));       // first zero
  EXPECT_THROW(Rational(1, 2) / Rational(0, 1), std::runtime_error);    // divide on zero
}

TEST(Rational, IsEqual) {
  EXPECT_TRUE(Rational(1, 2) == Rational(2, 4));
  EXPECT_TRUE(Rational(2, 3) == Rational(2, 3));
  EXPECT_FALSE(Rational(1, 3) == Rational(2, 3));
  EXPECT_FALSE(Rational(1, 3) == Rational(1, 4));
}

TEST(Rational, IsLess) {
  EXPECT_TRUE(Rational(1, 2) < Rational(3, 4));
  EXPECT_TRUE(Rational(3, 7) < Rational(1, 2));
  EXPECT_FALSE(Rational(2, 5) < Rational(4, 10));
  EXPECT_FALSE(Rational(3, 4) < Rational(1, 2));
  EXPECT_FALSE(Rational(1, 2) < Rational(3, 7));
}

TEST(Rational, IsGreater) {
  EXPECT_FALSE(Rational(1, 2) > Rational(3, 4));
  EXPECT_FALSE(Rational(3, 7) > Rational(1, 2));
  EXPECT_FALSE(Rational(2, 5) > Rational(4, 10));
  EXPECT_TRUE(Rational(3, 4) > Rational(1, 2));
  EXPECT_TRUE(Rational(1, 2) > Rational(3, 7));
}

TEST(Rational, ToString) {
  std::vector<std::pair<Rational, std::string>> cases;
  cases.push_back({{2, 3}, "2/3"});
  cases.push_back({{0, 5}, "0"});
  cases.push_back({{6, 3}, "2"});
  for (const auto& test_case : cases) {
    EXPECT_EQ(test_case.first.ToString(), test_case.second);
  }
}