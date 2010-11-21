/*
example_coroutines: An example that uses coroutines.
    Copyright (C) 2010  Daniel Gutson, FuDePAN

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

class CoRo1 : public Coroutine
{
    int x;
    int y;
    int z;
public:
    int operator()()
    {
        BEGIN_COROUTINE
        {
            for (x = 0; x < 10; ++x)
            {
                for (y = 0; y < 10; ++y)
                {
                    for (z = 0; z < 10; ++z)
                        mili_yield(x + y + z);
                }
                mili_yield(-x);
            }
        }
        END_COROUTINE(-1000);
    }
};

int main()
{
    CoRo1 cr1;
    int ret;
    do
    {
        ret = cr1();
        cout << ret << endl;
    }
    while (ret != -1000);
    return ret;
}

