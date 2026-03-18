#include <print>

#include "rainbowcpp/colors.hpp"
#include "rainbowcpp/rainbowcpp.hpp"

using rainbow::colors::bit4::Background;
using rainbow::colors::bit4::Foreground;

template <Foreground... Foregrounds>
static void printAll() {
  (std::println("{}Some example text{}",
                rainbow::color<Foregrounds, Background::Black>(),
                rainbow::reset()),
   ...);
}

template <Background... Backgrounds>
static void printAll() {
  (std::println("{}Some example text{}",
                rainbow::color<Foreground::Black, Backgrounds>(),
                rainbow::reset()),
   ...);
}

constexpr static auto staticColor =
    rainbow::color<Foreground::Black, Background::White>();

constexpr static auto staticColor2 =
    rainbow::color<Foreground::Black, Background::BrightBlue>();

auto main() -> int {  // NOLINT bugprone-exception-escape
  std::print("Static color code is:");
  for (char chr : staticColor) {
    std::print("{} ", static_cast<int>(chr));
  }

  std::print("\nStatic color 2 code is:");
  for (char chr : staticColor2) {
    std::print("{} ", static_cast<int>(chr));
  }
  std::println("");

  std::println("{} Possible 4bit {} foreground colors are:{} ", staticColor,
               staticColor2, rainbow::reset());
  printAll<Foreground::Black, Foreground::Red, Foreground::Green,
           Foreground::Yellow, Foreground::Blue, Foreground::Magenta,
           Foreground::Cyan, Foreground::White, Foreground::Gray,
           Foreground::BrightRed, Foreground::BrightGreen,
           Foreground::BrightYellow, Foreground::BrightBlue,
           Foreground::BrightMagenta, Foreground::BrightCyan,
           Foreground::BrightWhite>();

  std::println("Possible 4bit background colors are:");
  printAll<Background::Black, Background::Red, Background::Green,
           Background::Yellow, Background::Blue, Background::Magenta,
           Background::Cyan, Background::White, Background::Gray,
           Background::BrightRed, Background::BrightGreen,
           Background::BrightYellow, Background::BrightBlue,
           Background::BrightMagenta, Background::BrightCyan,
           Background::BrightWhite>();

  // You can color text like this
  std::println(
      "The next text will be colored {}Colored textcolor is:{} And this is "
      "not",
      rainbow::color<Foreground::Blue, Background::Red>(), rainbow::reset());
  return 0;
}
