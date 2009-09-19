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
#include "include/mili.h"

int main()
{
    Randomizer<float> rnd(10.0f, 11.0f);

    std::cout << rnd.get() << std::endl;

    if (bchain(1) < 2 < 3)
        std::cout << "1 < 2 < 3 -> TRUE" << std::endl;

    int x(10);
    if (5 >= bchain(4) < 10 == x)
        std::cout << "5 >= 4 < 10 == x -> TRUE" << std::endl;

    if (in_range(rnd.get(), 10.0f, 11.0f))
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;
}

