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

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "mili/mili.h"

using namespace mili;
using namespace testing;
using std::string;

struct IntOperation
{
    virtual void unaryOperation(int& n) = 0;
};

class PlusOne: public IntOperation
{
    virtual void unaryOperation(int& n)
    {
        n++;
    }
};

REGISTER_FACTORIZABLE_CLASS(IntOperation, PlusOne, string, string("PlusOne"));

class MinusOne: public IntOperation
{
    virtual void unaryOperation(int& n)
    {
        n--;
    }
};

REGISTER_FACTORIZABLE_CLASS(IntOperation, MinusOne, string, string("MinusOne"));

class TimesFive: public IntOperation
{
    virtual void unaryOperation(int& n)
    {
        n = n * 5;
    }
};

REGISTER_FACTORIZABLE_CLASS(IntOperation, TimesFive, string, string("TimesFive"));

TEST(FactoryRegistryTest, ReturnTest)
{
    int n = 3;
    IntOperation* plusone;
    IntOperation* minusone;
    IntOperation* timesfive;

    plusone = FactoryRegistry<IntOperation, string>::new_class(string("PlusOne"));
    ASSERT_NE(plusone, static_cast<IntOperation*>(NULL));
    minusone = FactoryRegistry<IntOperation, string>::new_class(string("MinusOne"));
    ASSERT_NE(minusone, static_cast<IntOperation*>(NULL));
    timesfive = FactoryRegistry<IntOperation, string>::new_class(string("TimesFive"));
    ASSERT_NE(timesfive, static_cast<IntOperation*>(NULL));
    plusone->unaryOperation(n);
    ASSERT_EQ(n, 4);
    minusone->unaryOperation(n);
    ASSERT_EQ(n, 3);
    timesfive->unaryOperation(n);
    ASSERT_EQ(n, 15);
    delete plusone;
    delete minusone;
    delete timesfive;
}

TEST(FactoryRegistryTest, NoRegisteredClassTest)
{
    IntOperation* anyone;

    anyone = FactoryRegistry<IntOperation, std::string>::new_class(string("TimesSeven"));
    ASSERT_EQ(anyone, static_cast<IntOperation*>(NULL));
}
