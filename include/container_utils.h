/*
container_utils: A minimal library with generic STL container utilities..
    Copyright (C) 2009  Daniel Gutson, FuDePAN
                        Ezequiel S. Velez

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

#ifndef CONTAINER_UTILS_H
#define CONTAINER_UTILS_H

// Supported containers for mili::find() and mili::contains():
#include <map>
#include <vector>
#include <list>
#include <set>
#include <new>

#include <algorithm>
#include <exception>
//#include <iterator>

NAMESPACE_BEGIN

struct ElementNotFound : std::exception{};

template <class Container, class Element>
inline Element& find(Container& c, const Element& element) throw(ElementNotFound)
{
    const typename Container::iterator it = find(c.begin(), c.end(), element);
    if (it == c.end())
        throw ElementNotFound();
    else
        return *it;
}

template <class Container, class Element>
inline const Element& find(const Container& c, const Element& element) throw(ElementNotFound)
{
    const typename Container::const_iterator it = find(c.begin(), c.end(), element);
    if (it == c.end())
        throw ElementNotFound();
    else
        return *it;
}

template <class Key, class T, class Comp, class Alloc, class Key2>
inline T& find(std::map<Key, T, Comp, Alloc>& m, const Key2& key) throw(ElementNotFound)
{
    const typename std::map<Key, T, Comp, Alloc>::iterator it = m.find(key);
    if (it == m.end())
        throw ElementNotFound();
    else
        return it->second;
}

template <class Key, class T, class Comp, class Alloc, class Key2>
inline const T& find(const std::map<Key, T, Comp, Alloc>& m, const Key2& key) throw(ElementNotFound)
{
    const typename std::map<Key, T, Comp, Alloc>::const_iterator it = m.find(key);
    if (it == m.end())
        throw ElementNotFound();
    else
        return it->second;
}

/* find, nothrow versions */
template <class Container, class Element>
inline Element* find(Container& c, const Element& element, const std::nothrow_t&)
{
    const typename Container::iterator it = find(c.begin(), c.end(), element);
    if (it == c.end())
        return NULL;
    else
        return *it;
}

template <class Container, class Element>
inline const Element* find(const Container& c, const Element& element, const std::nothrow_t&)
{
    const typename Container::const_iterator it = find(c.begin(), c.end(), element);
    if (it == c.end())
        return NULL;
    else
        return *it;
}

template <class Key, class T, class Comp, class Alloc, class Key2>
inline T* find(std::map<Key, T*, Comp, Alloc>& m, const Key2& key, const std::nothrow_t&)
{
    const typename std::map<Key, T*, Comp, Alloc>::iterator it = m.find(key);
    if (it == m.end())
        return NULL;
    else
        return it->second;
}

template <class Key, class T, class Comp, class Alloc, class Key2>
inline const T* find(const std::map<Key, T*, Comp, Alloc>& m, const Key2& key, const std::nothrow_t&)
{
    const typename std::map<Key, T*, Comp, Alloc>::const_iterator it = m.find(key);
    if (it == m.end())
        return NULL;
    else
        return it->second;
}

/* contains(): generic form */
template <class Container, class Element>
inline bool contains(const Container& c, const Element& element)
{
    try
    {
        find(c, element);
        return true;
    }
    catch(ElementNotFound)
    {
        return false;
    }
}

/* contains specializations */
template <class Element>
inline bool contains(const std::vector<Element>& v, const Element& element)
{
    return find(v.begin(), v.end(), element) != v.end();
}

template <class Element>
inline bool contains(const std::list<Element>& l, const Element& element)
{
    return find(l.begin(), l.end(), element) != l.end();
}

template <class Key, class T, class Comp, class Alloc, class Key2>
inline bool contains(const std::map<Key, T, Comp, Alloc>& m, const Key2& key)
{
    return m.count(key) > 0;
}

template <class Key, class Comp, class Alloc, class Key2>
inline bool contains(const std::set<Key, Comp, Alloc>& s, const Key2& key)
{
    return s.count(key) > 0;
}

// ------------ Insertion Utilities

