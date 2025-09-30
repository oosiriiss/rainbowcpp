#include <print>
#include "rainbowcpp/colors.hpp"
#include "rainbowcpp/rainbowcpp.hpp"

auto main() -> int {
  using rainbow::colors::bit4::Background;
  using rainbow::colors::bit4::Foreground;


  std::print("color is: {}",
             rainbow::color<Foreground::Blue, Background::Black>());

  return 0;
}
