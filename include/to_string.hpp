#include <print>
#include <algorithm>
#include <ranges>
#include <sstream>

#ifndef MLibHeader_ToStringHpp
#define MLibHeader_ToStringHpp 20241204

namespace mlib {

using ::std::to_string;
template <typename ... Args>
[[nodiscard]]
inline auto to_string(::std::format_string<Args...> _fmt, Args && ... _args)
{ return ::std::format(_fmt, ::std::forward<Args>(_args)...); }
template <typename ... Args>
[[nodiscard]]
inline auto to_string(::std::string_view _fmt, Args && ... _args)
{ return ::std::vformat(_fmt, ::std::make_format_args(_args...)); }

[[nodiscard]]
inline auto to_string(
  ::std::ranges::range auto && _input_value,
  ::std::string_view _sep = ", "
) {
  auto _iter = ::std::ranges::begin(_input_value);
  auto _cend = ::std::ranges::cend(_input_value);
  ::std::stringstream _stream;
  _stream << *_iter; ++_iter;
  for (; _iter != _cend; _stream << _sep << *_iter, ++_iter);
  return ::std::move(_stream).str();
}
template <::std::ranges::range T>
[[nodiscard]]
constexpr auto to_string(
  ::std::format_string<decltype(*::std::ranges::begin(::std::declval<T>()))> _fmt,
  T && _input_value,
  ::std::string_view _sep = ", ") {
  ::std::stringstream _stream;
  _stream << _input_value
  | ::std::ranges::transform(
    _input_value, [&](auto && _in){ return ::std::format(_fmt, _in); })
  | ::std::views::join_with(_sep);
  return _stream.str();
}

using ::std::to_wstring;
template <typename ... Args>
[[nodiscard]]
inline auto to_wstring(::std::wformat_string<Args...> _fmt, Args && ... _args)
{ return ::std::format(_fmt, ::std::forward<Args>(_args)...); }
template <typename ... Args>
[[nodiscard]]
inline auto to_wstring(::std::wstring_view _fmt, Args && ... _args)
{ return ::std::vformat(_fmt, ::std::make_format_args(_args...)); }

[[nodiscard]]
inline auto to_wstring(
  ::std::ranges::range auto && _input_value,
  ::std::wstring_view _sep = L", "
) {
  auto _iter = ::std::ranges::begin(_input_value);
  auto _cend = ::std::ranges::cend(_input_value);
  ::std::wstringstream _stream;
  _stream << *_iter; ++_iter;
  for (; _iter != _cend; _stream << _sep << *_iter, ++_iter);
  return ::std::move(_stream).str();
}
template <::std::ranges::range T>
[[nodiscard]]
constexpr auto to_wstring(
  ::std::wformat_string<decltype(*::std::ranges::begin(::std::declval<T>()))> _fmt,
  T && _input_value,
  ::std::wstring_view _sep = L", "
) {
  ::std::wstringstream _stream;
  _stream << _input_value
  | ::std::ranges::transform(
    _input_value, [&](auto && _in){ return ::std::format(_fmt, _in); })
  | ::std::views::join_with(_sep);
  return _stream.str();
}

using ::std::print;
inline void print(FILE * _stream, ::std::string_view _str) {
  if (::std::fwrite(
    _str.data(), 1, _str.size(), _stream) != _str.size())
    ::std::__throw_system_error(EIO);
}
inline void print(::std::string_view _str) { print(stdout, _str); }
using ::std::println;
inline void println(FILE * _stream, ::std::string_view _str) {
  ::std::string _out_str;
  _out_str.reserve(_str.size() + 1);
  print(_stream, (_out_str += _str) += '\n');
}
inline void println(::std::string_view _str) { println(stdout, _str); }

}

#endif