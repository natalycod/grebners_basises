#pragma once

#include "grebner_basises/polynom.hpp"

class BaseAlgorithms {
  public:
    bool IsReducableOnPolynom(const Polynom& a, const Polynom& b);

    Monom GetMonomLCM(const Monom& m1, const Monom& m2);

    Polynom ReduceOnPolynom(const Polynom& a, const Polynom& b);
    Polynom ReduceOnPolynomSet(const Polynom& a, const std::vector<Polynom>& vect);
    std::vector<Polynom> BuhbergerAlgorithm(const std::vector<Polynom>& vect);
    
    bool IsPolynomInIdeal(const Polynom& a, const std::vector<Polynom>& vect);
};
