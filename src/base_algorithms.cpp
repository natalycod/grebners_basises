#include "grebner_basises/base_algorithms.hpp"
#include "grebner_basises/monom_with_coef.hpp"
#include "grebner_basises/utils.hpp"

#include <iostream>

bool BaseAlgorithms::IsReducableOnPolynom(const Polynom& a, const Polynom& b) {
    const MonomWithCoef L = b.GetLeadingMonom();
    for (const auto& monom : a.monoms) {
        if (monom.monom.IsDivisible(L.monom)) {
            return true;
        }
    }
    return false;
}

Polynom BaseAlgorithms::ReduceOnPolynom(const Polynom& a, const Polynom &b) {
    Polynom result = a;
    MonomWithCoef L = b.monoms.back();
    int del_count = 1;
    while (del_count > 0) {
        del_count = 0;
        for (const auto monom : result.monoms) {
            if (monom.monom.IsDivisible(L.monom)) {
                MonomWithCoef h(monom.coef / L.coef, monom.monom / L.monom);
                result = result - Polynom({monom}) + Polynom({h}) * (Polynom({L}) - b);
                ++del_count;
            }
        }
    }
    return result;
}

Polynom BaseAlgorithms::ReduceOnPolynomSet(const Polynom& a, const std::vector<Polynom>& vect) {
    Polynom result = a;
    int del_count = 1;
    while (del_count > 0) {
        del_count = 0;
        for (const auto& pol : vect) {
            if (IsReducableOnPolynom(result, pol)) {
                result = ReduceOnPolynom(result, pol);
                ++del_count;
            }
        }
    }
    return result;
}

Monom BaseAlgorithms::GetMonomLCM(const Monom& m1, const Monom& m2) {
    std::vector<VarInPower> vars;
    vars = utils::MergeSort<VarInPower>(m1.powers, m2.powers, [&](const VarInPower& var) {return var;}, [&](const VarInPower& var1, const VarInPower& var2) {return VarInPower(var1.var_id, std::max(var1.power, var2.power));});
    return Monom(vars);
}

std::vector<Polynom> BaseAlgorithms::BuhbergerAlgorithm(const std::vector<Polynom>& vect) {
    std::vector<Polynom> result = vect;
    for (size_t i = 0; i < vect.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            MonomWithCoef m = GetMonomLCM(result[i].GetLeadingMonom(), result[j].GetLeadingMonom());
            MonomWithCoef h1(Rational(1) / result[i].monoms.back().coef, m.monom / result[i].GetLeadingMonom());
            MonomWithCoef h2(Rational(1) / result[j].monoms.back().coef, m.monom / result[j].GetLeadingMonom());
            Polynom candidate = Polynom({h1}) * result[i] - Polynom({h2}) * result[j];
            candidate = ReduceOnPolynomSet(candidate, result);
            if (!candidate.monoms.empty()) {
                result.push_back(candidate);
            }
        }
    }
    return result;
}

bool BaseAlgorithms::IsPolynomInIdeal(const Polynom& a, const std::vector<Polynom>& vect) {
    const std::vector<Polynom> grebner_basis = BuhbergerAlgorithm(vect);
    const Polynom reduced_pol = ReduceOnPolynomSet(a, grebner_basis);
    return reduced_pol.monoms.empty();
}
