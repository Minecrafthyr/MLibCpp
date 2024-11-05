#ifndef MLib_Ranges
#define MLib_Ranges 20241101L

#include <ranges>
#include "concepts.hpp"

#include "short_macros.hpp"

ns mlib {
ns ranges = ::std::ranges;

il ce dt(a) data = ranges::data;
il ce dt(a) size = ranges::size;
il ce dt(a) begin = ranges::begin;
il ce dt(a) end = ranges::end;


tp <::std::integral OffsetType>
cs index_range {
public:
  using offset_type = OffsetType;
  offset_type Begin, End;
  
  ce index_range(offset_type End) :
    Begin(0), End(End) {}
  ce index_range(offset_type Begin, offset_type End) :
    Begin(Begin), End(End) {}

  /// @brief Check is `offset` inside this range. [Begin, End]
  /// @param self
  /// @param offset
  [[gnu::always_inline]]
  ce a is_value_inside(th a && self, offset_type offset) {
    rt self.Range->Begin <= offset && offset <= self.Range->End;
  }
  /// @brief Check is `offset` valid on dereference with th range. [Begin, End)
  /// @param self 
  /// @param offset
  [[gnu::always_inline]]
  ce a is_value_deref(th a && self, offset_type offset) {
    rt self.Range->Begin <= offset && offset < self.Range->End;
  }
  
  class iterator {
  public:
    index_range * Range;
    offset_type Cur;
    ce iterator(index_range & Range, offset_type Cur = offset_type(0)) :
      Range(&Range), Cur(Cur) {}
    
    [[nodiscard, gnu::always_inline]]
    ce a operator*(th a && self) { rt self.Cur; }
    
    [[gnu::always_inline]]
    ce a operator+(th c a & self, offset_type offset) {
      if ce (::std::__is_constant_evaluated() || _DEBUG)
        if (self.Range->as_inside(self.Cur + offset)) {}
        else { throw; }
      rt iterator(*self.Range, self.Cur + offset);
    }
    [[gnu::always_inline]]
    ce a operator-(th c a & self, offset_type offset) {
      if ce (::std::__is_constant_evaluated() || _DEBUG)
        if (self.Range->as_inside(self.Cur + offset)) {}
        else { throw; }
      rt iterator(*self.Range, self.Cur - offset);
    }

    [[gnu::always_inline]]
    ce a operator++(th a & self) -> dt(a) {
      self - 1;
      ++self.Cur; rt self;
    }
    [[gnu::always_inline]]
    ce a operator--(th a & self) -> dt(a) {
      self - 1;
      --self.Cur; rt self;
    }
    
  };


  ce a begin(th c a && self) { rt iterator(self); }
  ce a end(th c a && self) { rt iterator(self, self.End); }

};

tp <tn Type, Type MinValue, tn Fn>
class limited_min {
public:
  using value_type = Type;


}


}

#include "undef_short_macros.hpp"

#endif