#ifndef MLib_Timer
#define MLib_Timer 20241103L

#include <cstdint>
#include <array>
#include <chrono>
#include <print>
#include <sstream>

#include "format.hpp"

namespace mlib {


class timer {
public:
	using clock_type = ::std::chrono::system_clock;

	clock_type::time_point TimePoint;

	timer() : TimePoint(clock_type::now()) {}
	~timer() {
		::std::print("\nTimer : {}\n", (clock_type::now() - TimePoint).count());
	}

};

template <::std::size_t N> requires (N > 1)
class timers {
public:

	using clock_type = ::std::chrono::system_clock;
	using duration = ::std::chrono::duration<double>;

public:
	static constexpr ::std::size_t Size = N;
	::std::array<clock_type::time_point, Size> Data{};
	::std::size_t Current = 0;


	void enable() {
		Data[Current] = clock_type::now();
		Current++;
	}

	~timers() {
		clock_type::time_point Now = clock_type::now(), & Begin = Data.front();
		clock_type::duration Prev, FromBegin;

		Prev = (Data[1] - Begin);
		std::stringstream Tmp;

		Tmp <<
R"(
== Timers == (100ns a tick)
{} -> {}
[1] +{}({})
)"_fmt(Begin, Now, Prev.count(), duration(Prev));

		for (::std::size_t I = 2; I != Size; ++I) {
			Prev = (Data[I] - Data[I - 1]);
			FromBegin = (Data[I] - Begin);
			Tmp << "[{}] +{}({})  begin+{}({})\n"_fmt(I, Prev.count(), duration(Prev), FromBegin.count(), duration(FromBegin));
		}
		Prev = (Now - Data.back());
		FromBegin = (Now - Begin);
		Tmp << "last: +{}({})  begin+{}({})\n"_fmt(Prev.count(), duration(Prev), FromBegin.count(), duration(FromBegin));

		::std::vprint_nonunicode(Tmp.view(), ::std::format_args{});
	}
};



}