#ifndef MLib_Any
#define MLib_Any 20241103L

#include <bit>
#include <typeindex>
#include <utility>
#include <optional>
#include <stdexcept>
#include "type_utils.hpp"
#include "pair.hpp"

#include "short_macros.hpp"

namespace mlib {

struct any {

	vi * ValPtr = np;
	sc type_index_t {
		un {
			::std::type_index Index;
			::std::size_t Int{};
		};
		ce type_index_t() ne {}
		ce type_index_t(::std::nullopt_t) ne {}
		type_index_t(a && Val) ne
			rq rq { ::std::type_index{Val}; } :
			Index(fw(Val)) {}
		ce op ::std::type_index &() & { rt Index; }
		ce op const ::std::type_index &() const & { rt Index; }
	} TyIndex{};
	
	::std::size_t TySize = 0uz;
	bl IsVolatile = f;
	bl IsConst = f;

	ce any() ne {}
	ce any(dt(np)) ne {}
	ce any(::std::nullopt_t) ne {}
	tp <tn T>
	any(T && Val) :
		ValPtr((vi *)(&Val)),
		TySize(szof(remove_ref<T>)),
		TyIndex(tid(remove_cvref<T>)),
		IsVolatile(c_volatile<remove_ref<T>>),
		IsConst(c_const<remove_ref<T>>) ne {}

	[[nodiscard]]
	ce bl empty() c & ne { rt ValPtr; }

	en cs errc {
		success = 0,
		index_not_same,
		discard_volatile,
		discard_const
	};

	tp <tn T>
	T & cast() c & {
		if (tid(T) != TyIndex)
			tr ::std::runtime_error("hyr::any: index not same");
		if (IsVolatile && not c_volatile<remove_ref<T>>)
			tr ::std::runtime_error("hyr::any: discard volatile");
		if (IsConst && not c_const<remove_ref<T>>)
			tr ::std::runtime_error("hyr::any: discard const");
		return *(T *)ValPtr;
	}
	tp <tn T>
	a cast_noexcept() c & ne {
		errc State;
		if (tid(T) != TyIndex) State = errc::index_not_same;
		elif (IsConst && not c_const<T>) State = errc::discard_const;
		elif (IsVolatile && not c_volatile<T>) State = errc::discard_volatile;
		else State = errc::success;
		return ref_pair(*(T *)ValPtr, State);
	}

};


}

#include "undef_short_macros.hpp"

#endif