#include <gtest/gtest.h>

#include "grebner_basises/base_algorithms.hpp"
#include "grebner_basises/monom_with_coef.hpp"


TEST(BaseAlgorithms, IsReducableOnPolynom) {
    struct Case {
        Polynom a;
        Polynom b;
        bool result;
    };
    std::vector<Case> cases;
    cases.push_back({
        Polynom({Monom({VarInPower{1, 1}, VarInPower{2, 2}}), Monom({VarInPower{3, 1}}), Monom({VarInPower{2, 4}})}),
        Polynom({Monom({VarInPower{1, 1}, VarInPower{2, 1}}), Monom({VarInPower{2, 1}})}),
        true
    });
    cases.push_back({
        Polynom({Monom({VarInPower{1, 2}}), MonomWithCoef({-1}, Monom({VarInPower{2, 1}}))}),
        Polynom({Monom({VarInPower{1, 2}}), MonomWithCoef({-1}, Monom({VarInPower{3, 1}}))}),
        true
    });
    cases.push_back({
        Polynom({Monom({VarInPower(1, 2), VarInPower(2, 2)}), Monom({VarInPower(3, 2)})}),
        Polynom({Monom({VarInPower(1, 2), VarInPower(3, 2)})}),
        false
    });
    for (const auto& test_case : cases) {
        EXPECT_EQ(BaseAlgorithms().IsReducableOnPolynom(test_case.a, test_case.b), test_case.result);
    }
}

TEST(BaseAlgorithms, ReduceOnPolynom) {
    struct PolynomCase {
        Polynom a;
        Polynom b;
        Polynom result;
    };
    std::vector<PolynomCase> cases;
    cases.push_back({
        Polynom({Monom({VarInPower{1, 1}, VarInPower{2, 2}}), Monom({VarInPower{3, 1}}), Monom({VarInPower{2, 4}})}),
        Polynom({Monom({VarInPower{1, 1}, VarInPower{2, 1}}), Monom({VarInPower{2, 1}})}),
        Polynom({MonomWithCoef({{-1}, Monom({VarInPower{2, 2}})}), Monom({VarInPower{3, 1}}), Monom({VarInPower{2, 4}})})
    });
    cases.push_back({
        Polynom({Monom({VarInPower{1, 2}}), MonomWithCoef({-1}, Monom({VarInPower{2, 1}}))}),
        Polynom({Monom({VarInPower{1, 2}}), MonomWithCoef({-1}, Monom({VarInPower{3, 1}}))}),
        Polynom({Monom({VarInPower{3, 1}}), MonomWithCoef({-1}, Monom({VarInPower{2, 1}}))})
    });
    cases.push_back({
        Polynom({MonomWithCoef(-1, Monom({VarInPower(1, 1), VarInPower(3, 2)})), MonomWithCoef(-1, Monom({VarInPower(1, 1), VarInPower(3, 1)})), Monom({VarInPower(3, 2)}), Monom({VarInPower(3, 1)}), Monom({VarInPower(2, 2), VarInPower(3, 1)})}),
        Polynom({Monom({VarInPower(1, 1), VarInPower(3, 1)}), MonomWithCoef({-1}, Monom({VarInPower(2, 2)})), MonomWithCoef({-1}, Monom({VarInPower(2, 1)}))}),
        Polynom({MonomWithCoef(-1, Monom({VarInPower(2, 1), VarInPower(3, 1)})), MonomWithCoef(-1, Monom({VarInPower(2, 2)})), MonomWithCoef(-1, Monom({VarInPower(2, 1)})), Monom({VarInPower(3, 2)}), Monom({VarInPower(3, 1)})})
    });

    for (const auto& test_case : cases) {
        EXPECT_EQ(BaseAlgorithms().ReduceOnPolynom(test_case.a, test_case.b).ToString(), test_case.result.ToString());
    }
}

