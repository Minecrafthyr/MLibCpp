// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLib_Pair
#define MLib_Pair 20241029L
#include "types.hpp"

namespace mlib {

template <c_object T, c_object T2 = T>
struct pair;
template <c_object T, c_object T2 = T>
pair(T &&, T &&) -> pair<T, T2>;

template <c_object T, c_object T2 = T>
struct pair {
	using first_type = T;
	using second_type = T2;

	first_type first;
	second_type second;
	
	template <int = 0>
		requires requires{ first_type{}; second_type{}; }
	constexpr explicit(not requires (void(&_f)(first_type), void(&_f2)(second_type)) { _f({}); _f2({}); })
		pair() noexcept(requires{ {first_type{}}noexcept; {second_type{}}noexcept; })
		: first(), second() {}

	constexpr pair(c_to<first_type> auto && first, c_to<second_type> auto && second)
		: first(first), second(second) {}

	constexpr pair(const pair &) = default;
	constexpr pair(pair &&) = default;
};


template <typename T, typename T2>
class ref_pair;
template <typename T, typename T2>
ref_pair(T, T2) -> ref_pair<T, T2>;
template <typename T, typename T2>
ref_pair(T &, T2 &) -> ref_pair<T &, T2 &>;
template <typename T, typename T2>
ref_pair(T &&, T2 &&) -> ref_pair<T &&, T2 &&>;

template <typename T, typename T2>
struct ref_pair {
	using first_type = T;
	using second_type = T2;

	first_type first;
	second_type second;

	constexpr ref_pair(auto && first, auto && second) :
		first(first), second(second) {}

	constexpr ref_pair(auto && pair) requires(
		c_to<decltype(pair.first), first_type> &&
		c_to<decltype(pair.second), second_type>) :
		first(pair.first), second(pair.second) {}
};

}

#endif