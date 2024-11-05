#ifndef MLib_Struct_1D
#define MLib_Struct_1D 20241102L

#include "base.hpp"

namespace mlib {


template <class Type>
class vector2 {
public:
	using value_type = Type;
	static constexpr ::size_t Size{2};

	union {
		value_type BuiltinArray[Size];
		::std::array<value_type, Size> StdArray;
		struct { value_type X, Y; };
	};
		
	constexpr vector2(auto && input)
		requires(::std::tuple_size_v<decltype(input)> == 2):
		X(::std::get<0>(MLibForward(input))),
		Y(::std::get<1>(MLibForward(input))) {}

	constexpr vector2(
		::std::convertible_to<value_type> auto && x, ::std::convertible_to<value_type> auto && y) :
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
	using value_type = Type;
	static constexpr ::std::size_t Size{3};

	union {
		Type BuiltinArray[Size];
		::std::array<Type, Size> StdArray;
		struct { Type X, Y, Z; };
	};
};

}

#endif