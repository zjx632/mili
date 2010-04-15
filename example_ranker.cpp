/*
example_fast-list: An example that uses MiLi's Ranker.
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

typedef Ranker<int, AddBeforeEqual> Ranking;

int main ()
{
    const size_t TOP = 5;
    const int I = -10;
    Ranking R(TOP);

    R.insert(10);
    R.insert(30);
    R.insert(I);
    R.insert(20);
    R.insert(I);

    CAutonomousIterator<Ranking> it(R);
    while(!it.end())
    {
        cout << *it << endl;
        ++it;
    }

    cout << "-- Insert 0 and 50 --" << endl;
    R.insert(0);
    cout << R.insert(50) << endl;              /* will print 0 (false) */

    CAutonomousIterator<Ranking> it1(R);
    while(!it1.end())
    {
        cout << *it1 << endl;
        ++it1;
    }
    
    R.remove_all(I);
    cout << "-- Remove All "<< I << " --" << endl;

    Ranking::const_iterator it2 = R.begin();
    while(it2 != R.end())
    {
        cout << *it2 << endl;
        ++it2;
    }
    cout << "----- size: " << R.size() << endl;
    cout << "top: " << R.top() << " - bottom: "<< R.bottom() << endl;    

    if(!R.empty()) R.clear();

    cout << "size after clear: " << R.size() << endl;
    return 0;
}

