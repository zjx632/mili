/*
arith_utils: A minimal library with arithmetic utilities.
    Copyright (C) 2009  Daniel Gutson, FuDePAN

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

int main()
{
    if (bchain(1) < 2 < 3)
        std::cout << "1 < 2 < 3 -> TRUE" << std::endl;

    int x(10);
    if ((5 >= bchain(4) < 10) == x)
        std::cout << "5 >= 4 < 10 == x -> TRUE" << std::endl;

    float r = power<2>(2);
    std::cout << "2^2 == " << r << std::endl;
    if (r != 4)
    {
        return EXIT_FAILURE;
    }

    r = power<-2>(2);
    std::cout << "2^(-2) == " << r << std::endl;
    if (r != .25)
    {
        return EXIT_FAILURE;
    }

    r = cubic_root(27);
    std::cout << "27^(1/3) == " << r << std::endl;
    if (r != 3)
    {
        return EXIT_FAILURE;
    }

    if (in_range(3.141692f, 10.0f, 11.0f))
        return EXIT_FAILURE;
    else
        return EXIT_SUCCESS;
}

