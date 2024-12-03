// Copyright © 2024 Minecraft_hyr - MIT License
// Core Header
#ifndef MLib_TypeUtils
#define MLib_TypeUtils 20241121L

#include <cstdint>
#include <array>
#include <concepts>

#include "macros/normal.hpp"

namespace mlib {

#pragma region No Requirements

template <typename T>
using typed = T;
template <typename T>
inline constexpr decltype(auto) static_size = ::std::tuple_size_v<T>;

template <typename T>
concept Const = ::std::is_const_v<T>;
template <typename T>
concept Volatile = ::std::is_volatile_v<T>;
template <typename T>
concept LValueReference = ::std::is_lvalue_reference_v<T>;
template <typename T>
concept RValueReference = ::std::is_rvalue_reference_v<T>;
template <typename T>
concept Pointer = ::std::is_pointer_v<T>;
template <typename T>
concept BuiltinArray = ::std::is_array_v<T>;
template <typename T>
concept Reference = ::std::is_reference_v<T>;
template <typename T>
concept Function = ::std::is_function_v<T>;
template <typename T>
concept Integral = ::std::integral<T>;
template <typename T>
concept Signed = ~T{} < T{};
template <typename T>
concept Unsigned = ~T{} > T{};
template <typename T>
concept SignedInt = Integral<T> && Signed<T>;
template <typename T>
concept UnsignedInt = Integral<T> && Unsigned<T>;
template <typename T>
concept FloatingPoint = ::std::floating_point<T>;
template <typename T, typename ... T2>
concept SameAs = (::std::same_as<T, T2> || ...);
template <typename T, template <typename> typename ApplyT, typename ... T2>
concept SameAsApply = (::std::same_as<ApplyT<T>, T2> || ...);

#pragma region Requires
template <typename T, typename ... T2>
concept Constructible = requires (T2 && ... _v) { T(_v...); };
template <typename T>
concept CopyConstructible = requires(T const& _v) { T(_v); };
template <typename T>
concept MoveConstructible = requires(T && _v) { T(_v); };

template <typename T, typename ... T2>
concept NothrowConstructible = requires (T2 && ... _v) { {T(_v...)}noexcept; };
template <typename T>
concept NothrowCopyConstructible = requires(T const& _v) { {T(_v)}noexcept; };
template <typename T>
concept NothrowMoveConstructible = requires(T && _v) { {T(_v)}noexcept; };

template <typename T>
concept ImplicitlyConstructible = requires(void(*_f)(T)) { _f({}); };

template <typename T, typename T2 = T>
concept Swappable = ::std::swappable_with<T, T2>;

template <typename T>
concept Iterator = requires(T _v) { *_v; } && (requires(T _v) { ++_v; } || requires(T _v) { --_v; });
template <typename T>
concept ForwardIterator = requires(T _v) { *_v; ++_v; };
template <typename T>
concept BackwardIterator = requires(T _v) { *_v; --_v; };
template <typename T>
concept BidirectionalIterator = requires(T _v) { *_v; ++_v; --_v; };
template <typename T>
concept RandomAccessIterator = BidirectionalIterator<T>
&& requires(T _v) { _v[0]; _v += 0; };

#pragma endregion

using ::std::conditional_t;


template <typename RefT, typename ToT>
using transfer_ref_t = 
conditional_t<LValueReference<RefT>, ToT &,
conditional_t<RValueReference<RefT>, ::std::remove_reference_t<ToT> &&, ToT>>;


namespace _ {

template <typename T, template <typename ...> typename Tp>
constexpr bool is_specialization_v = false;
template <template <typename ...> typename Tp, typename ... Ts>
constexpr bool is_specialization_v<Tp<Ts...>, Tp> = true;

}
template <typename T, template <typename ...> typename Tp>
concept Specialization = _::is_specialization_v<T, Tp>;

#pragma endregion

#pragma region Requirements1

template <typename ToT, typename FromT>
constexpr decltype(auto) smart_cast(FromT && _value) {
  if constexpr (LValueReference<ToT> && Pointer<FromT>)
    return *(::std::remove_reference_t<ToT> *)_value;
  else return (ToT)_value;
}

template <typename T>
concept BooleanTestable = ::std::convertible_to<T, bool> &&
  requires(T && _v) { { !_v } -> ::std::convertible_to<bool>; };

template <typename T, typename T2>
concept SameAsRemoveCV = SameAs<::std::remove_cv_t<T>, T2>;
template <typename T, typename T2>
concept SameAsRemoveRef = SameAs<::std::remove_reference_t<T>, T2>;
template <typename T, typename T2>
concept SameAsRemoveCVRef = SameAs<::std::remove_cvref_t<T>, T2>;

template <typename T>
concept Void = SameAsRemoveCV<T, void>;

template <typename T>
concept ConstLValueReference = Const<T> && LValueReference<T>;
template <typename T>
concept ConstRValueReference = Const<T> && RValueReference<T>;
template <typename T>
concept ConstReference = Const<T> && Reference<T>;

template <typename T>
concept Destructible = requires(T & _v) { { _v.~T() } noexcept; } || Reference<T> || BuiltinArray<T>;

template <typename T>
concept Object = not (Function<T> || Reference<T> || Void<T>);

#define Forward(...) (decltype(__VA_ARGS__) &&)(__VA_ARGS__)
#define ForwardLike(...) (::mlib::typed<__VA_ARGS__> &&)
/// @brief Transfer reference of `type` to object type of `value`.
#define MLibForwardTransfer(type, value) ((::mlib::transfer_ref_t<type, decltype(value)> &&)(value))

#pragma endregion


}


#endif