# Introduction #
The header consists only of preprocessor macros that are selectively defined depending on the compiler and the operating system.

# Operating System #
For the Operating System part, the following macro:
```
MILI_OS
```
will be defined as one of the following values, also defined in macros:
```
#define MILI_OS_LINUX   	1
#define MILI_OS_WINDOWS 	2
#define MILI_OS_MAC     	3
#define MILI_OS_UNKNOWN 	4
```
for the operating systems: "Linux", "Windows", "Mac" or "Other" respectively.

# Compiler #
For the Compiler part, the following macro:
```
MILI_COMPILER
```
will be defined as one of the following values, also defined in macros:
```
#define MILI_COMPILER_VS		1
#define MILI_COMPILER_GCC		2
#define MILI_COMPILER_ICC		3
#define MILI_COMPILER_UNKNOWN		4
```
for the compilers: "Visual C++", "GNU-GCC", "Intel C/C++" and "Other" respectively.

# Exceptions Support #
The following macro:
```
MILI_EXCEPTIONS_COMPILER_ENABLED
```
will be defined for gcc and icc only if exceptions are allowed. For all other compilers, this macro will be defined by default.