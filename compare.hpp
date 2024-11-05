#ifndef MLib_Compare
#define MLib_Compare 20241101L
#include <compare>
#include "concepts.hpp"

#include "short_macros.hpp"

ns mlib {

ce dt(a) synth3way(c a & __t, c a & __u) rq rq {
  { __t < __u } -> c_boolean_testable;
  { __u < __t } -> c_boolean_testable;
} {
  if ce (::std::three_way_comparable_with<dt(__t), dt(__u)>) rt __t <=> __u;
  else rt
  (__t < __u) ? ::std::weak_ordering::less :
  (__u < __t) ? ::std::weak_ordering::greater :
  ::std::weak_ordering::equivalent;
}

}

#include "undef_short_macros.hpp"

#endif