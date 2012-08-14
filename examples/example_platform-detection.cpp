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

    This is an example file.
*/

#include <iostream>
#include "mili/mili.h"

/* Operating System example */
#if defined (MILI_OS)
#    if   MILI_OS == MILI_OS_LINUX
#        define OS_STRING "Linux"
#    elif MILI_OS == MILI_OS_WINDOWS
#        define OS_STRING "Windows"
/*#    elif MILI_OS == MILI_OS_MAC
#        define OS_STRING "Mac"*/
#    elif MILI_OS == MILI_OS_UNKNOWN
#        define OS_STRING "Unknown"
#    else
#        define OS_STRING "Error (MILI_OS has an invalid value)"
#    endif

#else /* !defined (MILI_OS) */
#    define OS_STRING "Error (MILI_OS is not defined)"

#endif /* defined (MILI_OS) */

/* Compiler example */
#if defined (MILI_COMPILER)
#    if   MILI_COMPILER == MILI_COMPILER_VS
#        define COMPILER_STRING "Visual C++"
#    elif MILI_COMPILER == MILI_COMPILER_GCC
#        define COMPILER_STRING "GNU-GCC"
/*#    elif MILI_COMPILER == MILI_COMPILER_ICC
#        define COMPILER_STRING "Intel C/C++"*/
#    elif MILI_COMPILER == MILI_COMPILER_UNKNOWN
#        define COMPILER_STRING "Unknown"
#    else
#        define COMPILER_STRING "Error (MILI_COMPILER has an invalid value)"
#    endif

#else /* !defined (MILI_COMPILER) */
#    define COMPILER_STRING "Error (MILI_COMPILER is not defined)"

#endif /* defined (MILI_COMPILER) */

int main()
{
    int result = EXIT_SUCCESS;

    std::cout<<"switch/case output: ";

    /* Another Operating System example */
    switch(MILI_OS)
    {
        case MILI_OS_LINUX:
            std::cout<<"Linux"; 
            break;
        case MILI_OS_WINDOWS:
            std::cout<<"Windows";
            break;
        /*case MILI_OS_MAC:
            std::cout<<"Mac";
            break;*/
        case MILI_OS_UNKNOWN:
            std::cout<<"Unknown";
            break;
        default:
            std::cout<<"Error (MILI_OS has an invalid value)";
            result = EXIT_FAILURE;
    }

    std::cout<<" OS / ";

    /* Another Compiler example */
    switch(MILI_COMPILER)
    {
        case MILI_COMPILER_VS:
            std::cout<<"Visual C++"; 
            break;
        case MILI_COMPILER_GCC:
            std::cout<<"GNU-GCC";
            break;
       /* case MILI_COMPILER_ICC:
            std::cout<<"Intel C/C++";
            break;*/
        case MILI_COMPILER_UNKNOWN:
            std::cout<<"Unknown";
            break;
        default:
            std::cout<<"Error (MILI_COMPILER has an invalid value)";
            result = EXIT_FAILURE;
    }

    std::cout<<" Compiler"<<std::endl;
    
    std::cout<<"Conditional compilation output: " OS_STRING " OS / " COMPILER_STRING " Compiler"<<std::endl;

    return result;
}

