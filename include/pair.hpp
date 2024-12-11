// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLibHeader_PairHpp
#define MLibHeader_PairHpp 20241121L
#include <tuple>
#include "types.hpp"

namespace mlib {

template <typename T, typename T2>
class pair_base {
public:
	using first_type = T;
	using second_type = T2;

	first_type first;
	second_type second;

	template <int>
	constexpr explicit (!ImplicitlyConstructible<first_type> && !ImplicitlyConstructible<second_type>)
	pair_base()
	noexcept(requires{ {first_type{}}noexcept; {second_type{}}noexcept; })
	requires requires{ first_type{}; second_type{}; }
	: first(), second() {}
	
	constexpr pair_base(auto && _first, auto && _second)
	: first(Forward(_first)), second(Forward(_second)) {}

};

}

namespace std {
	template <int I> requires (I == 0)
	constexpr decltype(auto) get(::mlib::Specialization<::mlib::pair_base> auto && _pair)
	{ return Forward(_pair.first); }
	template <int I> requires (I == 1)
	constexpr decltype(auto) get(::mlib::Specialization<::mlib::pair_base> auto && _pair)
	{ return Forward(_pair.second); }
}

namespace mlib {

template <Object T, Object T2 = T>
class pair;
template <typename T, typename T2 = T>
pair(T const&, T const&) -> pair<T, T2>;

template <Object T, Object T2>
class pair : public pair_base<T, T2> {
public:
	using pair_base_type = pair_base<T, T2>;
	using first_type = T;
	using second_type = T2;

private:
	template <typename MatchT>
	constexpr decltype(auto) make_value(auto && _value) {
		decltype(auto) _rvalue = Forward(_value);
		using _rvalue_type = decltype(_rvalue);
		using _match_type = ::std::remove_cvref_t<MatchT>;
		if constexpr (SameAsRemoveCVRef<_rvalue_type, _match_type>)
			return _rvalue;
		else if constexpr (::std::convertible_to<_rvalue_type, _match_type>)
			return _match_type(_rvalue);
		else if constexpr (Specialization<_rvalue_type, ::std::tuple>)
			return ::std::make_from_tuple<_match_type>(_rvalue);
		else
			static_assert(false);
	}
public:
	
	constexpr pair(auto && _first, auto && _second)
	: pair_base_type(
		make_value<first_type>(Forward(_first)),
		make_value<second_type>(Forward(_second))
	) {}

	constexpr pair(auto && _pair)
	: pair_base_type(
		make_value<first_type>(::std::get<0>(Forward(_pair))),
		make_value<second_type>(::std::get<1>(Forward(_pair)))
	) {}

	constexpr pair(pair const&) = default;
	constexpr pair(pair &&) = default;
};

template <typename T, typename T2>
class forward_pair;
template <typename T, typename T2>
forward_pair(T &&, T2 &&) -> forward_pair<T &&, T2 &&>;
template <typename T>
forward_pair(T &&) -> forward_pair<
	decltype(::std::get<0>(DeclVal(T))),
	decltype(::std::get<1>(DeclVal(T)))>;

template <typename T, typename T2>
class forward_pair : public pair_base<T, T2> {
public:
	using pair_base_type = pair_base<T, T2>;
	using first_type = T;
	using second_type = T2;

	constexpr forward_pair(auto && _pair) requires(
		SameAs<decltype(::std::get<0>(_pair)), first_type> &&
		SameAs<decltype(::std::get<1>(_pair)), second_type>)
	: pair_base_type(Forward(::std::get<0>(_pair)), Forward(::std::get<1>(_pair))) {}
	constexpr forward_pair(auto && _first, auto && _second)
	: pair_base_type(Forward(_first), Forward(_second)) {}
	
	constexpr forward_pair(forward_pair const&) = default;
	constexpr forward_pair(forward_pair &&) = default;

};

}

#endif