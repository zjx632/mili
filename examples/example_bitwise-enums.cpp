/*
bitwise_enums: A minimal library for doing type-safe bitwise operations.
    Copyright (C) 2008, 2009  Daniel Gutson, FuDePAN
                  2011 Adrian Remonda FuDePAN

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

#include <iostream>
#include "mili/mili.h"

using namespace mili;
using std::cout;

enum MasksSet1
{
    kZero   = 0,
    kOne    = 1,
    kTwo    = 2,
    kThree  = 4,
    kFour   = 8
};
BITWISE_ENUM_ENABLE(MasksSet1)

enum MasksSet2
{
    kEight   = 8,
    kSixteen = 16,
};

typedef bitwise_enum<MasksSet1> M1;

void show_bits(M1 b)
{
    if (b.has_bits(kZero))  cout << "kZero  turned on\n";
    if (b.has_bits(kOne))   cout << "kOne   turned on\n";
    if (b.has_bits(kTwo))   cout << "kTwo   turned on\n";
    if (b.has_bits(kThree)) cout << "kThree turned on\n";
    if (b.has_bits(kFour))  cout << "kFour  turned on\n";
    cout << std::endl;
}

int main()
{
    //with bitwise nums
    bitwise_enum<MasksSet1>  myEnum(kOne | kTwo | kFour);

    show_bits(myEnum);

    //enum with bitwise enum
    myEnum = kOne & myEnum;
    show_bits(myEnum);

    // 2 enums
    show_bits(kOne | kThree);

    // << operator
    cout << "<< Operator test: 0x" << std::hex << (myEnum << 2) << std::endl;

    //without bitwise nums (built-in types)
    int normalEnum = kEight | kSixteen;
    cout << "Normal Enum: 0x" << std::hex << normalEnum << std::endl;

    normalEnum = kEight << 2;
    cout << "Normal Enum: 0x" << std::hex << normalEnum << std::endl;

    return 0;
}


