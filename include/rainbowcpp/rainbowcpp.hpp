#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <print>
#include <string_view>
#include <type_traits>
#include <utility>

#include "colors.hpp"
#include "rainbowcpp/static_str.hpp"
#include "utility.hpp"

// TODO
// - Generating the colored strings at compile time - injecting the start and
// end
//

namespace rainbow {

  namespace internal {

    template <typename T>
    concept Color4Bit = std::same_as<T, colors::bit4::Foreground> ||
                        std::same_as<T, colors::bit4::Background>;

    template <Color4Bit auto Clr>
    constexpr auto colorFormat() {
      constexpr auto clrSv = internal::toString<std::to_underlying(Clr)>();
      return static_string<clrSv.size()>(clrSv);
    }

    constexpr auto colorFormat(Color color) -> std::string_view {
      // constexpr auto red = internal::toString<color.r>();
      //  constexpr auto green = internal::countDigits(color.g);
      //  constexpr auto blue = internal::countDigits(color.b);
      //  constexpr static auto str = static_string<fgStr.size()>(fgStr.data());
      //  return str.view();
      return "";
    }

  }  // namespace internal

  template <rainbow::colors::bit4::Foreground Fg,
            rainbow::colors::bit4::Background Bg =
                rainbow::colors::bit4::Background::Default>
  constexpr auto color() -> std::string_view {
    constexpr static_string fgStr = internal::colorFormat<Fg>();
    constexpr static_string bgStr = internal::colorFormat<Bg>();

    constexpr static static_string result = "\033[" + fgStr + ";" + bgStr + "m";

    return result.view();
  }

  // 24-bit colors
  template <Color Fg, Color Bg>
  constexpr auto color() -> std::string_view {
    constexpr auto fgRedDigits = internal::countDigits(Fg.r);
    constexpr auto fgGreenDigits = internal::countDigits(Fg.g);
    constexpr auto fgBlueDigits = internal::countDigits(Fg.b);

    constexpr auto bgRedDigits = internal::countDigits(Bg.r);
    constexpr auto bgGreenDigits = internal::countDigits(Bg.g);
    constexpr auto bgBlueDigits = internal::countDigits(Bg.b);

    constexpr auto fgDigits = fgRedDigits + fgGreenDigits + fgBlueDigits;
    constexpr auto bgDigits = bgRedDigits + bgGreenDigits + bgBlueDigits;

    constexpr auto baseSize = std::string_view("\033[38;2;;;m").size();
    constexpr auto totalSize = (baseSize * 2) + fgDigits + bgDigits;

    constexpr std::size_t redIndex = 7;

    constexpr std::array fgArr = []() {
      std::array<char, baseSize + fgDigits> arr{'\033', '[', '3', '8',
                                                ';',    '2', ';'};

      std::ranges::copy(internal::toString<Fg.r>(),
                        std::next(arr.begin(), redIndex));
      arr.at(redIndex + fgRedDigits) = ';';
      std::ranges::copy(internal::toString<Fg.g>(),
                        std::next(arr.begin(), redIndex + fgRedDigits + 1));
      arr.at(redIndex + fgRedDigits + fgGreenDigits + 1) = ';';
      std::ranges::copy(
          internal::toString<Fg.b>(),
          std::next(arr.begin(), redIndex + fgRedDigits + fgGreenDigits + 2));

      arr.at(baseSize + fgDigits - 1) = 'm';

      return arr;
    }();

    constexpr std::array bgArr = []() {
      std::array<char, baseSize + bgDigits> arr{'\033', '[', '4', '8',
                                                ';',    '2', ';'};

      std::ranges::copy(internal::toString<Bg.r>(),
                        std::next(arr.begin(), redIndex));
      arr.at(redIndex + bgRedDigits) = ';';
      std::ranges::copy(internal::toString<Bg.g>(),
                        std::next(arr.begin(), redIndex + bgRedDigits + 1));

      arr.at(redIndex + bgRedDigits + bgGreenDigits + 1) = ';';
      std::ranges::copy(
          internal::toString<Bg.b>(),
          std::next(arr.begin(), redIndex + bgRedDigits + bgGreenDigits + 2));

      arr.at(baseSize + bgDigits - 1) = 'm';

      return arr;
    }();

    constexpr static std::array out = [fgArr, bgArr]() {
      std::array<char, totalSize + 1> arr{};
      std::ranges::copy(fgArr, arr.begin());
      std::ranges::copy(bgArr, std::next(arr.begin(), fgArr.size()));

      arr.at(totalSize) = '\0';
      return arr;
    }();

    return std::string_view{out.begin(), out.end()};
  }

  constexpr auto reset() -> std::string_view { return "\033[39;49m"; }

}  // namespace rainbow
