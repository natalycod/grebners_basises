#include <gtest/gtest.h>

#include "grebner_basises/utils.hpp"
#include "grebner_basises/var_in_power.hpp"
#include "grebner_basises/monom_with_coef.hpp"

namespace {
std::string VarInPowerToString(const VarInPower& x) {
    return "(" + std::to_string(x.var_id) + ", " + std::to_string(x.power) + ")";
}

std::string VectorVarInPowerToString(const std::vector<VarInPower>& x) {
    std::string result = "{ ";
    for (const VarInPower& var : x) {
        result += VarInPowerToString(var) + " ";
    }
    result += "}";
    return result;
}

testing::AssertionResult VarInPowerEq(const VarInPower& a, const VarInPower& b) {
    if (a.var_id == b.var_id && a.power == b.power) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "variables in powers are not equal, expected " << VarInPowerToString(b) << " got " << VarInPowerToString(a);
}

testing::AssertionResult VectorVarInPowerEq(const std::vector<VarInPower>& a, const std::vector<VarInPower>& b) {
    if (a.size() != b.size()) {
        return testing::AssertionFailure() << "variables in powers are not equal, expected " << VectorVarInPowerToString(b) << " got " << VectorVarInPowerToString(a);
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (!VarInPowerEq(a[i], b[i])) {
            return testing::AssertionFailure() << "variables in powers are not equal, expected " << VectorVarInPowerToString(b) << " got " << VectorVarInPowerToString(a);
        }
    }
    return testing::AssertionSuccess();
}
}

template <typename T>
struct MergeSortCase {
    std::vector<T> a;
    std::vector<T> b;
    std::vector<T> result;
    std::function<T(const T&)> b_func;
    std::function<T(const T&, const T&)> equal_func;
};

TEST(Utils, MergeSortVarInPower) {
    std::vector<MergeSortCase<VarInPower>> cases;
    cases.push_back({
        {{1, 2}, {3, 1}, {5, 7}},
        {{2, 1}, {4, 10}},
        {{1, 2}, {2, 1}, {3, 1}, {4, 10}, {5, 7}},
        [&] (const VarInPower& x) {return x;},
        [&] (const VarInPower& x, const VarInPower& y) {return x * y;}
    });
    cases.push_back({
        {{1, 2}, {2, 8}, {5, 1}},
        {{1, 0}, {2, 2}, {3, 5}},
        {{1, 2}, {2, 10}, {3, 5}, {5, 1}},
        [&] (const VarInPower& x) {return x;},
        [&] (const VarInPower& x, const VarInPower& y) {return x * y;}
    });
    cases.push_back({
        {{1, 2}, {2, 8}, {5, 1}},
        {{1, 0}, {2, 2}, {3, 5}},
        {{1, 2}, {2, 10}, {3, -5}, {5, 1}},
        [&] (const VarInPower& x) {return VarInPower() / x;},
        [&] (const VarInPower& x, const VarInPower& y) {return x * y;}
    });

    for (const auto& test_case : cases) {
        const auto result = utils::MergeSort<VarInPower>(test_case.a, test_case.b, test_case.b_func, test_case.equal_func);
        EXPECT_TRUE(VectorVarInPowerEq(result, test_case.result));
    }
}

TEST(Utils, CalculateGCD) {
    EXPECT_EQ(utils::CalculateGCD(1, 3), 1);
    EXPECT_EQ(utils::CalculateGCD(5, 0), 5);
    EXPECT_EQ(utils::CalculateGCD(6, 18), 6);
    EXPECT_EQ(utils::CalculateGCD(12, 18), 6);
}
