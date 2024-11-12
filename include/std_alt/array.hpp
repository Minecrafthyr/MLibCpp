// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLib_StdAlt_Array
#define MLib_StdAlt_Array 20241108L
#include <algorithm>
#include "../format.hpp"
#include "../builtin.hpp"
#include "../types.hpp"
#include "../compare.hpp"

#include "../short_macros.hpp"

ns std_alt {
us ns ::mlib::literals;

tp <tn T, sz N> rq (N != 0)
t array {
  us value_type = T;
  us pointer = value_type *;
  us const_pointer = c value_type *;
  us reference = value_type &;
  us const_reference = c value_type &;
  us iterator = pointer;
  us const_iterator = const_pointer;
  us size_type = sz;
  us difference_type = pd;
  us reverse_iterator = ::std::reverse_iterator<iterator>;
  us const_reverse_iterator = ::std::reverse_iterator<const_iterator>;
  st ce size_type size_v = N;

  us elements_type = value_type[size_v];

  elements_type elems;

  ce void fill(th a && self, c value_type & __v) {
    ::std::ranges::fill_n(self, __v);
  }
  ce void swap(th a && self, array & __other) ne {
    ::std::ranges::swap_ranges(self, __other);
  }
  nd_get st ce dt(a) make(::std::span<value_type, size_v> __v) {
    rt ::std::move(*(array *)__v.data());
  }
  tp <strv IStr> rq (IStr.size() > size_v)
  nd_get st cl dt(a) make() { rt ::std::move(*(array *)IStr.data()); }
  nd_get ail ce a data(th a && self) { rt self.elems; }
  nd_get ail cl a size() c ne { rt self.size_v; }
  nd_get ail cl a max_size() c ne { rt self.size_v; }
  nd_get ail cl a empty() c ne { rt false; }
  nd_get ail ce a & op[](th a && self, size_type __o) ne { rt self.elems[__o]; }
  nd_get ail ce a & at(th a && self, size_type __o) {
    if (__o >= self.size_v) tr ::std::out_of_range(
      "std_alt::array::at: __o ({}) >= size ({})"_format(__o, self.size_v));
    rt self.elems[__o];
  }

  nd_get ce a begin(th a && self) ne { rt self.data(); }
  nd_get ce a end(th a && self) ne { rt self.data() + self.size_v; }
  nd_get ce a rbegin(th a && self) ne { rt ::std::reverse_iterator(self.begin()); }
  nd_get ce a rend(th a && self) ne { rt ::std::reverse_iterator(self.end()); }
  nd_get ce a cbegin(th a && self) ne { rt const_iterator(self.begin()); }
  nd_get ce a cend(th a && self) ne { rt const_iterator(self.end()); }
  nd_get ce a crbegin(th a && self) ne { rt const_reverse_iterator(self.begin()); }
  nd_get ce a crend(th a && self) ne { rt const_reverse_iterator(self.end()); }
  nd_get ce dt(a) front(th a && self) ne { rt self.elems[size_type{}]; }
  nd_get ce dt(a) back(th a && self) ne { rt self.elems[self.size_v - 1]; }
  
  nd_get ce dt(a) unwrap(th a && self) { rt self.elems; }

};

tp<tn T, tn ... U> rq (::std::same_as<T, U> && ...)
array(T, U...) -> array<T, 1 + szof...(U)>;

tp <tn T, sz N>
nd_get ce il bl op==(c array<T, N> & __a, c array<T, N> & __b) { rt ::std::ranges::equal(__a, __b); }
tp<tn T, size_t N>
nd_get ce dt(a) op<=>(c array<T, N> & __a, c array<T, N> & __b) {
  if ce (N && ::std::__is_memcmp_ordered<T>::__value) if not cl {
    rt ::builtin::memcmp(__a.data(), __b.data(), N) <=> 0;
  }
  for (sz __i = 0; __i < N; ++__i)
  if (a && C = ::mlib::synth3way(__a[__i], __b[__i]); C != ::std::weak_ordering::equivalent) rt C;
  rt ::std::strong_ordering::equal;
}


ns _ {
tp <tn T>
il ce bool is_std_array_v = false;
tp <tp <tn, sz> tn Tp, tn T, sz N>
il ce bool is_std_array_v<Tp<T, N>> = true;

}
tp <tn T>
cc c_std_array = _::is_std_array_v<T>;

}

namespace std {

tp<tn T, sz N>
  rq (::mlib::c_swappable<::std_alt::array<T, N>>)
ce il void swap(::std_alt::array<T, N> & __a, ::std_alt::array<T, N> & __b)
  ne(ne(__a.swap(__b))) { __a.swap(__b); }
tp <sz I, tn T, sz N>
ce dt(a)
get(::std_alt::c_std_array a & Arr) {
  static_assert(I < N, "array index is within bounds");
  rt ::mlib::transfer_ref<dt(Arr)>(Arr.elems[I]);
}

tp <tn T, size_t N>
t tuple_size<::std_alt::array<T, N>> : pub integral_constant<size_t, N> {};

tp <sz I, tn T, sz N>
t tuple_element<I, array<T, N>>
{ st_assert(I < N, "array index is in range"); us type = T; };


tp <tn T, size_t N>
il ce sz tuple_size_v<::std_alt::array<T, N>> = N;

tp <tn T, size_t N>
il ce sz tuple_size_v<const ::std_alt::array<T, N>> = N;

tp<tn T, size_t N>
t __is_tuple_like_impl<::std_alt::array<T, N>> : true_type {};
}

#include "../undef_short_macros.hpp"

#endif