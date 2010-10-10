/*
example_ranker: An example that uses MiLi's Ranker.
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
typedef UniqueRanker<int> UniqueRanking;

template <class T>
void print (CAutonomousIterator<T> it)
{
    while(!it.end())
    {
        cout << *it << endl;
        ++it;
    }    
}

void unique_ranker_test ()
{
    UniqueRanking UR(5);
    UR.insert(1);
    UR.insert(1);
    UR.insert(3);
    UR.insert(6);
    UR.insert(2); 
    UR.insert(1);
    UR.insert(5); 
    UR.insert(4); 
    CAutonomousIterator<UniqueRanking> it(UR);
    print<UniqueRanking> (it);   
}

void ranker_test ()
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
    print<Ranking> (it);

    cout << "-- Insert 0 and 50 --" << endl;
    R.insert(0);
    R.insert(50);

    CAutonomousIterator<Ranking> it1(R);
    print<Ranking> (it1);
    
    R.remove_all(I);
    cout << "-- Remove All "<< I << " --" << endl;

    CAutonomousIterator<Ranking> it2(R);
    print<Ranking> (it2);
    cout << "----- size: " << R.size() << endl;
    cout << "top: " << R.top() << " - bottom: "<< R.bottom() << endl;    

    if(!R.empty()) R.clear();

    cout << "size after clear: " << R.size() << endl;
}

int main()
{
    string test;
    cout << "Indicate which library you want to test. (R = Ranker ; UR = Unique Ranker):" << endl;
    cin >> test;

    if(test == "R")
        ranker_test();
    else if (test == "UR")
        unique_ranker_test();
    else
        cout << "Error: you must choose R or UR" << endl;
    return 0;
}

