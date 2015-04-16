# Introduction #

This library helps to define object properties, causing minimal impact on the containing class.
Properties are method wrappers that take action when getting or setting an object attribute, without exposing the attribute to the class user.

This is useful for example when an attribute can be treated in different ways, but always referring to the same attribute. For example, a temperature attribute could be referred in Celcius or Kelvins, but the data attribute is always the same: so you declare the attribute once, but provide two sets of getter/setter, one for each unit, performing the conversion in them.

# Details #

This library provides wrappers to call a class' setter/getters without the calling syntax.
For example, suppose there's an attribute `a` of class `MyClass`, so you need to do some custom code either when you get or set `a`:
```
   MyClass obj;
   obj.a = value;   /* do something here*/
   value = obj.a;   /* do something else here */
```

The actions to perform (when setting or getting the value) shall be member functions: the setter and the getter respectively.

To do this, you have to do these things in this sequence:
  1. declare the accessors members before any attribute is defined in the class
  1. then declare the properties using the macros and classes of the librar (described below)
  1. finally declare the attributes

## Library Macros and Classes ##

This library provides the classes `PropertyR`, `PropertyW`, `PropertyRW` for declaring read-only, write-only, and read/write properties respectively.
Use the PROPERTIES{} block to define the properties within the class, always in the public section.

The signature of the classes are:
  * `PropertyR<ContainingClass, Type, Getter>`
  * `PropertyW<ContainingClass, Type, Setter>`
  * `PropertyRW<ContainingClass, Type, Getter, Setter>`

The signature of the `Getter` shall be: `Type ContainingClass::Getter() const`.
The signature of the `Setter` shall be: `void ContainingClass::Setter(Type)`.

# Example #
```
class MyClass
{
    int getter() const
    {
        return _value;
    }

    void setter(int newval)
    {
        _value = newval;
    }

public:
PROPERTIES
{
    PropertyRW<MyClass, int, &MyClass::getter, &MyClass::setter> x;
};

private:
    int _value;
};

int main()
{
    MyClass obj;
    obj.x = 1;
    return obj.x;
}
```




---

_thanks jkrause for the feedback!_