/*
factory: A minimal library for a generic factory.
    Copyright (C) 2009  Daniel Gutson and Marcelo Caro, FuDePAN

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
#include "mili/mili.h"

using std::string;
using std::cout;

struct Shape
{
    virtual void print_shape() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape
{
    virtual void print_shape() const
    {
        cout << "a circle\n";
    }
};

class Rectangle : public Shape
{
    virtual void print_shape() const
    {
        cout << "a rectangle\n";
    }
};

int main()
{
    Factory<string, Shape> shapes_factory;

    shapes_factory.register_factory<Circle>("circle");
    shapes_factory.register_factory<Rectangle>("rectangle");
    Shape* s = shapes_factory.new_class("circle");

    s->print_shape();

    delete s;

    return 0;
}