/* This works for vectors and lists */
template <class Container, class ElementType>
inline void insert_into(Container& cont, const ElementType& element)
{
    cont.push_back(element);
}

/* This works for sets */
template<class ElementType, class Comp, class Alloc>
inline void insert_into(std::set<ElementType, Comp, Alloc>& cont, const ElementType& element)
{
    cont.insert(element);
}

//------------ Remove Utilities

/*--removing by iterator--*/
/*This works for lists*/
template <class ElementType, class Alloc, class IteratorType>
inline void remove_from(std::list<ElementType, Alloc>& cont, IteratorType pos) throw(ElementNotFound)
{
    cont.remove(*pos);
}

/* This works for vectors */
template <class Container>
inline void remove_from(Container& cont, typename Container::iterator pos) throw(ElementNotFound)
{
    cont.erase(pos);
}

template <class Container>
inline void remove_from(Container& cont, typename Container::const_iterator pos) throw(ElementNotFound)
{
    cont.erase(pos);
}


/* This work for sets */
template<class ElementType, class Comp, class Alloc, class IteratorType>
inline void remove_from(std::set<ElementType, Comp, Alloc>& cont, IteratorType pos) throw(ElementNotFound)
{
    cont.erase(pos);
}

/*--removing by element--*/
/*This works for lists*/
template <class ElementType, class Alloc>
inline void remove_from(std::list<ElementType, Alloc>& cont, const ElementType& element) throw(ElementNotFound)
{
    cont.remove(element);
}

/* This works for vectors and sets */
template <class Container>
inline void remove_from(Container& cont, const typename Container::value_type& element) throw(ElementNotFound)
{
    const typename Container::iterator it = find(cont.begin(), cont.end(), element);
    if (it == cont.end())
        throw ElementNotFound();
    else
    cont.erase(it);
}

/* This works for maps */
template <class Key, class T, class Comp, class Alloc, class Key2>
inline void remove_from(std::map<Key, T, Comp, Alloc>& m, const Key2& key) throw(ElementNotFound)
{
    m.erase(key);
}

// Generic container
template <class T>
struct ContainerAdapter
{
    virtual void insert(const T& element) = 0;
    virtual ~ContainerAdapter(){}
};

template <class T, class Impl>
class ContainerAdapterImpl : public ContainerAdapter<T>
{
    Impl& container;
    virtual void insert(const T& element)
    {
        insert_into(container, element);
    }

public:
    ContainerAdapterImpl(Impl& cont)
        : container(cont)
    {}
};

// CopyContainer -----------------------------
template <class C1, class C2>
static inline void copy_container(const C1& c1, C2& c2)
{
	std::copy(c1.begin(), c1.end(), std::back_insert_iterator<C2> (c2));
}

// TODO: Add more containers.

// Autonomous iterators ----------------------
template <class T>
class AutonomousIterator
{
    T _current;
    const T _end;
public:
    typedef typename T::value_type value_type;
    typedef typename T::reference reference;

    AutonomousIterator(const T& begin, const T& end)
        : _current(begin), _end(end)
    {}

    AutonomousIterator(const AutonomousIterator<T>& other)
        : _current(other._current), _end(other._end)
    {}

    // Construct from a container
    // TBD

    AutonomousIterator<T>& operator ++()
    {
        ++_current;
        return *this;
    }

    AutonomousIterator<T> operator ++(int)
    {
        const AutonomousIterator<T> ret(*this);
        ++(*this);
        return ret;
    }

    AutonomousIterator<T>& operator --()
    {
        --_current;
        return *this;
    }

    AutonomousIterator<T> operator --(int)
    {
        const AutonomousIterator<T> ret(*this);
        --(*this);
        return ret;
    }

    bool operator == (const AutonomousIterator<T>& other) const
    {
        return _current == other._current;
    }

    reference operator*()
    {
        return *_current;
    }

    T& operator->()
    {
        return _current;
    }

    const T& operator->() const
    {
        return _current;
    }

    bool end() const
    {
        return _current == _end;
    }
}; 

NAMESPACE_END

#endif
