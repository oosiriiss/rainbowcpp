#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <string>
#include <string_view>
#include <utility>

#include "colors.hpp"

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

    template <const char*... Strings>
    struct Concat {
      [[nodiscard]] static constexpr auto eval() {
        constexpr std::size_t len =
            (std::string_view(Strings).size() + ... + 0);
        std::array<char, len + 1> arr{};
        auto append = [idx = 0UL, &arr](auto const& str) mutable {
          for (auto chr : std::string_view(str)) {
            arr[idx++] = chr;
          }
        };
        (append(Strings), ...);
        // Null terminator technically redundant
        arr[len] = 0;
        return arr;
      }
      static constexpr auto buf = eval();
      static constexpr std::string_view value{buf.data(), buf.size() - 1};
    };
    template <const char*... Strings>
    static constexpr auto concatv = Concat<Strings...>::value;

  }  // namespace internal

  template <rainbow::colors::bit4::Foreground Fg,
            rainbow::colors::bit4::Background Bg>
  constexpr auto color() -> std::string_view {
    static std::string Out = internal::toString(std::to_underlying(Fg)) +
                             internal::toString(std::to_underlying(Bg));
    // static auto Out = internal::concatv<fgStr.c_str(), bgStr.c_str()>;
    return Out;
  }

}  // namespace rainbow
