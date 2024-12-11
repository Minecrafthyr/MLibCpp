// Copyright © 2024 Minecraft_hyr - MIT License
// Core Header
#ifndef MLibHeader_LimitHpp
#define MLibHeader_LimitHpp 20241210
#include "pair.hpp"

namespace mlib {
  template<typename T1>
  decltype(auto) limit(auto const& _v, T1 const& _min, T1 const& _max) {
    using _v_type = decltype(_v);
    if (_v < _min) return _v_type(_min);
    if (_v > _max) return _v_type(_max);
    return _v;
  }
  template<typename T1, typename T2>
  decltype(auto) limit(auto const& _v, forward_pair<T1, T2> const& _min_max) {
    using _v_type = decltype(_v);
    if (_v < _min_max.first) return _v_type(_min_max.first);
    if (_v > _min_max.second) return _v_type(_min_max.second);
    return _v;
  }

  decltype(auto) limit_min(auto const& _v, auto const& _min) {
    if (_v < _min) return decltype(_v)(_min);
    return _v;
  }
  decltype(auto) limit_max(auto const& _v, auto const& _max) {
    if (_v > _max) return decltype(_v)(_max);
    return _v;
  }

}

#endif