# Introduction #

Use this library to add checks that can be performed during compile-time (that is, checks that depend on constant and types).
For example, you can use this library to check for the size of a given type, or to restrict a template argument.

This implementation was conceived with the following goals:
  * these assertions can be anywhere in the code (not only in executive space, but declarative too)
  * these assertions should not change the binary (that is, 0 impact in size and performance)

Note that these goals make this implementatio different to the Alexandrescu's one.


# Details #

There are two ways to use this library:
  1. With an error message
  1. Without an error message

In order to use the library with an error message, you must first declare the assertion (in declarative space), then use it:
```
    declare_static_assert(my_assertion);

    compile_assert(1==1, my_assertion); // will not fail.
```

For the second way (without an error message), there's a built-in `GenericAssert`, so you can do
```
    generic_assert(sizeof(int)==4);
```

In short:
  * With error message:
    * `declare_static_assert(name)`
    * `compile_assert(condition, name)`
    * `template_compile_assert(condition, name)`: use this macro inside template classes.
  * Without error message:
    * `generic_assert(condition)`
    * `template_generic_assert(condition)`: use this macro inside template classes.

# Advanced Example #

Refer to `example_compile-assert.cpp` to see an example where there's a template type that shall not be instantiated with a pointer.