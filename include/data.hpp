// Copyright © 2024 Minecraft_hyr - MIT License
// Core Header
#ifndef MLibHeader_DataHpp 20241028L
#define MLibHeader_DataHpp

#include <cmath>
#include <utility>
#include <stdexcept>
#include <variant>

#include "types.hpp"
#include "ranges.hpp"


namespace mlib {


template <typename T>
struct ref_ptr {
	T * Ptr;
	
	constexpr ref_ptr(T & _ref) :
		Ptr(&_ref) {}
	constexpr ref_ptr(T * _ptr) :
		Ptr(_ptr) {}
	constexpr T & ref() { return Ptr; }
	constexpr T & operator*(this auto && self) { return self.Ref; }
};


template <::std::size_t N>
struct byte_bits {
	static constexpr auto Size = N;
	static constexpr auto BitsSize = N * 8;
	::std::uint8_t Data[Size];

	constexpr auto get(::std::size_t _index) -> bool {
		return Data[_index / 8] & ((::std::uint8_t(1) << _index) % 8);
	}
	constexpr auto set(::std::size_t _index, bool _value) -> byte_bits & {
		auto Bit = ((::std::uint8_t(1) << _index) % 8);
		auto & Target = Data[_index / 8];
		if ((Target & Bit) != _value) {
			if (_value) { Target ^= Bit; }
			else { Target &= ~Bit; }
		}
		return *this;
	}
};


struct bit_ptr {

	byte_bits<1> * Ptr;
	::uint8_t Offset;

	bit_ptr & operator=(bool _input) {
		Ptr->set(Offset, _input);
		return *this;
	}
	constexpr bit_ptr & operator++() {
		if (++Offset > 7) { Offset = 0; ++Ptr; }
		return *this;
	}
	constexpr bit_ptr & operator--() {
		if (--Offset > 7) { Offset = 7; --Ptr; }
		return *this;
	}
};

struct range_from_data_and_size {
	constexpr auto begin(this auto && self) {
		return self.data();
	}
	constexpr auto end(this auto && self) {
		return self.data() + self.size();
	}
	constexpr auto operator[](this auto && self, Integral auto offset) {
		return self.data()[offset];
	}
};

template <typename T, typename SizeT>
struct sized_ptr;
template <typename T, typename SizeT, typename OffsetT = SizeT>
struct offset_sized_ptr;

template <typename T, typename SizeT>
struct sized_ptr : public range_from_data_and_size {
	using data_type = T;
	using size_type = SizeT;
	using offset_sized_ptr_type = offset_sized_ptr<data_type, size_type>;

private:
	data_type * Data = nullptr;
	size_type Size = 0;

public:
	constexpr sized_ptr() {}
	constexpr sized_ptr(data_type * data) :
		Data(data) {}
	constexpr sized_ptr(data_type * data, ::std::size_t size) :
		Data(data), Size(size) {}
	template <typename InputType>
	constexpr sized_ptr(const InputType & input) :
		Data(::std::ranges::data(input)), Size(::std::ranges::size(input)) {}

	constexpr auto data(this auto && self) -> auto * {
		return self.Data;
	}
	constexpr auto size(this const auto && self) -> size_type {
		return self.Size;
	}
	constexpr auto operator+(this const auto && self, ::std::intptr_t offset) {
		offset_sized_ptr_type(self.Data, self.Size, offset);
	}
	constexpr auto operator-(this const auto && self, ::std::intptr_t offset) {
		offset_sized_ptr_type(self.Data, self.Size, -offset);
	}


};

template <typename T, typename SizeT, typename OffsetT>
struct offset_sized_ptr : public range_from_data_and_size {
	using data_type = T;
	using size_type = SizeT;
	using offset_type = ::std::make_signed_t<SizeT>;
	using sized_ptr_type = sized_ptr<data_type, size_type>;

private:
	sized_ptr_type * SizedPtr;
	offset_type Offset;
	size_type Size;

public:
	constexpr auto data(this auto && self) { return self.SizedPtr + self.Offset; }
	constexpr auto size(this const auto && self) { return self.Size; }

	constexpr auto here(this auto && self) { return self.SizedPtr; }
	constexpr auto get_origin(this const auto && self) {
		return sized_ptr_type(self.data(), self.Size);
	}

};

}

#endif