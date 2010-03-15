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

// #define BSTREAMS_DEBUG //to enable type checking.

#include "mili.h"

#include <string>
#include <assert.h>

#ifdef BSTREAMS_DEBUG
#   include <typeinfo>
#endif

NAMESPACE_BEGIN

declare_static_assert(pointers_not_allowed);

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
            // Disallow pointers in binary streams.
            template_compile_assert(!template_is_pointer<T>::value, pointers_not_allowed);

#ifdef BSTREAMS_DEBUG
            const std::string s(typeid(T).name());
            const size_t sz(s.size());
            _s.append(reinterpret_cast<const char*>(&sz), sizeof(size_t));
            _s += s;
#endif
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

        template <class Other>
        bostream& operator<< (const std::vector<Other>& vec)
        {
            const size_t size(vec.size());
            (*this) << size;
            for (size_t i(0); i < size; ++i)
                (*this) << vec[i];

            return *this;
        }

        bostream& operator<< (const char* cs)
        {
            const std::string s(cs);
            return operator<< (s);
        }

        const std::string& str() const
        {
            return _s;
        }

        void clear()
        {
            _s.clear();
        }

    private:
        std::string _s;
};

class bistream
{
    public:
        bistream(const std::string& str) :
            _s(str),
            _pos(0)
        {
        }

        bistream() :
            _s(),
            _pos(0)
        {
        }

        void str(const std::string& str)
        {
            _pos = 0;
            _s = str;
        }

        template <class T>
        bistream& operator >> (T& x)
        {
            // Disallow pointers in binary streams.
            template_compile_assert(!template_is_pointer<T>::value, pointers_not_allowed);

#ifdef BSTREAMS_DEBUG
            std::string s(typeid(T).name());
            size_t sz;
            _pos += _s.copy(reinterpret_cast<char*>(&sz), sizeof(size_t),_pos);
            std::string name  = _s.substr(_pos,sz);
            _pos += sz;
            if (s != name)
                std::cerr << s << " | " << name << std::endl;
            assert( s == name);
#endif
            assert(_s.size() >= _pos + sizeof(x));
            _pos += _s.copy(reinterpret_cast<char*>(&x), sizeof(x),_pos);
            return *this;
        }

        bistream& operator >> (std::string& str)
        {
            size_t size;
            (*this) >> size;
            assert(_s.size() >= size+_pos);
            str  = _s.substr(_pos,size);
            _pos += size;
            return *this;
        }

        template <class Other>
        bistream& operator>> (std::vector<Other>& vec)
        {
            size_t size;
            (*this) >> size;
            assert(_s.size() >= (size * sizeof(Other)) + _pos);
            vec.resize(size);
            for (size_t i(0); i < size; i++)
                (*this) >> vec[i];

            return *this;
        }

        void clear()
        {
            _s.clear();
            _pos = 0;
        }

    private:
        std::string _s;
        std::size_t _pos;
};

NAMESPACE_END

#endif
