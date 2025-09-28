cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    rainbowcpp
    VERSION 0.1.0
    DESCRIPTION "C++ Colorful output micro-library"
    HOMEPAGE_URL " "
    LANGUAGES NONE
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

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
  option(BUILD_EXAMPLES "Build examples tree." "${rainbowcpp_DEVELOPER_MODE}")
  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
endif()

# ---- Developer mode ----

if(NOT rainbowcpp_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of rainbowcpp"
  )
endif()

include(cmake/dev-mode.cmake)
