/*
    Copyright (C) 2012 Lucas Paradisi, FuDePAN

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
#include <set>
#include <list>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define BSTREAMS_DEBUG
#include "mili/mili.h"

using namespace mili;


std::string get_TypeId(const std::string& s)
{
    size_t a;

    s.copy(reinterpret_cast<char*>(&a), sizeof(size_t), 0);

    return s.substr(sizeof(size_t), sizeof(char) * a);
}

struct A
{
    unsigned int id;
    std::string name;
    long double a;

    A()
        : id(0), name(), a(0)
    {}

    A(unsigned int Id, const std::string& Name, long double A)
        : id(Id), name(Name), a(A)
    {}

    friend bostream& operator<<(bostream& out, const A& o)
    {
        out << o.id << o.name << o.a;
        return out;
    }

    friend bistream& operator>>(bistream& in, A& o)
    {
        in >> o.id >> o.name >> o.a;
        return in;
    }

};


TEST(BinaryStream, BSTREAMS_DEBUG_identifier_test)
{
    bostream bos;

    bos << -13;
    ASSERT_EQ(typeid(int).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << 13u;
    ASSERT_EQ(typeid(unsigned int).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << 1.2f;
    ASSERT_EQ(typeid(float).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << 's';
    ASSERT_EQ(typeid(char).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << double(1.22);
    ASSERT_EQ(typeid(double).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << 1.22L;
    ASSERT_EQ(typeid(long double).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << std::string("FuDePAN");
    ASSERT_EQ(typeid(uint32_t).name(), get_TypeId(bos.str()));
    bos.clear();
}

TEST(BinaryStream, BSTREAMS_DEBUG_chainedValues_test)
{
    bostream bos;
    A a_original(3, "pepe", 43);

    bos << 1.2f << 3 << double(0.89) << a_original << true;

    bistream bis(bos.str());
    float f_loaded;
    int i_loaded;
    double d_loaded;
    A a_loaded;
    bool b_loaded;
    bis >> f_loaded >> i_loaded >> d_loaded >> a_loaded >> b_loaded;

    ASSERT_EQ(1.2f, f_loaded);
    ASSERT_EQ(3, i_loaded);
    ASSERT_EQ(double(0.89), d_loaded);
    ASSERT_EQ(3, a_loaded.id);
    ASSERT_EQ("pepe", a_loaded.name);
    ASSERT_EQ(43, a_loaded.a);
    ASSERT_TRUE(b_loaded);
}

TEST(BinaryStream, BSTREAMS_DEBUG_contaniers_test)
{
    bostream bos;
    std::vector<int> integers_original(16, -4);
    std::set<unsigned> set_original;
    std::list<char> list_original(4, 't');
    double numbers_original[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    set_original.insert(1000);
    set_original.insert(100);
    set_original.insert(10);
    set_original.insert(1);

    bos << integers_original << set_original << list_original << numbers_original;

    std::vector<int> integers_loaded;
    std::set<unsigned> set_loaded;
    std::list<char> list_loaded;
    double numbers_loaded[9];
    bistream bis(bos.str());
    bis >> integers_loaded >> set_loaded >> list_loaded >> numbers_loaded;

    for (int i = 0; i < 16; ++i)
    {
        ASSERT_EQ(-4, integers_loaded[i]);
    }

    std::set<unsigned>::iterator it = set_loaded.begin();
    ASSERT_EQ(1, *it++);
    ASSERT_EQ(10, *it++);
    ASSERT_EQ(100, *it++);
    ASSERT_EQ(1000, *it);

    for (std::list<char>::iterator it1 = list_loaded.begin(); it1 != list_loaded.end(); ++it1)
    {
        ASSERT_EQ('t', *it1);
    }

    for (int i = 0; i < 9; ++i)
    {
        ASSERT_EQ(i + 1, numbers_loaded[i]);
    }
}
