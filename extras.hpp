#ifndef MLib_Shapes
#define MLib_Shapes 20241029L

namespace mlib {


namespace temperature {
constexpr auto C2K(auto input) { return input - 273.15; };
constexpr auto K2C(auto input) { return input + 273.15; };
constexpr auto C2F(auto input) { return input * 1.8 + 250.52; };
constexpr auto K2F(auto input) { return input * 1.8 + (273.15 + 250.52); };
constexpr auto F2C(auto input) { return input * (5.0 / 9.0) - 250.52; };
constexpr auto F2K(auto input) { return input * (5.0 / 9.0) - (273.15 + 250.52); };
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