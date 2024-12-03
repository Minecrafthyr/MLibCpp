// Copyright © 2024 Minecraft_hyr - MIT License
// Core Header
#ifndef MLib_Format
#define MLib_Format 20241112L
#include <cstdint>
#include <iostream>
#include <format>

#include "macros/normal.hpp"

namespace mlib {

struct format_args : public std::format_args {
  template <typename Context = ::std::format_context>
  constexpr format_args(auto & ... _format_args)
  : ::std::format_args(::std::make_format_args<Context>(Forward(_format_args)...)) {}
  constexpr format_args(auto & ... _format_args)
  : ::std::format_args(::std::make_format_args(Forward(_format_args)...)) {}
};

template <typename T>
struct format_string_holder {
  using value_type = T;
  ::std::basic_string_view<value_type> Str;

  constexpr format_string_holder(value_type const * _ptr, ::std::size_t _size)
  : Str(_ptr, _size) {}
  
  decltype(auto) operator()(this format_string_holder const & self, auto && ... _args) {
    return ::std::vformat(self.Str, format_args(Forward(_args)...));
  }

};
format_string_holder(char const *, ::std::size_t) -> format_string_holder<char>;
format_string_holder(wchar_t const *, ::std::size_t) -> format_string_holder<wchar_t>;

inline namespace literals {

constexpr auto operator""_format(char const * _ptr, ::std::size_t _size) {
  return format_string_holder(_ptr, _size);
}
constexpr auto operator""_format(wchar_t const * _ptr, ::std::size_t _size) {
  return format_string_holder(_ptr, _size);
}

}

}


#endif