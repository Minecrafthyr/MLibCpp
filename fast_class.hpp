#ifndef MLib_Shapes
#define MLib_Shapes 20241029L

#include <cstdint>
#include <array>
#include "macros.hpp"
#include "concepts.hpp"

namespace mlib {


template <class Type>
class vector2 {
public:
	using element_type = Type;
	static constexpr ::size_t Size{2};

	union {
		element_type BuiltinArray[Size];
		::std::array<element_type, Size> StdArray;
		struct { element_type X, Y; };
	};
		
	constexpr vector2(auto && input)
		requires(::std::tuple_size_v<decltype(input)> == 2):
		X(::std::get<0>(MLibForward(input))),
		Y(::std::get<1>(MLibForward(input))) {}

	constexpr vector2(
		::std::convertible_to<element_type> auto && x, ::std::convertible_to<element_type> auto && y) :
		X(x), Y(y) {}

};

template <class Type>
	requires (::std::tuple_size_v<Type> == 2)
vector2(const Type &) -> vector2<decltype(::std::get<0>(MLibDeclVal(Type)))>;
template <class Type>
vector2(Type &&, Type &&) -> vector2<Type>;

template <class Type>
class vector3 {
public:
	using element_type = Type;
	static constexpr ::std::size_t Size{3};

	union {
		Type BuiltinArray[Size];
		::std::array<Type, Size> StdArray;
		struct { Type X, Y, Z; };
	};
};
template <class Type>
class rectangle2 {
public:
	using element_type = Type;
	static constexpr ::size_t Size{2};

	union {
		Type BuiltinArray[Size];
		::std::array<Type, Size> StdArray;
		struct { Type Width, Height; };
		struct { Type W, H; };
	};

};

template <class Type>
class rectangle4 {
public:
	using element_type = Type;
	static constexpr ::size_t Size{4};

	union {
		Type BuiltinArray[Size];
		::std::array<Type, Size> StdArray;
		struct { Type Left, Top, Right, Bottom; };
		struct { Type L, T, R, B; };
	};

};


}

#endif