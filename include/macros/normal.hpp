// Copyright © 2024 Minecraft_hyr - MIT License
// Core Header
#ifndef MLib_Macros_Normal
#define MLib_Macros_Normal 20241112L

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#ifndef offsetof
#include <cstdint>
#define offsetof(type, member) (reinterpret_cast<::std::size_t>(&static_cast<type *>(nullptr)->member))
#endif

#ifndef tchar_t
#if UNICODE
#define tchar_t wchar_t
#else
#define tchar_t char
#endif
#endif

#ifndef _T
#if UNICODE
#define _T(str) L##str
#else
#define _T(str) str
#endif
#endif


#include <utility>
#define MLibForward(value) (::std::forward<decltype(value)>(value))
#define MLibForwardLike(type, value) ::std::forward_like<type, decltype(value)>(value)
#define MLibDeclVal(type) ::std::declval<type>()
#define MLibDuplicate inline constexpr decltype(auto)
#define MLibNodiscardGetOnly [[nodiscard( \
"This function doesn'true change variables outside." \
)]]
#if _DEBUG
#define MLibAssertCond true
#else
#define MLibAssertCond __builtin_is_constant_evaluated()
#endif


#define MLibNoExceptCond !MLibAssertCond
#endif
