#include "grebner_basises/rational.hpp"
#include "grebner_basises/utils.hpp"

#include <cmath>
#include <stdexcept>

void Rational::simplify() {
    int g = utils::CalculateGCD(abs(num), abs(denum));
    num /= g;
    denum /= g;
    if (denum < 0) {
        denum = -denum;
        num = -num;
    }
}

Rational::Rational::Rational(int a, int b)
    : num(a), denum(b) {
    this->simplify();
}

Rational::Rational(int a)
    : num(a), denum(1) {}

Rational::Rational()
    : num(0), denum(1) {}

int Rational::GetNumerator() const& {
    return num;
}

int Rational::GetDenumerator() const& {
    return denum;
}

Rational Rational::operator -() const& {
    Rational result(-this->GetNumerator(), this->GetDenumerator());
    return result;
}

Rational Rational::operator +(const Rational& other) const& {
    Rational result(this->GetNumerator() * other.GetDenumerator() + other.GetNumerator() * this->GetDenumerator(), this->GetDenumerator() * other.GetDenumerator());
    result.simplify();
    return result;
}

Rational Rational::operator -(const Rational& other) const& {
    Rational result(this->GetNumerator() * other.GetDenumerator() - other.GetNumerator() * this->GetDenumerator(), this->GetDenumerator() * other.GetDenumerator());
    result.simplify();
    return result;
}

Rational Rational::operator *(const Rational& other) const& {
    Rational result(this->GetNumerator() * other.GetNumerator(), this->GetDenumerator() * other.GetDenumerator());
    result.simplify();
    return result;
}

Rational Rational::operator /(const Rational& other) const& {
    if (other.GetNumerator() == 0) {
        throw std::runtime_error("Can't divide on zero");
    }
    Rational result(this->GetNumerator() * other.GetDenumerator(), this->GetDenumerator() * other.GetNumerator());
    result.simplify();
    return result;
}

bool Rational::operator ==(const Rational& other) const& {
    return this->num == other.num && this->denum == other.denum;
}

bool Rational::operator <(const Rational& other) const& {
    Rational temp = *this - other;
    return temp.GetNumerator() < 0;
}

bool Rational::operator >(const Rational& other) const& {
    Rational temp = *this - other;
    return temp.GetNumerator() > 0;
}

std::string Rational::ToString() const& {
    if (this->GetNumerator() == 0) {
        return "0";
    }
    if (this->GetDenumerator() == 1) {
        return std::to_string(this->GetNumerator());
    }
    return std::to_string(this->GetNumerator()) + "/" + std::to_string(this->GetDenumerator());
}
