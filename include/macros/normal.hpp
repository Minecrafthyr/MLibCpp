// Copyright © 2024 Minecraft_hyr - MIT License
// Core Header
#ifndef MLibHeader_Macros_NormalHpp
#define MLibHeader_Macros_NormalHpp 20241202
#include <utility>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
#ifdef type
#undef type
#endif
#ifdef value
#undef value
#endif

#ifndef offsetof
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


#define DeclVal(...) ::std::declval<__VA_ARGS__>()
#define Forward(...) ::std::forward<decltype(__VA_ARGS__) &&>(__VA_ARGS__)

#define NodiscardPure [[nodiscard( \
"This function doesn'true change variables outside." \
)]]

#if _DEBUG
#define MLibAssertCond true
#else
#define MLibAssertCond __builtin_is_constant_evaluated()
#endif

#define MLibNoExceptCond !MLibAssertCond
#endif
