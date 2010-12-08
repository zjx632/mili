/*
stream_utils: A minimal library that provides CSV and other file/stream
    functionalities..
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
#include <iostream>
#include <fstream>
#include "include/mili.h"

using namespace std;

static void generate_file(const char* name)
{
    ofstream f(name);
    set<float> v;

    for(int i=0; i < 10; i++)
    {
        v.clear();
        for(int j=0; j <= i; j++)
            insert_into(v, i + j / 10.0f);

        f << v; /* PROVIDED BY MiLi */

        f << endl;
    }
}

static void load_file(const char* name)
{
    ifstream f(name);
    vector<float> v;

    while (f >> v)  /* PROVIDED BY MiLi */
    {
        cout << Separator(v, '\t');  /* PROVIDED BY MiLi */
        cout << endl;
        v.clear();
    }
}

int main()
{
    generate_file("stream-utils.test");
    load_file("stream-utils.test");

    return 0;
}

