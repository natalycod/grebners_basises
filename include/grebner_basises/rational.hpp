#pragma once

#include <string>

class Rational {
  private:
    int num;
    int denum;

  public:
    Rational(int a, int b);
    Rational(int a);
    Rational();

    int GetNumerator() const&;
    int GetDenumerator() const&;

    void simplify();

    Rational operator -() const&;

    Rational operator +(const Rational& other) const&;
    Rational operator -(const Rational& other) const&;
    Rational operator *(const Rational& other) const&;
    Rational operator /(const Rational& other) const&;

    bool operator ==(const Rational& other) const&;
    bool operator <(const Rational& other) const&;
    bool operator >(const Rational& other) const&;

    std::string ToString() const&;
};
