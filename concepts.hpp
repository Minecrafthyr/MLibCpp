#ifndef MLib_Concepts
#define MLib_Concepts 20241028L

#include <concepts>

namespace mlib {

template <typename T>
concept c_const = ::std::is_const_v<T>;
template <typename T>
concept c_volatile = ::std::is_volatile_v<T>;
template <typename T>
concept c_lref = ::std::is_lvalue_reference_v<T>;
template <typename T>
concept c_rref = ::std::is_rvalue_reference_v<T>;

template <typename T>
concept c_ref = ::std::is_reference_v<T>;
template <typename T>
concept c_object = ::std::is_object_v<T>;
template <typename T>
concept c_const_lref = c_const<T> && c_lref<T>;
template <typename T>
concept c_const_rref = c_const<T> && c_rref<T>;
template <typename T>
concept c_const_ref = c_const<T> && c_ref<T>;

}

#endif