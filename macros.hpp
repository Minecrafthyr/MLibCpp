#ifndef MLib_Macros
#define MLib_Macros 20241029L

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

#include <utility>
#define MLibForward(value) ::std::forward<decltype(value)>(value)
#define MLibForwardLike(type, value) ::std::forward_like<type, decltype(value)>(value)
#define MLibDeclVal(type) ::std::declval<type>()

#if _DEBUG
#define MLibAssertCond true
#else
#define MLibAssertCond __builtin_is_constant_evaluated()
#endif


#define MLibNoExceptCond !MLibAssertCond
#endif
