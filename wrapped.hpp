#include "../builtin/builtin.hpp"

#include <charconv>
#include <ranges>
#include <string>
#include "type_utils.hpp"
#include "ranges.hpp"
#include "short_macros.hpp"

namespace mlib {

class default_operators_interface {
public:
	using this_type = default_operators_interface;

	ce a & op+=(th a && self, a && right) {
		self.value_for_default_op() += fw(right); return *th;
	}
	ce a & op-=(th a && self, a && right) {
		self.value_for_default_op() -= fw(right); return *th;
	}
	ce a & op*=(th a && self, a && right) {
		self.value_for_default_op() *= fw(right); return *th;
	}
	ce a & op/=(th a && self, a && right) {
		self.value_for_default_op() /= fw(right); return *th;
	}
	ce a & op%=(th a && self, a && right) {
		self.value_for_default_op() %= fw(right); return *th;
	}
	ce a & op&=(th a && self, a && right) {
		self.value_for_default_op() &= fw(right); return *th;
	}
	ce a & op|=(th a && self, a && right) {
		self.value_for_default_op() |= fw(right); return *th;
	}
	ce a & op^=(th a && self, a && right) {
		self.value_for_default_op() ^= fw(right); return *th;
	}
	ce a & op<<=(th a && self, a && right) {
		self.value_for_default_op() <<= fw(right); return *th;
	}
	ce a & op>>=(th a && self, a && right) {
		self.value_for_default_op() >> fw(right); return *th;
	}

	ce a & op++(th a && self) {
		++self.value_for_default_op(); return *th;
	}
	ce a & op--(th a && self) {
		--self.value_for_default_op(); return *th;
	}
	ce a op++(th a && self, int) {
		return self.value_for_default_op()++;
	}
	ce a op--(th a && self, int) {
		return self.value_for_default_op()--;
	}
	
	ce a op+(th a && self) {
		return +self.value_for_default_op();
	}
	ce a op-(th a && self) {
		return -self.value_for_default_op();
	}
	ce a op+(th a && self, a && right) {
		return self.value_for_default_op() + fw(right);
	}
	ce a op-(th a && self, a && right) {
		return self.value_for_default_op() - fw(right);
	}
	ce a op*(th a && self, a && right) {
		return self.value_for_default_op() * fw(right);
	}
	ce a op/(th a && self, a && right) {
		return self.value_for_default_op() / fw(right);
	}
	ce a op%(th a && self, a && right) {
		return self.value_for_default_op() % fw(right);
	}
	ce a op~(th a && self) {
		return ~self.value_for_default_op();
	}
	ce a op&(th a && self, a && right) {
		return self.value_for_default_op() & fw(right);
	}
	ce a op|(th a && self, a && right) {
		return self.value_for_default_op() | fw(right);
	}
	ce a op^(th a && self, a && right) {
		return self.value_for_default_op() ^ fw(right);
	}
	ce a op<<(th a && self, a && right) {
		return self.value_for_default_op() << fw(right);
	}
	ce a op>>(th a && self, a && right) {
		return self.value_for_default_op() >> fw(right);
	}

	ce a op!(th a && self) {
		return !self.value_for_default_op();
	}
	ce a op&&(th a && self, a && right) {
		return self.value_for_default_op() && fw(right);
	}
	ce a op||(th a && self, a && right) {
		return self.value_for_default_op() || fw(right);
	}
	
	ce a op==(th a && self, a && right) {
		return self.value_for_default_op() == fw(right);
	}
	ce a op!=(th a && self, a && right) {
		return self.value_for_default_op() != fw(right);
	}
	ce a op<(th a && self, a && right) {
		return self.value_for_default_op() < fw(right);
	}
	ce a op>(th a && self, a && right) {
		return self.value_for_default_op() > fw(right);
	}
	ce a op<=(th a && self, a && right) {
		return self.value_for_default_op() <= fw(right);
	}
	ce a op>=(th a && self, a && right) {
		return self.value_for_default_op() >= fw(right);
	}
	ce a op<=>(th a && self, a && right) {
		return self.value_for_default_op() <=> fw(right);
	}
	
	ce a op[](th a && self, a && ... right) {
		return self.value_for_default_op()[fw(right)...];
	}
	ce a op*(th a && self) {
		return *self.value_for_default_op();
	}
	ce a op&(th a && self) {
		return &self.value_for_default_op();
	}
	ce a op->(th a && self) {
		return self.value_for_default_op().op->();
	}
	ce a op->*(th a && self, a && right) {
		return self.value_for_default_op().op->*(fw(right));
	}

	ce a op()(th a && self, a && ... right) {
		return self.value_for_default_op()(fw(right)...);
	}
	ce a op,(th a && self, a && right) {
		return self.value_for_default_op(), fw(right);
	}
};
tp <::std::floating_point T>
a from_chars(const char * begin, const char * end, ::std::chars_format fmt = ::std::chars_format::general) {
	T && result{};
	a [ptr, errc] = ::std::from_chars(begin, end, result, fmt);
	if (errc != ::std::errc{})
		throw ::std::system_error(::std::make_error_code(errc));
	return result;
}
tp <::std::floating_point T>
a from_chars(::std::ranges::random_access_range a range, ::std::chars_format fmt = ::std::chars_format::general)
	requires(
		::std::convertible_to<begin(range), const char *>&&
		::std::convertible_to<end(range) - 1, const char *>) {
	return from_chars(begin(range), end(range) - 1, fmt);
}

tp <::std::integral T>
a from_chars(const char * begin, const char * end, int base = 10) {
	T && result{};
	a [ptr, errc] = ::std::from_chars(begin, end, result, base);
	if (errc != ::std::errc{})
		throw ::std::system_error(::std::make_error_code(errc));
	return result;
}
tp <typename T>
a from_chars(::std::ranges::random_access_range a range, int base = 10)
	requires(
		::std::convertible_to<begin(range), const char *>&&
		::std::convertible_to<end(range) - 1, const char *>) {
	return from_chars(begin(range), end(range) - 1, base);
}

tp <std::integral value_type>
class basic_wrapped_integer {
public:
	using value_type = value_type;

