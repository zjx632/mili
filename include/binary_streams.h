/*
binary_streams: A minimal library supporting encoding of different data
                types in a single binary stream.
    Copyright (C) 2009  Guillermo Biset, FuDePAN

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

#ifndef BINARY_STREAMS_H
#define BINARY_STREAMS_H

#include <string>

class bostream
{
    public:
        bostream() :
            _s()
        {
        }

        template <class T>
        bostream& operator<< (T x)
        {
            _s.append(reinterpret_cast<char*>(&x), sizeof(T));
            return *this;
        }

        /* Inserting a string inserts its size first. */
        bostream& operator<< (const std::string& s)
        {
            (*this) << s.size();
            _s += s;
            return *this;
        }

        bostream& operator<< (const char* cs)
        {
            const std::string s(cs);
            return operator<< (s);
        }

        std::string str() const
        {
            return _s;
        }

    private:
        std::string _s;
};

class bistream
{
    public:
        bistream(std::string str) :
            _s(str),
            _pos(0)
        {
        }

        template <class T>
        bistream& operator >> (T& x)
        {
            _pos += _s.copy(reinterpret_cast<char*>(&x), sizeof(x),_pos);
            return *this;
        }

        bistream& operator >> (std::string& str)
        {
            int size;
            (*this) >> size;
            str  = _s.substr(_pos,size);
            _pos += size;
            return *this;
        }

    private:
        std::string _s;
        std::size_t _pos;
};

#endif