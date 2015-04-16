A very simple, 0-overhead, and yet type-safe 1-file library for doing bitwise operations between masks represented by enums.

For example, given:
```
enum ClearBufferMask
{
    GL_DEPTH_BUFFER_BIT    = 0x00000100,
    GL_ACCUM_BUFFER_BIT    = 0x00000200,
    GL_STENCIL_BUFFER_BIT  = 0x00000400,
    GL_COLOR_BUFFER_BIT    = 0x00004000,
};

void glClear(unsigned int mask);
```

the problem is that any bitwise operation between `ClearBufferMask` elements will loose the type, and will be casted to int. Thus, type-checking will be disabled, and `glClear()` can be called with any integer value.

`bitwise_enum` class wrapper just provides all the bitwise operations over a given enum (as a template parameter), always keeping the type. Given that, `glClear` can now be declared as:
```
void glClear( bitwise_enum<ClearBufferMask> mask );`

int main()
{
   glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );   // OK
   glClear( 0x00004000 | 0x00000100); // ERROR!
}
```

Got compiler errors? Click [here](BitwiseEnumsCompilerErrors.md).