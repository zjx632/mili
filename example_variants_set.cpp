/*
example_variants_set: An example that uses MiLi's Variants Set.
    Copyright (C) 2010  Ezequiel S. Velez

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

using namespace std;

int main ()
{
    VariantsSet VS;
    int ie = 0;
    string is;
    VS.insert<int>("int", 3);
    VS.insert<string>("string", "hello");
    VS.insert<float>("float", 0.1f);

    VS.get_element<int>("int", ie);
    cout << "int: " << ie << endl;
    VS.get_element<string>("string", is);
    cout << "string: " << is << endl;

    VS.erase("float");
    cout << "size: " << VS.size() << endl;
    return 0;
}