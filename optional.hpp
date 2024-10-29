#ifndef MLib_Optional 20241028L
#define MLib_Optional

#include <optional>
#include "concepts.hpp"

namespace mlib {


template <c_object Type>
class optional {
public:
	using value_type = Type;
	value_type value;
	bool has_value = false;

	constexpr optional(std::nullopt_t)
	noexcept(::std::is_nothrow_constructible_v<value_type>)
		: value(), has_value(false) {}
	constexpr optional() 
	noexcept(::std::is_nothrow_constructible_v<value_type>)
		: has_value(true) {}
	constexpr optional(auto && ... inputs)
	noexcept(noexcept(value(MLibForward(inputs)...)))
		: value(MLibForward(inputs)...), has_value(true) {}

	constexpr operator bool(this const auto && self) { return self.has_value; }
	constexpr explicit operator Type(this auto && self) { return self.value; }
	constexpr auto & operator*(this auto && self) { return self.value; }

};
template <c_object Type>
constexpr decltype(auto) operator<=>(const optional<Type> & left, const optional<Type> & right) {
	return (left && right) ? (*left <=> *right) : (left <=> right);
}
template <c_object Type>
constexpr decltype(auto) operator<=>(const optional<Type> & left, const Type & right) {
	return left ? (*left <=> right) : std::partial_ordering::unordered;
}
template <c_object Type>
constexpr decltype(auto) operator<=>(const Type & left, const optional<Type> & right) {
	return right ? (left <=> *right) : std::partial_ordering::unordered;
}


}

#endif