// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLibHeader_RangesHpp
#define MLibHeader_RangesHpp 20241121

#include <ranges>
#include "types.hpp"
#include "pair.hpp"

namespace mlib {
namespace ranges = ::std::ranges;
namespace views = ::std::views;

inline constexpr decltype(auto) data = ranges::data;
inline constexpr decltype(auto) size = ranges::size;
inline constexpr decltype(auto) begin = ranges::begin;
inline constexpr decltype(auto) end = ranges::end;


template <typename T, typename T2>
struct in_data_t : public forward_pair<T, T2> {
  constexpr in_data_t(T && _first, T2 && _second)
  : forward_pair<T, T2>(::std::forward<T>(_first), ::std::forward<T2>(_second)) {}
};
inline constexpr struct in_t {
	[[nodiscard, gnu::always_inline]]
	constexpr auto operator()(auto && _a, auto && _b) const&
  { return in_data_t(::std::forward<decltype(_a)>(_a), ::std::forward<decltype(_b)>(_b)); }
} in;
template <typename T, typename T2>
[[nodiscard, gnu::always_inline]]
inline constexpr auto operator|(auto const& _value, in_data_t<T, T2> _data)
{ return _value >= _data.first && _value <= _data.second; }

template <typename T, typename T2>
struct out_data_t : public forward_pair<T, T2> {
  constexpr out_data_t(T && _first, T2 && _second)
  : forward_pair<T, T2>(::std::forward<T>(_first), ::std::forward<T2>(_second)) {}
};
inline constexpr struct out_t {
	[[nodiscard, gnu::always_inline]]
	constexpr auto operator()(auto && _a, auto && _b) const&
  { return out_data_t(Forward(_a), Forward(_b)); }
} out;
template <typename T, typename T2>
[[nodiscard, gnu::always_inline]]
inline constexpr auto operator|(auto const& _value, out_data_t<T, T2> _data)
{ return _value < _data.first || _value > _data.second; }


template <typename T>
struct value_range;

template <::std::integral T>
struct value_range<T> {
  using value_type = T;
  value_type Begin, End;
  
  constexpr value_range(value_type _end)
  : Begin(0), End(_end) {}
  constexpr value_range(value_type _begin, value_type _end)
  : Begin(_begin), End(_end) {}

  /// @brief Check is `offset` inside this range. [Begin, End]
  /// @param self
  /// @param offset
  [[gnu::always_inline]]
  constexpr auto inside_with(this auto && self, value_type _offset)
  { return self.Range->Begin <= _offset && _offset <= self.Range->End; }
  /// @brief Check is `offset` valid on dereference with this range. [Begin, End)
  /// @param self 
  /// @param offset
  [[gnu::always_inline]]
  constexpr auto valid_with(this auto && self, value_type _offset)
  { return self.Range->Begin <= _offset && _offset < self.Range->End; }
  
  struct iterator {
    value_range * Range;
    value_type Current;

    constexpr iterator(value_range & Range, value_type Current = value_type{})
    : Range(&Range), Current(Current) {}
    
    [[nodiscard, gnu::always_inline]]
    constexpr auto operator*(this auto && self) { return self.Current; }
    
    constexpr inline void test_with(this auto const & self, value_type offset) {
      if constexpr (::std::__is_constant_evaluated() || _DEBUG)
      { if (self.Range->inside_with(self.Current + offset)) {} }
      else throw ::std::out_of_range("::mlib::value_range::iterator::test_with(self, offset)");
    }
    [[gnu::always_inline]]
    constexpr auto operator+(this const auto & self, value_type offset) {
      self.test_with(offset);
      return iterator(*self.Range, self.Current + offset);
    }
    [[gnu::always_inline]]
    constexpr auto operator-(this const auto & self, value_type offset) {
      self.test_with(-offset);
      return iterator(*self.Range, self.Current - offset);
    }
    [[gnu::always_inline]]
    constexpr auto operator++(this auto & self) -> decltype(auto) {
      self.test_with(1);
      ++self.Current;
      return self;
    }
    [[gnu::always_inline]]
    constexpr auto operator--(this auto & self) -> decltype(auto) {
      self.test_with(-1);
      --self.Current;
      return self;
    }
    
  };

  constexpr auto begin(this const auto && self) { return iterator(self); }
  constexpr auto end(this const auto && self) { return iterator(self, self.End); }
};

template <Iterator T>
struct value_range<T>
{
public:
  using value_type = T;
  value_type Begin, End;
  constexpr value_range(value_type _begin, value_type _end)
  : Begin(_begin), End(_end) {}
  
  constexpr auto begin() -> const auto & { return Begin; }
  constexpr auto end() -> const auto & { return End; }
};


template <typename T>
struct range;

template <::std::integral T>
struct range<T> : value_range<T> {};
template <ranges::range T>
struct range<T> {
  using value_type = T;
  value_type Value;

  constexpr range(value_type & _value)
  : Value(_value) {}
  constexpr range(value_type && _value)
  : Value(::std::move(_value)) {}

  constexpr auto begin() -> const auto & { return begin(Value); }
  constexpr auto end() -> const auto & { return end(Value); }
};

template <typename T>
range(T &) -> range<T &>;
template <typename T>
range(T &&) -> range<T &&>;

}


#endif