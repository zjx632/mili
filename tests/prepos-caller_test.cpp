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
*/
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mili/mili.h"
#include "mili/prepos_printer.h"
#include "mili/prepos_mutex.h"

using namespace mili;

class PrePosMock
{
public:
    void operator()() const
    {
        mocked_operator();
    }
    MOCK_CONST_METHOD0(mocked_operator, void());

};

class Foo
{
public:
    MOCK_CONST_METHOD0(f, void());
};

TEST(PreposCallerTest, bchain)
{
    Foo t;
    PrePosMock pre, pos;
    PrePosCaller<Foo * const, PrePosMock, PrePosMock> ppc(&t, pre, pos);
    testing::Expectation pre_expectation = EXPECT_CALL(pre, mocked_operator()).Times(1);
    testing::Expectation f_expectation = EXPECT_CALL(t, f()).Times(1).After(pre_expectation);
    EXPECT_CALL(pos, mocked_operator()).Times(1).After(f_expectation);
    ppc->f();
}
