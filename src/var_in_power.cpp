#include "grebner_basises/var_in_power.hpp"

#include <stdexcept>

VarInPower::VarInPower()
    : var_id(0), power(0) {};

VarInPower::VarInPower(int id)
    : var_id(id), power(1) {};

VarInPower::VarInPower(int id, int pow)
    : var_id(id), power(pow) {};

VarInPower VarInPower::operator *(const VarInPower& other) const& {
    if (this->var_id == other.var_id || other.power == 0) {
        return VarInPower(this->var_id, this->power + other.power);
    }
    if (this->power == 0) {
        return VarInPower(other.var_id, this->power + other.power);
    }
    throw std::runtime_error("Can't multiply variables with different ids");
}

VarInPower VarInPower::operator /(const VarInPower& other) const& {
    if (this->var_id == other.var_id || other.power == 0) {
        return VarInPower(this->var_id, this->power - other.power);
    }
    if (this->power == 0) {
        return VarInPower(other.var_id, this->power - other.power);
    }
    throw std::runtime_error("Can't divide variables with different ids");
}

bool VarInPower::operator <(const VarInPower& other) const& {
    return this->var_id < other.var_id;
}

bool VarInPower::operator >(const VarInPower& other) const& {
    return this->var_id > other.var_id;
}

bool VarInPower::operator ==(const VarInPower& other) const& {
    return this->var_id == other.var_id;
}

std::string VarInPower::ToString() const& {
    if (this->power == 1) {
        return "x_" + std::to_string(this->var_id);
    }
    return "x_" + std::to_string(this->var_id) + "^" + std::to_string(this->power);
}
 