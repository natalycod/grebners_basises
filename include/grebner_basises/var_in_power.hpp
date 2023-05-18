#pragma once

#include <string>

class VarInPower {
  public:
    int var_id;
    int power;

    VarInPower();
    VarInPower(int id);
    VarInPower(int id, int pow);

    VarInPower operator *(const VarInPower& other) const&;
    VarInPower operator /(const VarInPower& other) const&;

    bool operator <(const VarInPower& other) const&;
    bool operator >(const VarInPower& other) const&;
    bool operator ==(const VarInPower& other) const&;

    std::string ToString() const&;
};
