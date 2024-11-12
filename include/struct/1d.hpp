// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLib_Struct_1D
#define MLib_Struct_1D 20241112L

#include "base.hpp"

namespace mlib {

template <typename T>
struct vector2 {
	using value_type = T;
	static constexpr ::std::size_t Size{2};

	union {
		value_type BuiltinArray[Size];
		::std::array<value_type, Size> StdArray;
		struct { value_type X, Y; };
	};
		
	constexpr vector2(auto && input)
	requires(::std::tuple_size_v<decltype(input)> == 2)
	: X(::std::get<0>(MLibForward(input))),
		Y(::std::get<1>(MLibForward(input))) {}

	constexpr vector2(
		c_to<value_type> auto && _x, c_to<value_type> auto && _y) :
		X(_x), Y(_y) {}

};

template <typename T>
requires (::std::tuple_size_v<T> == 2)
vector2(T const &) -> vector2<decltype(::std::get<0>(MLibDeclVal(T)))>;
template <class T>
vector2(T &&, T &&) -> vector2<T>;

template <class T>
struct vector3 {
	using value_type = T;
	static constexpr ::std::size_t Size{3};

	union {
		T BuiltinArray[Size];
		::std::array<T, Size> StdArray;
		struct { T X, Y, Z; };
	};
};

}

#endif