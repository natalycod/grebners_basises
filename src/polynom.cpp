#include "grebner_basises/monom_with_coef.hpp"
#include "grebner_basises/rational.hpp"
#include "grebner_basises/monom.hpp"
#include "grebner_basises/polynom.hpp"
#include "grebner_basises/utils.hpp"

#include <vector>

namespace {
std::pair<Rational, Monom> EqualMonomsAddition(const std::pair<Rational, Monom>& a, const std::pair<Rational, Monom>& b) {
  return std::make_pair(a.first + b.first, a.second);
}
}

Polynom::Polynom()
    : monoms() {}

Polynom::Polynom(const Rational& r)
    : monoms({MonomWithCoef(r, Monom())}) {}

Polynom::Polynom(const Monom& var)
    : monoms({MonomWithCoef(Rational(1), var)}) {}

Polynom::Polynom(std::vector<MonomWithCoef> vect)
    : monoms(vect) {
    std::sort(monoms.begin(), monoms.end());
}

Polynom Polynom::operator +(const Polynom& other) const& {
    std::vector<MonomWithCoef> monoms;
    for (const auto& monom : utils::MergeSort<MonomWithCoef>(this->monoms, other.monoms,
                                                            [&] (const MonomWithCoef& x) {return x;},
                                                            [&] (const MonomWithCoef& x, const MonomWithCoef& y) {return x + y;})) {
        if (monom.coef.GetNumerator() != 0) {
            monoms.push_back(monom);
        }
    }
    return Polynom(monoms);
}

Polynom Polynom::operator -(const Polynom& other) const& {
    std::vector<MonomWithCoef> monoms;
    for (const auto& monom : utils::MergeSort<MonomWithCoef>(this->monoms, other.monoms,
                                                            [&] (const MonomWithCoef& x) {return MonomWithCoef(-x.coef, x.monom);},
                                                            [&] (const MonomWithCoef& x, const MonomWithCoef& y) {return x - y;})) {
        if (monom.coef.GetNumerator() != 0) {
            monoms.push_back(monom);
        }
    }
    return Polynom(monoms);
}

Polynom Polynom::operator *(const Polynom& other) const& {
    Polynom result;
    for (const auto monom1 : this->monoms) {
        std::vector<MonomWithCoef> vect;
        for (const auto monom2 : other.monoms) {
            vect.push_back(MonomWithCoef(monom1.coef * monom2.coef, monom1.monom * monom2.monom));
        }
        result = result + Polynom(vect);
    }
    return result;
}

Monom Polynom::GetLeadingMonom() const& {
    return this->monoms.back().monom;
}

std::string Polynom::ToString() const& {
    std::string result = "";
    for (const auto& monom : this->monoms) {
        if (!result.empty()) {
            result += (monom.coef > Rational(0) ? " + " : " - ");
        }
        if (!result.empty() && monom.coef < Rational(0)) {
            result += MonomWithCoef(-monom.coef, monom.monom).ToString();
        }
        else {
            result += monom.ToString();
        }
    }
    return result;
}
