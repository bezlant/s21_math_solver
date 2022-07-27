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

set(CMAKE_CONFIGURATION_TYPES "Debug" "Release")
set(CMAKE_VERBOSE_MAKEFILE ON)
add_executable(calc_test "${SOURCE_FILES}")

# Get compile commands for clangd & copy them to src/
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_target(
  copy-compile-commands ALL
  ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR})

# Standards
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compilation flags
set(CMAKE_C_FLAGS "-Wall -Werror -Wextra")

# Sources
set(SOURCE_FILES ./ui/ui_test.cpp)

# Executable
add_executable(ui_test "${SOURCE_FILES}")

# Link all libraries
find_package(glfw3 3.3 REQUIRED)

target_link_libraries(ui_test glfw)

# Debug Prints
message(STATUS "Sources: " ${SOURCE_FILES})
