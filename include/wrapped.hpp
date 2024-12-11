// Copy_right © 2024 Minecraft_hyr - MIT License
#ifndef MLibHeader_WrappedHpp
#define MLibHeader_WrappedHpp 20241109

#include <charconv>
#include <string>
#include "builtin.hpp"
#include "macros/normal.hpp"
#include "ranges.hpp"
#include "exception.hpp"

namespace mlib {

template <FloatingPoint T>
auto from_chars
(char const* _begin, char const* _end,
	::std::chars_format _format = ::std::chars_format::general) {
	T && _result{};
	auto [_ptr, _errc] = ::std::from_chars(_begin, _end, _result, _format);
	if (_errc != ::std::errc{}) throw system_error(_errc);
	return _result;
}
template <FloatingPoint T>
auto from_chars
(ranges::random_access_range auto const& _range,
	::std::chars_format fmt = ::std::chars_format::general)
requires(::std::convertible_to<decltype(begin(_range)), char const*>
&& ::std::convertible_to<decltype(end(_range) - 1), char const*>)
{ return from_chars<T>(begin(_range), end(_range) - 1, fmt); }

template <Integral T>
auto from_chars(char const* _begin, char const* _end, int _base = 10) {
	T && _result{};
	auto [_ptr, _errc] = ::std::from_chars(_begin, _end, _result, _base);
	if (_errc != ::std::errc{}) throw system_error(_errc);
	return _result;
}
template <Integral T>
auto from_chars(ranges::random_access_range auto const & _range, int _base = 10)
requires(::std::convertible_to<decltype(begin(_range)), char const*>
&& ::std::convertible_to<decltype(end(_range) - 1), char const*>)
{ return from_chars<T>(begin(_range), end(_range) - 1, _base); }

template <Integral T>
class basic_wrapped_int {
public:
	using value_type = T;

	static constexpr bool IsSigned{~value_type() < value_type()};
	static constexpr value_type Min{
		IsSigned ? (value_type(1) << (sizeof(value_type) * 8 - 1)) : 0},
		max_v{~Min};

	value_type Value;
	constexpr basic_wrapped_int(value_type _value) : Value(_value) {}

	static constexpr auto from(char * _first, char * _last, int _base = 10)
	{ return (basic_wrapped_int)from_chars<value_type>(_first, _last, _base); }
	static constexpr auto from(::std::string_view _str, int _base = 10)
	{ return (basic_wrapped_int)from_chars<value_type>(_str, _base); }
	constexpr decltype(auto) unwrap(this auto && self) { return Forward(self.value); }

	constexpr auto to_string(this basic_wrapped_int self)
	{ return ::std::to_string(self.Value); }
	constexpr operator ::std::string(this basic_wrapped_int self)
	{ return self.to_string(); }

};

constexpr auto to_ascii(int _value)
{ return _value & 0x7f; }

constexpr wchar_t to_lower(wchar_t _value) {
	if (_value | in('A', 'Z')) _value += ('A' - 'a');
	return _value;
}
constexpr wchar_t to_upper(wchar_t _value) {
	if (_value | in('a', 'z')) _value += ('a' - 'A');
	return _value;
}

constexpr bool is_alpha(int _value)
{ return _value | in('a', 'z') || _value | in('A', 'Z'); }
constexpr bool is_digit(int _value)
{ return _value | in('0', '9'); }

struct wrapped_char {
	using value_type = char;

	value_type value;
	
	constexpr wrapped_char(value_type _value) : value(_value) {}

	constexpr decltype(auto) unwrap(this auto && self)
	{ return self.value; }
	constexpr decltype(auto) operator*(this auto && self)
	{ return self.value; }

};

struct wrapped_wchar {
	using value_type = wchar_t;

	value_type value;

	constexpr wrapped_wchar(value_type _value) : value(_value) {}

	constexpr decltype(auto) unwrap(this auto && self)
	{ return self.value; }
	constexpr decltype(auto) operator*(this auto && self)
	{ return self.value; }

	constexpr decltype(auto) to_ascii(this auto && self)
	{ self = ::mlib::to_ascii(self.value); return Forward(self); }
	constexpr decltype(auto) to_lower(this auto && self)
	{ self = ::mlib::to_lower(self.value); return Forward(self); }
	constexpr decltype(auto) to_upper(this auto && self)
	{ self = ::mlib::to_upper(self.value); return Forward(self); }

	constexpr bool is_alpha(this auto self) { return ::mlib::is_alpha(self.value); }
	constexpr bool is_digit(this auto self) { return ::mlib::is_digit(self.value); }
};

struct wrapped_float {
	union {
		float float_v;
		struct {
			::std::uint32_t fraction_v : 23, exponent_v : 8, sign_v : 1;
		} bits_v;
	};
	constexpr wrapped_float(float _float) : float_v(_float) {}

	constexpr wrapped_float operator^(this wrapped_float self, wrapped_float _right)
	{ return builtin::powf(self.float_v, _right.float_v); }

	constexpr ::std::uint32_t fraction() const noexcept { return bits_v.fraction_v; }
	constexpr ::std::uint32_t exponent() const noexcept { return bits_v.exponent_v; }
	constexpr bool sign() const noexcept { return bits_v.sign_v; }
};

using wrapped_int8 = basic_wrapped_int<::std::int8_t>;
using wrapped_uint8 = basic_wrapped_int<::std::uint8_t>;
using wrapped_int16 = basic_wrapped_int<::std::int16_t>;
using wrapped_uint16 = basic_wrapped_int<::std::uint16_t>;
using wrapped_int32 = basic_wrapped_int<::std::int32_t>;
using wrapped_uint32 = basic_wrapped_int<::std::uint32_t>;
using wrapped_int64 = basic_wrapped_int<::std::int64_t>;
using wrapped_uint64 = basic_wrapped_int<::std::uint64_t>;

}

#endif