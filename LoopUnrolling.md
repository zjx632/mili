# Introduction #

This minimalistic library is used to perform loop unrolling during compile time.
This can be used either for known (constant) iterations loops (i.e. amount bits of a type),
or to aid vectorization, in both cases for performance speedup.

You basically provide the operation and the number of iterations to the `FOR` template structure.
Optionally, you may also specify (and extend) a clause to rule when to unroll and when to perform a normal `for` statement.

With g++, you may need -O3 for this to be effectively unrolled.

# Details #

The `FOR` template structure has two syntaxes:
  * `FOR<N, Operation>::iterate(Operation& op)`: call `op()` N times (no loop).
  * `FOR<N, Operation, UnrollClause>::iterate(Operation& op)`: do `op()` N times in an unrolled or regular loop, depending on the value of `UnrollClause::clause<N>::unroll`.

Example:

```
inline size_t CountBits(int x)
{
    struct BitCounter
    {
        int value;
        size_t ret;
        BitCounter(int value) : value(value), ret(0){}

        void operator()()
        {
            ret += value & 1;
            value >>= 1;
        }
    } bc(x);

    FOR<sizeof(int)*8, BitCounter>::iterate(bc);
    return bc.ret;
}
```

Note that the operation (`BitCounter` in the example) shall be a functor.

## Unroll Clauses ##

An unroll clause tells the `FOR` template structure when to unroll.
An unroll clause has to provide an inner template class `template <unsigned int N> class clause` (receiving the number of iterations as the template argument), which in terms provides an enumeration `unroll` which will be casted to bool.

An unroll clause will be evaluated in a similar manner of
```
   TheClause::clause<N>::unroll
```

Thus, an example could be:
```
struct UnrollUpTo8
{
    template <unsigned int N>
    struct clause
    {
        enum { unroll = (N <= 8) };
    };
};
```

The library provides the following unroll clauses:
  * `UnrollAlwaysClause`: (this is the default) - unroll always regardless of the number of iterations.
  * `UnrollUpToClause<MAX>`: a template clause receiving the maximum number of iterations to unroll; more than `MAX` will result in a regular `for` loop. The last example is equivalent to `UnrollUpToClause<8>`.