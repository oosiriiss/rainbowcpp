cmake_minimum_required(VERSION 3.14)

project(rainbowcppTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(rainbowcpp REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

add_executable(rainbowcpp_test source/rainbowcpp_test.cpp)
target_link_libraries(rainbowcpp_test PRIVATE rainbowcpp::rainbowcpp)
target_compile_features(rainbowcpp_test PRIVATE cxx_std_23)

add_test(NAME rainbowcpp_test COMMAND rainbowcpp_test)

# ---- End-of-file commands ----

add_folders(Test)
