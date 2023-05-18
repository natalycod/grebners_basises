#include <gtest/gtest.h>

#include "grebner_basises/var_in_power.hpp"

namespace {
std::string VarInPowerToString(VarInPower x) {
    return "(" + std::to_string(x.var_id) + ", " + std::to_string(x.power) + ")";
}

testing::AssertionResult VarInPowerEq(const VarInPower& a, const VarInPower& b) {
    if (a.var_id == b.var_id && a.power == b.power) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "variables in powers are not equal, expected " << VarInPowerToString(b) << " got " << VarInPowerToString(a);
}
}

TEST(VarInPower, ConstructorEmpty) {
    VarInPower x;
    EXPECT_EQ(x.power, 0);
}

TEST(VarInPower, ConstructorById) {
    VarInPower x(12);
    EXPECT_EQ(x.var_id, 12);
    EXPECT_EQ(x.power, 1);
}

TEST(VarInPower, ConstructorByIdAndPower) {
    VarInPower x(5, 3);
    EXPECT_EQ(x.var_id, 5);
    EXPECT_EQ(x.power, 3);
}

TEST(VarInPower, Multiplication) {
    EXPECT_TRUE(VarInPowerEq(VarInPower(4, 3) * VarInPower(4, 2), VarInPower(4, 5)));
    EXPECT_TRUE(VarInPowerEq(VarInPower(6) * VarInPower(6), VarInPower(6, 2)));
    EXPECT_TRUE(VarInPowerEq(VarInPower(3) * VarInPower(3, 4), VarInPower(3, 5)));
    EXPECT_TRUE(VarInPowerEq(VarInPower(3, 4) * VarInPower(3), VarInPower(3, 5)));

    EXPECT_TRUE(VarInPowerEq(VarInPower(3, 0) * VarInPower(4, 2), VarInPower(4, 2)));
    EXPECT_TRUE(VarInPowerEq(VarInPower(4, 2) * VarInPower(3, 0), VarInPower(4, 2)));

    EXPECT_THROW(VarInPower(3, 2) * VarInPower(2), std::runtime_error);
}

TEST(VarInPower, Division) {
    EXPECT_TRUE(VarInPowerEq(VarInPower(4, 3) / VarInPower(4, 2), VarInPower(4, 1)));
    EXPECT_TRUE(VarInPowerEq(VarInPower(6) / VarInPower(6), VarInPower(6, 0)));
    EXPECT_TRUE(VarInPowerEq(VarInPower(3) / VarInPower(3, 4), VarInPower(3, -3)));
    EXPECT_TRUE(VarInPowerEq(VarInPower(3, 4) / VarInPower(3), VarInPower(3, 3)));

    EXPECT_TRUE(VarInPowerEq(VarInPower(3, 0) / VarInPower(4, 2), VarInPower(4, -2)));
    EXPECT_TRUE(VarInPowerEq(VarInPower(4, 2) / VarInPower(3, 0), VarInPower(4, 2)));

    EXPECT_THROW(VarInPower(3, 2) / VarInPower(2), std::runtime_error);
}

TEST(VarInPower, IsLess) {
    EXPECT_TRUE(VarInPower(42) < VarInPower(43));
    EXPECT_TRUE(VarInPower(42, 10) < VarInPower(43));
    EXPECT_TRUE(VarInPower(42, 10) < VarInPower(43, 2));

    EXPECT_FALSE(VarInPower(42) < VarInPower(42));
    EXPECT_FALSE(VarInPower(42, 10) < VarInPower(42));
    EXPECT_FALSE(VarInPower(42, 10) < VarInPower(42, 5));
    EXPECT_FALSE(VarInPower(42, 10) < VarInPower(42, 10));

    EXPECT_FALSE(VarInPower(42) < VarInPower(12));
    EXPECT_FALSE(VarInPower(42, 10) < VarInPower(12));
    EXPECT_FALSE(VarInPower(42, 10) < VarInPower(12, 20));
}

TEST(VarInPower, IsGreater) {
    EXPECT_FALSE(VarInPower(42) > VarInPower(43));
    EXPECT_FALSE(VarInPower(42, 10) > VarInPower(43));
    EXPECT_FALSE(VarInPower(42, 10) > VarInPower(43, 2));

    EXPECT_FALSE(VarInPower(42) > VarInPower(42));
    EXPECT_FALSE(VarInPower(42, 10) > VarInPower(42));
    EXPECT_FALSE(VarInPower(42, 10) > VarInPower(42, 5));
    EXPECT_FALSE(VarInPower(42, 10) > VarInPower(42, 10));

    EXPECT_TRUE(VarInPower(42) > VarInPower(12));
    EXPECT_TRUE(VarInPower(42, 10) > VarInPower(12));
    EXPECT_TRUE(VarInPower(42, 10) > VarInPower(12, 20));
}

TEST(VarInPower, IsEqual) {
    EXPECT_FALSE(VarInPower(42) == VarInPower(43));
    EXPECT_FALSE(VarInPower(42, 10) == VarInPower(43));
    EXPECT_FALSE(VarInPower(42, 10) == VarInPower(43, 2));

    EXPECT_TRUE(VarInPower(42) == VarInPower(42));
    EXPECT_TRUE(VarInPower(42, 10) == VarInPower(42));
    EXPECT_TRUE(VarInPower(42, 10) == VarInPower(42, 5));
    EXPECT_TRUE(VarInPower(42, 10) == VarInPower(42, 10));

    EXPECT_FALSE(VarInPower(42) == VarInPower(12));
    EXPECT_FALSE(VarInPower(42, 10) == VarInPower(12));
    EXPECT_FALSE(VarInPower(42, 10) == VarInPower(12, 20));
}

TEST(VarInPower, ToString) {
    std::vector<std::pair<VarInPower, std::string>> cases;
    cases.push_back({{1, 3}, "x_1^3"});
    cases.push_back({{12, 0}, "x_12^0"});
    cases.push_back({{3, 1}, "x_3"});
    
    for (const auto& test_case : cases) {
        EXPECT_EQ(test_case.first.ToString(), test_case.second);
    }
}
