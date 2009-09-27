/*
stream_utils: A minimal library that provides CSV and other file/stream
    functionalities..
    Copyright (C) 2009  Daniel Gutson, FuDePAN

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

#ifndef STREAM_UTILS_H
#define STREAM_UTILS_H

#include <vector>
#include <iostream>
#include <string>
#include "string_utils.h"

NAMESPACE_BEGIN

template <class T>
inline std::istream& operator >> (std::istream& is, std::vector<T>& v)
{
    T t;
    std::string line;

    if (std::getline(is, line))
    {
        char sep;
        std::stringstream ss(line);

        do
        {
            while (ss >> t)
                v.push_back(t);

            ss.clear();
        }
        while (ss >> sep);
    }

    return is;
}

template <class T>
inline void _mili_base_output (std::ostream& os, const std::vector<T>& v, char separator)
{
    const size_t max = v.size();

    if (max > 0)    /* This is done for optimization purposes.  */
    {
        const size_t before_last(max - 1);

        for (size_t i = 0; i < before_last; i++)
            os << v[i] << separator;

        os << v[before_last];
    }
}

template <class T>
inline std::ostream& operator << (std::ostream& os, const std::vector<T>& v)
{
    _mili_base_output(os, v, ',');
    return os;
}

template <class T>
struct _Separator
{
    std::vector<T>& v;
    const char      s;

    _Separator(std::vector<T>& v, char s)
        : v(v), s(s)
    {}

    _Separator(const _Separator<T>& other)
        : v(other.v), s(other.s)
    {}
};

template <class T>
inline _Separator<T> Separator(std::vector<T>& v, char s)
{
    return _Separator<T>(v, s);
}

template <class T>
inline std::ostream& operator << (std::ostream& os, const _Separator<T>& s)
{
    _mili_base_output(os, s.v, s.s);
    return os;
}

template <class T>
inline std::istream& operator >> (std::istream& is, const _Separator<T>& s)
{    
    std::string line;

    if (std::getline(is, line))
    {
        std::string::size_type last_pos = 0, pos;
        bool found;

        do
        {
            pos = line.find(s.s, last_pos);
            found = (pos !=  std::string::npos);
            if (found)
            {
                s.v.push_back(
                    from_string<T>(
                        line.substr(last_pos, pos - last_pos)
                    )
                );
                last_pos = pos + 1;
            }
        }while(found);

        if (last_pos != std::string::npos)
            s.v.push_back(
                from_string<T>(
                    line.substr(last_pos)
                )
            );
    }

    return is;
}

NAMESPACE_END

#endif

