/*
find_utils: A minimal library with generic find functions with exceptions.
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

#include <string>
#include <iostream>
#include <vector>

#include "include/mili.h"

using namespace std;

int main()
{
    vector<int> v;
    v.push_back(1);

    map<string, string> m;
    m["hello"] = "goodbye";

    try
    {
        cout << contains(v, 2) << endl;         /* will print 0 (false) */
        cout << contains(m, "nothing") << endl; /* will print 0 (false) */

        cout << find(v, 1) << endl;             /* will print 1 */
        cout << find(m, "hello") << endl;       /* will print "goodbye" */
        cout << find(m, "world") << endl;       /* will throw ElementNotFound */
    }
    catch(ElementNotFound)
    {
        cerr << "Element not found!" << endl;
    }

    return 0;
}

