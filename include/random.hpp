// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLib_Random
#define MLib_Random 20241029L
#include <random>
#include <optional>
#include <chrono>

#include "short_macros.hpp"

namespace mlib {

inline struct {
	::std::mt19937 Random{::std::chrono::steady_clock::now().time_since_epoch().count()};
	
	inline auto operator()() & {
		return Random();
	}
	inline auto operator()(::std::uint32_t _max) & {
		return ::std::uniform_int_distribution{::std::uint32_t{}, _max}(Random);
	}
	inline auto operator()(::std::uint32_t _min, ::std::uint32_t _max) & {
		return ::std::uniform_int_distribution{_min, _max}(Random);
	}

} random32;

inline struct {
	::std::mt19937_64 Random{::std::chrono::steady_clock::now().time_since_epoch().count()};
	
	inline auto operator()() & {
		return Random();
	}
	inline auto operator()(::std::uint64_t _max) & {
		return ::std::uniform_int_distribution{::std::uint64_t{}, _max}(Random);
	}
	inline auto operator()(::std::uint64_t _min, ::std::uint64_t _max) & {
		return ::std::uniform_int_distribution{_min, _max}(Random);
	}

} random64;

}

#include "undef_short_macros.hpp"

#endif