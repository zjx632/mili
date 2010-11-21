/*
type_mapper: A minimal library that implements type mappers.
    Copyright (C) 2009  Daniel Gutson, FuDePAN

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

    This is an example file.
*/

#include <vector>
#include "include/mili.h"

declare_type_mapper(TypeMapper);
add_mapping(TypeMapper, char, int);
add_mapping(TypeMapper, unsigned int, int);
add_mapping(TypeMapper, short int, int);
add_mapping_for_pointers(TypeMapper, int);

template <class T>
class MyVector : public std::vector<map_type(TypeMapper, T)>
{};

int main()
{
    MyVector<short int> v1;
    MyVector<float> v2;

    v1.push_back(1);
    v2.push_back(1.0f);

    return 0;
}
