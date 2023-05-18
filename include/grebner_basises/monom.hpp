#pragma once

#include "grebner_basises/var_in_power.hpp"

#include <vector>

class Monom {
  public:
    std::vector<VarInPower> powers;

    Monom();
    Monom(std::vector<VarInPower> vect);
    
    Monom operator *(const Monom& other) const&;
    Monom operator /(const Monom& other) const&;

    bool operator <(const Monom& other) const&;
    bool operator >(const Monom& other) const&;
    bool operator ==(const Monom& other) const&;

    bool IsDivisible(const Monom& other) const&;

    std::string ToString() const&;
};
