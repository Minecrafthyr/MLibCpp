#ifndef MLib_Struct_2D
#define MLib_Struct_2D 20241102L

#include "base.hpp"

namespace mlib {


template <class Type>
class rectangle2 {
public:
	using value_type = Type;
	static constexpr ::size_t Size{2};

	union {
		value_type BuiltinArray[Size];
		::std::array<value_type, Size> StdArray;
		struct { value_type Width, Height; };
		struct { value_type W, H; };
	};

};

template <class Type>
class rectangle4 {
public:
	using value_type = Type;
	static constexpr ::size_t Size{4};

	union {
		value_type BuiltinArray[Size];
		::std::array<value_type, Size> StdArray;
		struct { value_type Left, Top, Right, Bottom; };
		struct { value_type L, T, R, B; };
	};

};

}

#endif