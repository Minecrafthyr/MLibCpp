#include "../builtin/builtin.hpp"

#include <charconv>
#include <ranges>
#include <string>
#include "type_utils.hpp"
#include "ranges.hpp"
#include "exception.hpp"

#include "short_macros.hpp"

namespace mlib {

class default_operators_interface {
public:
	using this_type = default_operators_interface;

	ce a & op+=(th a && self, a && right) {
		self.value_for_default_op() += fw(right); rt *th;
	}
	ce a & op-=(th a && self, a && right) {
		self.value_for_default_op() -= fw(right); rt *th;
	}
	ce a & op*=(th a && self, a && right) {
		self.value_for_default_op() *= fw(right); rt *th;
	}
	ce a & op/=(th a && self, a && right) {
		self.value_for_default_op() /= fw(right); rt *th;
	}
	ce a & op%=(th a && self, a && right) {
		self.value_for_default_op() %= fw(right); rt *th;
	}
	ce a & op&=(th a && self, a && right) {
		self.value_for_default_op() &= fw(right); rt *th;
	}
	ce a & op|=(th a && self, a && right) {
		self.value_for_default_op() |= fw(right); rt *th;
	}
	ce a & op^=(th a && self, a && right) {
		self.value_for_default_op() ^= fw(right); rt *th;
	}
	ce a & op<<=(th a && self, a && right) {
		self.value_for_default_op() <<= fw(right); rt *th;
	}
	ce a & op>>=(th a && self, a && right) {
		self.value_for_default_op() >> fw(right); rt *th;
	}

	ce a & op++(th a && self) {
		++self.value_for_default_op(); rt *th;
	}
	ce a & op--(th a && self) {
		--self.value_for_default_op(); rt *th;
	}
	ce a op++(th a && self, i) {
		rt self.value_for_default_op()++;
	}
	ce a op--(th a && self, i) {
		rt self.value_for_default_op()--;
	}
	
	ce a op+(th a && self) {
		rt +self.value_for_default_op();
	}
	ce a op-(th a && self) {
		rt -self.value_for_default_op();
	}
	ce a op+(th a && self, a && right) {
		rt self.value_for_default_op() + fw(right);
	}
	ce a op-(th a && self, a && right) {
		rt self.value_for_default_op() - fw(right);
	}
	ce a op*(th a && self, a && right) {
		rt self.value_for_default_op() * fw(right);
	}
	ce a op/(th a && self, a && right) {
		rt self.value_for_default_op() / fw(right);
	}
	ce a op%(th a && self, a && right) {
		rt self.value_for_default_op() % fw(right);
	}
	ce a op~(th a && self) {
		rt ~self.value_for_default_op();
	}
	ce a op&(th a && self, a && right) {
		rt self.value_for_default_op() & fw(right);
	}
	ce a op|(th a && self, a && right) {
		rt self.value_for_default_op() | fw(right);
	}
	ce a op^(th a && self, a && right) {
		rt self.value_for_default_op() ^ fw(right);
	}
	ce a op<<(th a && self, a && right) {
		rt self.value_for_default_op() << fw(right);
	}
	ce a op>>(th a && self, a && right) {
		rt self.value_for_default_op() >> fw(right);
	}

	ce a op!(th a && self) {
		rt !self.value_for_default_op();
	}
	ce a op&&(th a && self, a && right) {
		rt self.value_for_default_op() && fw(right);
	}
	ce a op||(th a && self, a && right) {
		rt self.value_for_default_op() || fw(right);
	}
	
	ce a op==(th a && self, a && right) {
		rt self.value_for_default_op() == fw(right);
	}
	ce a op!=(th a && self, a && right) {
		rt self.value_for_default_op() != fw(right);
	}
	ce a op<(th a && self, a && right) {
		rt self.value_for_default_op() < fw(right);
	}
	ce a op>(th a && self, a && right) {
		rt self.value_for_default_op() > fw(right);
	}
	ce a op<=(th a && self, a && right) {
		rt self.value_for_default_op() <= fw(right);
	}
	ce a op>=(th a && self, a && right) {
		rt self.value_for_default_op() >= fw(right);
	}
	ce a op<=>(th a && self, a && right) {
		rt self.value_for_default_op() <=> fw(right);
	}
	
	ce a op[](th a && self, a && ... right) {
		rt self.value_for_default_op()[fw(right)...];
	}
	ce a op*(th a && self) {
		rt *self.value_for_default_op();
	}
	ce a op&(th a && self) {
		rt &self.value_for_default_op();
	}
	ce a op->(th a && self) {
		rt self.value_for_default_op().op->();
	}
	ce a op->*(th a && self, a && right) {
		rt self.value_for_default_op().op->*(fw(right));
	}

