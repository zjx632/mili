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

#include <vector>
#include <fstream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mili/mili.h"

using namespace mili;

static void generate_file(const char* name)
{
    std::ofstream f(name);
    std::set<float> v;

    for (int i = 0; i < 10; i++)
    {
        v.clear();
        for (int j = 0; j <= 10; j++)
            insert_into(v, static_cast<float>(j));

        f << v; /* PROVIDED BY MiLi */
        f << std::endl;
    }
}

static void load_file(const char* name)
{
    std::ifstream f(name);
    std::vector<float> v;

    unsigned int i = 0;
    while (f >> v)  /* PROVIDED BY MiLi */
    {
        Separator(v, '\t');  /* PROVIDED BY MiLi */
        for (int j = 0; j < v.size(); j++)
            ASSERT_EQ(v[j], j);
        v.clear();
        ++i;
    }
    ASSERT_EQ(10, i);
}

TEST(StreamUtilsTest, test)
{
    const char file[] = "stream-utils.test";
    generate_file(file);
    load_file(file);
    remove(file);
}

