/*
find_utils: A minimal library with generic find functions with exceptions.
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

#ifndef FIND_UTILS_H
#define FIND_UTILS_H

// Supported containers for mili::find() and mili::contains():
#include <map>
#include <vector>
#include <list>
#include <set>

#include <algorithm>
#include <exception>

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

// TODO: Add more containers.

#endif
