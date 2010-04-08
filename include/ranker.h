/*
ranker: A minimal library that implements a ranking of elements.
    Copyright (C) 2010  Ezequiel S. Velez

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
#include <algorithm>
#include <functional>
#include <utility>

NAMESPACE_BEGIN

enum SameValueBehavior
    {
        AddBeforeEqual,
        AddAfterEqual
    };

template<class T,SameValueBehavior Behavior = AddAfterEqual, class Comp = std::less<T> >
class Ranker
{
private:
    typedef std::list<T> Ranking;
    typedef typename Ranking::iterator iterator;

    Ranking ranking;                           // Container. 
    const size_t TOP;                          // Maximum number of elements.

public:
    // typedef to simulate STL 
    typedef typename Ranking::const_iterator const_iterator;
    typedef typename Ranking::value_type value_type;
    typedef typename Ranking::reference reference;
    typedef typename Ranking::const_reference const_reference;

    // Constructor
    Ranker(size_t top): ranking(), TOP(top)
    {}

    // Member:
    /* Inserts the element. */
    inline const_iterator insert(const T& element); 
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
};

template<class T, SameValueBehavior Behavior, class Comp>
inline typename std::list<T>::const_iterator Ranker<T, Behavior, Comp>::insert(const T& element)
{
    std::pair<iterator, iterator> position = equal_range(ranking.begin(), ranking.end(), element, Comp());
    const bool top_not_reached (ranking.size() < TOP);

    if (top_not_reached)
    {
        if(Behavior == AddBeforeEqual)
            ranking.insert(position.first, element);
        else
            ranking.insert(position.second, element);
    }else
    {
        if(Behavior == AddBeforeEqual)
            ranking.insert(position.first, element);
        else
            ranking.insert(position.second, element);
        ranking.erase(--ranking.end());
    }
    return position.first;   
}

template<class T, SameValueBehavior Behavior, class Comp>
inline void Ranker<T, Behavior, Comp>::remove_first(const T& element)
{
    iterator pos = find(ranking.begin(), ranking.end(), element);
    ranking.erase(pos);
}

template<class T, SameValueBehavior Behavior, class Comp>
inline void Ranker<T, Behavior, Comp>::remove_all(const T& element)
{
    ranking.remove(element);
}

template<class T, SameValueBehavior Behavior, class Comp>
inline bool Ranker<T, Behavior, Comp>::empty() const
{
    return ranking.empty();
}

template<class T, SameValueBehavior Behavior, class Comp>
inline size_t Ranker<T, Behavior, Comp>::size() const
{
    return ranking.size();
}

template<class T, SameValueBehavior Behavior, class Comp>
inline void Ranker<T, Behavior, Comp>::clear()
{
    ranking.clear();
}

template<class T, SameValueBehavior Behavior, class Comp>
inline typename std::list<T>::const_iterator Ranker<T, Behavior, Comp>::begin() const
{
    return ranking.begin();
}

template<class T, SameValueBehavior Behavior, class Comp>
inline typename std::list<T>::const_iterator Ranker<T, Behavior, Comp>::end() const
{
    return ranking.end();
}

template<class T, SameValueBehavior Behavior, class Comp>
inline const T& Ranker<T, Behavior, Comp>::top() const
{
    return *(ranking.begin());
}

template<class T, SameValueBehavior Behavior, class Comp>
inline const T& Ranker<T, Behavior, Comp>::bottom() const
{
    return *(--ranking.end());
}

NAMESPACE_END

#endif
