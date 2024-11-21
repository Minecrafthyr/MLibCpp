// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLib_StdAlt_Array
#define MLib_StdAlt_Array 20241108L
#include <algorithm>
#include "../format.hpp"
#include "../builtin.hpp"
#include "../types.hpp"
#include "../compare.hpp"

namespace std_alt {
using namespace ::mlib::literals;

template <typename T, ::std::size_t N> requires (N != 0)
struct array {
  using value_type = T;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using size_type = ::std::size_t;
  using difference_type = pd;
  using reverse_iterator = ::std::reverse_iterator<iterator>;
  using const_reverse_iterator = ::std::reverse_iterator<const_iterator>;
  static constexpr size_type size_v = N;

  using elements_type = value_type[size_v];

  elements_type elems;

  constexpr void fill(this auto && self, const value_type & _v) {
    ::std::ranges::fill_n(self, _v);
  }
  constexpr void swap(this auto && self, array & _o) noexcept {
    ::std::ranges::swap_ranges(self, _o);
  }
  [[nodiscard]]
  static constexpr decltype(auto) make(::std::span<value_type, size_v> _v) {
    return ::std::move(*(array *)_v.data());
  }
  template <::std::string_view IStr> requires (IStr.size() > size_v)
  [[nodiscard]] static consteval decltype(auto) make() { return ::std::move(*(array *)IStr.data()); }
  [[nodiscard, gnu::always_inline]]
  constexpr auto data(this auto && self) { return self.elems; }
  [[nodiscard, gnu::always_inline]]
  consteval auto size() const noexcept { return self.size_v; }
  [[nodiscard, gnu::always_inline]]
  consteval auto max_size() const noexcept { return self.size_v; }
  [[nodiscard, gnu::always_inline]]
  consteval auto empty() const noexcept { return false; }
  [[nodiscard, gnu::always_inline]]
  constexpr auto & operator[](this auto && self, size_type _o) noexcept { return self.elems[_o]; }
  [[nodiscard, gnu::always_inline]]
  constexpr auto & at(this auto && self, size_type _o) {
    if (_o >= self.size_v) throw ::std::out_of_range(
      "std_alt::array::at: _o ({}) >= size ({})"_format(_o, self.size_v));
    return self.elems[_o];
  }

  [[nodiscard]]
  constexpr auto begin(this auto && self) noexcept { return self.data(); }
  [[nodiscard]]
  constexpr auto end(this auto && self) noexcept { return self.data() + self.size_v; }
  [[nodiscard]]
  constexpr auto rbegin(this auto && self) noexcept { return ::std::reverse_iterator(self.begin()); }
  [[nodiscard]]
  constexpr auto rend(this auto && self) noexcept { return ::std::reverse_iterator(self.end()); }
  [[nodiscard]]
  constexpr auto cbegin(this auto && self) noexcept { return const_iterator(self.begin()); }
  [[nodiscard]]
  constexpr auto cend(this auto && self) noexcept { return const_iterator(self.end()); }
  [[nodiscard]]
  constexpr auto crbegin(this auto && self) noexcept { return const_reverse_iterator(self.begin()); }
  [[nodiscard]]
  constexpr auto crend(this auto && self) noexcept { return const_reverse_iterator(self.end()); }
  [[nodiscard]]
  constexpr decltype(auto) front(this auto && self) noexcept { return self.elems[size_type{}]; }
  [[nodiscard]]
  constexpr decltype(auto) back(this auto && self) noexcept { return self.elems[self.size_v - 1]; }
  
  [[nodiscard]]
  constexpr decltype(auto) unwrap(this auto && self) { return self.elems; }

};

template<typename T, typename ... U> requires (::std::same_as<T, U> && ...)
array(T, U...) -> array<T, 1 + sizeof...(U)>;

template <typename T, ::std::size_t N>
[[nodiscard]]
constexpr inline bool operator==(const array<T, N> & _a, const array<T, N> & _b) {
  return ::std::ranges::equal(_a, _b);
}
template<typename T, size_t N>
[[nodiscard]]
constexpr decltype(auto) operator<=>(const array<T, N> & _a, const array<T, N> & _b) {
  if constexpr (N && ::std::__is_memcmp_ordered<T>::__value)
    if not consteval {
      return ::builtin::memcmp(_a.data(), _b.data(), N) <=> 0;
    }
  for (::std::size_t _i = 0; _i < N; ++_i)
    if (auto && _c = ::mlib::synth3way(_a[_i], _b[_i]); _c != ::std::weak_ordering::equivalent) return _c;
  return ::std::strong_ordering::equal;
}


namespace _ {
template <typename T>
inline constexpr bool is_std_array_v = false;
template <template <typename, ::std::size_t> typename Tp, typename T, ::std::size_t N>
inline constexpr bool is_std_array_v<Tp<T, N>> = true;

}
template <typename T>
concept c_std_array = _::is_std_array_v<T>;

}

namespace std {

template<typename T, ::std::size_t N>
  requires (::mlib::Swappable<::std_alt::array<T, N>>)
constexpr inline void swap(::std_alt::array<T, N> & _a, ::std_alt::array<T, N> & _b)
  noexcept(noexcept(_a.swap(_b))) { _a.swap(_b); }
template <::std::size_t I, typename T, ::std::size_t N>
constexpr decltype(auto)
get(::std_alt::c_std_array auto & _arr) {
  static_assert(I < N, "array index is within bounds");
  return ::mlib::transfer_ref<decltype(_arr)>(_arr.elems[I]);
}

template <typename T, size_t N>
struct tuple_size<::std_alt::array<T, N>> : pub integral_constant<size_t, N> {};

template <::std::size_t I, typename T, ::std::size_t N>
struct tuple_element<I, array<T, N>>
{ static_assert(I < N, "array index is in range"); using type = T; };


template <typename T, size_t N>
inline constexpr ::std::size_t tuple_size_v<::std_alt::array<T, N>> = N;

template <typename T, size_t N>
inline constexpr ::std::size_t tuple_size_v<const ::std_alt::array<T, N>> = N;

template<typename T, size_t N>
struct __is_tuple_like_impl<::std_alt::array<T, N>> : true_type {};
}


#endif