// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLib_Optional
#define MLib_Optional 20241112L

#include <optional>
#include "types.hpp"

namespace mlib {

template <c_object T>
struct optional_base {
	using value_type = T;
	
	[[nodiscard]]
	constexpr bool has_value(this auto && self);
	[[nodiscard]]
	constexpr decltype(auto) get(this auto && self);

	[[nodiscard]]
	constexpr operator bool(this const auto && self) { return self.has_value(); }
	[[nodiscard]]
	constexpr decltype(auto) operator*(this auto && self) { return self.get(); }
	[[nodiscard]]
	constexpr decltype(auto) value_or(this auto && self, const value_type & __v = {}) {
		return has_value() ? self.get() : __v;
	}
};

template <c_object T>
struct optional : public optional_base<T> {
	using value_type = T;
	bool HasVal{};
	union {
		value_type Value;
		::std::array<::std::uint8_t, sizeof(value_type)> Unused;
	};

	constexpr optional(::std::nullopt_t)	: Unused{} {}
	constexpr optional() noexcept(c_nothrow_constructible<value_type>) : Value{} {}
	constexpr optional(auto && ... In) noexcept(noexcept(Value(MLibForward(In)...)))
		: Value(MLibForward(In)...), HasVal(true) {}
	
	[[nodiscard, gnu::always_inline]]
	constexpr bool has_value(this auto && self) { return self.HasVal; };
	[[nodiscard, gnu::always_inline]]
	constexpr decltype(auto) get(this auto && self) { return self.Value; };
};

template <c_object T, T Null = T{}>
struct as_optional : public optional_base<T> {
	using value_type = T;
	static constexpr value_type NullValue = Null;
	
	value_type Value;

	constexpr as_optional()
	noexcept(c_nothrow_constructible<value_type>) : Value{} {}
	constexpr as_optional(::std::nullopt_t) : Value() {}
	constexpr as_optional(auto && ... In)
	noexcept(noexcept(Value(MLibForward(In)...)))
	: Value(MLibForward(In)...) {}
	
	[[nodiscard]]
	constexpr bool has_value(this auto && self) { return self.Value != self.NullValue; };
	[[nodiscard, gnu::always_inline]]
	constexpr decltype(auto) get(this auto && self) { return self.Value; };
};

template <c_object T>
constexpr decltype(auto) operator<=>(const optional_base<T> & _left, const optional_base<T> & _right)
{ return (_left && _right) ? (*_left <=> *_right) : (_left <=> _right); }
template <c_object T>
constexpr decltype(auto) operator<=>(const optional_base<T> & _left, const T & _right)
{ return _left ? (*_left <=> _right) : std::partial_ordering::unordered; }
template <c_object T>
constexpr decltype(auto) operator<=>(const T & _left, const optional_base<T> & _right)
{ return _right ? (_left <=> *_right) : std::partial_ordering::unordered; }


}

#endif