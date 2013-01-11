/*
factory_registry: A simple way to registry derived classes without .h file
    Copyright (C) 2012 Leandro Ramos, FuDePAN


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

    Example source file.
*/

#include<iostream>
#include<string>
#include"mili/mili.h"

/* This example was written in one file for simplicity but it could write in separete files */

//! Speaker interface .h

struct Speaker
{
    virtual void saySomething() = 0;
};

//! End of speaker interface file

//! Hello.cpp file


class Hello: public Speaker
{
    virtual void saySomething();
};

void Hello::saySomething()
{
    std::cout << "Hello" << std::endl;
}

REGISTER_FACTORIZABLE_CLASS(Speaker, Hello, std::string, "Hello");

//! End of Hello.cpp

//! Goodbye.cpp


class Goodbye: public Speaker
{
    virtual void saySomething();
};

void Goodbye::saySomething()
{
    std::cout << "Goodbye" << std::endl;
}

REGISTER_FACTORIZABLE_CLASS(Speaker, Goodbye, std::string, "Goodbye");

//! End of Goodbye.cpp

//! Main file


int main()
{
    std::string className;
    Speaker* speaker;
    mili::Factory<std::string,Speaker>::KeyIterator it;

    std::cout << "Which speaker would you like?" << std::endl;
    std::cin >> className;
    speaker = mili::FactoryRegistry<Speaker, std::string>::new_class(className);
    mili::FactoryRegistry<Speaker, std::string>::getConstructibleObjectsKeys(it);
    if (speaker == NULL)
    {
        std::cout << "Speaker " << className << " doesn't exist" << std::endl;
    }
    else
    {
        speaker->saySomething();
        delete speaker;
    }
    return 0;
}
