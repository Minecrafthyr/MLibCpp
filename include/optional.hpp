// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLib_Optional
#define MLib_Optional 20241112L

#include <optional>
#include "types.hpp"

namespace mlib {

template <Object T>
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
	constexpr decltype(auto) value_or(this auto && self, value_type const& _v = {}) {
		return self.has_value() ? self.get() : _v;
	}
};

template <Object T>
struct optional : public optional_base<T> {
	using value_type = T;
	bool HasVal{};
	union {
		value_type Value;
		::std::array<::std::uint8_t, sizeof(value_type)> Unused;
	};

	constexpr optional(::std::nullopt_t) : Unused{} {}
	constexpr optional()
	noexcept(NothrowConstructible<value_type>) : Value{} {}
	constexpr optional(auto && ... _input)
	noexcept(noexcept(Value(Forward(_input)...)))
		: Value(Forward(_input)...), HasVal(true) {}
	
	[[nodiscard, gnu::always_inline]]
	constexpr bool has_value(this auto && self) { return self.HasVal; };
	[[nodiscard, gnu::always_inline]]
	constexpr decltype(auto) get(this auto && self) { return self.Value; };
};

template <Object T, T Null = T{}>
struct as_optional : public optional_base<T> {
	using value_type = T;
	static constexpr value_type NullValue = Null;
	
	value_type Value;

	constexpr as_optional()
	noexcept(NothrowConstructible<value_type>) : Value{} {}
	constexpr as_optional(::std::nullopt_t) : Value() {}
	constexpr as_optional(auto && ... _input)
	noexcept(noexcept(Value(Forward(_input)...)))
	: Value(Forward(_input)...) {}
	
	[[nodiscard]]
	constexpr bool has_value(this auto && self) { return self.Value != self.NullValue; };
	[[nodiscard, gnu::always_inline]]
	constexpr decltype(auto) get(this auto && self) { return self.Value; };
};

template <Object T>
struct zero_optional : public optional_base<T> {
	using value_type = T;
	static constexpr ::std::size_t Size = sizeof(value_type);
	using array_type = ::std::uint8_t[Size];
	static constexpr array_type NullValue{};

	union {
		value_type Value;
		array_type Unused;
	};

	constexpr zero_optional(::std::nullopt_t) : Unused() {}
	constexpr zero_optional() : Value() {}
	constexpr zero_optional(auto && ... _input)
	: Value(::std::forward<decltype(_input)>(_input)...) {}
	
	[[nodiscard]] __forceinline
	constexpr auto has_value(this auto const&& self) {
		return memory_compare_range(self.Unused, self.NullValue);
	};
	[[nodiscard]] __forceinline
	constexpr decltype(auto) get_value(this auto && self) {
		if (not self.has_value())
			throw "NewStd::Optional::get_value(self) throw because value is nullopt.";
		return self.Value;
	};
};

template <Object T>
constexpr decltype(auto) operator<=>
(const optional_base<T> & _left, const optional_base<T> & _right) {
	return (_left && _right) ? (*_left <=> *_right) : (_left <=> _right);
}
template <Object T>
constexpr decltype(auto) operator<=>
(const optional_base<T> & _left, const T & _right) {
	return _left ? (*_left <=> _right) : std::partial_ordering::unordered;
}
template <Object T>
constexpr decltype(auto) operator<=>
(const T & _left, const optional_base<T> & _right) {
	return _right ? (_left <=> *_right) : std::partial_ordering::unordered;
}


}

#endif