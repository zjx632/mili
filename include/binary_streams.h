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
*/

#ifndef BINARY_STREAMS_H
#define BINARY_STREAMS_H

// #define BSTREAMS_DEBUG //to enable type checking.

#include <string>
#include <assert.h>
#include <stdint.h>
#include <stdexcept>

#include "compile_assert.h"
#include "generic_exception.h"
#include "template_info.h"

#ifdef BSTREAMS_DEBUG
#   include <typeinfo>
#endif

NAMESPACE_BEGIN

declare_static_assert(pointers_not_allowed);
declare_static_assert(must_use_container);

class BstreamExceptionHierarchy{};

typedef GenericException<BstreamExceptionHierarchy> BstreamException;

DEFINE_SPECIFIC_EXCEPTION_TEXT(container_not_finished,
                               BstreamExceptionHierarchy,
                               "More elements were expected to be written.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(container_finished,
                               BstreamExceptionHierarchy,
                               "The container was finished already.");


DEFINE_SPECIFIC_EXCEPTION_TEXT(stream_too_small,
                               BstreamExceptionHierarchy,
                               "Stream is too small for read size, maybe not a container.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(skip_excess,
                               BstreamExceptionHierarchy,
                               "Trying to skip too much.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(type_too_large,
                               BstreamExceptionHierarchy,
                               "The string can't be read from the stream.");

class bostream
{
    template<class T, bool IsContainer> struct _inserter_helper;

    template<class T, bool IsContainer> friend struct _inserter_helper;

    public:
        bostream() :
            _s()
        {
        }

        template <class T>
        bostream& operator<< (const T& x)
        {
            // Disallow pointers in binary streams.
            template_compile_assert(!template_is_pointer<T>::value, pointers_not_allowed);

#ifdef BSTREAMS_DEBUG
            const std::string s(typeid(T).name());
            const size_t sz(s.size());
            _s.append(reinterpret_cast<const char*>(&sz), sizeof(size_t));
            _s += s;
#endif

            _inserter_helper<T, template_is_container<T>::value >::call(this, x);
            return *this;
        }

        /* Inserting a string inserts its size first. */

        bostream& operator<< (const std::string& s)
        {
            (*this) << uint32_t(s.size());
            _s += s;
            return *this;
        }

        bostream& operator<< (const char* cs)
        {
            const std::string s(cs);
            return operator<< (s);
        }

        void operator += (const bostream& other)
        {
            _s += other.str();
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
    template<class T> friend class container_reader;

    template<class T, bool IsContainer> struct _extract_helper;

    template<class T, bool IsContainer> friend struct _extract_helper;

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

            _extract_helper<T, template_is_container<T>::value >::call(this, x);

            return *this;
        }

        bistream& operator >> (std::string& str)
        {
            uint32_t size;
            (*this) >> size;

            if( _s.size() < size + _pos )
                throw type_too_large();

            str   = _s.substr(_pos,size);

            _pos += size;
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

template<class T>
class container_writer
{
    public:
        container_writer( size_t size, bostream& bos) :
            _elements_left( size ),
            _bos( bos )
        {
            _bos << uint32_t( size );
        }

        container_writer& operator<<(const T& element)
        {
            if ( _elements_left == 0 )
                throw container_finished();

            --_elements_left;

            _bos << element;

            return *this;
        }

        ~container_writer()
        {
            if ( _elements_left != 0 )
                throw container_not_finished();
        }
    private:
        size_t    _elements_left;
        bostream& _bos;
};

template<class T>
class container_reader
{
    public:
        container_reader( bistream& bis) :
            _elements_left( 0 ),
            _bis( bis )
        {
            _bis >> _elements_left;

            if ( (_bis._pos + sizeof(T)*_elements_left) > _bis._s.size() )
                throw stream_too_small();
        }

        container_reader& operator>>(T& element)
        {
            assert( _elements_left > 0 );
            --_elements_left;

            _bis >> element;

            return *this;
        }

        void skip(size_t elements = 1)
        {
            if ( elements > _elements_left )
                throw skip_excess();

            _elements_left -= elements;

            _bis._pos += sizeof(T) * elements;
        }

        void finished()
        {
            skip( _elements_left );
            _elements_left = 0;
        }

        ~container_reader()
        {
            if ( _elements_left != 0 )
                finished();
        }

    private:
        size_t    _elements_left;
        bistream& _bis;
};

template<class T>
struct bostream::_inserter_helper<T, false>
{
    static void call(bostream* bos, const T& x)
    {
        bos->_s.append(reinterpret_cast<const char*>(&x), sizeof(T));
    }
};

template<class T>
struct bostream::_inserter_helper<T, true>
{
    static void call(bostream* bos, const T& cont)
    {
        const uint32_t size(cont.size());
        (*bos) << size;

        typename T::const_iterator it( cont.begin() );

        for (; it != cont.end(); ++it)
            (*bos) << *it;
    }
};

template<class T>
struct bistream::_extract_helper<T, false>
{
    static void call(bistream* bis, T& x)
    {
        if( bis->_s.size() < bis->_pos + sizeof(x) )
            throw type_too_large();

        bis->_pos += bis->_s.copy(reinterpret_cast<char*>(&x), sizeof(x), bis->_pos);   
    }
};

template<class T>
struct bistream::_extract_helper<T, true>
{
    static void call(bistream* bis, T& cont)
    {
        uint32_t size;
        (*bis) >> size;

        if ( bis->_s.size() < ( (size * sizeof(typename T::value_type)) + bis->_pos) )
            throw stream_too_small();

        for (size_t i(0); i < size; i++)
        {
            typename T::value_type elem;
            (*bis) >> elem;
            cont.push_back( elem );
        }
    }
};


NAMESPACE_END

#endif
