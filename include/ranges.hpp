// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLib_Ranges
#define MLib_Ranges 20241112L

#include <ranges>
#include "types.hpp"
#include "pair.hpp"

namespace mlib
{
namespace ranges = ::std::ranges;
namespace views = ::std::views;

MLibDuplicate data = ranges::data;
MLibDuplicate size = ranges::size;
MLibDuplicate begin = ranges::begin;
MLibDuplicate end = ranges::end;


template <typename T, typename T2>
struct in_data_t : public forward_pair<T, T2> {};
constexpr struct in_t {
	[[gnu::always_inline]]
	constexpr auto operator()(auto && _a, auto && _b) const & {
    return in_data_t{MLibForward(_a), MLibForward(_b)};
  }
} in;
template <typename T, typename T2>
[[gnu::always_inline]]
constexpr auto operator|(auto const & _value, in_data_t<T, T2> && _data) {
  return _value >= _data.first && _value <= _data.second;
}

template <typename T, typename T2>
struct out_data_t : public forward_pair<T, T2> {};
constexpr struct out_t {
	[[gnu::always_inline]]
	constexpr auto operator()(auto && _a, auto && _b) const & {
    return out_data_t(MLibForward(_a), MLibForward(_b));
  }
} out;
template <typename T, typename T2>
[[gnu::always_inline]]
constexpr auto operator|(auto const & _value, out_data_t<T, T2> && _data) {
  return _value < _data.first || _value > _data.second;
}


template <typename T>
struct value_range;

template <::std::integral T>
struct value_range<T> {
  using value_type = T;
  value_type Begin, End;
  
  constexpr index_range(value_type _end)
  : Begin(0), End(_end) {}
  constexpr index_range(value_type _begin, value_type _end)
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
    index_range * Range;
    value_type Current;

    constexpr iterator(index_range & Range, value_type Current = value_type{})
    : Range(&Range), Current(Current) {}
    
    [[nodiscard, gnu::always_inline]]
    constexpr auto operator*(this auto && self) { return self.Current; }
    
    constexpr inline void test_with(this auto const & self, value_type offset) {
      if constexpr (::std::__is_constant_evaluated() || _DEBUG)
        if (self.Range->inside_with(self.Current + offset)) {}
      else { throw; }
    }
    [[gnu::always_inline]]
    constexpr auto operator+(this const auto & self, value_type offset) {
      test_with(offset);
      return iterator(*self.Range, self.Current + offset);
    }
    [[gnu::always_inline]]
    constexpr auto operator-(this const auto & self, value_type offset) {
      test_with(-offset);
      return iterator(*self.Range, self.Current - offset);
    }
    [[gnu::always_inline]]
    constexpr auto operator++(this auto & self) -> decltype(auto) {
      test_with(1);
      ++self.Current;
      return self;
    }
    [[gnu::always_inline]]
    constexpr auto operator--(this auto & self) -> decltype(auto) {
      test_with(-1);
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
  constexpr iterator_range(value_type _begin, value_type _end)
  : Begin(_begin), End(_end) {}
  
  constexpr auto begin() -> const auto & { return Begin; }
  constexpr auto end() -> const auto & { return End; }
};


template <typename T>
struct range;

template <::std::integral T>
struct range<T> : index_range<T> {};
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


template <typename T, T MinValue, typename Fn>
struct limited_min {
  using value_type = T;


};


}


#endif