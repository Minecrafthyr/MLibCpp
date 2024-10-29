#ifndef MLib_TypeUtils
#define MLib_TypeUtils 20241029L

#include "concepts.hpp"

namespace mlib {

template <typename T>
using remove_const = ::std::remove_const_t<T>;
template <typename T>
using remove_volatile = ::std::remove_volatile_t<T>;
template <typename T>
using remove_ref = ::std::remove_reference_t<T>;
template <typename T>
using remove_cv = ::std::remove_cv_t<T>;
template <typename T>
using remove_cvref = ::std::remove_cvref_t<T>;
template <typename T, typename T2>
concept c_same_as = ::std::same_as<T, T2>;
template <typename T, template<typename> typename Op, typename T2>
concept c_same_as_if = c_same_as<Op<T>, T2>;

}

#endif