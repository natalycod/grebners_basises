#include <gtest/gtest.h>
#include <vector>

#include "grebner_basises/monom.hpp"

namespace {

std::string MonomToString(const Monom& x) {
    std::string result = "{ ";
    for (auto var : x.powers) {
        result += "(" + std::to_string(var.var_id) + ", " + std::to_string(var.power) + ") ";
    }
    result += "}";
    return result;
}

testing::AssertionResult MonomEq(const Monom& a, const Monom& b) {
    if (a.powers.size() != b.powers.size()) {
        return testing::AssertionFailure() << "monoms are not equal, expected " << MonomToString(b) << " got " << MonomToString(a);
    }
    for (size_t i = 0; i < a.powers.size(); ++i) {
        if (a.powers[i].var_id != b.powers[i].var_id || a.powers[i].power != b.powers[i].power) {
            return testing::AssertionFailure() << "monoms are not equal, expected " << MonomToString(b) << " got " << MonomToString(a);
        }
    }
    return testing::AssertionSuccess();
}
}

// Constructors

TEST(Monom, Empty) {
    Monom x;
    EXPECT_EQ(x.powers.size(), 0);
}

TEST(Monom, FromVector) {
    std::vector<VarInPower> vect;
    vect.push_back(VarInPower(1, 2));
    vect.push_back(VarInPower(4, 1));
    Monom x(vect);
    EXPECT_EQ(x.powers, vect);
}

struct OperationTestCase {
    Monom a;
    Monom b;
    Monom result;
    bool is_throw = false;
};

TEST(Monom, Multiplication) {
    std::vector<OperationTestCase> cases;
    cases.push_back({
        Monom({VarInPower(1, 2)}),
        Monom({VarInPower(2, 5)}),
        Monom({VarInPower(1, 2), VarInPower(2, 5)})
    });
    cases.push_back({
        Monom({VarInPower(1, 5)}),
        Monom({VarInPower(1, 3)}),
        Monom({VarInPower(1, 8)})
    });
    cases.push_back({
        Monom({VarInPower(1, 3), VarInPower(3, 1), VarInPower(5, 5)}),
        Monom({VarInPower(2, 4), VarInPower(3, 4), VarInPower(5, 0), VarInPower(6, 8)}),
        Monom({VarInPower(1, 3), VarInPower(2, 4), VarInPower(3, 5), VarInPower(5, 5), VarInPower(6, 8)})
    });

    for (const auto& test_case : cases) {
        Monom result = test_case.a * test_case.b;
        EXPECT_TRUE(MonomEq(result, test_case.result));
    }
}

TEST(Monom, Division) {
    std::vector<OperationTestCase> cases;
    cases.push_back({
        Monom({VarInPower(1, 5)}),
        Monom({VarInPower(1, 2)}),
        Monom({VarInPower(1, 3)})
    });
    cases.push_back({
        Monom({VarInPower(2, 4), VarInPower(3, 1)}),
        Monom({VarInPower(2, 1)}),
        Monom({VarInPower(2, 3), VarInPower(3, 1)})
    });
    cases.push_back({
        Monom({VarInPower(2, 4), VarInPower(3, 2), VarInPower(5, 6)}),
        Monom({VarInPower(2, 3), VarInPower(3, 2)}),
        Monom({VarInPower(2, 1), VarInPower(5, 6)})
    });
    cases.push_back({
        Monom({VarInPower(1, 3), VarInPower(2, 2)}),
        Monom({VarInPower(3, 1)}),
        Monom(),
        true
    });
    cases.push_back({
        Monom({VarInPower(1, 3), VarInPower(2, 2)}),
        Monom({VarInPower(1, 4)}),
        Monom(),
        true
    });

    for (const auto& test_case : cases) {
        if (test_case.is_throw) {
            EXPECT_THROW(test_case.a / test_case.b, std::runtime_error);
            continue;
        }
        Monom result = test_case.a / test_case.b;
        EXPECT_TRUE(MonomEq(result, test_case.result));
    }
}

struct BoolOperationTestCase {
    Monom a;
    Monom b;
    std::string result;
};

