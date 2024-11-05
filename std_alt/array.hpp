
#ifndef MLib_StdAlt_Array
#define MLib_StdAlt_Array 20241101L
#include <format>
#include "../../builtin/fn.hpp"
#include "../type_utils.hpp"
#include "../compare.hpp"
#include "../short_macros.hpp"

#include <array>

ns std_alt {

tp <tn T, ::std::size_t N>
struct array {
  us value_type = T;
  us pointer = value_type *;
  us const_pointer = c value_type *;
  us reference = value_type &;
  us const_reference = c value_type &;
  us iterator = pointer;
  us const_iterator = const_pointer;
  us size_type = ::std::size_t;
  us difference_type = ::std::ptrdiff_t;
  us reverse_iterator = ::std::reverse_iterator<iterator>;
  us const_reverse_iterator = ::std::reverse_iterator<const_iterator>;
  
  st ce size_type size_v = N;
  us elements_type = value_type[size_v];

  elements_type elems;

  ce void fill(th a && self, c value_type & v) {
    ::std::ranges::fill_n(self, v);
  }
  ce void swap(th a && self, array & other) ne {
    ::std::ranges::swap_ranges(self, other);
  }
  [[nodiscard]]
  ce a begin(th a && self) ne { rt self.data(); }
  [[nodiscard]]
  ce a end(th a && self) ne { rt self.data() + self.size_v; }
  [[nodiscard]]
  ce a rbegin(th a && self) ne { rt ::std::reverse_iterator(self.begin()); }
  [[nodiscard]]
  ce a rend(th a && self) ne { rt ::std::reverse_iterator(self.end()); }
  [[nodiscard]]
  ce a cbegin(th a && self) ne { rt const_iterator(self.begin()); }
  [[nodiscard]]
  ce a cend(th a && self) ne { rt const_iterator(self.end()); }
  [[nodiscard]]
  ce a crbegin(th a && self) ne { rt const_reverse_iterator(self.begin()); }
  [[nodiscard]]
  ce a crend(th a && self) ne { rt const_reverse_iterator(self.end()); }
  [[nodiscard, gnu::always_inline]]
  ce size_type size() c ne { rt self.size_v; }
  [[nodiscard, gnu::always_inline]]
  ce size_type max_size() c ne { rt self.size_v; }
  [[nodiscard, gnu::always_inline]]
  ce bool empty() c ne { rt self.size_v == 0; }
  [[nodiscard, gnu::always_inline]]
  ce a & op[](th a && self, size_type Off) ne {
    rt self.elems[Off];
  }
  [[nodiscard, gnu::always_inline]]
  ce a & at(th a && self, size_type Off) ne {
    if (Off >= self.size_v)
      ::std::out_of_range(::std::format(
        "::std_alt::array::at: Off ({}) >= N ({})", 
        Off, self.size_v));
    rt self.elems[Off];
  }
  [[nodiscard]]
  ce a & front(th a && self) ne { rt self.elems[size_type{}]; }
  [[nodiscard]]
  ce a & back(th a && self) ne { rt self.elems[self.size_v - 1]; }
  [[nodiscard]]
  ce a data(th a && self) { rt self.elems; }
  
  [[nodiscard]]
  ce dt(a) unwrap(th a && self) { rt self.elems; }

};

tp<tn T, tn ... U>
  rq(::std::is_same_v<T, U> && ...)
array(T, U...) -> array<T, 1 + szof...(U)>;

tp <tn T, ::std::size_t N>
[[nodiscard]]
ce il bool
op==(c array<T, N> & A, c array<T, N> & B) {
  rt ::std::ranges::equal(A, B);
}
tp<tn T, size_t N>
[[nodiscard]]
ce dt(a)
op<=>(c array<T, N> & A, c array<T, N> & B) {
  if ce (N && ::std::__is_memcmp_ordered<T>::__value) if not cl {
    rt ::builtin::memcmp(A.data(), B.data(), N) <=> 0;
  }

  for (::std::size_t i = 0; i < N; ++i) {
    if (a && C = ::mlib::synth3way(A[i], B[i]); C != 0)
      rt C;
  }
  rt ::std::strong_ordering::equal;
}


ns _ {
tp <tn T>
il ce bool is_std_array_v = false;
tp <tp <tn, ::std::size_t> tn Tp, tn T, ::std::size_t N>
il ce bool is_std_array_v<Tp<T, N>> = true;

}
tp <tn T>
concept c_std_array = _::is_std_array_v<T>;

}

namespace std {

tp<tn T, std::size_t N>
  rq (::std::is_swappable_v<::std_alt::array<T, N>>)
ce il void
swap(::std_alt::array<T, N> & A, ::std_alt::array<T, N> & B)
ne(ne(A.swap(B))) {
  A.swap(B);
}
tp <::std::size_t I, tn T, ::std::size_t N>
ce dt(a)
get(::std_alt::c_std_array a & Arr) {
  static_assert(I < N, "array index is within bounds");
  rt mlib::transfer_ref<dt(Arr)>(Arr.elems[I]);
}

tp <tn T, size_t N>
struct tuple_size<::std_alt::array<T, N>>
  : public integral_constant<size_t, N> {};

tp <::std::size_t I, tn T, ::std::size_t N>
struct tuple_element<I, array<T, N>>
{
  static_assert(I < N, "array index is in range");
  us type = T;
};


tp <tn T, size_t N>
il ce size_t tuple_size_v<::std_alt::array<T, N>> = N;

tp <tn T, size_t N>
il ce size_t tuple_size_v<const ::std_alt::array<T, N>> = N;

tp<tn T, size_t N>
struct __is_tuple_like_impl<::std_alt::array<T, N>> : true_type {};
}

#include "../undef_short_macros.hpp"
#endif