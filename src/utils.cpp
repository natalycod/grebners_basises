#include "grebner_basises/utils.hpp"

#include "grebner_basises/var_in_power.hpp"
#include "grebner_basises/monom_with_coef.hpp"

template <typename T>
std::vector<T> utils::MergeSort(const std::vector<T>& a, const std::vector<T>& b, std::function<T(const T&)> b_func, std::function<T(const T&, const T&)> equal_action) {
    std::vector<T> result;
    size_t La = 0;
    size_t Lb = 0;
    while (La < a.size() && Lb < b.size()) {
        if (a[La] < b[Lb]) {
            result.push_back(a[La]);
            ++La;
        } else if (a[La] > b[Lb]) {
            result.push_back(b_func(b[Lb]));
            ++Lb;
        } else {
            result.push_back(equal_action(a[La], b[Lb]));
            ++La;
            ++Lb;
        }
    }
    while (La < a.size()) {
        result.push_back(a[La]);
        ++La;
    }
    while (Lb < b.size()) {
        result.push_back(b_func(b[Lb]));
        ++Lb;
    }
    return result;
}

template std::vector<VarInPower> utils::MergeSort<VarInPower>(const std::vector<VarInPower>&, const std::vector<VarInPower>&, std::function<VarInPower(const VarInPower&)>, std::function<VarInPower(const VarInPower&, const VarInPower&)>);
template std::vector<MonomWithCoef> utils::MergeSort<MonomWithCoef>(const std::vector<MonomWithCoef>&, const std::vector<MonomWithCoef>&, std::function<MonomWithCoef(const MonomWithCoef&)>, std::function<MonomWithCoef(const MonomWithCoef&, const MonomWithCoef&)>);

int utils::CalculateGCD(int a, int b) {
    if (a == 0) {
        return b;
    }
    return CalculateGCD(b % a, a);
}
