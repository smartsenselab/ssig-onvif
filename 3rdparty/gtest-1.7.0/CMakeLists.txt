########################################################################
# CMake build script for Google Test.
#
# To run the tests for Google Test itself on Linux, use 'make test' or
# ctest.  You can select which tests to run using 'ctest -R regex'.
# For more options, run 'ctest --help'.

# When other libraries are using a shared version of runtime libraries,
# Google Test also has to use one.
set(
  gtest_force_shared_crt
  OFF)

set(gtest_disable_pthreads ON)

# Defines pre_project_set_up_hermetic_build() and set_up_hermetic_build().
include(cmake/hermetic_build.cmake OPTIONAL)

if (COMMAND pre_project_set_up_hermetic_build)
  pre_project_set_up_hermetic_build()
endif()

MARK_AS_ADVANCED(gtest_force_shared_crt gtest_disable_pthreads)

########################################################################
#
# Project-wide settings

# Name of the project.
#
# CMake files in this project can refer to the root source directory
# as ${gtest_SOURCE_DIR} and to the root binary directory as
# ${gtest_BINARY_DIR}.
# Language "C" is required for find_package(Threads).
project(gtest CXX C)
cmake_minimum_required(VERSION 2.6.2)

if (COMMAND set_up_hermetic_build)
  set_up_hermetic_build()
endif()

# Define helper functions and macros used by Google Test.
include(cmake/internal_utils.cmake)

config_compiler_and_linker()  # Defined in internal_utils.cmake.



# Where Google Test's libraries can be found.
#link_directories(${gtest_BINARY_DIR}/src)

########################################################################
#
# Defines the gtest & gtest_main libraries.  User tests should link
# with one of them.

# Google Test libraries.  We build them using more strict warnings than what
# are used for other targets, to ensure that gtest can be compiled by a user
# aggressive about warnings.
cxx_library(gtest "${cxx_strict}" src/gtest-all.cc)
cxx_library(gtest_main "${cxx_strict}" src/gtest_main.cc)
# Where Google Test's .h files can be found.
target_include_directories(gtest PUBLIC
  ${gtest_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR})

target_include_directories(gtest_main PUBLIC
  ${gtest_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR})

target_link_libraries(gtest_main gtest)

set_target_properties(gtest PROPERTIES FOLDER 3RDPARTY)
set_target_properties(gtest_main PROPERTIES FOLDER 3RDPARTY)
