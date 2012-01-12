/*
Copyright (C) 2011 Hugo Arregui FuDePAN

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
#include <vector>
#include <set>
#include <string>
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
        :id(0), name(""), a(0)
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

struct B : public A
{
    std::string surname;
    long int room;
    char sex;
    
    B()
        :A(), surname(""), room(0), sex('M')
    {}
    
    B(const std::string& Surname, long int Room, char Sex)
        :A(), surname(Surname), room(Room), sex(Sex)
    {}
    
    unsigned int get_id() const
    {
        return A::id;
    }
    std::string get_name() const
    {
        return A::name;
    }
    long double get_a() const
    {
        return A::a;
    }
    
    
    friend bostream& operator<<(bostream& out, const B& o)
    {
        out << static_cast<const A&>(o) << o.surname << o.room << o.sex;
        return out;
    }
    
    friend bistream& operator>>(bistream& in, B& o)
    {
        in >> static_cast<A&>(o) >> o.surname >> o.room >> o.sex;
        return in;
    }
    
};

TEST(BinaryStream, BSTREAMS_DEBUG_basicTypes)
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

TEST(BinaryStream, BSTREAMS_DEBUG_chained)
{
    bostream bos;
    float f;
    int i;
    double d;   
    A a(3,"pepe",43);
    A z(0,"",0);
    B x("asd", 3, 'u');
    B y("", 0, '0');
    
    bos << 1.2f << 3 << double(0.89) << a << x;
        
    bistream bis(bos.str());
    
    bis >> f >> i >> d >> z >> y;
    
    ASSERT_EQ(3, z.id);
    ASSERT_EQ("pepe", z.name);
    ASSERT_EQ(43, z.a);
    
    ASSERT_EQ(0, y.get_id());
    ASSERT_EQ("", y.get_name());
    ASSERT_EQ(0, y.get_a());
    ASSERT_EQ("asd", y.surname);
    ASSERT_EQ(3, y.room);
    ASSERT_EQ('u', y.sex);
    
}

TEST(BinaryStream, BSTREAMS_DEBUG_contaniers)
{
    bostream bos;
    std::vector<int> integers(16, -4), integers2;
    std::set<unsigned> set1, set2;
    double numbers[] = {1, 2, 3, 4, 5, 4, 3, 2, 1}, numbers2[9];
    bool boolean = true, boolean2;

    set1.insert(1000);
    set1.insert(100);
    set1.insert(10);
    set1.insert(1);
        
    bos << integers << set1 << numbers << boolean;
    
    bistream bis(bos.str());
    
    bis >> integers2 >> set2 >> numbers2 >> boolean2;
    
    ASSERT_EQ(-4, integers2[2]);
    ASSERT_EQ(1, *(set2.begin()));
    ASSERT_EQ(5, numbers2[4]);
    ASSERT_TRUE(boolean2);    
}
