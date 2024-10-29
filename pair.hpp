#ifndef MLib_Pair
#define MLib_Pair 20241029L
#include "concepts.hpp"

namespace mlib {

template <c_object Type, c_object Type2 = Type>
class pair;
template <c_object Type, c_object Type2 = Type>
pair(Type &&, Type &&) -> pair<Type, Type2>;

template <c_object Type, c_object Type2 = Type>
class pair {
public:
	using first_type = Type;
	using second_type = Type2;

	first_type first;
	second_type second;

	template <int = 0>
		requires requires{ first_type{}; second_type{}; }
	constexpr explicit(not requires (void(&f)(first_type), void(&f2)(second_type)) { f({}); f2({}); })
		pair() noexcept(::std::is_nothrow_default_constructible_v<first_type> && ::std::is_nothrow_default_constructible_v<second_type>)
		: first(), second() {}

	constexpr pair(::std::convertible_to<first_type> auto && first, ::std::convertible_to<second_type> auto && second)
		: first(first), second(second) {}

	pair(const pair &) = default;
	pair(pair &&) = default;


};


template <typename Type, typename Type2>
class ref_pair;
template <typename Type, typename Type2>
ref_pair(Type &, Type2 &) -> ref_pair<Type &, Type2 &>;
template <typename Type, typename Type2>
ref_pair(Type &&, Type2 &&) -> ref_pair<Type &&, Type2 &&>;

template <typename Type, typename Type2>
class ref_pair {
public:
	using first_type = Type;
	using second_type = Type2;

	first_type first;
	second_type second;

	constexpr ref_pair(auto && first, auto && second) :
		first(first), second(second) {}

	constexpr ref_pair(auto && pair) requires(
		::std::convertible_to<decltype(pair.first), first_type> &&
		::std::convertible_to<decltype(pair.second), second_type>) :
		first(pair.first), second(pair.second) {}


};

}

#endif