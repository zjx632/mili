# Introduction #
Use this library to get the RAII feature on your objects, to release resources after this objects are no longer useful or before permitting propagate exceptions.

# Details #
To instantiate the class template, must provide the type of your object, and the method you want to be called in the destructor of the raii class.
(i.e RAII<TYPE, &TYPE::method>)

If you have two or more methods to be called in the raii's class destructor, you must to make one instantiate for every method.
(i.e RAII<TYPE, &TYPE::method1> <TYPE, &TYPE::method2>)