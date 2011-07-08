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
#include <vector>
#include <iostream>
#include "mili/mili.h"

using namespace mili;

declare_type_mapper(TypeMapper);
add_mapping(TypeMapper, char, int);
add_mapping(TypeMapper, unsigned int, int);
add_mapping(TypeMapper, short int, int);
add_mapping_for_pointers(TypeMapper, int);

template<class T, class R>
struct Equal
{
    enum { value = false };
};

template<class T>
struct Equal<T, T>
{
    enum { value = true };
};

TEST(TypeMapperTest, test)
{
    bool v = Equal<int, map_type(TypeMapper, char)>::value;
    ASSERT_TRUE(v);
    v = Equal<int, map_type(TypeMapper, void*)>::value;
    ASSERT_TRUE(v);
    v = Equal<unsigned char, map_type(TypeMapper, unsigned char)>::value;
    ASSERT_TRUE(v);
}
