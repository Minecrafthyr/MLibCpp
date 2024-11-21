// Copyright © 2024 Minecraft_hyr - MIT License
// Core Header
#ifndef MLib_Data 20241112L
#define MLib_Data
#include <stdexcept>
#include <system_error>

namespace mlib {

struct error_code : public ::std::error_code {
  constexpr error_code(auto Input)
  : ::std::error_code(::std::make_error_code(Input)) {}
  constexpr error_code(auto && ... Input)
  : ::std::error_code(MLibForward(Input)...) {}
};

struct system_error : public ::std::system_error {
  constexpr system_error(error_code ErrorCode)
  : ::std::system_error(ErrorCode) {}
  constexpr system_error(auto && ... Input)
  : ::std::system_error(MLibForward(Input)...) {}
};


}


#endif