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

static void generate_file_with_separator(const char* name, char sep)
{
    std::ofstream f(name);
    std::set<float> v;

    _Separator< std::set<float> > s = Separator(v, sep);

    for (int i = 0; i < 10; i++)
    {
        v.clear();
        for (int j = 0; j <= 10; j++)
            insert_into(v, static_cast<float>(j));

        s.v = v;

        f << s ; /* PROVIDED BY MiLi */
        f << std::endl;
    }
}

/*load a file into a vector*/
static void load_file_with_separator_v(const char* name, char sep)
{
    std::ifstream f(name);
    std::vector<float> v;
    _Separator< std::vector<float> > s = Separator(v, sep);

    while (f >> s)  /* PROVIDED BY MiLi */
    {
        for (int j = 0; j < s.v.size(); ++j)
        {
            ASSERT_EQ(s.v[j], j);
        }

        ASSERT_EQ(s.v.size(), 11);
        s.v.clear();
    }
}

/* This loads a file into a list */
static void load_file_with_separator_l(const char* name, char sep)
{
    std::ifstream f(name);
    std::list<float> v;
    std::list<float>::iterator pos;
    int j;
    _Separator< std::list<float> > s = Separator(v, sep);

    while (f >> s)  /* PROVIDED BY MiLi */
    {
        j = 0;
        pos = s.v.begin();
        for (; pos != s.v.end(); pos++)
        {
            ASSERT_EQ(*pos, j);
            ++j;
        }

        ASSERT_EQ(s.v.size(), 11);
        s.v.clear();
    }
}

/* This loads a file into a set */
static void load_file_with_separator_s(const char* name, char sep)
{
    std::ifstream f(name);
    std::set<float> v;
    std::set<float>::iterator pos;
    int j;
    _Separator< std::set<float> > s = Separator(v, sep);

    while (f >> s)  /* PROVIDED BY MiLi */
    {
        j = 0;
        pos = s.v.begin();
        for (; pos != s.v.end(); pos++)
        {
            ASSERT_EQ(*pos, j);
            ++j;
        }

        ASSERT_EQ(s.v.size(), 11);
        s.v.clear();
    }
}

/* This loads a file generating an eror but not exceptions */
static void load_file_without_exception(const char* name)
{
    std::ifstream f(name);
    std::vector<float> v;

    if (!(f >> v))
    {
        ASSERT_EQ(true, f.fail()); /* fail is true if either badbit or failbit is set*/
        ASSERT_EQ(false, f.good());

    }

}
/* This tries to write a file then raises an exception */
static void write_file_with_exception(const char* name)
{
    std::ofstream f(name);
    std::vector<float> v;
    std::string message;
    f.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    for (int j = 0; j <= 10; j++)
        insert_into(v, static_cast<float>(j));
    f.close(); /*closing file will produce an expcetion*/

    try
    {
        f << v; /* PROVIDED BY MiLi */
    }
    catch (const std::exception& e)
    {
        message = e.what();
    }

    ASSERT_NE(message, ""); /* Empty message means no exception */
}

/* This tries to read a file then raises an exception */
static void read_file_with_exception(const char* name)
{

    std::ifstream f(name);
    std::vector<float> v;
    std::string message;
    f.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    f.close(); /* Closing file will produce an expcetion */

    try
    {
        f >> v;  /* PROVIDED BY MiLi */
    }
    catch (const std::exception& e)
    {
        message = e.what();
    }

    ASSERT_NE(message, ""); /* Empty message means no exception */
}

TEST(StreamUtilsTest, testReadWithException)
{
    const char file[] = "stream-utils.test";
    generate_file(file);
    read_file_with_exception(file);
    remove(file);
}
TEST(StreamUtilsTest, testWriteWithException)
{
    const char file[] = "stream-utils.test";
    write_file_with_exception(file);
    remove(file);
}

TEST(StreamUtilsTest, testErrosWithoutException)
{
    const char file[] = "stream-utils.test";
    load_file_without_exception(file);
    remove(file);
}


TEST(StreamUtilsTest, testReadWithGenericSeparator)
{
    const char file[] = "stream-utils.test";
    generate_file_with_separator(file, ';');
    load_file_with_separator_v(file, ';');
    load_file_with_separator_l(file, ';');
    load_file_with_separator_s(file, ';');
    remove(file);
}

