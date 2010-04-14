/*
ranker: A minimal library that implements a ranking of elements.
    Copyright (C) 2010  Ezequiel S. Velez
                        Daniel Gutson, FuDePAN

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

#ifndef RANKER_H
#define RANKER_H

#include <list>
#include <iterator>
#include <algorithm>
#include <functional>
#include <utility>

NAMESPACE_BEGIN

/* to do when you insert an existing value */
enum SameValueBehavior
{
    AddBeforeEqual,
    AddAfterEqual
};

template<class T,SameValueBehavior Behavior = AddAfterEqual, class Comp = std::less<T> >
class ranker
{
private:
    typedef std::list<T> Ranking;
    typedef typename Ranking::iterator iterator;

    Ranking ranking;                           /* Container. */ 
    const size_t TOP;                          /* Maximum number of elements.*/

public:
    /* typedef to simulate STL */ 
    typedef typename Ranking::const_iterator const_iterator;
    typedef typename Ranking::value_type value_type;
    typedef typename Ranking::reference reference;
    typedef typename Ranking::const_reference const_reference;

    /* Constructor */
    ranker(size_t top): ranking(), TOP(top)
    {}

    /* Member: */

    /* Inserts the element. */
    inline bool insert(const T& element); 
    /* Removes the first occurrence of element. */  
    inline void remove_first(const T& element);
    /* Removes all occurrences of element. */ 
    inline void remove_all(const T& element);
    /* Erases all of the elements. */
    inline void clear();
    /* True if the ranker is empty. */
    inline bool empty() const;
    /* Returns the size of the ranker. */
    inline size_t size() const;
    /* Returns a const_iterator pointing to the beginning of the ranker. */
    inline const_iterator begin() const;
    /* Returns a const_iterator pointing to the end of the ranker. */ 
    inline const_iterator end() const;
    /* Returns the top element. */
    inline const T& top() const;
    /* Returns the bottom element. */
    inline const T& bottom() const;
    /* Finds an element into the ranker */
    inline const_iterator find_element(const_iterator first, const_iterator last, const T& element) const;
};

template<class T, SameValueBehavior Behavior, class Comp>
inline bool ranker<T, Behavior, Comp>::insert(const T& element)
{
    const std::pair<iterator, iterator> position = equal_range(ranking.begin(), ranking.end(), element, Comp());
    const bool top_not_reached (ranking.size() < TOP);
    bool success (true);
    iterator pos;

    if(Behavior == AddBeforeEqual)
        pos = position.first;
    else
        pos = position.second;

    ranking.insert(pos, element);

    if(!top_not_reached)
    {
        if(distance(pos, ranking.end())==0)
            success = false;
        ranking.erase(--ranking.end());
    }
    return success;   
}

template<class T, SameValueBehavior Behavior, class Comp>
inline void ranker<T, Behavior, Comp>::remove_first(const T& element)
{
    iterator pos = find(ranking.begin(), ranking.end(), element);
    ranking.erase(pos);
}

template<class T, SameValueBehavior Behavior, class Comp>
inline void ranker<T, Behavior, Comp>::remove_all(const T& element)
{
    ranking.remove(element);
}

template<class T, SameValueBehavior Behavior, class Comp>
inline bool ranker<T, Behavior, Comp>::empty() const
{
    return ranking.empty();
}

template<class T, SameValueBehavior Behavior, class Comp>
inline size_t ranker<T, Behavior, Comp>::size() const
{
    return ranking.size();
}

template<class T, SameValueBehavior Behavior, class Comp>
inline void ranker<T, Behavior, Comp>::clear()
{
    ranking.clear();
}

template<class T, SameValueBehavior Behavior, class Comp>
inline typename std::list<T>::const_iterator ranker<T, Behavior, Comp>::begin() const
{
    return ranking.begin();
}

template<class T, SameValueBehavior Behavior, class Comp>
inline typename std::list<T>::const_iterator ranker<T, Behavior, Comp>::end() const
{
    return ranking.end();
}

template<class T, SameValueBehavior Behavior, class Comp>
inline const T& ranker<T, Behavior, Comp>::top() const
{
    return *(ranking.begin());
}

template<class T, SameValueBehavior Behavior, class Comp>
inline const T& ranker<T, Behavior, Comp>::bottom() const
{
    return *(--ranking.end());
}

template<class T, SameValueBehavior Behavior, class Comp>
inline typename std::list<T>::const_iterator ranker<T, Behavior, Comp>::find_element(const_iterator first, const_iterator last, const T& element) const
{
    return find(first, last, element);
}

NAMESPACE_END

#endif
