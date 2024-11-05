#ifndef MLib_ShortMacros
#define MLib_ShortMacros 20241102L

#include "macros.hpp"
#define fw MLibForward
#define fwl MLibForwardLike
#define nec MLibNoExceptCond
#define dv MLibDeclVal

#define dt decltype
#define ne noexcept
#define tr throw
#define rt return
#define rt_th return*this
#define op operator
#define tp template
#define el else
#define elif else if
#define ns namespace
#define rq requires
#define szof sizeof
#define alas alignas
#define alof alignof
#define sw switch
#define ca case
#define dft default
#define fi final
#define fr friend

#define a auto
#define c const
#define vol volatile
#define ce constexpr
#define cl consteval
#define il inline
#define st static
#define st_assert static_assert
#define cc concept
#define new new

#define vi void
#define bl bool
#define si signed
#define ui unsigned
#define ch char
#define wch wchar_t
#define sh short
#define i int
#define lo long
#define ll long long

#include <cstdint>
#define i8 ::std::int8_t
#define ui8 ::std::uint8_t
#define i16 ::std::int16_t
#define ui16 ::std::uint16_t
#define i32 ::std::int32_t
#define ui32 ::std::uint32_t
#define i64 ::std::int64_t
#define ui64 ::std::uint64_t
#define if8 ::std::int_fast8_t
#define uif8 ::std::uint_fast8_t
#define if16 ::std::int_fast16_t
#define uif16 ::std::uint_fast16_t
#define if32 ::std::int_fast32_t
#define uif32 ::std::uint_fast32_t
#define if64 ::std::int_fast64_t
#define uif64 ::std::uint_fast64_t
#define il8 ::std::int_least8_t
#define uil8 ::std::uint_least8_t
#define il16 ::std::int_least16_t
#define uil16 ::std::uint_least16_t
#define il32 ::std::int_least32_t
#define uil32 ::std::uint_least32_t
#define il64 ::std::int_least64_t
#define uil64 ::std::uint_least64_t
#define im ::std::intmax_t
#define uim ::std::uintmax_t
#define ip ::std::intptr_t
#define uip ::std::uintptr_t
#define pd ::std::ptrdiff_t
#define sz ::std::size_t

#define str ::std::string
#define wstr ::std::wstring
#define u8str ::std::u8string
#define u16str ::std::u16string
#define u32str ::std::u32string
#define strv ::std::string_view
#define wstrv ::std::wstring_view
#define u8strv ::std::u8string_view
#define u16strv ::std::u16string_view
#define u32strv ::std::u32string_view
#define sstr ::std::stringstream
#define wsstr ::std::wstringstream
#define u8sstr ::std::u8stringstream
#define u16sstr ::std::u16stringstream
#define u32sstr ::std::u32stringstream


#define cs class
#define sc struct
#define un union
#define en enum

#define tid typeid
#define td typedef
#define tn typename
#define us using

#define th this
#define np nullptr
#define t true
#define f false

#define st_cast static_cast
#define rip_cast reinterpret_cast
#define c_cast const_cast
#define dn_cast dynamic_cast
#define s_cast safe_cast

#define pub public
#define pro protected
#define pri private

#endif