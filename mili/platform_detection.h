/*
    Copyright (C) 2012 Daniel Muñoz, FuDePAN

    This file is part of the MiLi Minimalistic Library.

    MiLi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MiLi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MiLi.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PLATFORM_DETECTION_H
#define PLATFORM_DETECTION_H

/* There is no need for namespace (NAMESPACE_BEGIN and NAMESPACE_END) */

/* OS detection
   See: http://sourceforge.net/apps/mediawiki/predef/index.php?title=Operating_Systems
*/
#define MILI_OS_LINUX   	1
#define MILI_OS_WINDOWS 	2
#define MILI_OS_MAC     	3
#define MILI_OS_UNKNOWN 	4

/* Windows */
#if   defined (WIN32)		\
   || defined (_WIN32)		\
   || defined (_WIN64)		\
   || defined (__WIN32__)	\
   || defined (__TOS_WIN__)	\
   || defined (__WINDOWS__)
#    define MILI_OS MILI_OS_WINDOWS

/* Linux */
#elif defined (__linux__)	\
   || defined (linux)		\
   || defined (__linux)
#    define MILI_OS MILI_OS_LINUX

/* MAC */
/*#elif defined (macintosh)	\
   || defined (Macintosh)	\
   || defined (__APPLE__)	\
   || defined (__MACH__)
#    define MILI_OS MILI_OS_MAC*/

/* Unknown OS */
#else
#    define MILI_OS MILI_OS_UNKNOWN

#endif /* end OS Detection */



/* Compiler detection
   See: http://sourceforge.net/apps/mediawiki/predef/index.php?title=Compilers
*/
#define MILI_COMPILER_VS		1
#define MILI_COMPILER_GCC		2
#define MILI_COMPILER_ICC		3
#define MILI_COMPILER_UNKNOWN		4

/* Microsoft Visual C++ */
#if   defined (_MSC_VER)
#    define MILI_COMPILER MILI_COMPILER_VS

/* GCC C/C++ */
#elif defined (__GNUC__)
#    define MILI_COMPILER MILI_COMPILER_GCC

/* Intel C/C++ */
/*#elif defined (__INTEL_COMPILER)	\
   || defined (__ICC)			\
   || defined (__ECC)			\
   || defined (__ICL)
#    define MILI_COMPILER MILI_COMPILER_ICC*/

/* Unknown compiler */
#else
#    define MILI_COMPILER MILI_COMPILER_UNKNOWN

#endif /* end Compiler detection */

#endif /* PLATFORM_DETECTION_H */

