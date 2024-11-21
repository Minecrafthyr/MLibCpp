// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLib_Builtin
#define MLib_Builtin 20241106L
#include <cstdint>
#include <string.h>
#include <ranges>
#include "types.hpp"
#include "ranges.hpp"


namespace builtin {


template <typename T>
using type = T;
template <typename T, ::std::size_t N>
using array = T[N];

template <typename OT, typename ... ITs>
using function = OT(*)(ITs...);

#if __is_identifier(_builtin_memcmp)
template <typename T>
[[nodiscard, gnu::always_inline]]
constexpr auto memcmp(const T * _a, const T * _b, ::std::size_t _sz) { 
	return ::__builtin_memcmp(_a, _b, _sz * sizeof(T));
}
#else
/// @brief memory copy. copy `_b` into `_a`.
[[nodiscard, gnu::always_inline]]
constexpr int memcmp(const ::std::uint8_t * _a, const ::std::uint8_t * _b, ::std::size_t _sz) { 
	if consteval {
		for (::std::size_t _i{}; _i != _sz; ++_i) {
			if (_a[_i] < _b[_i]) return -1;
			if (_a[_i] > _b[_i]) return 1;
		}
		return 0;
	}
	else { return ::memcmp(_a, _b, _sz * sizeof(T)); }
}
template <typename T>
[[nodiscard, gnu::always_inline]]
constexpr auto memcmp(const T * _a, const T * _b, ::std::size_t _sz) { 
	return ::__builtin_memcmp((const ::std::uint8_t *)_a, (const ::std::uint8_t *)_b, _sz * sizeof(T));
}
#endif

#if __is_identifier(__builtin_memcpy)
template <typename T>
	requires (!::mlib::Const<T>)
/// @brief memory copy. copy `_b` into `_a`.
[[gnu::always_inline]]
constexpr void memcpy(T * _a, const T * _b, ::std::size_t _sz) {
	::__builtin_memcpy(_a, _b, _sz * sizeof(Type));
}
#else
/// @brief memory copy. copy `_b` into `_a`.
[[gnu::always_inline]]
constexpr void memcpy(::std::uint8_t * _a, const ::std::uint8_t * _b, ::std::size_t _sz) {
	if consteval {
		for (::std::size_t _i{}; _i != _sz; ++_i)
			_a[_i] = _b[_i];
	}
	else { ::memcpy(_a, _b, _sz); }
}
template <typename T>
	requires (!::mlib::Const<T>)
/// @brief memory copy. copy `_b` into `_a`.
[[gnu::always_inline]]
constexpr void memcpy(T * _a, const T * _b, ::std::size_t _sz) {
	::memcpy((::std::uint8_t *)_a, (const ::std::uint8_t *)_b, _sz * sizeof(Type));
}
#endif
template <typename T> requires requires {
	::mlib::data(MLibDeclVal(const T &));
	::mlib::size(MLibDeclVal(const T &)); }
/// @brief memory copy. copy `_b` into `_a`.
[[gnu::always_inline]]
constexpr void memcpy(T & _a, const T & _b) { 
	::memcpy(::mlib::data(_a), ::mlib::data(_b), ::mlib::size(_b));
}

#if __is_identifier(_builtin_strlen)
[[nodiscard, gnu::always_inline]]
constexpr auto strlen(const char * _s) { return ::__builtin_strlen(_s); }
#else
[[nodiscard, gnu::always_inline]]
constexpr auto strlen(const char * _s) {
	if consteval {
		auto _begin = _s;
		for (; _s != '\0'; ++_s);
		return _s - _begin;
	}
	else { return ::strlen(_s); }
}
#endif

[[nodiscard, gnu::always_inline]]
constexpr auto powf(float _base, float _power) { return ::__builtin_powf(_base, _power); }
[[nodiscard, gnu::always_inline]]
constexpr auto pow(double _base, double _power) { return ::__builtin_pow(_base, _power); }
[[nodiscard, gnu::always_inline]]
constexpr auto powl(long double _base, long double _power) { return ::__builtin_powl(_base, _power); }

[[nodiscard, gnu::always_inline]]
constexpr auto huge_valf() { return ::__builtin_huge_valf(); }
[[nodiscard, gnu::always_inline]]
constexpr auto huge_val() { return ::__builtin_huge_val(); }
[[nodiscard, gnu::always_inline]]
constexpr auto huge_vall() { return ::__builtin_huge_vall(); }

[[nodiscard, gnu::always_inline]]
constexpr auto nanf(const char * _ch) { return ::__builtin_nanf(_ch); }
[[nodiscard, gnu::always_inline]]
constexpr auto nan(const char * _ch) { return ::__builtin_nan(_ch); }
[[nodiscard, gnu::always_inline]]
constexpr auto nanl(const char * _ch) { return ::__builtin_nanl(_ch); }

}

namespace mlib {

namespace math {

[[nodiscard, gnu::always_inline]]
constexpr float pow(float _base, float _power) { return ::builtin::powf(_base, _power); }
[[nodiscard, gnu::always_inline]]
constexpr double pow(double _base, double _power) { return ::builtin::pow(_base, _power); }
[[nodiscard, gnu::always_inline]]
constexpr long double pow(long double _base, long double _power) { return ::builtin::powl(_base, _power); }

constexpr struct {
  constexpr operator float() const { return ::builtin::huge_valf(); }
  constexpr operator double() const { return ::builtin::huge_val(); }
  constexpr operator long double() const { return ::builtin::huge_vall(); }
} infinity_v;
constexpr struct {
  constexpr operator float() const { return ::builtin::nanf("0"); }
  constexpr operator double() const { return ::builtin::nan("0"); }
  constexpr operator long double() const { return ::builtin::nanl("0"); }
} nan_v;

}

}


#endif