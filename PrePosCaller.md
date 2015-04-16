Pre-Pos caller library is a headers only package, that allows you to wrap and 'intercept' method calls to any object, without modifying your objects' code.
For example, you can add a mutex in order to make object calls thread safe, or want to add debug messages before and after the method calls.

Suppose you have an object, Obj, and you want to print a message before and after every time somebody access the object (either by invoking a method or accessing an attribute):
```
   obj->m();
```

Then, you just have to define a ppc-caller as this:
```
   PrePosPrinter pre("before");
   PrePosPrinter pos("after");

   PrePosCaller<Obj*, PrePosPrinter, PrePosPrinter> ppc(obj, pre, pos);

   ppc->m();
```

The `PrePosCaller ppc` instance provides the same interface that Obj provides.
Every method you invoke to ppc, will be forwarded to obj, but calling pre before and pos afterwards.

Another feature of `PrePosCaller` is the ability to easily chain them, in a stack (LIFO)-fashion.