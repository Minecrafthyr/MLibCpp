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
concept Const = ::std::is_const_v<T>;
template <typename T>
concept Volatile = ::std::is_volatile_v<T>;
template <typename T>
concept LRef = ::std::is_lvalue_reference_v<T>;
template <typename T>
concept RRef = ::std::is_rvalue_reference_v<T>;
template <typename T>
concept Ptr = ::std::is_pointer_v<T>;
template <typename T>
concept BuiltinArray = ::std::is_array_v<T>;
template <typename T>
concept Ref = ::std::is_reference_v<T>;
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

using ::std::remove_const_t;
using ::std::remove_volatile_t;
template <typename T>
using remove_ref_t = remove_reference_t<T>;
using ::std::remove_cv_t;
using ::std::remove_cvref_t;

#pragma region Requires
template <typename T, typename ... T2>
concept Constructible = requires (T2 && ... _v) { T(_v...); };
template <typename T>
concept CopyConstructible = requires(const T & _v) { T(_v); };
template <typename T>
concept MoveConstructible = requires(T && _v) { T(_v); };

template <typename T, typename ... T2>
concept NothrowConstructible = requires (T2 && ... _v) { {T(_v...)}noexcept; };
template <typename T>
concept NothrowCopyConstructible = requires(const T & _v) { {T(_v)}noexcept; };
template <typename T>
concept NothrowMoveConstructible = requires(T && _v) { {T(_v)}noexcept; };

template <typename T>
concept ImplicitlyDefaultConstructible = requires(void(*_f)(T)) { _f({}); };

template <typename T, typename T2>
concept ConvertibleTo = requires(T _v) { static_cast<T2>(_v); };

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
conditional_t<LRef<RefT>, ToT &,
conditional_t<RRef<RefT>, remove_ref_t<ToT> &&, ToT>>;


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
  if constexpr (LRef<ToT> && Ptr<FromT>)
    return *(remove_ref_t<ToT> *)_value;
  else return (ToT)_value;
}

template <typename T>
concept BooleanTestable = ConvertibleTo<T, bool> &&
  requires(T && _v) { { !_v } -> ConvertibleTo<bool>; };

template <typename T, typename T2>
concept RemoveCVSameAs = SameAs<remove_cv_t<T>, T2>;
template <typename T, typename T2>
concept RemoveRefSameAs = SameAs<remove_ref_t<T>, T2>;
template <typename T, typename T2>
concept RemoveCVRefSameAs = SameAs<remove_cvref_t<T>, T2>;

template <typename T>
concept Void = RemoveCVSameAs<T, void>;

template <typename T>
concept ConstLRef = Const<T> && LRef<T>;
template <typename T>
concept ConstRRef = Const<T> && RRef<T>;
template <typename T>
concept ConstRef = Const<T> && Ref<T>;

template <typename T>
concept Destructible = requires(T & _v) { { _v.~T() } noexcept; } || Ref<T> || BuiltinArray<T>;

template <typename T>
concept Object = not (Function<T> || Ref<T> || Void<T>);

#define MLibForward(value) ((decltype(value) &&)(value))
#define MLibForwardLike(type, value) ((::mlib::typed<type> &&)(value))
/// @brief Transfer reference of `type` to object type of `value`.
#define MLibForwardTransfer(type, value) ((::mlib::transfer_ref_t<type, decltype(value)> &&)(value))

#pragma endregion


}


#endif