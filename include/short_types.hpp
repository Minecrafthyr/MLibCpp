
// Copyright © 2024 Minecraft_hyr - MIT License
// Core Header
#ifndef MLib_ShortTypes
#define MLib_ShortTypes 20241204
#include <cstdint>
#include "stdfloat"
#include <cstddef>

namespace mlib {
  using i8 = ::std::int8_t;
  using i16 = ::std::int16_t;
  using i32 = ::std::int32_t;
  using i64 = ::std::int64_t;
  using iptr = ::std::intptr_t;
  using imax = ::std::intmax_t;

  using u8 = ::std::uint8_t;
  using u16 = ::std::uint16_t;
  using u32 = ::std::uint32_t;
  using u64 = ::std::uint64_t;
  using uptr = ::std::uintptr_t;
  using umax = ::std::uintmax_t;

#ifdef __STDCPP_FLOAT16_T__
  using f16 = decltype(0.0f16);
#endif
#ifdef __STDCPP_FLOAT32_T__
  using f32 = decltype(0.0f32);
#endif
#ifdef __STDCPP_FLOAT64_T__
  using f64 = decltype(0.0f64);
#endif
#ifdef __STDCPP_FLOAT128_T__
  using f128 = decltype(0.0f128);
#endif
#ifdef __STDCPP_BFLOAT16_T__
  using bf16 = decltype(0.0bf16);
#endif
}

#endif