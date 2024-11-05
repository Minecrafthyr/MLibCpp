#ifndef MLib_Concepts
#define MLib_Concepts 20241103L

#include <array>
#include <concepts>

#include "short_macros.hpp"

ns mlib {

tp <tn T>
cc c_const = ::std::is_const_v<T>;
tp <tn T>
cc c_volatile = ::std::is_volatile_v<T>;
tp <tn T>
cc c_lref = ::std::is_lvalue_reference_v<T>;
tp <tn T>
cc c_rref = ::std::is_rvalue_reference_v<T>;
tp <tn T>
cc c_ptr = ::std::is_pointer_v<T>;

tp <tn T>
cc c_ref = ::std::is_reference_v<T>;
tp <tn T>
cc c_object = ::std::is_object_v<T>;
tp <tn T, tn T2>
cc c_swappable_with = ::std::is_swappable_with_v<T, T2>;
tp <tn T, tn T2>
cc c_nothrow_swappable_with = ::std::is_nothrow_swappable_with_v<T, T2>;
tp <tn T>
cc c_swappable = ::std::is_swappable_v<T>;
tp <tn T>
cc c_nothrow_swappable = ::std::is_nothrow_swappable_v<T>;
tp <tn T>
cc c_const_lref = c_const<T> && c_lref<T>;
tp <tn T>
cc c_const_rref = c_const<T> && c_rref<T>;
tp <tn T>
cc c_const_ref = c_const<T> && c_ref<T>;

tp <tn T, tn T2>
cc c_able_from = ::std::constructible_from<T, T2>;
tp <tn T, tn T2>
cc c_able_to = ::std::convertible_to<T, T2>;

ns _ {

tp <tn T, tp <tn ...> tn Tp>
ce bl is_specialization_v = f;
tp <tp <tn ...> tn Tp, tn ... Ts>
ce bl is_specialization_v<Tp<Ts...>, Tp> = t;

}
tp <tn T, tp <tn ...> tn Tp>
cc c_spec = _::is_specialization_v<T, Tp>;

tp <tn T>
cc c_boolean_testable = c_able_to<T, bool> &&
  rq { { !dv(T &&) } -> c_able_to<T, bool>; };


tp <tn T>
cc c_int = ::std::integral<T>;
tp <tn T>
cc c_signed = ::std::is_signed_v<T>;
tp <tn T>
cc c_unsigned = ::std::is_unsigned_v<T>;
tp <tn T>
cc c_sint = c_int<T> && c_signed<T>;
tp <tn T>
cc c_uint = c_int<T> && c_unsigned<T>;
tp <tn T>
cc c_flt = ::std::floating_point<T>;



}




#include "undef_short_macros.hpp"


#endif