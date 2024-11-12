// Copy_right © 2024 Minecraft_hyr - MIT License
#ifndef MLibWrapped
#define MLibWrapped 20241109

#include <charconv>
#include <string>
#include "builtin.hpp"
#include "pair.hpp"
#include "macros/normal.hpp"
#include "ranges.hpp"
#include "exception.hpp"
#include "types.hpp"

namespace mlib {

template <c_float T>
auto from_chars(const char * _begin, const char * _end, ::std::chars_format _format = ::std::chars_format::general)
{
	T && _result{};
	auto [_ptr, _errc] = ::std::from_chars(_begin, _end, _result, _format);
	if (_errc != ::std::errc{}) throw system_error(_errc);
	return _result;
}
template <c_float T>
auto from_chars(ranges::random_access_range auto const & _range, ::std::chars_format fmt = ::std::chars_format::general)
requires(c_to<decltype(begin(_range)), const char *>
&& c_to<decltype(end(_range) - 1), const char *>)
{ return from_chars<T>(begin(_range), end(_range) - 1, fmt); }

template <c_int T>
auto from_chars(const char * _begin, const char * _end, int _base = 10) {
	T && _result{};
	auto [_ptr, _errc] = ::std::from_chars(_begin, _end, _result, _base);
	if (_errc != ::std::errc{}) throw system_error(_errc);
	return _result;
}
template <c_int T>
auto from_chars(ranges::random_access_range auto const & _range, int _base = 10)
requires(c_to<decltype(begin(_range)), const char *>
&& c_to<decltype(end(_range) - 1), const char *>)
{ return from_chars<T>(begin(_range), end(_range) - 1, _base); }

template <c_int T>
class basic_wrapped_int
{
public:
	using value_type = T;

	static constexpr bool is_signed_v{~value_type() < value_type()};
	static constexpr value_type min_v{
		is_signed_v ? (value_type(1) << (sizeof(value_type) * 8 - 1)) : 0},
		max_v{~min_v};

	value_type value;
	constexpr basic_wrapped_int(value_type _value) : value(_value) {}

	static constexpr auto from(char * _first, char * _last, int _base = 10)
	{ return (basic_wrapped_int)from_chars<value_type>(_first, _last, _base); }
	static constexpr auto from(::std::string_view _str, int _base = 10)
	{ return (basic_wrapped_int)from_chars<value_type>(_str, _base); }
	constexpr decltype(auto) unwrap(this auto && self) { return MLibForward(self.value); }

	constexpr auto to_string(this basic_wrapped_int self)
	{ return ::std::to_string(self.value); }
	constexpr operator ::std::string(this basic_wrapped_int self)
	{ return self.to_string(); }
	constexpr decltype(auto) operator+=(this auto && self, value_type _right)
	{ self.value += _right; return self; }
	constexpr decltype(auto) operator-=(this auto && self, value_type _right)
	{ self.value -= _right; return self; }
	constexpr decltype(auto) operator*=(this auto && self, value_type _right)
	{ self.value *= _right; return self; }
	constexpr decltype(auto) operator/=(this auto && self, value_type _right)
	{ self.value /= _right; return self; }
	constexpr decltype(auto) operator%=(this auto && self, value_type _right)
	{ self.value %= _right; return self; }
	constexpr decltype(auto) operator&=(this auto && self, value_type _right)
	{ self.value &= _right; return self; }
	constexpr decltype(auto) operator|=(this auto && self, value_type _right)
	{ self.value |= _right; return self; }
	constexpr decltype(auto) operator^=(this auto && self, value_type _right)
	{ self.value ^= _right; return self; }
	constexpr decltype(auto) operator<<=(this auto && self, value_type _right)
	{ self.value <<= _right; return self; }
	constexpr decltype(auto) operator>>=(this auto && self, value_type _right)
	{ self.value >>= _right; return self; }
	constexpr decltype(auto) operator++(this auto && self)
	{ ++self.value; return self; }
	constexpr decltype(auto) operator++(this auto && self, int)
	{ return basic_wrapped_int(self.value++); }
	constexpr decltype(auto) operator--(this auto && self)
	{ --self.value; return self; }
	constexpr decltype(auto) operator--(this auto && self, int)
	{ return basic_wrapped_int(self.value--); }
};

template <typename T, typename T2>
struct in_data_t : public ref_pair<T, T2> {};
struct in_t {
	[[gnu::always_inline]]
	constexpr auto operator()(auto && _a, auto && _b) const &
	{ return in_data_t{MLibForward(_a), MLibForward(_b)}; }
} in;
template <typename T, typename T2>
[[gnu::always_inline]]
constexpr auto operator|(auto const & _value, in_data_t<T, T2> && _data)
{ return _value >= _data.first && _value <= _data.second; }

template <typename T, typename T2>
struct out_data_t : public ref_pair<T, T2> {};
struct out_t {
	[[gnu::always_inline]]
	constexpr auto operator()(auto && _a, auto && _b) const &
	{ return out_data_t(MLibForward(_a), MLibForward(_b)); }
} out;
template <typename T, typename T2>
[[gnu::always_inline]]
constexpr auto operator|(auto const & _value, out_data_t<T, T2> && _data)
{ return _value < _data.first || _value > _data.second; }

constexpr auto to_ascii(int _value)
{ return _value & 0x7f; }
constexpr wchar_t to_lower(wchar_t _value)
{
	if (_value | in('A', 'Z'))
		_value += ('A' - 'a');
	return _value;
}
constexpr wchar_t to_upper(wchar_t _value)
{
	if (_value | in('a', 'z')) 
	  _value += ('a' - 'A');
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
	{ self = to_ascii(self.value); return self; }
	constexpr decltype(auto) to_lower(this auto && self)
	{ self = to_lower(self.value); return self; }
	constexpr decltype(auto) to_upper(this auto && self)
	{ self = to_upper(self.value); return self; }

	constexpr bool is_alpha(this auto self) { return is_alpha(self.value); }
	constexpr bool is_digit(this auto self) { return is_digit(self.value); }
};

struct wr_float {
	union {
		float float_v;
		struct bits {
			::std::uint32_t fraction_v : 23, exponent_v : 8, sign_v : 1;
		} bits_v;
	};
	constexpr wr_float(float _float) : float_v(_float) {}

	constexpr wr_float operator^(this wr_float self, wr_float _right)
	{ return builtin::powf(self.float_v, _right.float_v); }

	constexpr ::std::uint32_t fraction() const noexcept { return bits_v.fraction_v; }
	constexpr ::std::uint32_t exponent() const noexcept { return bits_v.exponent_v; }
	constexpr bool sign() const noexcept { return bits_v.sign_v; }
};

using wr_int8 = basic_wrapped_int<::int8_t>;
using wr_uint8 = basic_wrapped_int<::uint8_t>;
using wr_int16 = basic_wrapped_int<::int16_t>;
using wr_uint16 = basic_wrapped_int<::uint16_t>;
using wr_int32 = basic_wrapped_int<::int32_t>;
using wr_uint32 = basic_wrapped_int<::uint32_t>;
using wr_int64 = basic_wrapped_int<::int64_t>;
using wr_uint64 = basic_wrapped_int<::uint64_t>;

}

#endif