/*
template_info: A minimal library to obtain type information of a template
    parameter.
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

#include <iostream>
#include "include/mili.h"
#include <vector>
#include <set>

struct S {};

int main()
{
    std::cout << bool(template_info<S>::is_native) << std::endl;
    std::cout << bool(template_info<char>::is_native) << std::endl;
    std::cout << bool(template_info<int>::is_same_size<long int>::value) << std::endl;
    std::cout << bool(template_info<std::vector<int> >::is_container) << std::endl;
    std::cout << bool(template_info<std::set<int> >::is_container) << std::endl;
    return 0;
}
