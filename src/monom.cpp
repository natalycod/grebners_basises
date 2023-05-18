#include "grebner_basises/monom.hpp"
#include "grebner_basises/utils.hpp"

namespace {
bool VarsInPowersFullyEqual(const VarInPower& a, const VarInPower& b) {
    return a.var_id == b.var_id && a.power == b.power;
}

bool VarsInPowersFullyLess(const VarInPower& a, const VarInPower& b) {
    if (a.var_id != b.var_id) {
        return a.var_id < b.var_id;
    }
    return a.power < b.power;
}

bool VarsInPowersFullyGreater(const VarInPower& a, const VarInPower& b) {
    if (a.var_id != b.var_id) {
        return a.var_id > b.var_id;
    }
    return a.power > b.power;
}

}

Monom::Monom()
    : powers() {}

Monom::Monom(std::vector<VarInPower> vect)
    : powers(vect) {}

Monom Monom::operator *(const Monom& other) const& {
    std::vector<VarInPower> powers;
    powers = utils::MergeSort<VarInPower>(this->powers, other.powers,
                                          [&] (const VarInPower& x) {return x;},
                                          [&] (const VarInPower& x, const VarInPower& y) {return x * y;});
    return Monom(powers);
}

Monom Monom::operator /(const Monom& other) const& {
    std::vector<VarInPower> powers;
    for (const auto var : utils::MergeSort<VarInPower>(this->powers, other.powers,
                                                       [&] (const VarInPower& x) {return VarInPower() / x;},
                                                       [&] (const VarInPower& x, const VarInPower& y) {return x / y;})) {
        if (var.power < 0) {
            throw std::runtime_error("Can't divide monoms, got negative powers");
        }
        if (var.power > 0) {
            powers.push_back(var);
        }
    }
    return Monom(powers);
}

bool Monom::operator <(const Monom& other) const& {
    for (size_t i = 0; i < this->powers.size(); ++i) {
        if (i >= other.powers.size()) {
            return false;
        }
        if (this->powers[i].var_id < other.powers[i].var_id) {
            return false;
        }
        if (this->powers[i].var_id > other.powers[i].var_id) {
            return true;
        }
        if (this->powers[i].power < other.powers[i].power) {
            return true;
        }
        if (this->powers[i].power > other.powers[i].power) {
            return false;
        }
    }
    if (other.powers.size() > this->powers.size()) {
        return true;
    }
    return false;
}

bool Monom::operator >(const Monom& other) const& {
    for (size_t i = 0; i < this->powers.size(); ++i) {
        if (i >= other.powers.size()) {
            return true;
        }
        if (this->powers[i].var_id < other.powers[i].var_id) {
            return true;
        }
        if (this->powers[i].var_id > other.powers[i].var_id) {
            return false;
        }
        if (this->powers[i].power < other.powers[i].power) {
            return false;
        }
        if (this->powers[i].power > other.powers[i].power) {
            return true;
        }
    }
    if (other.powers.size() < this->powers.size()) {
        return false;
    }
    return false;
}

bool Monom::operator ==(const Monom& other) const& {
    if (this->powers.size() != other.powers.size()) {
        return false;
    }
    for (size_t i = 0; i < this->powers.size(); ++i) {
        if (!VarsInPowersFullyEqual(this->powers[i], other.powers[i])) {
            return false;
        }
    }
    return true;
}

bool Monom::IsDivisible(const Monom& other) const& {
    try {
        *this / other;
    }
    catch (...) {
        return false;
    }
    return true;
}

std::string Monom::ToString() const& {
    std::string result = "";
    for (const VarInPower& var : this->powers) {
        if (!result.empty()) {
            result += " ";
        }
        result += var.ToString();
    }
    return result;
}
