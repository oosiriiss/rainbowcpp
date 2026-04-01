#include <print>
#include <rainbowcpp/rainbowcpp.hpp>

#include "rainbowcpp/colors.hpp"

int main() {
  using Bg4Bit = rainbow::colors::bit4::Background;
  using Fg4Bit = rainbow::colors::bit4::Foreground;

  std::println("{}Colored text with 4bit colors{}",
               rainbow::color<Fg4Bit::Black, Bg4Bit::BrightYellow>(),
               rainbow::reset());
  std::println("{}Colored text with 24bit colors{}",
               rainbow::color<rainbow::Color(100, 220, 255),
                              rainbow::Color(0, 15, 30)>(),
               rainbow::reset());
  std::println(
      "{}Colored text with 4bit foreground and 24bit background colors{}",
      rainbow::color<Fg4Bit::BrightWhite, rainbow::Color(76, 114, 137)>(),
      rainbow::reset());

  std::println(
      "{}Colored text with 24bit foreground and 4bit background colors{}",
      rainbow::color<rainbow::Color(255, 180, 150), Bg4Bit::Black>(),
      rainbow::reset());
}
