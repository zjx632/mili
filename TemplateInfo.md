# Introduction #

This library is useful to query type information, e.g. for compile time assertions.

# Details #

The library provides two things:
  * a set of individual type predicates
  * a structure that encapsulates all the predicates and has some operators.

The individual predicates are:
  * `template_is_pointer<T>::value`
  * `template_is_reference<T>::value`
  * `template_is_const<T>::value`
  * `template_is_volatile<T>::value`
  * `template_is_integral<T>::value`: returns true if `T` is some kind of int (short, long, signed, etc.).
  * `template_is_native<T>::value`: returns true if `T` is a native (unqualified) data type.
  * `type_equal<T1,T2>::value`: returns true if `T1` and `T2` are the same type.


The encapsulating structure is `template_info<T>`, which provides the following members:
  * `template_info<T>::is_pointer`
  * `template_info<T>::is_reference`
  * `template_info<T>::is_const`
  * `template_info<T>::is_volatile`
  * `template_info<T>::is_integral`
  * `template_info<T>::is_native`
  * `template_info<T>::is_pointer`
  * `template_info<T>::is_equal_to<T2>::value`: similar to `type_equal`.
  * `template_info<T>::is_smaller_than<T2>::value`: returns true if sizeof(T) < sizeof(T2)
  * `template_info<T>::is_greater_than<T2>::value`: returns true if sizeof(T) > sizeof(T2)
  * `template_info<T>::is_same_size<T2>::value`: returns true if sizeof(T) == sizeof(T2)
  * `template_info<T>::size`: returns sizeof(T)

The `template_info<T>` can be used as a template parameter itself.