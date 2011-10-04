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

using namespace mili;

TEST(MetaprogrammingUtils, testTrue)
{
    const bool result = mili::template_info<Select<true, int, float>::value>::is_equal_to<int>::value;
    ASSERT_TRUE(result);
}

TEST(MetaprogrammingUtils, testFalse)
{
    const bool result = mili::template_info<Select<false, int, float>::value>::is_equal_to<float>::value;
    ASSERT_TRUE(result);
}


