// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLib_Any
#define MLib_Any 20241108L

#include <bit>
#include <typeindex>
#include <utility>
#include <stdexcept>
#include "optional.hpp"
#include "types.hpp"
#include "pair.hpp"
#include "macros/normal.hpp"

namespace mlib {

struct optional_type_index {
	union {
		::std::type_index Index;
		::std::size_t Int{};
	};
	constexpr optional_type_index() noexcept {}
	constexpr optional_type_index(::std::nullopt_t) noexcept {}
	optional_type_index(auto && Value)
	noexcept requires requires { ::std::type_index{Value}; }
	: Index(MLibForward(Value)) {}
	constexpr operator ::std::type_index &() & { return Index; }
	constexpr operator const ::std::type_index &() const & { return Index; }
};

struct any {
	void * ValuePtr = nullptr;
	optional_type_index TypeIndex{};
	
	::std::size_t TypeSize = 0uz;
	bool IsVolatile = false;
	bool IsConst = false;

	constexpr any() noexcept {}
	constexpr any(::std::nullptr_t) noexcept {}
	constexpr any(::std::nullopt_t) noexcept {}
	template <typename T>
	any(T & Value)
	: ValuePtr((void *)::std::addressof(Value)),
		TypeSize(sizeof(remove_ref_t<T>)),
		TypeIndex(typeid(remove_cvref_t<T>)),
		IsVolatile(c_volatile<remove_ref_t<T>>),
		IsConst(c_const<remove_ref_t<T>>) noexcept {}
	template <typename T>
	any(T && Value) requires (c_move_constructible<T>)
	: ValuePtr(new T(MLibForward(Value))),
		TypeSize(sizeof(remove_ref_t<T>)),
		TypeIndex(typeid(remove_cvref_t<T>)),
		IsVolatile(c_volatile<remove_ref_t<T>>),
		IsConst(c_const<remove_ref_t<T>>) noexcept {}
	template <typename T>
	any(T * Value)
	: ValuePtr((void *)Value),
		TypeSize(sizeof(T)),
		TypeIndex(typeid(remove_cv_t<T>)),
		IsVolatile(c_volatile<T>),
		IsConst(c_const<T>) noexcept {}

	[[nodiscard]]
	constexpr bool empty() const & noexcept { return ValuePtr; }

	enum class errc {
		success = 0,
		index_not_same,
		discard_volatile,
		discard_const
	};

	template <typename T>
	T & cast() const & {
		using _err = ::std::runtime_error;
		if (typeid(T) != TypeIndex)
			throw _err("hyr::any: index not same");
		if (IsVolatile && !c_volatile<remove_ref_t<T>>)
			throw _err("hyr::any: discard volatile");
		if (IsConst && !c_const<remove_ref_t<T>>)
			throw _err("hyr::any: discard const");
		return *(T *)ValuePtr;
	}
	template <typename T>
	auto cast_noexcept() const & noexcept {
		return ref_pair(
			*(T *)ValuePtr,
			(typeid(T) != TypeIndex) ? errc::index_not_same
			: (IsConst && !c_const<T>) ? errc::discard_const
			: (IsVolatile && !c_volatile<T>) ? errc::discard_volatile
			: errc::success);
	}

};


}


#endif