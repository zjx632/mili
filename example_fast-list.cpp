/*
example_fast-list: An example that uses MiLi's fast lists.
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

static void print_list(const FastList<int>& list)
{
    FastList<int>::ConstElementHandler h(list.first());

    cout << list.size() << ":" << endl;
    while(h.is_valid())
    {
        cout << *h << endl;
        ++h;
    }

    cout << endl;
}

int main()
{
    FastList<int> list;
    FastList<int>::RemovableElementHandler
        one   = list.new_node(1),
        two   = list.new_node(2),
        three = list.new_node(3);

    print_list(list);

    // remove 'two'
    two.destroy();

    print_list(list);

    two = list.new_node(2);
    print_list(list);

    for(int i=10; i<20; ++i)
        list.new_node(i);

    print_list(list);

    list.clear();

    for(int i=10; i<30; ++i)
        list.new_node(i);

    print_list(list);

    return 0;
}

