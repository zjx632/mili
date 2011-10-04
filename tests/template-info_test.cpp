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
#include <vector>
#include <set>
#include "mili/mili.h"

using namespace mili;

struct S {};

TEST(TemplateInfoTest, is_native)
{
    ASSERT_FALSE(bool(template_info<S>::is_native));
    ASSERT_TRUE(bool(template_info<char>::is_native));
}

TEST(TemplateInfoTest, is_same_size)
{
    ASSERT_EQ(sizeof(int) == sizeof(long int), bool(template_info<int>::is_same_size<long int>::value));
}

TEST(TemplateInfoTest, is_container)
{
    ASSERT_TRUE(bool(template_info<std::vector<int> >::is_container));
    ASSERT_TRUE(bool(template_info<std::set<int> >::is_container));
}

TEST(TemplateInfoTest, is_const)
{
    ASSERT_TRUE(bool(template_info<const int>::is_const));
    ASSERT_TRUE(bool(template_info<const int*>::is_const));
}
