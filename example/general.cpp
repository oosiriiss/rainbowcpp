#include <print>
#include <rainbowcpp/rainbowcpp.hpp>

#include "rainbowcpp/colors.hpp"

int main() {
  using Bg4Bit = rainbow::colors::bit4::Background;
  using Fg4Bit = rainbow::colors::bit4::Foreground;

  std::println("{}Colored text with 4bit colors{}",
               rainbow::color<Fg4Bit::Blue, Bg4Bit::BrightCyan>(),
               rainbow::reset());
  std::println("{}Colored text with 24bit colors{}",
               rainbow::color<rainbow::Color(255, 0, 0),
                              rainbow::Color(120, 120, 120)>(),
               rainbow::reset());

  std::println(
      "{}Colored text with 4bit foreground and 24bit background colors{}",
      rainbow::color<Fg4Bit::BrightRed, rainbow::Color(180, 90, 45)>(),
      rainbow::reset());

  std::println(
      "{}Colored text with 4bit foreground and 24bit background colors{}",
      rainbow::color<Fg4Bit::Yellow, rainbow::Color(20, 77, 150)>(),
      rainbow::reset());
}
