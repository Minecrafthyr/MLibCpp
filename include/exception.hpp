// Copyright © 2024 Minecraft_hyr - MIT License
// Core Header
#ifndef MLibHeader_DataHpp
#define MLibHeader_DataHpp 20241201
#include <stdexcept>
#include <system_error>

namespace mlib {

struct error_code : public ::std::error_code {
  error_code(auto _input)
  : ::std::error_code(::std::make_error_code(_input)) {}
  error_code(auto && ... _input)
  : ::std::error_code(::std::forward<decltype(_input)>(_input)...) {}
};

struct system_error : public ::std::system_error {
  system_error(error_code _errc)
  : ::std::system_error(_errc) {}
  system_error(auto && ... _input)
  : ::std::system_error(::std::forward<decltype(_input)>(_input)...) {}
};


}


#endif