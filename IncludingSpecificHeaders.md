# Introduction #

If (for some reason) you want to include only one header rather than `mili/mili.h`, you will have to define the following macros: (I'll update this later).

```
#define NAMESPACE_BEGIN
#define NAMESPACE_END
```


However, it's preferable to #include mili and disable the unwanted headers using the specific macro. For example, if you want to avoid bitwise enums:

```
#define NO_BITWISE_ENUMS
#include "mili/mili.h"
```