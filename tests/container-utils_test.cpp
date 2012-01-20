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
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "mili/mili.h"

using namespace std;
using namespace mili;

TEST(ContainerUtilsTest, vector)
{
    vector<int> v;
    v.push_back(1);
    ASSERT_EQ(1, find(v, 1));
    ASSERT_FALSE(contains(v, 2));
}

struct MapTest: public ::testing::Test
{
    void SetUp()
    {
        m["hello"] = "good bye";
        m["Bonjour"] = "au revoir";
        m["ハロー"] = "さようなら";
        m["hola"] = "adios";
        m["buenas"] = "adios";
    }
    map<string, string> m;
};

TEST_F(MapTest, contains)
{
    ASSERT_FALSE(contains(m, "nothing"));
}

TEST_F(MapTest, remove_first_from)
{
    ASSERT_TRUE(remove_first_from(m, "au revoir"));
}

TEST_F(MapTest, remove_all_from)
{
    ASSERT_TRUE(remove_all_from(m, "adios"));
}

TEST_F(MapTest, found)
{
    ASSERT_EQ("good bye", find(m, "hello"));
}

TEST_F(MapTest, not_found)
{
    ASSERT_THROW(find(m, "world"), ElementNotFound);
}

TEST(ContainerUtilsTest, queue)
{
    queue<int> myqueue;
    insert_into(myqueue, 100);
    insert_into(myqueue, 100);
}
