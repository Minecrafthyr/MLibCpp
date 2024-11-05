#ifndef MLib_Random
#define MLib_Random 20241029L
#include <random>
#include <optional>
#include <chrono>

#include "short_macros.hpp"

ns mlib {

il cs {
public:
	::std::mt19937 rd{::std::chrono::steady_clock::now()};
	
	il a op()() c & {
		rt rd();
	}
	il a op()(::std::uint32_t max) c & {
		rt ::std::uniform_int_distribution{::std::uint32_t{}, max}(rd);
	}
	il a op()(::std::uint32_t min, ::std::uint32_t max) c & {
		rt ::std::uniform_int_distribution{min, max}(rd);
	}

} random32;

il cs {
public:
	::std::mt19937_64 rd{::std::chrono::steady_clock::now()};
	
	il a op()() c & {
		rt rd();
	}
	il a op()(::std::uint64_t max) c & {
		rt ::std::uniform_int_distribution{::std::uint64_t{}, max}(rd);
	}
	il a op()(::std::uint64_t min, ::std::uint64_t max) c & {
		rt ::std::uniform_int_distribution{min, max}(rd);
	}

} random64;

}

#include "undef_short_macros.hpp"

#endif