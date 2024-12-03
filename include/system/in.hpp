#include <array>
#include <cstdint>
#include <windows.h>
#include "../exception.hpp"

_CRTIMP bool __cdecl _kbhit();
_CRTIMP ::std::uint8_t __cdecl _getch();
_CRTIMP ::std::uint16_t __cdecl _getwch();

namespace mlib {
namespace system {

  namespace in {

    namespace key {

      inline ::std::uint8_t get() {
        if (::_kbhit()) return ::_getch();
        else throw ::mlib::system_error(::std::errc::io_error);
      }
      inline ::std::uint16_t getw() {
        if (::_kbhit()) return ::_getwch();
        else throw ::mlib::system_error(::std::errc::io_error);
      }

      struct state_t {
        SHORT value{};

        constexpr state_t(SHORT _input) : value(_input) {}

        constexpr bool is_enabled(this state_t self)
        { return self.value & 0x1; }
        constexpr bool is_holding(this state_t self)
        { return self.value & 0x8000; }
        static state_t get(int _virtual_key)
        { return (state_t)::GetKeyState(_virtual_key); }
        static state_t get_async(int _virtual_key)
        { return (state_t)::GetAsyncKeyState(_virtual_key); }
      };

    }

    namespace keyboard {

      struct state_t {
        
        struct element_t { bool enabled : 1, none: 6, holding: 1; };
        ::std::array<element_t, 256> buffer{};

        bool get(this auto & self)
        { return ::GetKeyboardState((::std::uint8_t *)&self.buffer); }
        bool set(this auto const& self)
        { return ::SetKeyboardState((::std::uint8_t *)&self.buffer); }

      };


    }

  }
}
}