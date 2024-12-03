// Copyright © 2024 Minecraft_hyr - MIT License
#ifndef MLib_Extras
#define MLib_Extras 20241118L
#include "exception.hpp"
#include "macros/normal.hpp"

namespace mlib {


namespace temperature {
constexpr auto C2K(auto _input) { return _input - 273.15; };
constexpr auto K2C(auto _input) { return _input + 273.15; };
constexpr auto C2F(auto _input) { return _input * 1.8 + 250.52; };
constexpr auto K2F(auto _input) { return _input * 1.8 + (273.15 + 250.52); };
constexpr auto F2C(auto _input) { return _input * (5.0 / 9.0) - 250.52; };
constexpr auto F2K(auto _input) { return _input * (5.0 / 9.0) - (273.15 + 250.52); };

struct base {
	double Value;
	
	void check();
	constexpr base() : Value() {}
	constexpr base(double _input) : Value(_input) {}
	[[nodiscard]] __forceinline
	constexpr auto & operator*(this auto && self) { return self.Value; }
	[[nodiscard]] __forceinline
	constexpr auto & unwrap(this auto && self) { return self.Value; }
	[[nodiscard]] __forceinline
	constexpr operator double(this auto self) { return self.Value; }
};

struct baseC : base {};
struct baseK : base {};
struct baseF : base {};

#define MLibTrLTStr(s) "mlib::temperature::" #s ": temperature less than "

struct C : baseC {
	void check() {
		if (this->Value < -273.15)
			throw ::std::range_error(MLibTrLTStr(C)"-273.15°C");
	}
	
	explicit constexpr C(double _input) : baseC(_input) { check(); }
	constexpr C(baseK _input) : baseC(K2C(_input)) { check(); }
	constexpr C(baseF _input) : baseC(F2C(_input)) { check(); }
	constexpr operator baseC() const { return baseC(this->Value); }
};
struct K : baseK {
	double Val;
	void check() {
		if (this->Val < 0.0)
			throw ::std::range_error(MLibTrLTStr(K)"0°K");
	}
	explicit constexpr K(double _input) : baseK(_input) { check(); }
	constexpr K(baseC _input) : baseK(C2K(_input)) { check();	}
	constexpr K(baseF _input) : baseK(F2K(_input)) { check();	}
	constexpr operator baseK() const { return baseK(this->Value); }
};
struct F : baseF {
	double Value;
	void check() {
		if (this->Value < -241.15/*-273.15 * 1.8 + 250.52*/) 
			throw ::std::range_error(MLibTrLTStr(F)"-241.15°F");
	}
	explicit constexpr F(double _input) : baseF(_input) { check(); }
	constexpr F(baseC _input) : baseF(C2F(_input)) { check();	}
	constexpr F(baseK _input) : baseF(K2F(_input)) { check();	}
	constexpr operator baseF() const { return baseF(this->Value); }
};

}

namespace chemistry {

enum element {
	H = 1, He,
	Li, Be, B, C, N, O, F, Ne,
	Na, Mg, Al, Si, P, S, Cl, Ar,
	K, Ca, Sc, Ti, V, Cr, Mn, Fe, Co, Ni, Cu, Zn, Ga, Ge, As, Se, Br, Kr,
	Rb, Sr, Y, Zr, Nb, Mo, Tc, Ru, Rh, Pd, Ag, Cd, In, Sn, Sb, Te, I, Xe,
	Cs, Ba, La, Ce, Pr, Nd, Pm, Sm, Eu, Gd, Tb, Dy, Ho, Er, Tm, Yb, Lu, Hf, Ta, W, Re, Os, Ir, Pt, Au, Hg, Tl, Pb, Bi, Po, At, Rn,
	Fr, Ra, Ac, Th, Pa, U, Np, Pu, Am, Cm, Bk, Cf, Es, Fm, Md, No, Lr, Ef, Db, Sg, Bh, Hs, Mt, Ds, Rg, Cn, Nh, Fl, Mc, Lv, Ty, Og
};

}


}


#endif