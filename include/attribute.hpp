// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLibHeader_AttributeHpp
#define MLibHeader_AttributeHpp 20241108L
#include <map>
#include <string>
#include "types.hpp"
#include "short_types.hpp"
#include "macros/normal.hpp"

namespace mlib {

// template <class Type>
struct attribute {
	using value_type = double;

	struct modifier {
		value_type Value;
		enum class op_t : u8
		{ none, add_base, add_multiplied_base, multiply_total } Op;
		bool IsEnabled = true;

		constexpr modifier
		( value_type _value = (0),
			op_t _op = op_t::none,
			bool _is_enabled = true)
		: Value(_value), Op(_op), IsEnabled(_is_enabled) {}

	};

	static const value_type DefaultBase;
	value_type Base;

	struct Modifiers : private ::std::map<std::string_view, modifier> {
		using map_type = ::std::map<std::string_view, modifier>;
		
		bool IsChanged = false;

		enum successful : u8
		{ fail = 0, unchanged = 1, success = 2 };
		using map_type::empty;
		[[nodiscard]] decltype(auto) operator[](auto && ... _value) const &
		{ return operator[](Forward(_value)...); };
		[[nodiscard]] auto begin() { return cbegin(); }
		[[nodiscard]] auto end() { return cend(); }
		successful set_value
		(std::string_view const& _key, attribute::value_type _value) {
			auto _it = find(_key);
			if (_it == end()) [[unlikely]] return fail;
			else if (_it->second.Value == _value) [[unlikely]] return unchanged;
			else { _it->second.Value = _value; IsChanged = true; return success; }
		}
		successful set_enabled
		(std::string_view const& _key, bool _enabled) {
			auto _it = find(_key);
			if (_it == end()) [[unlikely]] return fail;
			else if (_it->second.IsEnabled == _enabled) [[unlikely]] return unchanged;
			else { _it->second.IsEnabled = _enabled; IsChanged = true; return success; }
		}
		successful set_type
		(std::string_view const& _key, modifier::op_t _op) {
			auto _it = find(_key);
			if (_it == end()) [[unlikely]] return fail;
			else if (_it->second.Op == _op) [[unlikely]] return unchanged;
			else { _it->second.Op = _op; IsChanged = true; return success; }
		}
		bool add(value_type const& _input) {
			if (insert(_input).second) { IsChanged = true; return true;}
			else return false;
		}
			
		bool add(auto && ... _input)
		requires requires { value_type{::std::forward<decltype(_input)>(_input)...}; } {
			if (insert(Forward(_input)...).second) { IsChanged = true; return true;}
			else return false;
		}

	} Modifiers;
	value_type ResultCache;


	void do_cache() {
		if (Modifiers.empty()) { ResultCache = Base; }
		else {
			value_type
				_add_base{0.0},
				_add_multiplied_base{0.0},
				_multiply_total{0.0};

			for (auto const& _pair : Modifiers) {
				auto const& _modifier = _pair.second;
				if (_modifier.IsEnabled) switch (_modifier.Op) {
				using _op = modifier::op_t;
				case _op::add_base:
				_add_base += _modifier.Value; break;
				case _op::add_multiplied_base:
				_add_multiplied_base += _modifier.Value; break;
				case _op::multiply_total:
				_multiply_total += _modifier.Value; break;
				default: break;
				}
			}
			ResultCache = (Base + _add_base + Base * _add_multiplied_base) * _multiply_total;
		}
		Modifiers.IsChanged = false;
	}

	value_type get() {
		if (Modifiers.IsChanged) do_cache();
		return ResultCache;
	}

	value_type operator*() { return get(); }
};


}

#endif