	ce a op()(th a && self, a && ... right) {
		rt self.value_for_default_op()(fw(right)...);
	}
	ce a op,(th a && self, a && right) {
		rt self.value_for_default_op(), fw(right);
	}
};
tp <c_flt T>
a from_chars(c ch begin, c ch * end, ::std::chars_format fmt = ::std::chars_format::general) {
	T && result{};
	a [ptr, errc] = ::std::from_chars(begin, end, result, fmt);
	if (errc != ::std::errc{})
		throw system_error(errc);
	rt result;
}
tp <c_flt T>
a from_chars(ranges::random_access_range a c & range, ::std::chars_format fmt = ::std::chars_format::general)
	requires(
		c_able_to<begin(range), c ch *>&&
		c_able_to<end(range) - 1, c ch *>) {
	rt from_chars<T>(begin(range), end(range) - 1, fmt);
}

tp <c_int T>
a from_chars(c ch * begin, c ch * end, i base = 10) {
	T && result{};
	a [ptr, errc] = ::std::from_chars(begin, end, result, base);
	if (errc != ::std::errc{})
		throw system_error(errc);
	rt result;
}
tp <c_int T>
a from_chars(ranges::random_access_range a c & range, i base = 10)
	requires(
		c_able_to<begin(range), c ch *> &&
		c_able_to<end(range) - 1, c ch *>) {
	rt from_chars<T>(begin(range), end(range) - 1, base);
}

tp <c_int T>
class basic_wr_int {
public:
	using value_type = T;

	st ce bl is_signed_v{~value_type() < value_type()};
	st ce value_type min_v{
			is_signed_v ? (value_type(1) << (sizeof(value_type) * 8 - 1)) : 0
		}, max_v{~min_v};

	value_type value;

	ce basic_wr_int(value_type input) : 
		value(input) {}

	st ce a from_chars(ch * First, ch * Last, i Base = 10) {
		rt (basic_wr_int)from_chars(First, Last, Base);
	}
	st ce a from_str(std::string_view Str, i Base = 10
	) {
		rt (basic_wr_int)from_chars(Str, Base);
	}
	ce dt(a) as_int(th a c & self) { rt fw(self.value); }

	st ce a to_string(basic_wr_int wr) {
		rt ::std::to_string(wr.value);
	}
	ce a to_string(th basic_wr_int self) {
		rt to_string(self);
	}
	ce op ::std::string(th basic_wr_int self) {
		rt to_string(self);
	}
#define MLibBasicWrIntegerOp(op) \
ce dt(a) op##op##(th a && self, value_type right) { \
	self.value op right; rt fw(self); \
}
	MLibBasicWrIntegerOp(+=)
	MLibBasicWrIntegerOp(-=)
	MLibBasicWrIntegerOp(*=)
	MLibBasicWrIntegerOp(/=)
	MLibBasicWrIntegerOp(%=)
	MLibBasicWrIntegerOp(&=)
	MLibBasicWrIntegerOp(|=)
	MLibBasicWrIntegerOp(^=)
	MLibBasicWrIntegerOp(<<=)
	MLibBasicWrIntegerOp(>>=)
	

	ce dt(a) op++(th a && self) {
		++self.value; rt fw(self);
	}
	ce dt(a) op++(th a && self, i) {
		rt basic_wr_int(++self.value);
	}
	ce dt(a) op--(th a && self) {
		--self.value; rt fw(self);
	}
	ce dt(a) op--(th a && self, i) {
		rt basic_wr_int(--self.value);
	}


};

class wr_wchar {
public:
	using value_type = wchar_t;

	value_type value;

	ce a & unwrap(th a && self) {
		rt self.value;
	}

	st ce a to_ascii(value_type input) {
		rt value_type(input & 0x7f);
	}
	ce dt(a) to_ascii(th a && self) {
		self.value &= 0x7f; rt fw(self);
	}

	st ce a to_lower(value_type input) {
		st ce wchar_t diff = L'a' - L'A';
		if (input >= L'A' && input <= L'Z') rt input + diff;
		rt input;
	}
	ce dt(a) to_lower(th a && self) {
		self = to_lower(self.value);
		rt fw(self);
	}

	st ce a to_upper(value_type input) {
		st ce wchar_t diff = L'A' - L'z';
		if (input >= L'a' && input <= L'z') rt input + diff;
		rt input;
	}
	ce wr_wchar & to_upper() {
		if (value >= 'a' && value <= 'z') value += ('A' - 'a');
		rt *th;
	}

	st ce bl is_alpha(c a & input) {
		rt (input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z');
	}
	ce bl is_alpha() c {
		rt (value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z');
	}

	st ce bl is_digit(c a & input) {
		rt (input >= '0' && input <= '9');
	}
	ce bl is_digit() c {
		rt (value >= '0' && value <= '9');
	}

};


class wr_float {
public:
	union {
		float Float;
		ui32 UInt;
		struct {
			ui32 Frac : 23, Expo : 8, Sign : 1;
		};
	};
	ce wr_float(float Float) : Float(Float) {}


	a op^(th wr_float left, wr_float right) c {
		rt builtin::powf(Float, right.Float);
	}

	ce ui32 fraction() c {
		rt Frac;
	}
	ce ui32 exponent() c {
		rt Expo;
	}
	ce bl sign() c {
		rt Sign;
	}

	ce op float() {
		rt Float;
	}

};


using wr_int8 = basic_wr_int<::int8_t>;
using wr_uint8 = basic_wr_int<::uint8_t>;
using wr_int16 = basic_wr_int<::int16_t>;
using wr_uint16 = basic_wr_int<::uint16_t>;
using wr_int32 = basic_wr_int<::int32_t>;
using wr_uint32 = basic_wr_int<::uint32_t>;
using wr_int64 = basic_wr_int<::int64_t>;
using wr_uint64 = basic_wr_int<::uint64_t>;

}

#include "undef_short_macros.hpp"