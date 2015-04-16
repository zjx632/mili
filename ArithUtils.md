# Introduction #

This minimalistic library provides some arithmetic manipulation utilities.


# Details #

This library provides:
  * `bool in_range(T value, T min, T max)`: returns `true` if `value` is in the range `[min, max]`
  * `bchain<T>`: a class for chaining boolean conditions.
  * `Randomizer<T>`: a class to produce random numbers.
  * `FirstTimeFlag`: a class that values initially `true`, and `false` after it's evaluated.
  * `maximize<T>(T& m, T value)`: sets `m` to `value` if the latter is greater than the former, ensuring to set `m` to the maximum. Returns `m`.
  * `minimize()`: ditto `maximize` but with minimum.
  * `square(T value)`: returns value^2.
  * `bool implies(bool p, bool q)`: returns p=>q

## The `bchain` class ##

The `bchain` class (Boolean Chain) is meant to chain boolean operations, such as
```
    value1 < value2 <= value3 ...
```

In order to perform such operations, use `bchain` as follows:
```
    bchain(value1) < value2 <= value3
```
You can build a bchain from the first (or second) value, then chain the comparisons, and put all that into an `if`, `while`, etc., or even a boolean variable.

A more complete example:
```
    if (4 <= bchain(value) <= 5)
       do_something();
```

If you want to use the same value several times, you can declare a bchain once as a variable: `_bchain<T>(value) variable;`.


## The `Randomizer` class ##

This class is a standalone random number generators (meaning that may exist several instances, each one having its own seed).
The class is constructed with the desired range in which the random numbers will be generated:
```
   Randomizer<T>(T min, T max);
```

It also provides the `get` method to get the next random number:
```
   Randomizer<float> r(0.0f, 1.0f);
   float number = r.get();
```


Internally, the class has a specialization for integral types and for floating point types for better results.


## The `FirstTimeFlag` class ##

This class is useful for iterations, when something special has to be done the first time.
An instance of this class can be evaluated in a condition (i.e. in an `if`), and automagically is self-set to `false` afterwards.

For example:
```
   FirstTimeFlag first_iteration;

   while (something)
   {
      do_something();

      if (first_iteration)
          do_something_once();
   }
```