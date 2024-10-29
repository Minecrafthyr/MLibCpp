#ifndef MLib_Utility
#define MLib_Utility 20241026L

#include <array>
#include <ranges>
#include <string_view>
#include "macros.hpp"

namespace mlib {
using namespace ::std::literals;


template <typename T>
using type = T;


inline constexpr void for_each_with_delimiter(::std::ranges::range auto r, auto fn, auto const& delimiter = ", "sv) {
  auto it = ::std::ranges::begin(r);
  auto end = ::std::ranges::cend(r);
  if (it == end) return;
  fn(*it); ++it;
  for (; it != end; fn(delimiter), fn(*it), ++it);
  
}

inline constexpr void out_with_delimiter(::std::ranges::range auto r, auto & out, auto const& delimiter = ", "sv) {
  for_each_with_delimiter(r, [](auto const& in){ out << in; }, delimiter);
}
template <typename T>
inline constexpr decltype(auto) none = T{};
template <typename T>
inline constexpr decltype(auto) null = [](){
  if constexpr (requires { static_cast<T>(::std::nullopt); })
    return static_cast<T>(::std::nullopt);
  else if constexpr (requires { static_cast<T>(nullptr); })
    return static_cast<T>(nullptr);
  else if constexpr (requires { static_cast<T>(0); })
    return static_cast<T>(0);
  else return std::bit_cast<T>(::std::array<unsigned char, sizeof(T)>{});
}();

}

#endif