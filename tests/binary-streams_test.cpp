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

template <typename T>
void assertArrayEquals(const T& a1, const T& a2, unsigned int size)
{
    bool equals = true;
    int i = 0;
    while (i < size && equals)
    {
        equals = (a1[i] == a2[i]);
        ++i;
    }
    ASSERT_TRUE(equals) << "Arrays not equals";
}

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

struct Z : public A
{
    float asd;
    char d;

    Z()
        : A(), asd(0), d('0')
    {}

    Z(float Asd, char D)
        : A(), asd(Asd), d(D)
    {}

    friend bostream& operator<<(bostream& out, const Z& o)
    {
        out << static_cast<const A&>(o)  << o.asd << o.d;
        return out;
    }

    friend bistream& operator>>(bistream& in, Z& o)
    {
        in >> static_cast<A&>(o) >> o.asd >> o.d;
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

TEST(BinaryStream, BSTREAMS_DEBUG_typemismatch_test)
{
    bostream bos;
    A a;
    Z z;

    bos << a;
    bistream bis(bos.str());

    ASSERT_THROW(bis >> z, type_mismatch);

    float float_loaded;
    bos << 3;
    bis.str(bos.str());

    ASSERT_THROW(bis >> float_loaded, type_mismatch);
}

TEST(BinaryStream, chainedValues_test)
{
    bostream bos;
    float f_original = 1.2;
    int i_original = 3;
    double d_original = 0.89;
    A a_original(3, "pepe", 43);
    bool b_original = true;

    bos << f_original << i_original << d_original << a_original << b_original;

    bistream bis(bos.str());
    float f_loaded;
    int i_loaded;
    double d_loaded;
    A a_loaded;
    bool b_loaded;
    bis >> f_loaded >> i_loaded >> d_loaded >> a_loaded >> b_loaded;

    ASSERT_EQ(f_original, f_loaded);
    ASSERT_EQ(i_original, i_loaded);
    ASSERT_EQ(d_original, d_loaded);
    ASSERT_EQ(a_original.id, a_loaded.id);
    ASSERT_EQ(a_original.name, a_loaded.name);
    ASSERT_EQ(a_original.a, a_loaded.a);
    ASSERT_EQ(b_original, b_loaded);
}

TEST(BinaryStream, contaniers_test)
{
    bostream bos;
    std::vector<int> integers_original;
    std::set<float> set_original;
    std::list<char> list_original();
    double numbers_original[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    insert_into(integers_original, 6);
    insert_into(integers_original, 7);
    insert_into(integers_original, 8);
    insert_into(integers_original, 9);
    insert_into(integers_original, 0);
    insert_into(integers_original, 1);
    insert_into(set_original, 0.1f);
    insert_into(set_original, 1.1f);
    insert_into(set_original, 2.1f);
    insert_into(set_original, 3.1f);
    insert_into(set_original, 4.1f);
    insert_into(list_original, 't');
    insert_into(list_original, 'y');
    insert_into(list_original, 'w');
    insert_into(list_original, 'A');

    bos << integers_original << set_original << list_original << numbers_original;

    std::vector<int> integers_loaded;
    std::set<float> set_loaded;
    std::list<char> list_loaded;
    double numbers_loaded[9];
    bistream bis(bos.str());
    bis >> integers_loaded >> set_loaded >> list_loaded >> numbers_loaded;

    ASSERT_EQ(integers_original, integers_loaded);

    ASSERT_EQ(set_original, set_loaded);

    ASSERT_EQ(list_original, list_loaded);

    assertArrayEquals(numbers_original, numbers_loaded, 9);
}
