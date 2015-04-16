# Abstract #

MiLi is a collection of useful C++ libraries, composed only by headers.
No installation, no makefile, no complications: just KISS. Simple solutions for simple problems.

# Libraries #
MiLi version 17 includes the following libraries (one header file length each):

  * **[bitwise-enums](BitwiseEnums.md)**: library for type-safe bitwise operations based on enums.
  * **[pre-pos caller](PrePosCaller.md)**: library for wrapping object methods calls.
  * **[promotion-disable](PromotionDisable.md)**: library for disabling undesired C++ type conversions.
  * **[delete-container](DeleteContainer.md)**: deletes the elements of an STL container filled with pointers.
  * **[factory](Factory.md)**: provides a simple machinery to create subclasses from a given key.
  * **[invariants](Invariants.md)**: provides invariants for function arguments and classes.
  * **[type-mapper](TypeMapper.md)**: simple type mapping declarations.
  * **[properties](Properties.md)**: simple properties implementation.
  * **[string-utils](StringUtils.md)**: various string utilities, such as case-insensitive strings and number/text conversions.
  * **[container-utils](ContainerUtils.md)**: **UPDATED!** generic STL container utilities, optimized for specific containers. (formerly find-utils).
  * **[stream-utils](StreamUtils.md)**: i/o stream utilities for reading/writing formatted data (such as CSV).
  * **[arith-utils](ArithUtils.md)**: **FIXED!** arithmetic utilities (random numbers, range checks).
  * **[binary-streams](BinaryStreams.md)**: binary streams for serializing data.
  * **[loop-unrolling](LoopUnrolling.md)**: compile-time loop unrolling using TMP.
  * **[compile-assert](CompileAssert.md)**: compile-time (a.k.a. static) assertions.
  * **[template-info](TemplateInfo.md)**: template parameters information (a la typeinfo).
  * **[fast-list](FastList.md)**: very optimized list for high performance.
  * **[ranker](Ranker.md)**: **UPDATED!** ranker library.
  * **[coroutines](CoRoutines.md)**: simple and os-independant coroutines library.
  * **[generic exception](GenericException.md)**: utilities to generate a custom exception hierarchy.
  * **[variants-set](VariantsSet.md)**: **NEW!** a simple set of heterogenic types library.
  * **[circular-buffer](CircularBuffer.md)**: **NEW!** A circular buffer.
  * some more new libraries not documented yet.

## NEWS: License change! ##
MiLi has changed the license from GPLv3 to Boost 1.0, making it suitable for some commercial projects and still being free software.

# Donations #
MiLi is maintained at FuDePAN, an NGO/NPO for bioinformatics research. If you find MiLi useful, please consider to donate so we can keep up the research and maintenance.

[![](https://www.paypal.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=BKPL5FYMLGXFQ&lc=AR&item_name=FuDePAN&item_number=mili&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donateCC_LG%2egif%3aNonHosted)


# Usage #

Just #include "mili.h". You can disable then inclusion of individual libraries by adding a specific #define (refer to README), or just include specific headers ([note](IncludingSpecificHeaders.md)).
Additionally, you may enclose all the libraries within the `mili` namespace by #defining `MILI_NAMESPACE` before including "mili.h".

# More Libraries #

Coming soon: PendingLibraries

Feel free to ask for more functionalities.

Need it for commercial use? Contact the email address contained in the README.

# Contributing #
See HowToContribute.


---

This project belongs to [FuDePAN](http://www.fudepan.org.ar).
&lt;wiki:gadget url="http://www.revolvermaps.com/gadget/rm2\_gadget.xml" height="180" width="180" &gt;