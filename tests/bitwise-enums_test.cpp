/*
    Copyright (C) 2011 Hugo Arregui FuDePAN
                  2011 Adrian Remonda FuDePAN

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

#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mili/mili.h"

using namespace mili;
using std::cout;

enum MasksSet1
{
    kZero   = 0,
    kOne    = 1,
    kTwo    = 2,
    kThree  = 4,
    kFour   = 8
};
BITWISE_ENUM_ENABLE(MasksSet1)

enum MasksSet2
{
    kEight   = 8,
    kSixteen = 16,
};

typedef bitwise_enum<MasksSet1> M1;

TEST(BitwiseEnumsTest, test)
{
    M1 b = kOne | kFour;

    ASSERT_FALSE(b.has_bits(kZero));
    ASSERT_TRUE(b.has_bits(kOne));
    ASSERT_FALSE(b.has_bits(kTwo));
    ASSERT_FALSE(b.has_bits(kThree));
    ASSERT_TRUE(b.has_bits(kFour));

    ASSERT_TRUE(kFour | kEight);
    ASSERT_TRUE(kSixteen | kEight);

    ASSERT_EQ(0x24u, b << 2);
}
