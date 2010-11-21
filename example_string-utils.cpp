/*
string_utils: A minimal library with string utilities.
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
#include <map>
#include "include/mili.h"

using namespace std;

int main()
{
    lstring ls("helLO");

    ls[1] = 'E';
    cout << (ls[2] == 'L') << endl;             /* prints 1 (true) */

    cout << ls << endl;                         /* prints "hello" */
    cout << (ls == "HELLO") << endl;            /* prints 1 (true) */

    map<lstring, int> m;
    m["Hello"] = 3;
    m["Goodbye"] = 5;

    cout << m["hELLo"] << endl;                 /* prints 3 (matches with "Hello") */

    cout << begins_with(ls, "HE") << endl;      /* prints 1 (true) */
    cout << ends_with(ls, "Ello") << endl;      /* prints 1 (true) */

    cout << toupper("Hello World!") << endl;    /* prints "HELLO WORLD!" */

    cout << to_string(123.4) << endl;
    int n;
    cout << to_number("abc", n) << endl;        /* prints 0 (false), because "abc" is not valid */
    cout << to_number<float>("123.4") << endl;

    std::string str = "Why?";
    cout << ensure_found(str.find_first_of("h", 0)) << endl;    /* prints 1 */
    try
    {
        cout << ensure_found(str.find_first_of(" ", 0)) << endl;    /* throw StringNotFound  */
    }
    catch (const StringNotFound &f)
    {
        cout << "Do something" << endl;     /* prints Do something */
    }
    cout << ensure_found(str.find_first_of(" ", 0), str.size()) << endl;    /* prints str.size() */

    return 0;
}

