/*
    Copyright (C) 2012 Lucas Paradisi FuDePAN

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
#include "mili/mili.h" 
#define BSTREAMS_DEBUG 

using namespace mili;


std::string get_TypeId(const std::string& s)
{
    size_t a;
        
    s.copy(reinterpret_cast<char*>(&a), sizeof(size_t), 0);

    return s.substr(sizeof(size_t), sizeof(char)*a);
}

struct A
{
    unsigned int id;
    std::string name;
    long double a;
    
    A()
        :id(0), name(), a(0)
    {}
    
    A(unsigned int Id, const std::string& Name, long double A)
        :id(Id), name(Name), a(A)
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
    A a(3,"pepe",43);
    A z;
    
    bos << 1.2f << 3 << double(0.89) << a << true;

    bistream bis(bos.str());
    float f;
    int i;
    double d;
    bool b;
    bis >> f >> i >> d >> z >> b; 
    
    ASSERT_EQ(3, z.id);
    ASSERT_EQ("pepe", z.name);
    ASSERT_EQ(43, z.a);
    ASSERT_TRUE(b);            
}

TEST(BinaryStream, BSTREAMS_DEBUG_contaniers_test)
{
    bostream bos;
    std::vector<int> integers(16, -4), integers2;
    std::set<unsigned> set1, set2;
    std::list<char> list1(4, 't'), list2;
    double numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}, numbers2[9];

    set1.insert(1000);
    set1.insert(100);
    set1.insert(10);
    set1.insert(1);
    
    bos << integers << set1 << list1 << numbers;
    
    bistream bis(bos.str());
    bis >> integers2 >> set2 >> list2 >> numbers2;
    
    for (int i = 0; i < 16; ++i)
    {
        ASSERT_EQ(-4, integers2[i]);
    }    
    
    std::set<unsigned>::iterator it = set2.begin();
    ASSERT_EQ(1, *it++);
    ASSERT_EQ(10, *it++);
    ASSERT_EQ(100, *it++);
    ASSERT_EQ(1000, *it);
    
    
    for (std::list<char>::iterator it1 = list2.begin(); it1 != list2.end(); ++it1)
    {
        ASSERT_EQ('t', *it1);
    }
    
    for (int i = 0; i < 9; ++i)
    {
        ASSERT_EQ(i+1, numbers2[i]);
    }
}
