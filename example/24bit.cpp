#include <print>

#include "rainbowcpp/colors.hpp"
#include "rainbowcpp/rainbowcpp.hpp"

using rainbow::Color;

constexpr static auto staticColor =
    rainbow::color<Color(255, 0, 0), Color(0, 0, 0)>();

auto main() -> int { // NOLINT
  std::print("Static color code is:");
  for (char chr : staticColor) {
    std::print("{} ", static_cast<int>(chr));
  }
  std::println("");

  std::println("Hello {}This is colored text with 24-bit{}",
               staticColor,  // NOLINT
               rainbow::reset());
}
