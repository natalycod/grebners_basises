#include <gtest/gtest.h>
#include <vector>

#include "grebner_basises/monom_with_coef.hpp"
#include "grebner_basises/polynom.hpp"

namespace {
std::string PolynomToString(const Polynom& p) {
    std::string result = "{ ";
    for (const auto& monom : p.monoms) {
        result += "+ ";
        result += std::to_string(monom.coef.GetNumerator()) + "/" + std::to_string(monom.coef.GetDenumerator()) + " ";
        for (const auto var : monom.monom.powers) {
            result += " * ";
            result += std::to_string(var.var_id) + "^" + std::to_string(var.power);
        }
    }
    result += "}";
    return result;
}

testing::AssertionResult PolynomEq(const Polynom& a, const Polynom& b) {
    if (a.monoms.size() != b.monoms.size()) {
        return testing::AssertionFailure() << "polynoms are not equal, expected: " << PolynomToString(b) << ", got: " << PolynomToString(a);
    }
    for (size_t i = 0; i < a.monoms.size(); ++i) {
        if (!(a.monoms[i].coef == b.monoms[i].coef) || !(a.monoms[i].monom == b.monoms[i].monom)) {
            return testing::AssertionFailure() << "polynoms are not equal, expected: " << PolynomToString(b) << ", got: " << PolynomToString(a);
        }
    }
    return testing::AssertionSuccess();
}
}

TEST(Polynom, ConstructorEmpty) {
    Polynom p;
    EXPECT_EQ(p.monoms.size(), 0);
}

TEST(Polynom, ConstructorRational) {
    Polynom p(Rational(1, 2));
    EXPECT_EQ(p.monoms.size(), 1);
    EXPECT_EQ(p.monoms[0].coef, Rational(1, 2));
    EXPECT_EQ(p.monoms[0].monom.powers.size(), 0);
}

TEST(Polynom, ConstructorMonom) {
    Monom m({VarInPower(1, 2), VarInPower(2, 5), VarInPower(7, 1)});
    Polynom p(m);
    EXPECT_EQ(p.monoms.size(), 1);
    EXPECT_EQ(p.monoms[0].coef, Rational(1));
    EXPECT_EQ(p.monoms[0].monom, m);
}

TEST(Polynom, ConstructorVector) {
    std::vector<MonomWithCoef> vect = {
        MonomWithCoef(Rational(1, 2), Monom({VarInPower(1, 2), VarInPower(2, 5), VarInPower(7, 1)})),
        MonomWithCoef(Rational(3), Monom({VarInPower(2, 3)})),
        MonomWithCoef(Rational(), Monom({VarInPower(1), VarInPower(2), VarInPower(3)}))
    };
    std::vector<MonomWithCoef> sorted_vect = {
        MonomWithCoef(Rational(3), Monom({VarInPower(2, 3)})),
        MonomWithCoef(Rational(), Monom({VarInPower(1), VarInPower(2), VarInPower(3)})),
        MonomWithCoef(Rational(1, 2), Monom({VarInPower(1, 2), VarInPower(2, 5), VarInPower(7, 1)}))
    };
    Polynom p(vect);
    EXPECT_EQ(p.monoms, sorted_vect);
}

struct PolynomOperationCase {
    Polynom a;
    Polynom b;
    Polynom result;
};

TEST(Polynom, Sum) {
    std::vector<PolynomOperationCase> cases;
    cases.push_back({
        Polynom({Monom({VarInPower(1, 3), VarInPower(2, 2)})}),
        Polynom({Monom({VarInPower(1, 2), VarInPower(2, 2)})}),
        Polynom({Monom({VarInPower(1, 2), VarInPower(2, 2)}), Monom({VarInPower(1, 3), VarInPower(2, 2)})})
    });
    cases.push_back({
        Polynom({MonomWithCoef(Rational(3), Monom({3, 4})), MonomWithCoef(Rational(-2, 3), Monom({5, 6}))}),
        Polynom({MonomWithCoef(Rational(3), Monom({1, 5})), MonomWithCoef(Rational(1, 3), Monom({3, 4}))}),
        Polynom({MonomWithCoef(Rational(3), Monom({1, 5})), MonomWithCoef(Rational(10, 3), Monom({3, 4})), MonomWithCoef(Rational(-2, 3), Monom({5, 6}))})
    });
    cases.push_back({
        Polynom({MonomWithCoef(Rational(-2, 5), Monom({2, 2})), Monom({3, 5})}),
        Polynom({Rational(1, 2), MonomWithCoef(Rational(2, 5), Monom({2, 2}))}),
        Polynom({Rational(1, 2), Monom({3, 5})})
    });

    for (const auto& test_case : cases) {
        EXPECT_TRUE(PolynomEq(test_case.a + test_case.b, test_case.result));
    }
}

