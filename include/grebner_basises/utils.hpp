#include "grebner_basises/rational.hpp"

#include <vector>

namespace utils {

template <typename T>
std::vector<T> MergeSort(const std::vector<T>& a, const std::vector<T>& b, std::function<T(const T&)> b_func, std::function<T(const T&, const T&)> equal_action);

int CalculateGCD(int a, int b);

} // utils
