cmake_minimum_required(VERSION 3.14)

project(rainbowcppExamples CXX)

include(../cmake/project-is-top-level.cmake)

if(PROJECT_IS_TOP_LEVEL)
  find_package(rainbowcpp REQUIRED)
endif()

add_custom_target(run-examples)


function(add_example NAME)
  add_executable("${NAME}" "${NAME}.cpp")
  target_link_libraries("${NAME}" PRIVATE rainbowcpp::rainbowcpp)
  target_compile_features("${NAME}" PRIVATE cxx_std_23)

   # std::print on windows mingw
   if(WIN32 AND MINGW)
      target_link_libraries("${NAME}" PRIVATE stdc++exp)
   endif()


  add_custom_target("run_${NAME}" COMMAND "${NAME}" VERBATIM)
  add_dependencies("run_${NAME}" "${NAME}")
  add_dependencies(run-examples "run_${NAME}")
endfunction()

add_example(4bit)
add_example(24bit)
add_example(general)
