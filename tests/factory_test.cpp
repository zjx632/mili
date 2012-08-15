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
#include <string>
#include "mili/mili.h"

using namespace mili;
using namespace testing;
using std::string;

struct Shape
{
    virtual string shape_name() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape
{
    virtual string shape_name() const
    {
        return "circle";
    }
};

class Rectangle : public Shape
{
    virtual string shape_name() const
    {
        return "rectangle";
    }
};

TEST(FactoryTest, test)
{
    Factory<string, Shape> shapes_factory;
    shapes_factory.register_factory<Circle>("circle");

	/* When compiling for Windows the Rectangle template argument in
    the following line is considered to be the function
    __gdi_entry WINGDIAPI BOOL WINAPI Rectangle(__in HDC hdc, __in int left, __in int top, __in int right, __in int bottom);
    defined in WinGDI.h. So I must ad the class keyword to discriminate. */
    shapes_factory.register_factory<class Rectangle>("rectangle");
    
    Shape* s = shapes_factory.new_class("circle");

    ASSERT_EQ("circle", s->shape_name());
    delete s;
}
