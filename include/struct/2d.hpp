// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLib_Struct_2D
#define MLib_Struct_2D 20241112L

#include "base.hpp"

namespace mlib {

template <typename T>
struct rectangle2 {
	using value_type = T;
	static constexpr ::std::size_t Size{2};

	union {
		value_type BuiltinArray[Size];
		::std::array<value_type, Size> StdArray;
		struct { value_type Width, Height; };
		struct { value_type W, H; };
	};

};

template <typename T>
struct rectangle4 {
	using value_type = T;
	static constexpr ::std::size_t Size{4};

	union {
		value_type BuiltinArray[Size];
		::std::array<value_type, Size> StdArray;
		struct { value_type Left, Top, Right, Bottom; };
		struct { value_type L, T, R, B; };
	};

};

}

#endif