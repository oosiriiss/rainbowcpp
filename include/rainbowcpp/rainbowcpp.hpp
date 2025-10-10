#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <string_view>
#include <utility>

#include "colors.hpp"

// TODO
// - Generating the colored strings at compile time - injecting the start and
// end
//

namespace rainbow {
  namespace internal {

    template <std::integral T>
    constexpr auto countDigits(T value) -> std::uint8_t {
      std::uint8_t digits = 1;

      constexpr int radix = 10;
      while (value >= radix) {
        ++digits;
        value = value / radix;
      }

      return digits;
    }

    template <std::uint8_t Value>
    constexpr auto toString() -> std::string_view {
      constexpr static std::array arr = []() {
        constexpr auto digits = countDigits(Value);

        std::array<char, digits> str{};
        constexpr int radix = 10;
        auto value = Value;
        for (int i = digits - 1; i >= 0; --i) {
          auto digit = static_cast<std::uint8_t>((value + radix) % radix);
          value = value / radix;

          // i is always positive and digit is in range 0-9
          str.at(static_cast<std::size_t>(i)) = static_cast<char>('0' + digit);
        }
        return str;
      }();

      return std::string_view{arr.begin(), arr.end()};
    }
  }  // namespace internal

  template <rainbow::colors::bit4::Foreground Fg,
            rainbow::colors::bit4::Background Bg>
  constexpr auto color() -> std::string_view {
    constexpr static std::array arr = []() {
      constexpr auto fgColorCode = std::to_underlying(Fg);
      constexpr auto bgColorCode = std::to_underlying(Bg);

      constexpr auto fgStr = internal::toString<fgColorCode>();
      constexpr auto bgStr = internal::toString<bgColorCode>();

      static_assert(fgStr.size() == 2,
                    "Encountered invalid foreground color code");

      static_assert(bgStr.size() == 2 || bgStr.size() == 3,
                    "Encountered invalid background color code");

      std::array str = []() {
        if constexpr (internal::countDigits(bgColorCode) == 2) {
          return std::array{'\x1B', '[', 'X', 'X', ';', 'X', 'X', 'm', '\0'};
        } else {
          return std::array{'\x1B', '[', 'X', 'X', ';',
                            'X',    'X', 'X', 'm', '\0'};
        }
      }();

      constexpr auto fgStartIndex = 2;
      std::ranges::copy(fgStr.begin(), fgStr.end(),
                        std::next(str.begin(), fgStartIndex));

      constexpr auto bgStartIndex = 5;
      std::ranges::copy(bgStr.begin(), bgStr.end(),
                        std::next(str.begin(), bgStartIndex));

      return str;
    }();

    return std::string_view{arr.begin(), arr.end()};
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