TEST(Polynom, Diff) {
    std::vector<PolynomOperationCase> cases;
    cases.push_back({
        Polynom({Monom({VarInPower(1, 3), VarInPower(2, 2)})}),
        Polynom({Monom({VarInPower(1, 2), VarInPower(2, 2)})}),
        Polynom({{Rational(-1), Monom({VarInPower(1, 2), VarInPower(2, 2)})}, Monom({VarInPower(1, 3), VarInPower(2, 2)})})
    });
    cases.push_back({
        Polynom({MonomWithCoef(Rational(3), Monom({3, 4})), MonomWithCoef(Rational(-2, 3), Monom({5, 6}))}),
        Polynom({MonomWithCoef(Rational(-3), Monom({1, 5})), MonomWithCoef(Rational(1, 3), Monom({3, 4}))}),
        Polynom({MonomWithCoef(Rational(3), Monom({1, 5})), MonomWithCoef(Rational(8, 3), Monom({3, 4})), MonomWithCoef(Rational(-2, 3), Monom({5, 6}))})
    });
    cases.push_back({
        Polynom({MonomWithCoef(Rational(2, 5), Monom({2, 2})), Monom({3, 5})}),
        Polynom({Rational(1, 2), MonomWithCoef(Rational(2, 5), Monom({2, 2}))}),
        Polynom({Rational(-1, 2), Monom({3, 5})})
    });

    for (const auto& test_case : cases) {
        EXPECT_TRUE(PolynomEq(test_case.a - test_case.b, test_case.result));
    }
}

TEST(Polynom, Production) {
    std::vector<PolynomOperationCase> cases;
    cases.push_back({
        Polynom({Monom({VarInPower(1, 3), VarInPower(2, 2)})}),
        Polynom({Monom({VarInPower(1, 2), VarInPower(2, 2)})}),
        Polynom({Monom({VarInPower(1, 5), VarInPower(2, 4)})})
    });
    cases.push_back({
        Polynom({Monom({VarInPower(1, 3)}), Monom({VarInPower(2, 2)})}),
        Polynom({Monom({VarInPower(1, 1)}), Monom({VarInPower(2, 3)})}),
        Polynom({Monom({VarInPower(1, 4)}), Monom({VarInPower(1, 3), VarInPower(2, 3)}), Monom({VarInPower(1, 1), VarInPower(2, 2)}), Monom({VarInPower(2, 5)})})
    });
    cases.push_back({
        Polynom({Monom({VarInPower(1, 1)}), Monom({VarInPower(2, 1)})}),
        Polynom({Monom({VarInPower(1, 1)}), Monom({VarInPower(2, 1)})}),
        Polynom({Monom({VarInPower(1, 2)}), MonomWithCoef(Rational(2), Monom({VarInPower(1, 1), VarInPower(2, 1)})), Monom({VarInPower(2, 2)})})
    });
    
    for (const auto& test_case : cases) {
        EXPECT_TRUE(PolynomEq(test_case.a * test_case.b, test_case.result));
    }
}

TEST(Polynom, GetLeadingMonom) {
    std::vector<std::pair<Polynom, Monom>> cases;
    cases.push_back({
        Polynom(Monom({3, 1})),
        Monom({3, 1})
    });
    cases.push_back({
        Polynom({Monom({1, 2}), Monom({3, 1})}),
        Monom({1, 2})
    });
    cases.push_back({
        Polynom({Monom({1, 2}), MonomWithCoef(Rational(1, 2), Monom({3, 1}))}),
        Monom({1, 2})
    });
    
    for (const auto& test_case : cases) {
        EXPECT_EQ(test_case.first.GetLeadingMonom(), test_case.second);
    }
}

TEST(Polynom, ToString) {
    std::vector<std::pair<Polynom, std::string>> cases;
    cases.push_back({
        Polynom({MonomWithCoef({1, 2}, Monom({{1, 3}, {2, 5}, {6, 10}})), MonomWithCoef({6, 2}, Monom({{1, 1}, {2, 1}}))}),
        "3 x_1 x_2 + 1/2 x_1^3 x_2^5 x_6^10"
    });
    cases.push_back({
        Polynom({MonomWithCoef(2, Monom({VarInPower(2, 2)})), MonomWithCoef(-2, Monom({VarInPower(2, 3)}))}),
        "2 x_2^2 - 2 x_2^3"
    });
    cases.push_back({
        Polynom({MonomWithCoef(2, Monom({VarInPower(2, 3)})), MonomWithCoef(-2, Monom({VarInPower(2, 2)}))}),
        "-2 x_2^2 + 2 x_2^3"
    });
    cases.push_back({
        Polynom({MonomWithCoef(-1, Monom({VarInPower(1)})), MonomWithCoef(-1, Monom({VarInPower(2)})), MonomWithCoef(-1, Monom({VarInPower(3)}))}),
        "-x_3 - x_2 - x_1"
    });

    for (const auto& test_case : cases) {
        EXPECT_EQ(test_case.first.ToString(), test_case.second);
    }
}
