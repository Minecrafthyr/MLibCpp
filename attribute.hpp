#ifndef MLib_Attribute
#define MLib_Attribute 20241028L
#include <cstdint>
#include <map>
#include <string>
#include "concepts.hpp"
#include "macros.hpp"

#include "short_macros.hpp"

namespace mlib {

// template <class Type>
class attribute {
pub:
	using value_type = double;

	class modifier {
	pub:
		value_type Val;
		enum class op_t : ::std::uint8_t {
			none, add_base, add_multiplied_base, multiply_total
		} Op;
		bl IsEnabled = t;

		ce modifier(
			value_type Value = value_type(0),
			op_t Op = op_t::none,
			bl IsEnabled = t) :
			Val(Value), Op(Op), IsEnabled(IsEnabled) {}

	};

	st c value_type DefaultBase;
	value_type Base;

	class modifiers : pri ::std::map<std::string_view, modifier> {
	pub:
		using map_type = ::std::map<std::string_view, modifier>;
		using map_value_type = map_type::value_type;
		
	pub:
		bl IsChanged = f;

		enum successful : ::std::uint8_t {
			fail = 0,
			unchanged = 1,
			success = 2
		};
		using map_type::empty;
		[[nodiscard]]
		dt(a) op[](a && ... Val) const & { rt op[](fw(Val)...) };
		[[nodiscard]]
		a begin() { rt cbegin(); }
		[[nodiscard]]
		a end() { rt cend(); }
		successful set_value(c std::string_view & key, value_type value) {
			a iter = Map.find(key);
			if (iter == Map.end()) [[unlikely]] rt fail;
			else if (iter->second.Val == value) [[unlikely]] rt unchanged;
			else { iter->second.Val = value; IsChanged = t; rt success; }
		}
		successful set_enabled(c std::string_view & key, bl enabled) {
			a iter = Map.find(key);
			if (iter == Map.end()) [[unlikely]] rt fail;
			else if (iter->second.IsEnabled == enabled) [[unlikely]] rt unchanged;
			else { iter->second.IsEnabled = enabled; IsChanged = t; rt success; }
		}
		successful set_type(c std::string_view & key, modifier::op_t operation) {
			a iter = Map.find(key);
			if (iter == Map.end()) [[unlikely]] rt fail;
			else if (iter->second.Op == operation) [[unlikely]] rt unchanged;
			else { iter->second.Op = operation; IsChanged = t; rt success; }
		}
		bl add(c map_value_type & input) {
			if (Map.insert(input).second)
				IsChanged = t, rt t;
			else rt f;
		}
			
		bl add(auto && ... input) rq rq { map_value_type{fw(input)...}; } {
			if (Map.insert(fw(input)...).second)
				IsChanged = t, rt t;
			else rt f;
		}

	} modifiers;
	value_type result_cache;


	void do_cache() {
		if (modifiers.empty()) { result_cache = Base; }
		else {
			value_type
				add_base{0.0},
				add_multiplied_base{0.0},
				multiply_total{0.0};

			for (c a & pair : modifiers) {
				c a & _modifier = pair.second;
				if (_modifier.IsEnabled) switch (_modifier.Op) {
					using _op = modifier::op_t;
				case _op::add_base: add_base += _modifier.value; break;
				case _op::add_multiplied_base: add_multiplied_base += _modifier.value; break;
				case _op::multiply_total: multiply_total += _modifier.value; break;
				default: break;
				}
			}
			result_cache = (Base + add_base + Base * add_multiplied_base) * multiply_total;
		}
		modifiers.IsChanged = f;
	}

	value_type get() {
		if (modifiers.IsChanged) do_cache();
		rt result_cache;
	}

	value_type op*() {
		rt get();
	}
};


}

#include "undef_short_macros.hpp"

#endif