# Introduction #

This minimalistic library provides some utils for metaprogramming.

# Details #

This library provides:

`Select<condition, Type if condition is false, Type if condition if true>` an "if" equivalent for metaprograms.

`ParameterType<T>::type` return the optimal type to be used as a parameter for functions that take T (based on Alexandrescu Loki lib)