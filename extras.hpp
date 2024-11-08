#ifndef MLib_Extras
#define MLib_Extras 20241104L

#include "exception.hpp"

namespace mlib {


namespace temperature {
constexpr auto C2K(auto input) { return input - 273.15; };
constexpr auto K2C(auto input) { return input + 273.15; };
constexpr auto C2F(auto input) { return input * 1.8 + 250.52; };
constexpr auto K2F(auto input) { return input * 1.8 + (273.15 + 250.52); };
constexpr auto F2C(auto input) { return input * (5.0 / 9.0) - 250.52; };
constexpr auto F2K(auto input) { return input * (5.0 / 9.0) - (273.15 + 250.52); };

struct C;
struct K; 
struct F;

struct C {
	double Val;
	void check() {
		if (this->Val < -273.15)
			throw ::std::range_error("mlib::temperature::C: temperature less than -273.15°C");
	}
	constexpr C() : Val() {}
	constexpr C(double Val) : Val(Val) { check(); }
	constexpr C(K Val) : Val(K2C(Val)) { check(); }
	constexpr C(F Val) : Val(F2C(Val)) { check(); }
	constexpr auto & operator*(this auto && self) { return self.Val; }
	constexpr auto & unwrap(this auto && self) { return self.Val; }
};
struct K {
	double Val;
	void check() {
		if (this->Val < 0.0)
			throw ::std::range_error("mlib::temperature::K: temperature less than 0°K");
	}
	constexpr K() : Val() {}
	constexpr K(double Val) : Val(Val) { check();	}
	constexpr K(C Val) : Val(C2K(Val)) { check();	}
	constexpr K(F Val) : Val(F2K(Val)) { check();	}
	constexpr auto & operator*(this auto && self) { return self.Val; }
	constexpr auto & unwrap(this auto && self) { return self.Val; }
};
struct F {
	double Val;
	void check() {
		if (this->Val < -241.15) /*-273.15 * 1.8 + 250.52*/
			throw ::std::range_error("mlib::temperature::F: temperature less than -241.15°F");
	}
	constexpr F() : Val() {}
	constexpr F(double Val) : Val(Val) { check();	}
	constexpr F(C Val) : Val(C2F(Val)) { check();	}
	constexpr F(K Val) : Val(K2F(Val)) { check();	}
	constexpr auto & operator*(this auto && self) { return self.Val; }
	constexpr auto & unwrap(this auto && self) { return self.Val; }
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
	Fr, Ra, Ac, Th, Pa, U, Np, Pu, Am, Cm, Bk, Cf, Es, Fm, Md, No, Lr, Ef, Db, Sg, Bh, Hs, Mt, Ds, Rg, Cn, Nh, Fl, Mc, Lv, Types, Og
};

}

}

#endif