TEST(BaseAlgorithms, ReduceOnPolynomSet) {
    struct Case {
        Polynom a;
        std::vector<Polynom> b;
        Polynom result;
    };
    std::vector<Case> cases;
    cases.push_back({
        Polynom({MonomWithCoef({-1}, Monom({VarInPower(1, 1), VarInPower(3, 2)})), MonomWithCoef({-1}, Monom({VarInPower(1, 1), VarInPower(3, 1)})), Monom({VarInPower(1, 1), VarInPower(2, 1)}), Monom({VarInPower(2, 2), VarInPower(3, 1)})}),
        {
            Polynom({Monom({VarInPower(1, 1), VarInPower(2, 1)}), MonomWithCoef({-1}, Monom({VarInPower(3, 2)})), MonomWithCoef({-1}, Monom({VarInPower(3, 1)}))}),
            Polynom({Monom({VarInPower(1, 2)}), MonomWithCoef({-1}, Monom({VarInPower(1, 1)})), MonomWithCoef({-1}, Monom({VarInPower(2, 1), VarInPower(3, 1)}))}),
            Polynom({Monom({VarInPower(1, 1), VarInPower(3, 1)}), MonomWithCoef({-1}, Monom({VarInPower(2, 2)})), MonomWithCoef({-1}, Monom({VarInPower(2, 1)}))})
        },
        Polynom({MonomWithCoef(-1, Monom({VarInPower(2, 1), VarInPower(3, 1)})), MonomWithCoef(-1, Monom({VarInPower(2, 2)})), MonomWithCoef(-1, Monom({VarInPower(2, 1)})), Monom({VarInPower(3, 2)}), Monom({VarInPower(3, 1)})})
    });

    for (const auto& test_case : cases) {
        EXPECT_EQ(BaseAlgorithms().ReduceOnPolynomSet(test_case.a, test_case.b).ToString(), test_case.result.ToString());
    }
}

TEST(BaseAlgorithms, MonomLCM) {
    struct TestCase {
        Monom a;
        Monom b;
        Monom result;
    };
    std::vector<TestCase> cases;
    cases.push_back({
        Monom({VarInPower(1, 2)}),
        Monom({VarInPower(1, 3)}),
        Monom({VarInPower(1, 3)})
    });
    cases.push_back({
        Monom({VarInPower(1, 2), VarInPower(2, 4), VarInPower(3, 6)}),
        Monom({VarInPower(2, 3), VarInPower(3, 9), VarInPower(4, 1)}),
        Monom({VarInPower(1, 2), VarInPower(2, 4), VarInPower(3, 9), VarInPower(4, 1)})
    });

    for (const auto& test_case : cases) {
        EXPECT_EQ(BaseAlgorithms().GetMonomLCM(test_case.a, test_case.b).ToString(), test_case.result.ToString());
    }
}

TEST(BaseAlgorithms, Buhberger) {
    struct TestCase {
        std::vector<Polynom> vect;
        std::vector<Polynom> result;
    };
    std::vector<TestCase> cases;
    cases.push_back({
        {
            Polynom({Monom({VarInPower(1, 1), VarInPower(2, 1)}), MonomWithCoef({-1}, Monom({VarInPower(3, 2)})), MonomWithCoef({-1}, Monom({VarInPower(3, 1)}))}),
            Polynom({Monom({VarInPower(1, 2)}), MonomWithCoef({-1}, Monom({VarInPower(1, 1)})), MonomWithCoef({-1}, Monom({VarInPower(2, 1), VarInPower(3, 1)}))}),
            Polynom({Monom({VarInPower(1, 1), VarInPower(3, 1)}), MonomWithCoef({-1}, Monom({VarInPower(2, 2)})), MonomWithCoef({-1}, Monom({VarInPower(2, 1)}))})
        },
        {
            Polynom({Monom({VarInPower(1, 1), VarInPower(2, 1)}), MonomWithCoef({-1}, Monom({VarInPower(3, 2)})), MonomWithCoef({-1}, Monom({VarInPower(3, 1)}))}),
            Polynom({Monom({VarInPower(1, 2)}), MonomWithCoef({-1}, Monom({VarInPower(1, 1)})), MonomWithCoef({-1}, Monom({VarInPower(2, 1), VarInPower(3, 1)}))}),
            Polynom({Monom({VarInPower(1, 1), VarInPower(3, 1)}), MonomWithCoef({-1}, Monom({VarInPower(2, 2)})), MonomWithCoef({-1}, Monom({VarInPower(2, 1)}))}),
            Polynom({Monom({VarInPower(2, 1), VarInPower(3, 1)}), Monom({VarInPower(2, 2)}), Monom({VarInPower(2, 1)}), MonomWithCoef(-1, Monom({VarInPower(3, 2)})), MonomWithCoef(-1, Monom({VarInPower(3, 1)}))}),
            Polynom({MonomWithCoef(-2, Monom({VarInPower(2, 1), VarInPower(3, 2)})), MonomWithCoef(-2, Monom({VarInPower(2, 1), VarInPower(3, 1)})), MonomWithCoef(2, Monom({VarInPower(3, 3)})), MonomWithCoef(2, Monom({VarInPower(3, 2)}))}),
            Polynom({MonomWithCoef(-2, Monom({VarInPower(2, 1), VarInPower(3, 1)}))})
        }
    });

    for (const auto& test_case : cases) {
        std::vector<Polynom> result = BaseAlgorithms().BuhbergerAlgorithm(test_case.vect);
        EXPECT_EQ(result.size(), test_case.result.size());
        for (size_t i = 0; i < result.size(); ++i) {
            EXPECT_EQ(result[i].ToString(), test_case.result[i].ToString());
        }
    }
}

