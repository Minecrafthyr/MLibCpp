#pragma once

#include <bit>
#include <typeindex>
#include <utility>
#include <optional>
#include <stdexcept>
#include "concepts.hpp"
#include "pair.hpp"

#ifndef MLib_Any
#define MLib_Any 20241028L

namespace mlib {

class any {
public:
	void * ptr_to_value = nullptr;
	::std::optional<::std::type_index> type_index{::std::nullopt};
	::size_t type_size = 0;
	bool is_volatile_v = false;
	bool is_const_v = false;

	constexpr any() {}
	constexpr any(::std::nullptr_t) {}
	template <class Type>
	any(Type && input) :
		ptr_to_value((void *)(&input)),
		type_size(sizeof(::std::remove_reference_t<Type>)),
		type_index(typeid(::std::remove_cvref_t<Type>)),
		is_volatile_v(::std::is_volatile_v<::std::remove_reference_t<Type>>),
		is_const_v(::std::is_const_v<::std::remove_reference_t<Type>>) noexcept {}

	[[nodiscard]] constexpr bool empty() const noexcept {
		return ptr_to_value;
	}

	enum class errc {
		success = 0,
		index_not_same,
		discard_volatile,
		discard_const
	};

	template <class Type>
	Type & cast() const {
		if (typeid(Type) != type_index)
			throw ::std::runtime_error("hyr::any: index not same");
		if (is_volatile_v && not c_volatile<::std::remove_reference_t<Type>>)
			throw ::std::runtime_error("hyr::any: discard volatile");
		if (is_const_v && not ::std::is_const_v<::std::remove_reference_t<Type>>)
			throw ::std::runtime_error("hyr::any: discard const");
		return *(Type *)ptr_to_value;
	}
	template <class Type>
	auto cast_noexcept() const noexcept {
		errc state;
		if (typeid(Type) != type_index) state = errc::index_not_same;
		else if (is_const_v && not c_const<Type>) state = errc::discard_const;
		else state = errc::success;
		return ref_pair((Type &)ptr_to_value, state);
	}

};


}

#endif