#ifndef MLib_Data 20241028L
#define MLib_Data

#include <cstdint>
#include <cmath>
#include <utility>
#include <stdexcept>

namespace mlib {


using tchar =
#if UNICODE
wchar_t
#else
char
#endif
;
using byte = ::std::uint8_t;
using word = ::std::uint16_t;
using dword = ::std::uint32_t;
using qword = ::std::uint64_t;


template <class Type>
class ref_ptr {
public:
	union {
		Type & Ref;
		Type * Ptr;
	};
	constexpr ref_ptr(Type & ref) :
		Ref(ref) {}
	constexpr ref_ptr(Type * ptr) :
		Ptr(ptr) {}
};

template<::std::size_t Size>
	requires(Size <= 8)
class bits {
public:
	using unsigned_type = ::std::make_unsigned_t<Size>;

	unsigned_type Data;

	constexpr auto operator[](::std::size_t index) -> bool {
		return Data & (unsigned_type(1) << index);
	}
	constexpr auto set(::std::size_t index, bool value) -> bits & {
		auto target_bit = (unsigned_type(1) << index);
		if ((Data & target_bit) != value) {
			if (value) { Data ^= target_bit; }
			else { Data &= ~target_bit; }
		}
		return *this;
	}
};

template <::std::size_t Size>
	requires(Size > 8)
class bits {
public:
	unsigned char Data[Size / 8];

	constexpr auto get(::std::size_t index) -> bool {
		return Data[index / 8] & ((unsigned char(1) << index) % 8);
	}
	constexpr auto set(::std::size_t index, bool value) -> bits & {
		auto target_bit = ((unsigned char(1) << index) % 8);
		auto & target_address = Data[index / 8];
		if ((target_address & target_bit) != value) {
			if (value) { target_address ^= target_bit; }
			else { target_address &= ~target_bit; }
		}
		return *this;
	}
};

class bit_ptr {
public:
	bits<8> * Ptr;
	::uint8_t Offset;

	bit_ptr & operator=(bool input) {
		Ptr->set(Offset, input);
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

class range_from_data_and_size {
public:
	constexpr auto begin(this auto && self) {
		return self.data();
	}
	constexpr auto end(this auto && self) {
		return self.data() + self.size();
	}
	constexpr auto operator[](this auto && self, ::std::integral auto offset) {
		return self.data()[offset];
	}
};

template <typename Type, typename SizeType>
class sized_ptr;
template <typename Type, typename SizeType, typename OffsetType = SizeType>
class offset_sized_ptr;

template <typename Type, typename SizeType>
class sized_ptr : public range_from_data_and_size {
public:
	using data_type = Type;
	using size_type = SizeType;
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
		return offset_sized_ptr_type(self.Data, self.Size, offset);
	}
	constexpr auto operator-(this const auto && self, ::std::intptr_t offset) {
		return offset_sized_ptr_type(self.Data, self.Size, -offset);
	}


};

template <typename Type, typename SizeType>
class offset_sized_ptr : public range_from_data_and_size {
public:
	using data_type = Type;
	using size_type = SizeType;
	using offset_type = ::std::make_signed_t<SizeType>;
	using sized_ptr_type = sized_ptr_type<data_type, size_type>;

private:
	sized_ptr_type * SizedPtr;
	offset_type Offset;

public:
	constexpr auto data(this auto && self) {
		return self.Pointer + self.Offset;
	}
	constexpr auto size(this const auto && self) {
		return self.Size;
	}

	constexpr auto here(this auto && self) {
		return self.Pointer;
	}

	constexpr auto get_origin(this const auto && self) const -> sized_ptr_type {
		return sized_ptr_type(self.data(), self.Size);
	}

};


}

#endif