#ifndef MLib_Constants
#define MLib_Constants 20241018L

namespace mlib {

constexpr class {
public:
  constexpr operator float() {
    return __builtin_huge_valf();
  }
  constexpr operator double() {
    return __builtin_huge_val();
  }
  constexpr operator long double() {
    return __builtin_huge_vall();
  }
} infinity_v;

constexpr class {
public:
  constexpr operator float() {
    return __builtin_nanf("0");
  }
  constexpr operator double() {
    return __builtin_nan("0");
  }
  constexpr operator long double() {
    return __builtin_nanl("0");
  }
} nan_v;

}

#endif