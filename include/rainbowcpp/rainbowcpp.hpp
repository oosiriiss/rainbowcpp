#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <string>
#include <string_view>
#include <utility>

#include "colors.hpp"

// TODO
//
// - Generating the colored strings at compile time - injecting the start and
// end
//
//
//
//
//
//
//

namespace rainbow {
  namespace internal {

    template <std::integral T>
    constexpr auto toString(T value) -> std::string {
      std::string out;

      constexpr int base = 10;

      while (value > 0) {
        out.push_back((value % base) + '0');
        value = value / base;
      }
      std::ranges::reverse(out);
      return out;
    }
  }  // namespace internal

  template <rainbow::colors::bit4::Foreground Fg,
            rainbow::colors::bit4::Background Bg>
  constexpr auto color() -> std::string_view {
    static std::string Out = "\033[" +
                             internal::toString(std::to_underlying(Fg)) + ";" +
                             internal::toString(std::to_underlying(Bg)) + "m";
    return Out;
  }

  // 24-bit colors
  template <Color Fg, Color Bg>
  constexpr auto color() -> std::string_view {
    static std::string Out =
        "\033[38;2;" + internal::toString(Fg.r) + ";" +
        internal::toString(Fg.g) + ";" + internal::toString(Fg.b) + "m" +
        "\033[38;2;" + internal::toString(Bg.r) + ";" +
        internal::toString(Bg.g) + ";" + internal::toString(Bg.b) + "m";

    return Out;
  }

  constexpr auto reset() -> std::string_view { return "\033[39;49m"; }

}  // namespace rainbow
