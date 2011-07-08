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
#include "mili/mili.h"

#include <iostream>
using namespace std;
using namespace mili;

TEST(VariantsSetTest, test)
{
    VariantsSet variantSet;
    ElementName str = "greeting";
    variantSet.insert("number", 3);
    variantSet.insert(str, "hello");
    variantSet.insert("temperature", 0.1f);

    ASSERT_EQ(3, variantSet.size());

    int ie = 0;
    variantSet.get_element("number", ie);
    ASSERT_EQ(3, ie);

    string is;
    variantSet.get_element(str, is);
    ASSERT_EQ("hello", is);

    ASSERT_EQ("hello", variantSet.get_element<string>(str));

    float f;
    ASSERT_THROW(variantSet.get_element("float", f), BadElementName);

    variantSet.erase("temperature");
    ASSERT_EQ(2, variantSet.size());
}
