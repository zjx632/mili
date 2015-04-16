# Abstract #

This one-file library helps to specify functions with specific parameter types, controlling what promotions/demotions are available.
Conversion rules can be specified, and a hierarchy tree of conversion rules can also be defined.

# Example #

Use Case 1: Define a function that can **only** receive floats, not doubles or any other type.

```
void f(Restrict<float> rf);

void g()
{
   f(1.0f);
   f(2); //Error
}
```

Use Case 2: Define a function that can receive floats and allows doubles to be demoted as floats.

```
void f(Restrict<float, FloatingPoints> rf);   /* FloatingPoints allows double to floats conversions */

void g()
{
   f(1.0f);
   f(1.0); // OK
   f(2); //Error
}
```

# Usage #
Use the `Restrict<type,rules>` as parmeter type.
This object provides a `value` member which holds the value passed as parameter.

The `rules` template class parameter has the following template type:
```
template <class ExpectedType, class PassedType>
struct Rule;
```

Specialize each allowed conversion inheriting `AllowConversion` class:
```
template <class ExpectedType, class PassedType> struct Rule : AllowConversion
{};
```

The default conversion rule is `StrictRules`, which doesn't allow any conversion (only the exact specified type is allowed).

To create a new rule, either inherit from another stricter or write it from scratch as follows. `FloatingPoints` described as an example:

```
/* FloatingPoints allows T-->T, plus Double to Float */

/* The generic case inherits from a stricter one */
template <class T, class U>
struct FloatingPoints : StrictRules<T, U>
{};

/* The specific case/s inherit from AllowConversion */
template <>
struct FloatingPoints<float,double>: AllowConversion
{};
```

# Provided Rules #

The following rules are provided:
  * StrictRules: only allows T->T conversions
  * NotNarrowing: prevents conversions to types of smaller sizes, plus float->int