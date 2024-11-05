#ifndef MLib_TypeUtils
#define MLib_TypeUtils 20241101L

#include "concepts.hpp"

#include "short_macros.hpp"

namespace mlib {

tp <tn T>
us remove_const = ::std::remove_const_t<T>;
tp <tn T>
us remove_volatile = ::std::remove_volatile_t<T>;
tp <tn T>
us remove_ref = ::std::remove_reference_t<T>;
tp <tn T>
us remove_cv = ::std::remove_cv_t<T>;
tp <tn T>
us remove_cvref = ::std::remove_cvref_t<T>;
tp <tn T, tn T2>
cc c_same_as = ::std::same_as<T, T2>;
tp <tn T, tp<tn> tn Op, tn T2>
cc c_same_as_if = c_same_as<Op<T>, T2>;


namespace _ {
tp <tn FromT, tn ToT> rq(c_lref<FromT>)
sc transfer_ref_type { us type = ToT &; };
tp <tn FromT, tn ToT> rq(c_rref<FromT>)
sc transfer_ref_type { us type = remove_ref<ToT> &&; };
}

tp <tn FromT, tn ToT>
us transfer_ref_type = _::transfer_ref_type<FromT, ToT>::type;

tp <tn FromT, tn ToT>
[[nodiscard]]
ce dt(a) transfer_ref(ToT && value) {
  rt transfer_ref_type<FromT, ToT>(value);
}

tp <tn ToT, tn FromT>
ce dt(a) smart_cast(FromT && Val) {
  if ce (c_lref<ToT> && c_ptr<FromT>)
    rt *(remove_ref<ToT> *)Val;
  else rt (ToT)Val;
}


}

#include "undef_short_macros.hpp"

#endif