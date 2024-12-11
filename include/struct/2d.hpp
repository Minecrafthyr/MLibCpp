// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLibHeader_Struct_2DHpp
#define MLibHeader_Struct_2DHpp 20241113

#include "base.hpp"

namespace mlib {

template <typename T_>
struct rectangle2 {
	using value_type = T_;
	static constexpr ::std::size_t Size{2};

	union {
		::std::array<value_type, Size> StdArray;
		struct { value_type Width, Height; };
		struct { value_type W, H; };
	};

};

template <typename T_>
struct rectangle4 {
	using value_type = T_;
	static constexpr ::std::size_t Size{4};

	union {
		::std::array<value_type, Size> StdArray;
		struct { value_type Left, Top, Right, Bottom; };
		struct { value_type L, T, R, B; };
	};

};

}

#endif