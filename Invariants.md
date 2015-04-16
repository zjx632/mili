# Introduction #

The goal of this library is to provide Design By Contract to functions/methods, and class invariants, automagically, and as part of the interface.

What is it? Suppose you've got a function that receives some parameters, and returns something:
```
   /* x shall be > 0 */
   int function(int x);
```

With this library, instead of adding requirements in comments and doing the checks manually, you can write the above function as:
```
   int function(invariant::gt<int, 0> x);
```

Then, each time you call `function()`, the parameter will be checked; if it is <= 0, `InvariantNotMet` exception will be thrown.

# Details #

As mentioned above, two kind of invariants can be specified: individual arguments invariants, and class invariants.

## Individual Arguments Invariants ##

This library provides invariant checks that can be applied to individual function arguments (pre condition) and the returned value (post condition).

For example, suppose an allocation function: the amount of bytes shall be greater than 0, and the returned pointer shall not be NULL:
```
   invariant::NeverNull<char> allocate(invariant::gt<int, 0> bytes);
```

That tells the user that `bytes` is a number > 0, and that a `NULL` pointer will never be returned (so no need to manually check it). `NeverNull` can be also applied to arguments.

All the invariants are defined in the `invariant::` namespace.

The following invariants are provided:
  * With the form `xx<Type, Value>`, xx can be: gt, ge, eq, ne, le, lt (greater than, greater or equal, etc.)
  * `InRange<Type, Min, Max>` checks that `Min <= value <= Max`
  * `NeverNull<Type>` checks that `value != (Type*)NULL`

## Class Invariants ##

A class invariant means that a predicate is always valid for every state of an object.
The predicate is given in the form of a function returning `bool`.

For example, consider:
```
struct AClass
{
    int x;
    int y;
    void setxy(int newx, int newy) { x = newx; y = newy; }
};
```

Then suppose that the sum of `x` and `y` shall always be > 0.

We can then define the class invariant as:
```
bool AClassInvariant(const AClass& aclass) /* the predicate */
{
    return aclass.x + aclass.y > 0;
};

typedef InvariantClass<AClass, AClassInvariant> AClass_inv;
```

The invariant has the form `InvariantClass<Type, Predicate>`.
Then, the invariant has to be instantiated with an instance of the class, and used with the `->` operator:
```
void f()
{
    AClass aclass;    
    AClass_inv inv(aclass);
    inv->setxy(3, 4);
}
```

If the invariant is not met (e.g. by doing `inv->setxy(3, -4)`), the exception `InvariantNotMet` is thrown.