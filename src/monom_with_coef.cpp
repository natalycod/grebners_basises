#include "grebner_basises/monom_with_coef.hpp"

#include <stdexcept>

MonomWithCoef::MonomWithCoef()
    : coef(Rational()), monom(Monom()) {}

MonomWithCoef::MonomWithCoef(const Rational& r)
    : coef(r), monom(Monom()) {}

MonomWithCoef::MonomWithCoef(const Monom& m)
    : coef(Rational(1)), monom(m) {}

MonomWithCoef::MonomWithCoef(const Rational& r, const Monom& m)
    : coef(r), monom(m) {}

MonomWithCoef MonomWithCoef::operator +(const MonomWithCoef& other) const& {
    if (this->monom == other.monom) {
        return MonomWithCoef(this->coef + other.coef, this->monom);
    }
    throw std::runtime_error("Can't find sum of different monoms");
}

MonomWithCoef MonomWithCoef::operator -(const MonomWithCoef& other) const& {
    if (this->monom == other.monom) {
        return MonomWithCoef(this->coef - other.coef, this->monom);
    }
    throw std::runtime_error("Can't find sum of different monoms");
}

bool MonomWithCoef::operator ==(const MonomWithCoef& other) const& {
    return this->monom == other.monom;
}

bool MonomWithCoef::operator <(const MonomWithCoef& other) const& {
    return this->monom < other.monom;
}

bool MonomWithCoef::operator >(const MonomWithCoef& other) const& {
    return this->monom > other.monom;
}

std::string MonomWithCoef::ToString() const& {
    if (this->coef.ToString() == "1") {
        return this->monom.ToString();
    }
    if (this->coef.ToString() == "-1") {
        return "-" + this->monom.ToString();
    }
    if (this->coef.ToString() == "0") {
        return "0";
    }
    return this->coef.ToString() + " " + this->monom.ToString();
}