std::vector<BoolOperationTestCase> BOOL_OPERATION_CASES = {
    {
        Monom({VarInPower(2, 2)}),
        Monom({VarInPower(1, 3)}),
        "less"
    },
    {
        Monom({VarInPower(2, 3)}),
        Monom({VarInPower(2, 5)}),
        "less"
    },
    {
        Monom({VarInPower(3, 4)}),
        Monom({VarInPower(3, 4)}),
        "equal"
    },
    {
        Monom({VarInPower(5, 8), VarInPower(6, 5), VarInPower(8, 9)}),
        Monom({VarInPower(5, 8), VarInPower(6, 6), VarInPower(7, 1)}),
        "less"
    },
    {
        Monom({VarInPower(5, 8), VarInPower(7, 6), VarInPower(8, 1)}),
        Monom({VarInPower(5, 8), VarInPower(6, 5), VarInPower(9, 8)}),
        "less"
    },
    {
        Monom({VarInPower(5, 8), VarInPower(6, 5)}),
        Monom({VarInPower(5, 8), VarInPower(6, 5), VarInPower(7, 1)}),
        "less"
    },
    {
        Monom({VarInPower(5, 8), VarInPower(6, 5)}),
        Monom({VarInPower(5, 8), VarInPower(6, 5)}),
        "equal"
    }
};

TEST(Monom, IsLess) {
    for (const auto& test_case : BOOL_OPERATION_CASES) {
        if (test_case.result == "equal") {
            EXPECT_FALSE(test_case.a < test_case.b);
        }
        else if (test_case.result == "less") {
            EXPECT_TRUE(test_case.a < test_case.b);
            EXPECT_FALSE(test_case.b < test_case.a);
        }
    }
}

TEST(Monom, IsGreater) {
    for (const auto& test_case : BOOL_OPERATION_CASES) {
        if (test_case.result == "equal") {
            EXPECT_FALSE(test_case.a > test_case.b);
        }
        else if (test_case.result == "less") {
            EXPECT_FALSE(test_case.a > test_case.b);
            EXPECT_TRUE(test_case.b > test_case.a);
        }
    }
}

TEST(Monom, IsEqual) {
    for (const auto& test_case : BOOL_OPERATION_CASES) {
        if (test_case.result == "equal") {
            EXPECT_TRUE(test_case.a == test_case.b);
        }
        else if (test_case.result == "less") {
            EXPECT_FALSE(test_case.a == test_case.b);
            EXPECT_FALSE(test_case.b == test_case.a);
        }
    }
}

TEST(Monom, IsVisible) {
    std::vector<BoolOperationTestCase> cases;
    cases.push_back({
        Monom({VarInPower(1, 2), VarInPower(2, 3), VarInPower(3, 1)}),
        Monom({VarInPower(1, 1), VarInPower(2, 3)}),
        "true"
    });
    cases.push_back({
        Monom({VarInPower(1, 2), VarInPower(2, 3), VarInPower(3, 1)}),
        Monom({VarInPower(1, 3), VarInPower(2, 3)}),
        "false"
    });
    cases.push_back({
        Monom({VarInPower(1, 2), VarInPower(2, 3), VarInPower(3, 1)}),
        Monom({VarInPower(1, 2), VarInPower(2, 3), VarInPower(3, 1)}),
        "true"
    });
    cases.push_back({
        Monom({VarInPower(3, 7)}),
        Monom({VarInPower(1, 1)}),
        "false"
    });

    for (const auto& test_case : cases) {
        if (test_case.result == "true") {
            EXPECT_TRUE(test_case.a.IsDivisible(test_case.b));
        }
        else {
            EXPECT_FALSE(test_case.a.IsDivisible(test_case.b));
        }
    }
}

TEST(Monom, ToString) {
    std::vector<std::pair<Monom, std::string>> cases;
    cases.push_back({Monom({VarInPower{1, 3}, VarInPower{2, 2}}), "x_1^3 x_2^2"});
    cases.push_back({Monom({VarInPower{2, 4}, VarInPower{5, 1}}), "x_2^4 x_5"});
    cases.push_back({Monom({VarInPower{2, 4}, VarInPower{5, 1}}), "x_2^4 x_5"});
    
    for (const auto& test_case : cases) {
        EXPECT_EQ(test_case.first.ToString(), test_case.second);
    }
}