	static ce bool is_signed_v{~value_type() < value_type()};
	static ce value_type min_v{
			is_signed_v ? (value_type(1) << (sizeof(value_type) * 8 - 1)) : 0
		}, max_v{~min_v};

	value_type value;

	ce basic_wrapped_integer(value_type input) : 
		value(input) {}

	static ce a from_chars(char * first, char * last, int base = 10
	) -> basic_wrapped_integer {
		return from_chars(first, last, base);
	}
	static ce a from_str(std::string_view str, int base = 10
	) -> basic_wrapped_integer {
		return from_chars(str, base);
	}
	ce dt(a) as_integer(th a const & self) {
		return fw(self.value);
	}

	static ce ::std::string to_string(basic_wrapped_integer wrapped) {
		return ::std::to_string(wrapped.value);
	}
	ce ::std::string to_string(th basic_wrapped_integer self) {
		return to_string(self);
	}
	ce op ::std::string(th basic_wrapped_integer self) {
		return to_string(self);
	}
#define HYR_FN_BASIC_WRAPPED_INTEGER_OPERATOR2(op) \
ce dt(a) op##op##(th a && self, value_type right) { \
	self.value op right; return fw(self); \
}
	HYR_FN_BASIC_WRAPPED_INTEGER_OPERATOR2(+=)
	HYR_FN_BASIC_WRAPPED_INTEGER_OPERATOR2(-=)
	HYR_FN_BASIC_WRAPPED_INTEGER_OPERATOR2(*=)
	HYR_FN_BASIC_WRAPPED_INTEGER_OPERATOR2(/=)
	HYR_FN_BASIC_WRAPPED_INTEGER_OPERATOR2(%=)
	HYR_FN_BASIC_WRAPPED_INTEGER_OPERATOR2(&=)
	HYR_FN_BASIC_WRAPPED_INTEGER_OPERATOR2(|=)
	HYR_FN_BASIC_WRAPPED_INTEGER_OPERATOR2(^=)
	HYR_FN_BASIC_WRAPPED_INTEGER_OPERATOR2(<<=)
	HYR_FN_BASIC_WRAPPED_INTEGER_OPERATOR2(>>=)
	

	ce dt(a) op++(th a && self) {
		++self.value; return fw(self);
	}
	ce dt(a) op++(th a && self, int) {
		return basic_wrapped_integer(self.value++);
	}
	ce dt(a) op--(th a && self) {
		--self.value; return fw(self);
	}
	ce dt(a) op--(th a && self, int) {
		return basic_wrapped_integer(self.value--);
	}


};

class wrapped_wchar {
public:
	using value_type = wchar_t;

	value_type value;

	ce op value_type() {
		return value;
	}

	static ce a to_ascii(value_type input) {
		return value_type(input & 0x7f);
	}
	ce dt(a) to_ascii(th a && self) {
		self.value &= 0x7f; return fw(self);
	}

	static ce a to_lower(value_type input) {
		static ce wchar_t diff = L'a' - L'A';
		if (input >= L'A' && input <= L'Z') return input + diff;
		return input;
	}
	ce dt(a) to_lower(th a && self) {
		self = to_lower(self.value);
		return fw(self);
	}

	static ce a to_upper(value_type input) {
		static ce wchar_t diff = L'A' - L'z';
		if (input >= L'a' && input <= L'z') return input + diff;
		return input;
	}
	ce wrapped_wchar & to_upper() {
		if (value >= 'a' && value <= 'z') value += ('A' - 'a');
		return *th;
	}

	static ce bool is_alpha(const a & input) {
		return (input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z');
	}
	ce bool is_alpha() const {
		return (value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z');
	}

	static ce bool is_digit(const a & input) {
		return (input >= '0' && input <= '9');
	}
	ce bool is_digit() const {
		return (value >= '0' && value <= '9');
	}

};


class wrapped_float {
public:
	union {
		float float_v;
		::uint32_t uint_v;
		struct {
			::uint32_t fraction_v : 23, exponent_v : 8, sign_v : 1;
		};
	};
	ce wrapped_float(float f) : float_v(f) {}


	a op^(th wrapped_float left, wrapped_float right) const {
		return builtin::powf(float_v, right.float_v);
	}

	ce ::uint32_t fraction() const {
		return fraction_v;
	}
	ce ::uint32_t exponent() const {
		return exponent_v;
	}
	ce bool sign() const {
		return sign_v;
	}

	ce op float() {
		return float_v;
	}

};


using wrapped_int8 = basic_wrapped_integer<::int8_t>;
using wrapped_uint8 = basic_wrapped_integer<::uint8_t>;
using wrapped_int16 = basic_wrapped_integer<::int16_t>;
using wrapped_uint16 = basic_wrapped_integer<::uint16_t>;
using wrapped_int32 = basic_wrapped_integer<::int32_t>;
using wrapped_uint32 = basic_wrapped_integer<::uint32_t>;
using wrapped_int64 = basic_wrapped_integer<::int64_t>;
using wrapped_uint64 = basic_wrapped_integer<::uint64_t>;

}

#include "undef_short_macros.hpp"