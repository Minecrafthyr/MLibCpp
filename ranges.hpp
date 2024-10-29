#ifndef MLib_Ranges
#define MLib_Ranges 20241029L

#include <ranges>
#include "concepts.hpp"


namespace mlib {

namespace std_r {
using namespace ::std::ranges;
}

inline constexpr decltype(auto) data = std_r::data;
inline constexpr decltype(auto) size = std_r::size;
inline constexpr decltype(auto) begin = std_r::begin;
inline constexpr decltype(auto) end = std_r::end;


template <::std::integral OffsetType>
class index_range {
public:
  using offset_type = OffsetType;
  offset_type Begin, End;
  
  constexpr index_range(offset_type End) :
    Begin(0), End(End) {}
  constexpr index_range(offset_type Begin, offset_type End) :
    Begin(Begin), End(End) {}

  /// @brief Check is `offset` inside this range. [Begin, End]
  /// @param self
  /// @param offset
  [[gnu::always_inline]] constexpr auto is_value_inside(
    this auto && self, offset_type offset) {
    return self.Range->Begin <= offset && offset <= self.Range->End;
  }
  /// @brief Check is `offset` valid on dereference with this range. [Begin, End)
  /// @param self 
  /// @param offset
  [[gnu::always_inline]] constexpr auto is_value_deref(
    this auto && self, offset_type offset) {
    return self.Range->Begin <= offset && offset < self.Range->End;
  }
  
  class iterator {
  public:
    index_range * Range;
    offset_type Cur;
    constexpr iterator(index_range & Range, offset_type Cur = offset_type(0)) :
      Range(&Range), Cur(Cur) {}
    
    [[nodiscard, gnu::always_inline]] constexpr auto operator*(this auto && self) { return self.Cur; }
    
    [[gnu::always_inline]] constexpr auto operator+(this const auto & self, offset_type offset) {
      if constexpr (consteval || _DEBUG)
        if (self.Range->as_inside(self.Cur + offset)) {}
        else { throw; }
      return iterator(*self.Range, self.Cur + offset);
    }
    [[gnu::always_inline]] constexpr auto operator-(this const auto & self, offset_type offset) {
      if constexpr (consteval || _DEBUG)
        if (self.Range->as_inside(self.Cur + offset)) {}
        else { throw; }
      return iterator(*self.Range, self.Cur - offset);
    }

    [[gnu::always_inline]] constexpr auto operator++(this auto & self) -> dc(auto) {
      self - 1;
      ++self.Cur; return self;
    }
    [[gnu::always_inline]] constexpr auto operator--(this auto & self) -> dct(auto) {
      self - 1;
      --self.Cur; return self;
    }
    
  };


  constexpr auto begin(this const auto && self) { return iterator(self); }
  constexpr auto end(this const auto && self) { return iterator(self, self.End); }

};

template <typename Type, Type MinValue, typename Fn>
class limited_min {
public:
  using value_type = Type;


}


}

#endif