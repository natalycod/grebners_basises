#include "grebner_basises/rational.hpp"
#include "grebner_basises/monom.hpp"
#include "grebner_basises/monom_with_coef.hpp"

#include <vector>

class Polynom {
  public:
    std::vector<MonomWithCoef> monoms;

    Polynom();
    Polynom(const Rational& r);
    Polynom(const Monom& var);
    Polynom(std::vector<MonomWithCoef> _vect);

    Polynom operator +(const Polynom& other) const&;
    Polynom operator -(const Polynom& other) const&;
    Polynom operator *(const Polynom& other) const&;

    Monom GetLeadingMonom() const&;

    std::string ToString() const&;
};
