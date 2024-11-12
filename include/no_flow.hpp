// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLib_NoFlow
#define MLib_NoFlow 20241112L
#include <concepts>
#include <limits>
#include <utility>
#include <cmath>

#include "types.hpp"

namespace mlib {

template <c_signed_int T>
[[nodiscard, gnu::always_inline]]
constexpr int bin_sign(T Val) {
	return Val < T{} ? -1 : 0;
}
template <c_signed_int T>
[[nodiscard, gnu::always_inline]]
constexpr int num_sign(T Val) {
	return (T{} < Val) - (Val < T{});
}


enum flow_state : int8_t {
	underflow = -1,
	no_flow = 0,
	overflow = 1
};

template <c_unsigned_int T>
constexpr auto no_flow_add(T A, T B) {
	using unsigned_type = T;
	using signed_type = ::std::make_signed_t<T>;
	static constexpr unsigned_type Min = 0, Max = ~Min;

	auto C = A + B;
	if (auto Half = A >> 1 + B >> 1;
	Half > Max >> 1 || (Half == Max >> 1 && A % 2 && B % 2))
		return Max;
	return C;
}
template <c_signed_int T>
constexpr auto no_flow_add(T A, T B) {
	using unsigned_type = ::std::make_unsigned_t<T>;
	using signed_type = T;
	static constexpr signed_type Min = signed_type(1) << (sizeof(signed_type) * 8 - 1), Max = ~Min;

	auto C = signed_type((unsigned_type)A + (unsigned_type)B);
	if (bool SignA = A < 0;	SignA == A < 0 && SignA != C < 0)
		return SignA ? Min : Max;
	return C;
}

template <c_unsigned_int T>
constexpr flow_state flow_state_add(T A, T B) {
	using unsigned_type = T;
	using signed_type = ::std::make_signed_t<T>;
	static constexpr unsigned_type Min = 0, Max = ~Min;

	if (auto Half = A >> 1 + B >> 1;
	Half > Max >> 1 || (Half == Max >> 1 && A % 2 && B % 2))
		return flow_state::overflow;
	return flow_state::no_flow;
}
template <c_signed_int T>
constexpr auto flow_state_add(T A, T B) {
	using unsigned_type = ::std::make_unsigned_t<T>;
	using signed_type = T;
	static constexpr signed_type Min = signed_type(1) << (sizeof(signed_type) * 8 - 1), Max = ~Min;

	auto C = signed_type((unsigned_type)A + (unsigned_type)B);
	if (bool SignA = A < 0;	SignA == A < 0 && SignA != C < 0)
		return SignA ? flow_state::underflow : flow_state::overflow;
	return flow_state::no_flow;
}


template <c_signed_int T>
class no_flow {
public:
	using value_type = T;
	value_type Val;

	constexpr no_flow(const value_type & Val)
		: Val(Val) {}
	constexpr operator value_type() {
		return Val;
	}
	constexpr value_type operator*() const {
		return Val;
	}
	
	static constexpr value_type Min =
		c_signed<value_type>
		? (value_type(1) << (sizeof(value_type) * 8 - 1))
		: value_type(), Max = ~Min, HalfMax = Max / 2;

	static constexpr auto flow_state_add(const no_flow & A, const no_flow & B) {
		return (flow_state)flow_state_add(A.Val, B.Val)
	}

	constexpr value_type operator+(const no_flow & right) {
		return no_flow_add(*this, right);
	}
	constexpr no_flow & operator+=(const no_flow & right) {
		return *this = *this + right;
	}

	constexpr flow_state flow_state_loop_multiphy(no_flow left, c_unsigned_int auto right) {
		if (right != 0) while (--right != 0)
		switch (flow_state_add(left, left)) {
		case flow_state::underflow: return flow_state::underflow;
		case flow_state::overflow: return flow_state::overflow;
		case flow_state::no_flow: left += left; break;
		}
		return flow_state::no_flow;
	}
	constexpr T loop_multiphy(no_flow left, c_unsigned_int auto right) {
		if (right != 0) while (--right != 0)
		switch (flow_state_add(left, left)) {
		case flow_state::underflow: return Min;
		case flow_state::overflow: return Max;
		case flow_state::no_flow: *left += *left; break;
		}
		return *left;
	}

	constexpr T operator*(c_unsigned_int auto right) {
		return loop_multiphy(*this, right);
	}
	constexpr T operator*(std::signed_integral auto right) {
		return (right < 0)
			? -loop_multiphy(*this, -right)
			: loop_multiphy(*this, right);

	}
	constexpr no_flow & operator*=(c_unsigned_int auto right) {
		return *this = *this * right;
	}
	constexpr no_flow & operator*=(std::signed_integral auto right) {
		return *this = *this * right;
	}

};


}

#endif