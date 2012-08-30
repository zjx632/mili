/*
example_license_text: An example that uses license_text.
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

    This is an example file.
*/

#include <iostream>
#include "mili/mili.h"

using namespace mili;
using namespace std;


int main()
{
    cout << "This is an example of GPL3 version 3 license text:" << endl;
    cout << getGPL3LicenseText("mili", "16", "Fudepan Team", "2012");

    return EXIT_SUCCESS;
}

