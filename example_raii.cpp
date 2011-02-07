/*
raii.h: A minimal library for generic RAII implementation
    Copyright (C) 2011 Lucas Besso & Raul Striglio, UNRC

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
*/


#include "include/mili.h"
#include <iostream>
#include <cstdio>

class file
{

public:
    file (std::string path): _file(std::fopen(path.c_str(),"w")){} 
    void close(){fclose(_file);}
    void write(std::string str) {std::fputs(str.c_str(), _file);}
 
private:
    std::FILE* _file;
};

int main()
{
    file fi("file");
    RAII<file, &file::close> rs(fi);
    fi.write("new line in the file");   

    return 0;
}
