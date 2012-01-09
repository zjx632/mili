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

    This is a test program.
*/

#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mili/mili.h"

using namespace mili;

struct MockObject
{
    int i;
    float f;
    MOCK_CONST_METHOD0(die, void());
    ~MockObject()
    {
        die();
    }
};

TEST(DeleteContainerTest, delete_container)
{
    std::vector<MockObject*> vec1;

    MockObject* o1 = new MockObject;
    MockObject* o2 = new MockObject;
    MockObject* o3 = new MockObject;
    vec1.push_back(o1);
    vec1.push_back(o2);
    vec1.push_back(o3);

    EXPECT_CALL(*o1, die()).Times(1);
    EXPECT_CALL(*o2, die()).Times(1);
    EXPECT_CALL(*o3, die()).Times(1);
    delete_container(vec1);
}
