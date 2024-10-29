#ifndef MLib_Color
#define MLib_Color 20241025L

#include <array>
#include <cstdint>

namespace mlib::color {

class rgb {
public:
  union {
    ::std::array<::std::byte, 3> array;
    struct { ::std::byte r, g, b; };
  };

  constexpr rgb(::std::array<::std::byte, 3> array):
    array(array) {}
  constexpr rgb(::std::byte r, ::std::byte g, ::std::byte b):
    r(r), g(g), b(b) {}

  constexpr operator ::std::array<::std::byte, 3>() {
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
    ::std::array<::std::byte, 4> array;
    struct { ::std::byte r, g, b, a; };
  };

  constexpr rgba(::std::int32_t color_int):
    integer(color_int) {}
  constexpr rgba(::std::array<::std::byte, 4> array):
    array(array) {}
  constexpr rgba(::std::byte r, ::std::byte g, ::std::byte b, ::std::byte a):
    r(r), g(g), b(b), a(a) {}

  constexpr operator ::std::array<::std::byte, 4>() {
    return array;
  }
  constexpr operator ::std::int32_t() {
    return a << 24 | b << 16 | g << 8 | r;
  }
  
};

enum colors : ::uint32_t {
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