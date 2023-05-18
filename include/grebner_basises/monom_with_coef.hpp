#pragma once

#include "grebner_basises/monom.hpp"
#include "grebner_basises/rational.hpp"

class MonomWithCoef {
  public:
    Rational coef;
    Monom monom;
    int var_id;
    int power;

    MonomWithCoef();
    MonomWithCoef(const Rational& r);
    MonomWithCoef(const Monom& m);
    MonomWithCoef(const Rational& r, const Monom& m);

    MonomWithCoef operator +(const MonomWithCoef& other) const&;
    MonomWithCoef operator -(const MonomWithCoef& other) const&;

    bool operator ==(const MonomWithCoef& other) const&;
    bool operator <(const MonomWithCoef& other) const&;
    bool operator >(const MonomWithCoef& other) const&;

    std::string ToString() const&;
};
