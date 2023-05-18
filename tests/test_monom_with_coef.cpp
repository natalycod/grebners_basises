#include <gtest/gtest.h>

#include "grebner_basises/monom_with_coef.hpp"

TEST(MonomWithCoef, ConstructorEmpty) {
    MonomWithCoef m;
    EXPECT_EQ(m.coef, Rational());
    EXPECT_EQ(m.monom, Monom());
}

TEST(MonomWithCoef, ConstructorRational) {
    MonomWithCoef m(Rational(1, 2));
    EXPECT_EQ(m.coef, Rational(1, 2));
    EXPECT_EQ(m.monom, Monom());
}

TEST(MonomWithCoef, ConstructorMonom) {
    MonomWithCoef m(Monom({VarInPower(1, 2), VarInPower(2, 4)}));
    EXPECT_EQ(m.coef, Rational(1));
    EXPECT_EQ(m.monom, Monom({VarInPower(1, 2), VarInPower(2, 4)}));
}

TEST(MonomWithCoef, ConstructorFull) {
    MonomWithCoef m(Rational(1, 2), Monom({VarInPower(1, 2), VarInPower(2, 4)}));
    EXPECT_EQ(m.coef, Rational(1, 2));
    EXPECT_EQ(m.monom, Monom({VarInPower(1, 2), VarInPower(2, 4)}));
}

struct OperationCase {
    MonomWithCoef a;
    MonomWithCoef b;
    MonomWithCoef result;
    bool is_throw = false;
};

TEST(MonomWithCoef, Sum) {
    std::vector<OperationCase> cases;
    cases.push_back({
        MonomWithCoef(Rational(1), Monom({VarInPower(1, 5), VarInPower(3, 2)})),
        MonomWithCoef(Rational(3, 2), Monom({VarInPower(1, 5), VarInPower(3, 2)})),
        MonomWithCoef(Rational(5, 2), Monom({VarInPower(1, 5), VarInPower(3, 2)})),
    });
    cases.push_back({
        MonomWithCoef(Rational(1), Monom({VarInPower(1, 5), VarInPower(3, 2)})),
        MonomWithCoef(Rational(-3, 2), Monom({VarInPower(1, 5), VarInPower(3, 2)})),
        MonomWithCoef(Rational(-1, 2), Monom({VarInPower(1, 5), VarInPower(3, 2)})),
    });
    cases.push_back({
        MonomWithCoef(Rational(1), Monom({VarInPower(1, 5), VarInPower(3, 2)})),
        MonomWithCoef(Rational(3, 2), Monom({VarInPower(1, 5)})),
        MonomWithCoef(),
        true
    });
    
    for (const auto test_case : cases) {
        if (test_case.is_throw) {
            EXPECT_THROW(test_case.a + test_case.b, std::runtime_error);
            continue;
        }
        MonomWithCoef result = test_case.a + test_case.b;
        EXPECT_EQ(result.coef, test_case.result.coef);
        EXPECT_EQ(result.monom, test_case.result.monom);
    }
}

TEST(MonomWithCoef, Diff) {
    std::vector<OperationCase> cases;
    cases.push_back({
        MonomWithCoef(Rational(1), Monom({VarInPower(1, 5), VarInPower(3, 2)})),
        MonomWithCoef(Rational(3, 2), Monom({VarInPower(1, 5), VarInPower(3, 2)})),
        MonomWithCoef(Rational(-1, 2), Monom({VarInPower(1, 5), VarInPower(3, 2)})),
    });
    cases.push_back({
        MonomWithCoef(Rational(1), Monom({VarInPower(1, 5), VarInPower(3, 2)})),
        MonomWithCoef(Rational(-3, 2), Monom({VarInPower(1, 5), VarInPower(3, 2)})),
        MonomWithCoef(Rational(5, 2), Monom({VarInPower(1, 5), VarInPower(3, 2)})),
    });
    cases.push_back({
        MonomWithCoef(Rational(1), Monom({VarInPower(1, 5), VarInPower(3, 2)})),
        MonomWithCoef(Rational(3, 2), Monom({VarInPower(1, 5)})),
        MonomWithCoef(),
        true
    });
    
    for (const auto test_case : cases) {
        if (test_case.is_throw) {
            EXPECT_THROW(test_case.a - test_case.b, std::runtime_error);
            continue;
        }
        MonomWithCoef result = test_case.a - test_case.b;
        EXPECT_EQ(result.coef, test_case.result.coef);
        EXPECT_EQ(result.monom, test_case.result.monom);
    }
}

struct BoolOperationCase {
    MonomWithCoef a;
    MonomWithCoef b;
    std::string result;
};

std::vector<BoolOperationCase> BOOL_OPERATION_CASES_MONOM_WITH_COEF = {
    {
        {Rational(1), Monom({VarInPower(1, 2), VarInPower(2, 5)})},
        {Rational(3, 8), Monom({VarInPower(1, 2), VarInPower(2, 5)})},
        "equal"
    },
    {
        {Rational(2), Monom({VarInPower(1, 2), VarInPower(2, 5)})},
        {Rational(2), Monom({VarInPower(1, 2), VarInPower(2, 5)})},
        "equal"
    },
    {
        {Rational(9), Monom({VarInPower(1, 2), VarInPower(2, 4)})},
        {Rational(2), Monom({VarInPower(1, 2), VarInPower(2, 5)})},
        "less"
    }
};

TEST(MonomWithCoef, IsEqual) {
    for (const auto& test_case : BOOL_OPERATION_CASES_MONOM_WITH_COEF) {
        if (test_case.result == "equal") {
            EXPECT_TRUE(test_case.a == test_case.b);
            continue;
        }
        EXPECT_FALSE(test_case.a == test_case.b);
        EXPECT_FALSE(test_case.b == test_case.a);
    }
}

TEST(MonomWithCoef, IsLess) {
    for (const auto& test_case : BOOL_OPERATION_CASES_MONOM_WITH_COEF) {
        if (test_case.result == "equal") {
            EXPECT_FALSE(test_case.a < test_case.b);
            continue;
        }
        EXPECT_TRUE(test_case.a < test_case.b);
        EXPECT_FALSE(test_case.b < test_case.a);
    }
}

TEST(MonomWithCoef, IsGreater) {
    for (const auto& test_case : BOOL_OPERATION_CASES_MONOM_WITH_COEF) {
        if (test_case.result == "equal") {
            EXPECT_FALSE(test_case.a > test_case.b);
            continue;
        }
        EXPECT_FALSE(test_case.a > test_case.b);
        EXPECT_TRUE(test_case.b > test_case.a);
    }
}

TEST(MonomWithCoef, ToString) {
    std::vector<std::pair<MonomWithCoef, std::string>> cases;
    cases.push_back({
        {{2, 3}, Monom({VarInPower(2, 5), VarInPower(3, 1), VarInPower(6, 2)})},
        "2/3 x_2^5 x_3 x_6^2"
    });
    cases.push_back({
        {{5, 5}, Monom({VarInPower(2, 5), VarInPower(3, 1), VarInPower(6, 2)})},
        "x_2^5 x_3 x_6^2"
    });
    cases.push_back({
        {{0, 11}, Monom({VarInPower(2, 5), VarInPower(3, 1), VarInPower(6, 2)})},
        "0"
    });

    for (const auto& test_case : cases) {
        EXPECT_EQ(test_case.first.ToString(), test_case.second);
    }
}
