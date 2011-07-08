/*
    Copyright (C) 2011  Hugo Arregui, FuDePAN

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

    This is a test file.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <list>
#include "mili/mili.h"

using namespace mili;

typedef FastList<int, OptimizedShrinkOnRequestPolicy> IntList;

static bool compare(const IntList& flist, const std::list<int>& l)
{
    if (flist.size() == l.size())
    {
        IntList::ConstElementHandler h(flist.first());
        std::list<int>::const_iterator it = l.begin();

        bool equals = true;
        while (h.is_valid() && equals)
        {
            equals = *h == *it;
            ++h;
            ++it;
        }
        return equals;
    }
    else
    {
        return false;
    }
}

TEST(FastListTest, test)
{
    IntList flist;
    IntList::RemovableElementHandler
    one   = flist.new_node(1),
    two   = flist.new_node(2),
    three = flist.new_node(3);

    std::list<int> rlist;
    rlist.push_back(1);
    rlist.push_back(2);
    rlist.push_back(3);
    ASSERT_TRUE(compare(flist, rlist));

    // remove 'two'
    two.destroy();
    flist.shrink();
    rlist.remove(2);
    ASSERT_TRUE(compare(flist, rlist));

    two = flist.new_node(2);
    rlist.push_back(2);
    ASSERT_TRUE(compare(flist, rlist));

    for (int i = 10; i < 20; ++i)
    {
        flist.new_node(i);
        rlist.push_back(i);
    }
    ASSERT_TRUE(compare(flist, rlist));

    flist.clear();
    flist.shrink();
    rlist.clear();
    ASSERT_TRUE(flist.empty());
    ASSERT_TRUE(compare(flist, rlist));

    for (int i = 10; i < 30; ++i)
    {
        flist.new_node(i);
        rlist.push_back(i);
    }
    ASSERT_TRUE(compare(flist, rlist));
}

