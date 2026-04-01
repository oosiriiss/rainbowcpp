cmake_minimum_required(VERSION 3.14)

project(
    rainbowcpp
    VERSION 0.3.1
    DESCRIPTION "C++ ANSI color escape codes output library"
    HOMEPAGE_URL " "
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)

add_library(rainbowcpp_rainbowcpp INTERFACE)
add_library(rainbowcpp::rainbowcpp ALIAS rainbowcpp_rainbowcpp)

set_property(
    TARGET rainbowcpp_rainbowcpp PROPERTY
    EXPORT_NAME rainbowcpp
)

target_include_directories(
    rainbowcpp_rainbowcpp ${warning_guard}
    INTERFACE
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(rainbowcpp_rainbowcpp INTERFACE cxx_std_23)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
   option(BUILD_EXAMPLES "Build rainbowcpp examples." ON)
  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
endif()

