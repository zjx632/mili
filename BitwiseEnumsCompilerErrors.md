# Introduction #

Some compilers (such as the SUN's Solaris for x86) complain with error messages similar to
> Cannot cast from bitwise\_enum<std::ios\_base::open\_mode> to int

This is because their STL's implementation of streams clashes with the declaration of the bitwise\_enum class.
Just place the bitwise\_enum (along with the rest of MiLi) inside the `mili` namespace by #defining `MILI_NAMESPACE` and you're done. See the example below.

# Example #
The following example (same as the one packed) encloses the MiLi classes into the `mili` namespace. (look for `mili::` in this code, or the '**HERE!**' comment).

```
#include <iostream>
using std::cout;

#define MILI_NAMESPACE                                // HERE!
#include "mili.h"


enum MasksSet1
{
    kZero     = 0,
    kOne      = 1,
    kTwo      = 2,
    kThree    = 4,
    kFour     = 8
};

typedef mili::bitwise_enum<MasksSet1> M1;      // HERE!

void show_bits(M1 b)
{
    if (b.has_bits(kZero))  cout << "kZero  turned on\n";
    if (b.has_bits(kOne))   cout << "kOne   turned on\n";
    if (b.has_bits(kTwo))   cout << "kTwo   turned on\n";
    if (b.has_bits(kThree)) cout << "kThree turned on\n";
    if (b.has_bits(kFour))  cout << "kFour  turned on\n";
}

int main()
{
    using namespace mili;                     // HERE!
    show_bits(kOne | kTwo);
   
    return 0;
}
```