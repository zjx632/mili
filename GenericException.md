# Introduction #

Generic exception allows you to define your own exception hierarchy in a simple manner.

It also provides assert\_throw, which replaces the
```
if (failure_condition)
{
     throw some_exception;
}
```
idiom.

# Details #

## `GenericException` ##

Mili's `GenericException` template receives the base class of your exception hierarchy.

You can typedef `GenericException<YourBaseException>` to some shortened name you prefer, for instance:
```
struct MyExceptionHierarchyBase
{};

typedef GenericException<MyExceptionHierarchyBase> MyMiliException;
```

Once you have the typedef above, you can use:
```
DEFINE_SPECIFIC_EXCEPTION_TEXT(NewExceptionType, MyMiliException, "Text of the exception");
```
to define a new exception class called _NewExceptionType_.

You can also use
```
DEFINE_SPECIFIC_EXCEPTION(NewExceptionType, MyMiliException)
```
which is a shortcut for
```
DEFINE_SPECIFIC_EXCEPTION(NewExceptionType, MyMiliException, #NewExceptionType)
```

## `AssertThrow` ##

assert\_throw checks a condition; if it fails, it throws a predefined exception. It is a templetized function that receives the exception it is meant to throw as a template parameter, and the boolean expression it should evaluate as argument.

For instance, writing
```
    assert_throw<NewExceptionType>(some_condition);
```
is equivalent to
```
if (!some_condition)
{
     throw NewExceptionType;
}
```