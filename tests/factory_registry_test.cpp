/*
    Copyright (C) 2012  Leandro Ramos, FuDePAN

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
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mili/mili.h"

using namespace mili;
using namespace testing;
using std::string;

struct IntOperation
{
    virtual int unaryOperation(const int n) = 0;
    virtual ~IntOperation() {}
};

class PlusOne: public IntOperation
{
    virtual int unaryOperation(const int n)
    {
        return n + 1;
    }
};

REGISTER_FACTORIZABLE_CLASS(IntOperation, PlusOne, string, string("PlusOne"));

class MinusOne: public IntOperation
{
    virtual int unaryOperation(const int n)
    {
        return n - 1;
    }
};

REGISTER_FACTORIZABLE_CLASS(IntOperation, MinusOne, string, string("MinusOne"));

class TimesFive: public IntOperation
{
    virtual int unaryOperation(const int n)
    {
        return n * 5;
    }
};

REGISTER_FACTORIZABLE_CLASS(IntOperation, TimesFive, string, string("TimesFive"));

TEST(FactoryRegistryTest, ReturnTest)
{
    IntOperation* plusone;
    plusone = FactoryRegistry<IntOperation, string>::new_class("PlusOne");
    ASSERT_NE(static_cast<IntOperation*>(NULL), plusone);
    IntOperation* minusone;
    minusone = FactoryRegistry<IntOperation, string>::new_class("MinusOne");
    ASSERT_NE(static_cast<IntOperation*>(NULL), minusone);
    IntOperation* timesfive;
    timesfive = FactoryRegistry<IntOperation, string>::new_class("TimesFive");
    ASSERT_NE(static_cast<IntOperation*>(NULL), timesfive);
    ASSERT_EQ(4, plusone->unaryOperation(3));
    delete plusone;
    ASSERT_EQ(3, minusone->unaryOperation(4));
    delete minusone;
    ASSERT_EQ(15, timesfive->unaryOperation(3));
    delete timesfive;
}

TEST(FactoryRegistryTest, NoRegisteredClassTest)
{
    IntOperation* anyone;
    anyone = FactoryRegistry<IntOperation, std::string>::new_class("TimesSeven");
    ASSERT_EQ(static_cast<IntOperation*>(NULL), anyone);
}
