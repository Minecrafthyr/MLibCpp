// Copyright © 2024 Minecraft_hyr - MIT License
// Core Header
#ifndef MLib_Compare
#define MLib_Compare 20241112L
#include <compare>
#include "types.hpp"

namespace mlib {

template <typename T, typename T2>
concept c_3way_cmp_with = ::std::three_way_comparable_with<T, T2>;

constexpr decltype(auto) synth3way(const auto & _t, const auto & _u)
requires requires {
  { _t < _u } -> BooleanTestable;
  { _u < _t } -> BooleanTestable;
} {
  using _ord = ::std::weak_ordering;
  if constexpr (c_3way_cmp_with<decltype(_t), decltype(_u)>)
    return _t <=> _u;
  else return
  (_t < _u) ? _ord::less
  : (_u < _t) ? _ord::greater
  : _ord::equivalent;
}

}

#endif