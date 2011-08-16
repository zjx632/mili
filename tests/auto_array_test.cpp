/*
    Copyright (C) 2011 Hugo Arregui, FuDePAN

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
#include "mili/mili.h"

using namespace mili;

TEST(AutoArrayTest, create)
{
    auto_array<int> p(new int[30]);
}

TEST(AutoArrayTest, get)
{
    auto_array<int> p(new int[30]);
    int* array = p.get();
    ASSERT_TRUE(array != NULL);
}

TEST(AutoArrayTest, subscript)
{
    auto_array<int> p(new int[30]);
    p[1] = 1;
    ASSERT_EQ(1, p[1]);
}

TEST(AutoArrayTest, release)
{
    auto_array<int> p(new int[30]);
    p.release();
    ASSERT_TRUE(p.get() == NULL);
}

TEST(AutoArrayTest, reset)
{
    int* other = new int[20];
    auto_array<int> p(new int[30]);
    p.reset(other);
    ASSERT_EQ(other, p.get());
}
