/*
promotion_disable.h: A minimalistic library to disable undesired
    type promotions in C++.
    Copyright (C) 2009, Daniel Gutson, FuDePAN

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
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    C++ Example.
*/

#include "mili/mili.h"

float f(Restrict<float> rf)
{
    return rf + 1.0f;
}

float g(Restrict<float, FloatingPoints> fp)
{
    return fp + 1.0f;
}

float h(Restrict<double, NotNarrowing> nn)
{
    return nn + 1.2;
}

int main()
{
    f(1.0f);
    // f(1); error
    g(1.0);
    h(2.0);

    return 0;
}
