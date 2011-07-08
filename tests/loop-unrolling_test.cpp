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
#include "mili/mili.h"

#include <iostream>
using namespace mili;

using std::cout;

template <class T>
struct BitCounter
{
    T value;
    size_t ret;
    BitCounter(T value) : value(value), ret(0) {}

    void operator()()
    {
        ret += value & 1;
        value >>= 1;
    }
};

template <class T>
inline size_t CountBits(T x)
{
    BitCounter<T> bc(x);
    FOR<sizeof(T) * 8, BitCounter<T> >::iterate(bc);
    return bc.ret;
}

TEST(LoopUnrollingTest, test)
{
    int i = -1;
    ASSERT_EQ(32, CountBits(i));
}


