/*
binary_streams: A minimal library supporting encoding of different data
                types in a single binary stream.
    Copyright (C) 2009, 2010  Guillermo Biset, FuDePAN

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
#include <string>
#include <vector>
#include "mili/mili.h"

typedef mili::bostream<> bostream;
typedef mili::bistream<> bistream;

int main()
{
    std::vector<int> v(5, 3); //all 3's
    v[1] = 1;
    v[4] = 7; //so it is [3,1,3,3,7]

    bostream bos;
    bos << 1 << 2 << 3 << std::string("Hello ") << v << 4 << std::string("World!");

    bostream bos2;
    bos2 << 100;
    bos +=  bos2;

    bistream bis(bos.str());

    int         nums[4];
    std::string str1;
    std::string str2;

    std::vector<int> v2;

    bis >> nums[0] >> nums[1] >> nums[2] >> str1 >> v2 >> nums[3] >> str2;

    for (int i = 0; i < 4 ; ++i)
        std::cout << nums[i] << std::endl;

    std::cout << str1 << str2 << std::endl;

    std::cout << '[';
    for (size_t i = 0; i < 5; ++i)
        std::cout << v2[i] << ' ';
    std::cout << ']' << std::endl;

    bos.clear();

    mili::container_writer<int, mili::NoDebugPolicyBostream> cw(5, bos);

    cw << 1 << 2 << 3 << 4 << 5;

    bis.clear();
    bis.str(bos.str());

    std::vector<int> v3;
    bis >> v3;

    std::cout << '[' << v3[0] << ',' << v3[1] << ',' << v3[2] << ',' << v3[3] << ',' << v3[4] << "]\n";

    std::list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    bos.clear();
    bos << list;

    bis.clear();
    bis.str(bos.str());

    std::vector<int> v4;
    bis >> v4;
    std::cout << '[' << v3[0] << ',' << v3[1] << ',' << v3[2] << "]\n";

    bos.clear();
    bos << list;

    bis.clear();
    bis.str(bos.str());

    mili::container_reader<int, mili::NoDebugPolicyBistream> reader(bis);

    int a;
    reader.skip();
    reader >> a;
    reader.finished();

    std::cout << "2nd element: " << a << "\n";
// To check for no-pointer compile error uncomment these lines:
    /*
        int *p = new int(1);
        bos << p;
    */
}
