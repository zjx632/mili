/*
    Copyright (C) 2011  Hugo Arregui, FuDePAN

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

    This is a test file.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "mili/mili.h"

using std::cout;
using namespace mili;

invariant::NeverNull<const char> get_message(invariant::InRange < int, -1, 1 > number)
{
    return "Hello World\n";
}

TEST(InvariantsTest, function_invariant)
{
    ASSERT_EQ("Hello World\n", get_message(-1));
    ASSERT_THROW(get_message(2), InvariantNotMet);
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
};

typedef InvariantClass<AClass, AClassInvariant> AClass_inv;

TEST(InvariantsTest, class_invariant)
{
    AClass aclass;
    AClass_inv inv(aclass);
    inv->setxy(3, 4);
    ASSERT_EQ(3, inv->x);
    ASSERT_THROW(inv->setxy(-9, 0), InvariantNotMet);
}