TEST(BaseAlgorithms, IsPolynomInIdeal) {
    struct TestCase {
        Polynom pol;
        std::vector<Polynom> vect;
        bool result;
    };
    std::vector<TestCase> cases;
    cases.push_back({
        Polynom({Monom({VarInPower(1, 1), VarInPower(3, 1)}), MonomWithCoef({-1}, Monom({VarInPower(2, 2)})), MonomWithCoef({-1}, Monom({VarInPower(2, 1)}))}),
        {
            Polynom({Monom({VarInPower(1, 1), VarInPower(2, 1)}), MonomWithCoef({-1}, Monom({VarInPower(3, 2)})), MonomWithCoef({-1}, Monom({VarInPower(3, 1)}))}),
            Polynom({Monom({VarInPower(1, 2)}), MonomWithCoef({-1}, Monom({VarInPower(1, 1)})), MonomWithCoef({-1}, Monom({VarInPower(2, 1), VarInPower(3, 1)}))}),
            Polynom({Monom({VarInPower(1, 1), VarInPower(3, 1)}), MonomWithCoef({-1}, Monom({VarInPower(2, 2)})), MonomWithCoef({-1}, Monom({VarInPower(2, 1)}))})
        },
        true
    });
    cases.push_back({
        Polynom({MonomWithCoef(-2, Monom({VarInPower(2, 1), VarInPower(3, 1)}))}),
        {
            Polynom({Monom({VarInPower(1, 1), VarInPower(2, 1)}), MonomWithCoef({-1}, Monom({VarInPower(3, 2)})), MonomWithCoef({-1}, Monom({VarInPower(3, 1)}))}),
            Polynom({Monom({VarInPower(1, 2)}), MonomWithCoef({-1}, Monom({VarInPower(1, 1)})), MonomWithCoef({-1}, Monom({VarInPower(2, 1), VarInPower(3, 1)}))}),
            Polynom({Monom({VarInPower(1, 1), VarInPower(3, 1)}), MonomWithCoef({-1}, Monom({VarInPower(2, 2)})), MonomWithCoef({-1}, Monom({VarInPower(2, 1)}))})
        },
        true
    });
    cases.push_back({
        Polynom({MonomWithCoef(-3, Monom({VarInPower(4, 3),}))}),
        {
            Polynom({Monom({VarInPower(1, 1), VarInPower(2, 1)}), MonomWithCoef({-1}, Monom({VarInPower(3, 2)})), MonomWithCoef({-1}, Monom({VarInPower(3, 1)}))}),
            Polynom({Monom({VarInPower(1, 2)}), MonomWithCoef({-1}, Monom({VarInPower(1, 1)})), MonomWithCoef({-1}, Monom({VarInPower(2, 1), VarInPower(3, 1)}))}),
            Polynom({Monom({VarInPower(1, 1), VarInPower(3, 1)}), MonomWithCoef({-1}, Monom({VarInPower(2, 2)})), MonomWithCoef({-1}, Monom({VarInPower(2, 1)}))})
        },
        false
    });

    for (const auto& test_case : cases) {
        EXPECT_EQ(BaseAlgorithms().IsPolynomInIdeal(test_case.pol, test_case.vect), test_case.result);
    }
}
