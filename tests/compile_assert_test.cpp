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

#ifndef __GXX_EXPERIMENTAL_CXX0X__

#define COMPILE_ASSERT_TEST
#include "mili/mili.h"

using namespace mili;

declare_static_assert(assert1);

TEST(CompileAssert, test_no_fail)
{
    compile_assert(sizeof(char) == 1, assert1);
    ASSERT_TRUE(bool(template_info<assert1__>::is_equal_to<int>::value));
}

declare_static_assert(assert2);
TEST(CompileAssert, test_fail)
{
    compile_assert(sizeof(char) == 2, assert2); // fails
    ASSERT_TRUE(bool(template_info<assert2__>::is_equal_to<float>::value));
}

#endif
