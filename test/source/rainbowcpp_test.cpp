#include "rainbowcpp/rainbowcpp.hpp"

auto main() -> int
{
  auto const result = name();

  return result == "rainbowcpp" ? 0 : 1;
}
