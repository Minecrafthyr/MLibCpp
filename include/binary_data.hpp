// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLibHeader_BinaryDataHpp
#define MLibHeader_BinaryDataHpp 20241204

#include <ratio>

#include "short_types.hpp"
#include "builtin.hpp"

namespace mlib {

  namespace literals {
    template <typename T, typename Ratio>
    class ratio_data {
    public:
      using value_type = T;
      using ratio_type = Ratio;

      value_type Data;

      constexpr ratio_data(value_type _v)
      : Data(_v) {}

      constexpr decltype(auto) count() const
      { return Data * ratio_type::num; }
      
      template <u64 V_, typename Ratio_> requires (::std::integral<value_type>)
      constexpr decltype(auto) try_simplify(ratio_data<value_type, Ratio_> _v) const {
        if (not ratio_type::den % V_)
          return ::std::pair(true, ratio_data<value_type, ::std::ratio_multiply<ratio_type, ::std::ratio<V_>>>(Data * (V_)));
        return ::std::pair(false, _v);
      }
      template <u64 V_, typename Ratio_> requires (::std::integral<value_type>)
      constexpr decltype(auto) try_simplify_loop(ratio_data<value_type, Ratio_> _v) const {
        auto _r = try_simplify<V_>(_v);
        return (_r.first ? try_simplify_loop<V_>(_r) : _r).second;
      }

      template <int>
      requires (::std::integral<value_type>)
      constexpr decltype(auto) simplify() const {
        auto _r = try_simplify_loop<2>(*this);
        _r = try_simplify_loop<3>(_r);
        _r = try_simplify_loop<5>(_r);
        _r = try_simplify_loop<7>(_r);
        _r = try_simplify_loop<11>(_r);
        _r = try_simplify_loop<13>(_r);
        _r = try_simplify_loop<17>(_r);
        _r = try_simplify_loop<19>(_r);
        _r = try_simplify_loop<23>(_r);
        return _r;
      }
    };

    template <typename T, typename Ratio>
    class binary_data : public ratio_data<T, Ratio> {
    public:
      using value_type = T;
      using ratio_type = Ratio;
      using ratio_data_type = ratio_data<T, Ratio>;

      constexpr binary_data(value_type _v)
      : ratio_data_type(_v) {}

    };

    inline constexpr u64 step_v = 1000;
    inline constexpr u64 step_i_v = 1024;

    inline constexpr u64 b_v = 1;
    constexpr auto operator""_b(umax _v)
    { return binary_data<umax, ::std::ratio<b_v>>(_v); }
    constexpr auto operator""_b(long double _v)
    { return binary_data<long double, ::std::ratio<b_v>>(_v); }
    inline constexpr u64 B_v = 8;
    constexpr auto operator""_B(umax _v)
    { return binary_data<umax, ::std::ratio<B_v>>(_v); }
    constexpr auto operator""_B(long double _v)
    { return binary_data<long double, ::std::ratio<B_v>>(_v); }

    inline constexpr u64 Kb_v = step_v * b_v;
    constexpr auto operator""_Kb(umax _v)
    { return binary_data<umax, ::std::ratio<Kb_v>>(_v); }
    constexpr auto operator""_Kb(long double _v)
    { return binary_data<long double, ::std::ratio<Kb_v>>(_v); }
    inline constexpr u64 KB_v = step_v * B_v;
    constexpr auto operator""_KB(umax _v)
    { return binary_data<umax, ::std::ratio<KB_v>>(_v); }
    constexpr auto operator""_KB(long double _v)
    { return binary_data<long double, ::std::ratio<KB_v>>(_v); }

    inline constexpr u64 Kib_v = step_i_v * b_v;
    constexpr auto operator""_Kib(umax _v)
    { return binary_data<umax, ::std::ratio<Kib_v>>(_v); }
    constexpr auto operator""_Kib(long double _v)
    { return binary_data<long double, ::std::ratio<Kib_v>>(_v); }
    inline constexpr u64 KiB_v = step_i_v * B_v;
    constexpr auto operator""_KiB(umax _v)
    { return binary_data<umax, ::std::ratio<KiB_v>>(_v); }
    constexpr auto operator""_KiB(long double _v)
    { return binary_data<long double, ::std::ratio<KiB_v>>(_v); }

    inline constexpr u64 Mb_v = step_v * Kb_v;
    constexpr auto operator""_Mb(umax _v)
    { return binary_data<umax, ::std::ratio<Mb_v>>(_v); }
    constexpr auto operator""_Mb(long double _v)
    { return binary_data<long double, ::std::ratio<Mb_v>>(_v); }
    inline constexpr u64 MB_v = step_v * KB_v;
    constexpr auto operator""_MB(umax _v)
    { return binary_data<umax, ::std::ratio<MB_v>>(_v); }
    constexpr auto operator""_MB(long double _v)
    { return binary_data<long double, ::std::ratio<MB_v>>(_v); }

    inline constexpr u64 Mib_v = step_i_v * Kib_v;
    constexpr auto operator""_Mib(umax _v)
    { return binary_data<umax, ::std::ratio<Mib_v>>(_v); }
    constexpr auto operator""_Mib(long double _v)
    { return binary_data<long double, ::std::ratio<Mib_v>>(_v); }
    inline constexpr u64 MiB_v = step_i_v * KiB_v;
    constexpr auto operator""_MiB(umax _v)
    { return binary_data<umax, ::std::ratio<MiB_v>>(_v); }
    constexpr auto operator""_MiB(long double _v)
    { return binary_data<long double, ::std::ratio<MiB_v>>(_v); }

    inline constexpr u64 Gb_v = step_v * Mb_v;
    constexpr auto operator""_Gb(umax _v)
    { return binary_data<umax, ::std::ratio<Gb_v>>(_v); }
    constexpr auto operator""_Gb(long double _v)
    { return binary_data<long double, ::std::ratio<Gb_v>>(_v); }
    inline constexpr u64 GB_v = step_v * MB_v;
    constexpr auto operator""_GB(umax _v)
    { return binary_data<umax, ::std::ratio<GB_v>>(_v); }
    constexpr auto operator""_GB(long double _v)
    { return binary_data<long double, ::std::ratio<GB_v>>(_v); }

    inline constexpr u64 Gib_v = step_i_v * Mib_v;
    constexpr auto operator""_Gib(umax _v)
    { return binary_data<umax, ::std::ratio<Gib_v>>(_v); }
    constexpr auto operator""_Gib(long double _v)
    { return binary_data<long double, ::std::ratio<Gib_v>>(_v); }
    inline constexpr u64 GiB_v = step_i_v * MiB_v;
    constexpr auto operator""_GiB(umax _v)
    { return binary_data<umax, ::std::ratio<GiB_v>>(_v); }
    constexpr auto operator""_GiB(long double _v)
    { return binary_data<long double, ::std::ratio<GiB_v>>(_v); }

  }
}

void test() {

}

#endif