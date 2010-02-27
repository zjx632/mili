/*
find_utils: A minimal library with generic find functions with exceptions.
    Copyright (C) 2009  Daniel Gutson, FuDePAN
                        Ezequiel S. Velez

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
#include <string>

#include "include/mili.h"

using namespace std;

static void test_autonomous_iterators();

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

        test_autonomous_iterators();

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

template <class T>
static void insert_elements(T& container)
{
    insert_into(container, 100);
    insert_into(container, 100);
    insert_into(container, 100);
    insert_into(container, 200);
    insert_into(container, 300);
    insert_into(container, 400);
    insert_into(container, 400);
}

template <class T>
static void delete_elements(T& container)
{
    remove_first_from(container, 400);                 
    remove_all_from(container, container.begin());   /* amending iterators */

}

template <class T>
static void show_elements(AutonomousIterator<T> it)
{
    while (!it.end())
        cout << *(it++) << endl;
}

void test_autonomous_iterators()
{
    vector<int> v;
    list<int> l;
    set<int> s;

    insert_elements(v);
    insert_elements(l);
    insert_elements(s);

    delete_elements(v);
    delete_elements(l);
    delete_elements(s);

    AutonomousIterator<vector<int>::const_iterator> vi(v.begin(), v.end());
    AutonomousIterator<list<int>::const_iterator> li(l.begin(), l.end());
    AutonomousIterator<set<int>::const_iterator> si(s.begin(), s.end());

    cout << "vector: " << endl;
    show_elements(vi);
    cout << "list: " << endl;
    show_elements(li);
    cout << "set: " << endl;
    show_elements(si);
}

