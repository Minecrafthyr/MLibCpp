// Copyright © 2024 Minecraft_hyr - MIT License
// Core Header
#ifndef MLib_TypeUtils
#define MLib_TypeUtils 20241107L

#include <cstdint>
#include <array>
#include <concepts>

#include "macros/normal.hpp"

namespace mlib {

#pragma region No Requirements

template <typename T>
MLibDuplicate static_size = ::std::tuple_size_v<T>;

template <typename T>
concept c_const = ::std::is_const_v<T>;
template <typename T>
concept c_volatile = ::std::is_volatile_v<T>;
template <typename T>
concept c_lref = ::std::is_lvalue_reference_v<T>;
template <typename T>
concept c_rref = ::std::is_rvalue_reference_v<T>;
template <typename T>
concept c_ptr = ::std::is_pointer_v<T>;
template <typename T>
concept c_builtin_array = ::std::is_array_v<T>;
template <typename T>
concept c_ref = ::std::is_reference_v<T>;
template <typename T>
concept c_function = ::std::is_function_v<T>;
template <typename T>
concept c_int = ::std::integral<T>;
template <typename T>
concept c_signed = ~T{} < T{};
template <typename T>
concept c_unsigned = ~T{} > T{};
template <typename T>
concept c_signed_int = c_int<T> && c_signed<T>;
template <typename T>
concept c_unsigned_int = c_int<T> && c_unsigned<T>;
template <typename T>
concept c_float = ::std::floating_point<T>;
template <typename T, typename T2>
concept c_same_as = ::std::same_as<T, T2>;

using ::std::remove_const_t;
using ::std::remove_volatile_t;
template <typename T>
using remove_ref_t = remove_reference_t<T>;
using ::std::remove_cv_t;
using ::std::remove_cvref_t;

#pragma region Requires
template <typename T, typename ... T2>
concept c_constructible = requires (T2 && ... _v) { T(_v...); };
template <typename T>
concept c_default_constructible = requires { T(); };
template <typename T>
concept c_copy_constructible = requires(const T & _v) { T(_v); };
template <typename T>
concept c_move_constructible = requires(T && _v) { T(_v); };

template <typename T, typename ... T2>
concept c_nothrow_constructible = requires (T2 && ... _v) { {T(_v...)}noexcept; };
template <typename T>
concept c_nothrow_default_constructible = requires { {T()}noexcept; };
template <typename T>
concept c_nothrow_copy_constructible = requires(const T & _v) { {T(_v)}noexcept; };
template <typename T>
concept c_nothrow_move_constructible = requires(T && _v) { {T(_v)}noexcept; };

template <typename T>
concept c_implicitly_default_constructible = requires(void(*_f)(T)) { _f({}); };

template <typename T, typename T2>
concept c_to = requires(T _v) { static_cast<T2>(_v); };
template <typename T, typename T2>
concept c_convertible_to = requires(T _v) { static_cast<T2>(_v); };

template <typename T, typename T2>
concept c_swappable_with = requires(T _v, T2 _v2) { swap(_v, _v2); swap(_v2, _v); };
template <typename T, typename T2>
concept c_nothrow_swappable_with = requires(T _v, T2 _v2) { {swap(_v, _v2)}noexcept; {swap(_v2, _v)}noexcept; };
template <typename T>
concept c_swappable = c_swappable_with<T, T>;
template <typename T>
concept c_nothrow_swappable = c_nothrow_swappable_with<T, T>;

template <typename T>
concept c_iterator = requires(T _v) { *_v; } && (requires(T _v) { ++_v; } || requires(T _v) { --_v; });
template <typename T>
concept c_forward_iterator = requires(T _v) { *_v; ++_v; };
template <typename T>
concept c_backward_iterator = requires(T _v) { *_v; --_v; };
template <typename T>
concept c_bidirectional_iterator = requires(T _v) { *_v; ++_v; --_v; };
template <typename T>
concept c_random_access_iterator = c_bidirectional_iterator<T>
&& requires(T _v) { _v[0]; _v += 0; };

#pragma endregion

namespace _ {
template <typename FromT, typename ToT> requires(c_lref<FromT>)
struct transfer_ref_t { using type = ToT &; };
template <typename FromT, typename ToT> requires(c_rref<FromT>)
struct transfer_ref_t { using type = remove_ref_t<ToT> &&; };
}

template <typename FromT, typename ToT>
using transfer_ref_t = _::transfer_ref_t<FromT, ToT>::type;

template <typename FromT, typename ToT>
[[nodiscard]]
MLibDuplicate transfer_ref(ToT && value) {
  return transfer_ref_t<FromT, ToT>(value);
}

namespace _ {

template <typename T, template <typename ...> typename Tp>
constexpr bool is_specialization_v = false;
template <template <typename ...> typename Tp, typename ... Ts>
constexpr bool is_specialization_v<Tp<Ts...>, Tp> = true;

}
template <typename T, template <typename ...> typename Tp>
concept c_specialization = _::is_specialization_v<T, Tp>;

#pragma endregion

#pragma region Requirements1

template <typename ToT, typename FromT>
constexpr decltype(auto) smart_cast(FromT && _value) {
  if constexpr (c_lref<ToT> && c_ptr<FromT>)
    return *(remove_ref_t<ToT> *)_value;
  else return (ToT)_value;
}

template <typename T>
concept c_boolean_testable = c_to<T, bool> &&
  requires(T && _v) { { !_v } -> c_to<bool>; };

template <typename T, template<typename> typename Op, typename T2>
concept c_same_as_if = c_same_as<Op<T>, T2>;
template <typename T, typename T2>
concept c_remove_cv_same_as = c_same_as<remove_cv_t<T>, T2>;
template <typename T, typename T2>
concept c_remove_ref_same_as = c_same_as<remove_ref_t<T>, T2>;
template <typename T, typename T2>
concept c_remove_cvref_same_as = c_same_as<remove_cvref_t<T>, T2>;

template <typename T>
concept c_void = c_remove_cv_same_as<T, void>;


template <typename T>
concept c_const_lref = c_const<T> && c_lref<T>;
template <typename T>
concept c_const_rref = c_const<T> && c_rref<T>;
template <typename T>
concept c_const_ref = c_const<T> && c_ref<T>;


template <typename T>
concept c_destructible = requires(T & _v) { { _v.~T() } noexcept; } || c_ref<T> || c_builtin_array<T>;

template <typename T>
concept c_object = not (c_function<T> || c_ref<T> || c_void<T>);

#pragma endregion


}


#endif