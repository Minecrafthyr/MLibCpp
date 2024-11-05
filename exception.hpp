#include <stdexcept>
#include <system_error>

#include "short_macros.hpp"

namespace mlib {

struct error_code : public ::std::error_code {
  constexpr error_code(auto Input) :
    ::std::error_code(::std::make_error_code(Input)) {}
  constexpr error_code(auto && ... Input) :
    ::std::error_code(fw(Input)...) {}
}

struct system_error : public ::std::system_error {
  constexpr system_error(error_code ErrorCode) :
    ::std::system_error(ErrorCode) {}
  constexpr system_error(auto && ... Input) :
    ::std::system_error(fw(Input)...) {}
}




}


#include "undef_short_macros.hpp"

#endif