/*
delete_container: A minimal library for deleting the objects of a container of pointers.
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

    This is an example program.
*/

#include <vector>
#include "mili/mili.h"

using namespace mili;

struct AnObject
{
    int i;
    float f;
};

int main()
{
    std::vector<AnObject*> vec1;
    auto_vector_delete_container<std::vector<char*> > vec2;

    vec1.push_back(new AnObject);
    vec1.push_back(new AnObject);
    vec1.push_back(new AnObject);

    vec2.push_back(new char[10]);
    vec2.push_back(new char[10]);
    vec2.push_back(new char[10]);

    delete_container(vec1);
    // vector_delete_container(vec2) is called when exiting

    return 0;
}
