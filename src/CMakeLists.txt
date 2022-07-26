cmake_minimum_required(VERSION 3.1)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(
  MathSolver
  VERSION 1.0
  DESCRIPTION
    "Implementation of the math solver in C following the principles of structured programming"
  HOMEPAGE_URL "https://github.com/bezlant/s21_math_solver"
  LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(calc_test ./test/test_stack.c ./test/test_runner.c
                         ./stack/stack.c)
target_link_libraries(calc_test PUBLIC Check)
target_compile_options(calc_test PRIVATE -pedantic -std=c11 -Wall -Werror
                                         -Wextra)
