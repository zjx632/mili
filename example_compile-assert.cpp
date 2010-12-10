/*
compile_assert: A minimal library supporting compile time (static) assertions,
    a la C++0x.
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

#include "include/mili.h"

generic_assert(sizeof(int) == 4);

declare_static_assert(this_assertion_will_always_fail);
declare_static_assert(pointers_not_allowed_assert);

template <class T> struct MyType
{
    template_compile_assert(!template_is_pointer<T>::value, pointers_not_allowed_assert);
};

int main()
{
    compile_assert(sizeof(char) == 2, this_assertion_will_always_fail); // fails

    MyType<char*> mt1;  // fails
    MyType<char>  mt2;  // OK
    return 0;
}
