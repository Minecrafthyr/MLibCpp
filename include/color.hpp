// Copyright © 2024 Minecraft_hyr - MIT License
// Core Header
#ifndef MLib_Color
#define MLib_Color 20241112L

#include <array>
#include <cstdint>

namespace mlib::color {

class rgb {
public:
  union {
    ::std::array<::std::uint8_t, 3> array;
    struct { ::std::uint8_t r, g, b; };
  };

  constexpr rgb(::std::array<::std::uint8_t, 3> _array):
    array(_array) {}
  constexpr rgb(::std::uint8_t _r, ::std::uint8_t _g, ::std::uint8_t _b):
    r(_r), g(_g), b(_b) {}

  constexpr operator ::std::array<::std::uint8_t, 3>() {
    return array;
  }
  constexpr operator ::std::int32_t() {
    return b << 16 | g << 8 | r;
  }
  
};

class rgba {
public:
  union {
    ::std::int32_t integer{};
    ::std::array<::std::uint8_t, 4> array;
    struct { ::std::uint8_t r, g, b, a; };
  };

  constexpr rgba(::std::int32_t _int):
    integer(_int) {}
  constexpr rgba(::std::array<::std::uint8_t, 4> _array):
    array(_array) {}
  constexpr rgba(::std::uint8_t _r, ::std::uint8_t _g, ::std::uint8_t _b, ::std::uint8_t _a):
    r(_r), g(_g), b(_b), a(_a) {}

  constexpr operator ::std::array<::std::uint8_t, 4>() {
    return array;
  }
  constexpr operator ::std::int32_t() {
    return a << 24 | b << 16 | g << 8 | r;
  }
  
};

enum colors : ::std::uint32_t {
	black = 0,
	blue = 0xAA0000,
	green = 0x00AA00,
	cyan = 0xAAAA00,
	red = 0x0000AA,
	magenta = 0xAA00AA,
	brown = 0x0055AA,
	light_gray = 0xAAAAAA,
	dark_gray = 0x555555,
	light_blue = 0xFF5555,
	light_green = 0x55FF55,
	light_cyan = 0xFFFF55,
	light_red = 0x5555FF,
	light_magenta = 0xFF55FF,
	yellow = 0x55FFFF,
	white = 0xFFFFFF
};

}

#endif