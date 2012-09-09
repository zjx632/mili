/*
invariants: A minimal library for checking invariants.
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

using namespace mili;
using std::cout;

invariant::NeverNull<const char> get_message(invariant::InRange < int, -1, 1 > /*number*/)
{
    return "Hello World\n";
}

struct AClass
{
    int x;
    int y;
    void setxy(int newx, int newy)
    {
        x = newx;
        y = newy;
    }
};

bool AClassInvariant(const AClass& aclass)
{
    return aclass.x + aclass.y > 0;
}

typedef InvariantClass<AClass, AClassInvariant> AClass_inv;

int main()
{
    const char* msg = get_message(-1);
    cout << msg;

    AClass aclass;
    AClass_inv inv(aclass);
    inv->setxy(3, 4);
    cout << inv->x << std::endl;

    return 0;
}
