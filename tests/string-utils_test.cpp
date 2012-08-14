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
#include <map>
#include "mili/mili.h"

using namespace mili;

TEST(StringUtilsTest, lstring_test)
{
    lstring ls("helLO");
    ls[1] = 'E';

    ASSERT_TRUE(ls[2] == 'L');
    ASSERT_TRUE(ls == "HELLO");

    std::map<lstring, int> m;
    m["Hello"] = 3;
    m["Goodbye"] = 5;
    ASSERT_EQ(3, m["hELLo"]);

    ASSERT_TRUE(begins_with(ls, "HE"));
    ASSERT_TRUE(ends_with(ls, "Ello"));
}

TEST(StringUtilsTest, toupper)
{
    ASSERT_EQ("HELLO WORLD!", toupper("Hello World!"));
}

TEST(StringUtilsTest, to_string)
{
    ASSERT_EQ("123.4", to_string(123.4));
}

TEST(StringUtilsTest, to_number)
{
    int n;
    ASSERT_FALSE(to_number("abc", n));
    ASSERT_EQ(123.4f, to_number<float>("123.4"));
}

TEST(StringUtilsTest, ensure_found)
{
    std::string str = "Why?";
    ASSERT_TRUE(ensure_found(str.find_first_of("h", 0)));
    ASSERT_THROW(ensure_found(str.find_first_of(" ", 0)), StringNotFound);
    ASSERT_EQ(str.size(), ensure_found(str.find_first_of(" ", 0), str.size()));
}

TEST(StringUtilsTest, substr)
{
    ASSERT_EQ("llo Wo", substr("Hello World", _Pos(2), _Count(6)));
    ASSERT_EQ("llo W", substr("Hello World", _Pos(2), _Pos(6)));
}

