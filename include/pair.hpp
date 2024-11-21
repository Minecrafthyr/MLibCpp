// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLib_Pair
#define MLib_Pair 20241120L
#include <tuple>
#include "types.hpp"

namespace mlib {

template <typename T, typename T2>
struct pair_base {
	using first_type = T;
	using second_type = T2;

	first_type first;
	second_type second;

	template <int = 0>
		requires requires{ first_type{}; second_type{}; }
	constexpr explicit(not(ImplicitlyDefaultConstructible<first_type>
	&& ImplicitlyDefaultConstructible<second_type>))
	pair_base() noexcept(requires{ {first_type{}}noexcept; {second_type{}}noexcept; })
	: first(), second() {}
	
	constexpr pair_base(auto && _first, auto && _second)
	: first(MLibForward(_first)), second(MLibForward(_second)) {}

};

}

namespace std {
	template <int I> requires (I == 0)
	constexpr decltype(auto) get(::mlib::Specialization<::mlib::pair_base> auto && _pair) { return MLibForward(_pair.first); }
	template <int I> requires (I == 1)
	constexpr decltype(auto) get(::mlib::Specialization<::mlib::pair_base> auto && _pair) { return MLibForward(_pair.second); }
}

namespace mlib {

template <Object T, Object T2 = T>
struct pair;
template <typename T, typename T2 = T>
pair(T const&, T const&) -> pair<T, T2>;

template <Object T, Object T2>
struct pair : public pair_base<T, T2> {
	using pair_base_type = pair_base<T, T2>;
	using pair_base_type::first_type;
	using pair_base_type::second_type;

private:
	template <typename MatchT>
	constexpr decltype(auto) make_value(auto && _value) {
		decltype(auto) _rvalue = MLibForward(_value);
		using _rvalue_type = decltype(_rvalue);
		using _match_type = ::std::remove_cvref_t<MatchT>;
		if constexpr (RemoveCVRefSameAs<_rvalue_type, _match_type>)
			return _rvalue;
		else if constexpr (ConvertibleTo<_rvalue_type, _match_type>)
			return _match_type(_rvalue);
		else if constexpr (Specialization<_rvalue_type, ::std::tuple>)
			return ::std::make_from_tuple<_match_type>(_rvalue);
		else
			static_assert(false);
	}
public:
	
	template <typename InT, typename InT2>
	constexpr pair(InT && _first, InT2 && _second)
	: pair_base_type(
		make_value<first_type>(MLibForward(_first)),
		make_value<second_type>(MLibForward(_second))
	) {}

	constexpr pair(auto && _pair)
	: pair_base_type(
		make_value<first_type>(::std::get<0>(MLibForward(_pair))),
		make_value<second_type>(::std::get<1>(MLibForward(_pair)))
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
	decltype(::std::get<0>(MLibDeclVal(T))),
	decltype(::std::get<1>(MLibDeclVal(T)))>;

template <typename T, typename T2>
struct forward_pair : public pair_base<T, T2> {
	using pair_base_type = pair_base<T, T2>;
	using pair_base_type::first_type;
	using pair_base_type::second_type;

	constexpr forward_pair(auto && _pair) requires(
		SameAs<decltype(::std::get<0>(_pair)), first_type> &&
		SameAs<decltype(::std::get<1>(_pair)), second_type>)
	: pair_base_type(MLibForward(::std::get<0>(_pair)), MLibForward(::std::get<1>(_pair))) {}
	
	constexpr forward_pair(forward_pair const&) = default;
	constexpr forward_pair(forward_pair &&) = default;

};

}

#endif