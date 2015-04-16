# Introduction #

The idea of this library is to create subclasses of a base class, given a key.
The rationale is:
  1. You create the Factory specifying what (base) class it will create, the key type, and optionally the argument of the constructors.
  1. You register the subclasses you will want to create, each one identified with a key
  1. You ask the factory to create subclasses by giving the key.

# Details #

Suppose you have a shape class hierarchy: Shape is the base class, then Circle and Rectangle are derived classes.
You would like to create the subclasses, without knowing the implementation, by providing some sort of key, for example, a string containing either "circle" or "rectangle" or whatever name you want.

To do this, you first create the `Factory` as follows:
```
   Factory<string, Shape> my_factory;
```

Then, you'll register the possible subclasses:
```
   my_factory.register_class<Circle>("circular_shape");
   my_factory.register_class<Rectangle>("rectangular_shape");
```

Finally, you can then be abstracted of the sub classes, just knowing Shape and the keys:
```
   Shape* ashape = my_factory.new_class("circular_shape");
```

If the key doesn't match with any registered subclass, `NULL` is returned.

So, the most important methods of Factory are:
  * In `template <class Key, class BaseClass, class ParameterType = void> class Factory;`:
    * `void register_class<SubclassType>(Key key);`
    * `BaseClass* new_class(Key key [, ParameterType p]);`

As you can see, the default parameter type is `void`, meaning that the factory will invoke the default constructor.

# Contributors #
Original Idea: Marcelo Caro
Implementation: Daniel Gutson