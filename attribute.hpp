#pragma once

#include <cstdint>
#include <map>
#include <string>
#include "concepts.hpp"
#include "macros.hpp"

namespace mlib {

// template <class Type>
class attribute {
public:
	using value_type = double;

	class modifier {
	public:
		value_type value;
		enum class op_t : ::std::uint8_t {
			none, add_base, add_multiplied_base, multiply_total
		} operation;
		bool is_enabled = true;

		constexpr modifier(
			value_type value = value_type(0),
			op_t operation = op_t::none,
			bool is_enabled = true) :
			value(value), operation(operation), is_enabled(is_enabled) {}

	};

	static const value_type DefaultBase;
	value_type Base;

	class modifiers_t {
	public:
		using map_type = ::std::map<std::string_view, modifier>;

	private:
		map_type map_v;
		
	public:
		bool is_changed_v = false;

		enum successful : ::std::uint8_t {
			fail = 0,
			unchanged = 1,
			success = 2
		};

		[[nodiscard]] bool empty() const noexcept {
			return map_v.empty();
		}
		[[nodiscard]] decltype(auto) begin() noexcept {
			return map_v.begin();
		}
		[[nodiscard]] decltype(auto) end() noexcept {
			return map_v.end();
		}
		[[nodiscard]] decltype(auto) operator[](auto && ... key) {
			return map_v[MLibForward(key)...];
		}

		successful set_value(const std::string_view & key, value_type value) {
			auto iterator = map_v.find(key);
			if (iterator == map_v.end()) [[unlikely]] return fail;
			else if (iterator->second.value == value) [[unlikely]] return unchanged;
			else { iterator->second.value = value; is_changed_v = true; return success; }
		}
		successful set_enabled(const std::string_view & key, bool enabled) {
			auto iterator = map_v.find(key);
			if (iterator == map_v.end()) [[unlikely]] return fail;
			else if (iterator->second.is_enabled == enabled) [[unlikely]] return unchanged;
			else { iterator->second.is_enabled = enabled; is_changed_v = true; return success; }
		}
		successful set_type(const std::string_view & key, modifier::op_t operation) {
			auto iterator = map_v.find(key);
			if (iterator == map_v.end()) [[unlikely]] return fail;
			else if (iterator->second.operation == operation) [[unlikely]] return unchanged;
			else { iterator->second.operation = operation; is_changed_v = true; return success; }
		}
		bool add(const map_type::value_type & input) {
			if (map_v.insert(input).second) {
				is_changed_v = true;
				return true;
			}
			else return false;
		}
		template <class ... ValType>
			requires (::std::constructible_from<map_type::value_type, ValType ...>)
		bool add(ValType && ... input) {
			if (map_v.insert(::std::forward<ValType>(input)...).second) {
				is_changed_v = true;
				return true;
			}
			else return false;
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

			for (const auto & pair : modifiers) {
				const auto & _modifier = pair.second;
				if (_modifier.is_enabled) switch (_modifier.operation) {
					using _op = modifier::op_t;
				case _op::add_base: add_base += _modifier.value; break;
				case _op::add_multiplied_base: add_multiplied_base += _modifier.value; break;
				case _op::multiply_total: multiply_total += _modifier.value; break;
				default: break;
				}
			}
			result_cache = (Base + add_base + Base * add_multiplied_base) * multiply_total;
		}
		modifiers.is_changed_v = false;
	}

	value_type get() {
		if (modifiers.is_changed_v) do_cache();
		return result_cache;
	}

	value_type operator*() {
		return get();
	}
	operator value_type() {
		return get();
	}
};


}
