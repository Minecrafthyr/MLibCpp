// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLibHeader_NoFlowHpp
#define MLibHeader_NoFlowHpp 20241112L
#include <concepts>
#include <limits>
#include <utility>
#include <cmath>

#include "types.hpp"

namespace mlib {

template <SignedInt T>
[[nodiscard, gnu::always_inline]]
constexpr int bin_sign(T _v) {
	return _v < T{} ? -1 : 0;
}
template <SignedInt T>
[[nodiscard, gnu::always_inline]]
constexpr int num_sign(T _v) {
	return (T{} < _v) - (_v < T{});
}


enum flow_state : int8_t {
	underflow = -1,
	no_flow = 0,
	overflow = 1
};

template <UnsignedInt T>
constexpr auto no_flow_add(T _a, T _b) {
	using unsigned_type = T;
	using signed_type = ::std::make_signed_t<T>;
	static constexpr unsigned_type Min = 0, Max = ~Min;

	auto C = _a + _b;
	if (auto _half = (_a >> 1) + (_b >> 1);
	_half > Max >> 1 || (_half == Max >> 1 && _a % 2 && _b % 2))
		return Max;
	return C;
}
template <SignedInt T>
constexpr auto no_flow_add(T _a, T _b) {
	using unsigned_type = ::std::make_unsigned_t<T>;
	using signed_type = T;
	static constexpr signed_type Min = signed_type(1) << (sizeof(signed_type) * 8 - 1), Max = ~Min;

	auto C = signed_type((unsigned_type)_a + (unsigned_type)_b);
	if (bool _sign_a = _a < 0;	_sign_a == _a < 0 && _sign_a != C < 0)
		return _sign_a ? Min : Max;
	return C;
}

template <UnsignedInt T>
constexpr flow_state flow_state_add(T _a, T _b) {
	using unsigned_type = T;
	using signed_type = ::std::make_signed_t<T>;
	static constexpr unsigned_type Min = 0, Max = ~Min;

	if (auto _half = (_a >> 1) + (_b >> 1);
	_half > Max >> 1 || (_half == Max >> 1 && _a % 2 && _b % 2))
		return flow_state::overflow;
	return flow_state::no_flow;
}
template <SignedInt T>
constexpr auto flow_state_add(T _a, T _b) {
	using unsigned_type = ::std::make_unsigned_t<T>;
	using signed_type = T;
	static constexpr signed_type Min = signed_type(1) << (sizeof(signed_type) * 8 - 1), Max = ~Min;

	auto C = signed_type((unsigned_type)_a + (unsigned_type)_b);
	if (bool _sign_a = _a < 0;	_sign_a == _a < 0 && _sign_a != C < 0)
		return _sign_a ? flow_state::underflow : flow_state::overflow;
	return flow_state::no_flow;
}


template <SignedInt T>
class flowless_int {
public:
	using value_type = T;
	value_type Value;

	constexpr flowless_int(const value_type & _v)
		: Value(_v) {}
	constexpr operator value_type() { return Value; }
	constexpr value_type operator*() const& { return Value; }
	
	static constexpr value_type Min =
		Signed<value_type>
		? (value_type(1) << (sizeof(value_type) * 8 - 1))
		: value_type(), Max = ~Min, HalfMax = Max / 2;

	static constexpr auto flow_state_add(flowless_int const& _a, flowless_int const& _b)
	{ return (flow_state)flow_state_add(_a.Value, _b.Value); }

	constexpr value_type operator+(flowless_int const& right)
	{ return no_flow_add(*this, right); }
	constexpr flowless_int & operator+=(flowless_int const& right)
	{ return *this = *this + right; }

	constexpr flow_state flow_state_loop_multiphy
	(flowless_int left, UnsignedInt auto right) {
		if (right != 0) while (--right != 0)
		switch (flow_state_add(left, left)) {
		case flow_state::underflow: return flow_state::underflow;
		case flow_state::overflow: return flow_state::overflow;
		case flow_state::no_flow: left += left; break;
		}
		return flow_state::no_flow;
	}
	constexpr T loop_multiply(flowless_int left, UnsignedInt auto right) {
		if (right != 0) while (--right != 0)
		switch (flow_state_add(left, left)) {
		case flow_state::underflow: return Min;
		case flow_state::overflow: return Max;
		case flow_state::no_flow: *left += *left; break;
		}
		return *left;
	}

	constexpr T operator*(UnsignedInt auto right)
	{ return loop_multiply(*this, right); }
	constexpr T operator*(std::signed_integral auto right) {
		return (right < 0)
			? -loop_multiply(*this, -right)
			: loop_multiply(*this, right);
	}
	constexpr flowless_int & operator*=(UnsignedInt auto right)
	{ return *this = *this * right; }
	constexpr flowless_int & operator*=(std::signed_integral auto right)
	{ return *this = *this * right; }

};


}

#endif