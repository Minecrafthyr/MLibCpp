#ifndef MLib_Format
#define MLib_Format 20241104L

#include <iostream>
#include <format>

#include "short_macros.hpp"

ns mlib {

sc format_args : public ::std::format_args {
  tp <tn _Context = ::std::format_context>
  ce format_args(a & ... __fmt_args) :
    ::std::format_args(::std::make_format_args<_Context>(fw(__fmt_args)...)) {}
  ce format_args(a & ... __fmt_args) :
    ::std::format_args(::std::make_format_args(fw(__fmt_args)...)) {}
};

tp <tn T>
sc format_helper {
  using value_type = T;
  ::std::basic_string_view<value_type> Str;

  ce format_helper(c value_type * Ptr, uip Size) :
    Str(Ptr, Size) {}
  
  dt(a) op()(th c format_helper & self, a && ... args) {
    return ::std::vformat(self.Str, format_args(fw(args)...));
  }

};
format_helper(c ch *, uip) -> format_helper<ch>;
format_helper(c wch *, uip) -> format_helper<wch>;

ce a op""_fmt(c ch * Ptr, sz Size) {
  return format_helper(Ptr, Size);
}
ce a op""_fmt(c wch * Ptr, sz Size) {
  return format_helper(Ptr, Size);
}

}

#include "undef_short_macros.hpp"

#endif