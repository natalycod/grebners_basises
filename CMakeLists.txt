# cmake config 
cmake_minimum_required(VERSION 3.14)
project(grebner_basises VERSION 1.0.1)

# c++ requirements
set(CMAKE_CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)

# directory for binary files
set(PROJECT_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# "compile" library
set(target grebner_basises_lib)

add_library(${target} STATIC 
    src/polynom.cpp
    src/monom.cpp
    src/monom_with_coef.cpp
    src/var_in_power.cpp
    src/rational.cpp
    src/utils.cpp
    src/base_algorithms.cpp
)

target_include_directories(${target} PUBLIC include)

# add tests
add_subdirectory(tests)

# downloading google test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
