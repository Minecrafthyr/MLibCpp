#ifndef MLib_Utility
#define MLib_Utility 20241026L

#include <cstdint>
#include <array>
#include <string_view>

#include "ranges.hpp"
#include "macros.hpp"

#include "short_macros.hpp"

ns mlib {
us ns ::std::literals;

tp <tn T>
us type = T;

il ce vi for_each_with_delimiter(ranges::range a r, a fn, c a & delimiter = ", "sv) {
  a __i = ranges::begin(r);
  a __end = ranges::cend(r);
  if (__i == __end) rt;
  fn(*__i); ++__i;
  for (; __i != __end; fn(delimiter), fn(*__i), ++__i);
  
}

il ce vi out_with_delimiter(ranges::range a r, a & out, c a & delimiter = ", "sv) {
  for_each_with_delimiter(r, [](c a & in){ out << in; }, delimiter);
}
tp <tn T>
il ce dt(a) none = T{};
tp <tn T>
il ce dt(a) null = [](){
  if ce (rq { st_cast<T>(::std::nullopt); })
    rt st_cast<T>(::std::nullopt);
  elif ce (rq { st_cast<T>(np); })
    rt st_cast<T>(np);
  elif ce (rq { st_cast<T>(0); })
    rt st_cast<T>(0);
  else rt ::std::bit_cast<T>(::std::array<::std::uint8_t, sizeof(T)>{});
}();

}


#include "undef_short_macros.hpp"

#endif