#include <print>

#include "rainbowcpp/colors.hpp"
#include "rainbowcpp/rainbowcpp.hpp"
auto main() -> int {
  using rainbow::Color;

  std::println(
      "Hello {}This is colored text with 24-bit{}",
      rainbow::color<Color(255, 255, 255), Color(255, 0, 0)>(),  // NOLINT
      rainbow::reset());
}
