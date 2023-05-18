enable_testing()

add_executable(
  test_rational test_rational.cpp
  test_monom test_monom.cpp
  test_var_in_power test_var_in_power.cpp
  test_utils test_utils.cpp
  test_polynom test_polynom.cpp
  test_monom_with_coef test_monom_with_coef.cpp
  test_base_algorithms test_base_algorithms.cpp
)

target_link_libraries(
  test_rational
  GTest::gtest_main
  grebner_basises_lib
)
  
add_executable(test_monom test_monom.cpp)
target_link_libraries(
  test_monom
  GTest::gtest_main
  grebner_basises_lib
)

add_executable(test_var_in_power test_var_in_power.cpp)
target_link_libraries(
  test_var_in_power
  GTest::gtest_main
  grebner_basises_lib
)

add_executable(test_utils test_utils.cpp)
target_link_libraries(
  test_utils
  GTest::gtest_main
  grebner_basises_lib
)

add_executable(test_polynom test_polynom.cpp)
target_link_libraries(
  test_polynom
  GTest::gtest_main
  grebner_basises_lib
)

add_executable(test_monom_with_coef test_monom_with_coef.cpp)
target_link_libraries(
  test_monom_with_coef
  GTest::gtest_main
  grebner_basises_lib
)

add_executable(test_base_algorithms test_base_algorithms.cpp)
target_link_libraries(
  test_base_algorithms
  GTest::gtest_main
  grebner_basises_lib
)

include(googletest)
gtest_discover_tests(
  test_rational
  test_monom
  test_var_in_power
  test_utils
  test_polynom
  test_monom_with_coef
  test_base_algorithms
)
