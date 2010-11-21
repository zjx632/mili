/*
Ranker: A minimal library that implements a ranking of elements.
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

/* This value disables the DisposalPolicy */
enum _NoDisposalPolicy
{
    NoDisposalPolicy
};

template<class T>
struct DisposalNullPolicy
{
    void operator()(const T& element)
    {}
};

template<class T>
struct DisposalDeletePolicy
{
    void operator()(const T& element)
    {
        delete element;
    }
};

template < class T, SameValueBehavior Behavior = AddAfterEqual, class Comp = std::less<T>, class DisposalPolicy = DisposalNullPolicy<T> >
class Ranker
{
protected:
    typedef std::list<T> Ranking;
    typedef typename Ranking::iterator iterator;

    Ranking ranking;                           /* Container. */
    const size_t TOP;                          /* Maximum number of elements.*/

    /* Insert an element and returns the position at it */
    inline bool insert(const T& element, iterator& it);

public:
    /* typedef to simulate STL */
    typedef typename Ranking::const_iterator const_iterator;
    typedef typename Ranking::value_type value_type;
    typedef typename Ranking::reference reference;
    typedef typename Ranking::const_reference const_reference;

    /* Constructor */
    Ranker(size_t top): ranking(), TOP(top)
    {}

    /* Member: */

    /* Inserts the element. */
    inline bool insert(const T& element);
    /* Removes the first occurrence of element. */
    inline void remove_first(const T& element);
    /* Removes all occurrences of element. */
    inline void remove_all(const T& element);
    /* Removes the first occurrence of element. */
    inline void remove_first(T* element);
    /* Removes all occurrences of element. */
    inline void remove_all(T* element);
    /* Removes the first occurrence of element without applying the DisposalPolicy. */
    inline void remove_first(const T& element, _NoDisposalPolicy);
    /* Removes all occurrences of element without applying the DisposalPolicy. */
    inline void remove_all(const T& element, _NoDisposalPolicy);
    /* Removes the first occurrence of element without applying the DisposalPolicy. */
    inline void remove_first(T* element, _NoDisposalPolicy);
    /* Removes all occurrences of element without applying the DisposalPolicy. */
    inline void remove_all(T* element, _NoDisposalPolicy);
    /* Erases all of the elements. */
    inline void clear();
    /* True if the Ranker is empty. */
    inline bool empty() const;
    /* Returns the size of the Ranker. */
    inline size_t size() const;
    /* Returns a const_iterator pointing to the beginning of the Ranker. */
    inline const_iterator begin() const;
    /* Returns a const_iterator pointing to the end of the Ranker. */
    inline const_iterator end() const;
    /* Returns the top element. */
    inline const T& top() const;
    /* Returns the bottom element. */
    inline const T& bottom() const;

    ~Ranker()
    {
        this->clear();
    }
};

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline bool Ranker<T, Behavior, Comp, DisposalPolicy>::insert(const T& element)
{
    const std::pair<iterator, iterator> position = equal_range(ranking.begin(), ranking.end(), element, Comp());
    const bool top_not_reached(ranking.size() < TOP);
    bool success(true);
    iterator pos;

    if (Behavior == AddBeforeEqual)
        pos = position.first;
    else
        pos = position.second;

    ranking.insert(pos, element);

    if (!top_not_reached)
    {
        if (distance(pos, ranking.end()) == 0)
            success = false;
        DisposalPolicy()(*(--ranking.end()));
        ranking.erase(--ranking.end());
    }
    return success;
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline bool Ranker<T, Behavior, Comp, DisposalPolicy>::insert(const T& element, iterator& it)
{
    const std::pair<iterator, iterator> position = equal_range(ranking.begin(), ranking.end(), element, Comp());
    const bool top_not_reached(ranking.size() < TOP);
    bool success(true);
    iterator pos;

    if (Behavior == AddBeforeEqual)
        pos = position.first;
    else
        pos = position.second;

    it = pos;
    ranking.insert(pos, element);

    if (!top_not_reached)
    {
        if (distance(pos, ranking.end()) == 0)
            success = false;
        DisposalPolicy()(*(--ranking.end()));
        ranking.erase(--ranking.end());
    }
    return success;
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::remove_first(const T& element)
{
    const iterator pos = find(ranking.begin(), ranking.end(), element);
    DisposalPolicy()(*pos);
    ranking.erase(pos);
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::remove_all(const T& element)
{
    iterator it = ranking.begin();
    while (it != ranking.end())
    {
        if (element == *it)
            DisposalPolicy()(*it);
        ++it;
    }
    ranking.remove(element);
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::remove_first(T* element)
{
    const iterator pos = find(ranking.begin(), ranking.end(), *element);
    DisposalPolicy()(*element);
    ranking.erase(pos);
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::remove_all(T* element)
{
    iterator it = ranking.begin();
    while (it != ranking.end())
    {
        if (*element == *it)
            DisposalPolicy()(*it);
        ++it;
    }
    ranking.remove(*element);
}

/* version which does not apply DisposalPolicy */
template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::remove_first(const T& element, _NoDisposalPolicy)
{
    const iterator pos = find(ranking.begin(), ranking.end(), element);
    ranking.erase(pos);
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::remove_all(const T& element, _NoDisposalPolicy)
{
    ranking.remove(element);
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::remove_first(T* element, _NoDisposalPolicy)
{
    const iterator pos = find(ranking.begin(), ranking.end(), *element);
    ranking.erase(pos);
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::remove_all(T* element, _NoDisposalPolicy)
{
    ranking.remove(*element);
}

/*---------------------------------------------------------------*/
template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline bool Ranker<T, Behavior, Comp, DisposalPolicy>::empty() const
{
    return ranking.empty();
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline size_t Ranker<T, Behavior, Comp, DisposalPolicy>::size() const
{
    return ranking.size();
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::clear()
{
    iterator it = ranking.begin();
    while (it != ranking.end())
    {
        DisposalPolicy()(*it);
        ++it;
    }
    ranking.clear();
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline typename Ranker<T, Behavior, Comp, DisposalPolicy>::const_iterator Ranker<T, Behavior, Comp, DisposalPolicy>::begin() const
{
    return ranking.begin();
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline typename Ranker<T, Behavior, Comp, DisposalPolicy>::const_iterator Ranker<T, Behavior, Comp, DisposalPolicy>::end() const
{
    return ranking.end();
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline const T& Ranker<T, Behavior, Comp, DisposalPolicy>::top() const
{
    return *(ranking.begin());
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline const T& Ranker<T, Behavior, Comp, DisposalPolicy>::bottom() const
{
    return *(--ranking.end());
}

//---------------- Unique Ranker --------------------

template < class T, class Comp = std::less<T>, class CompEq = std::less<T>, class DisposalPolicy = DisposalNullPolicy<T> >
class UniqueRanker: public Ranker<T, AddAfterEqual, Comp, DisposalPolicy>
{
    typedef Ranker<T, AddAfterEqual, Comp, DisposalPolicy> Inheritance;

    typedef typename Inheritance::iterator iterator;
    typedef std::map<T, iterator, CompEq> UniqueRanking;
    typedef typename UniqueRanking::iterator uniqueIterator;

    UniqueRanking unique;
    size_t TOP;

public:
    typedef typename Inheritance::const_iterator const_iterator;

    UniqueRanker(size_t top): Inheritance::Ranker(top), TOP(top)
    {}

    /* Inserts the element. */
    inline bool insert(const T& element);
    /* Find a element. */
    inline const_iterator find(const T& element);
};

template<class T, class Comp, class CompEq, class DisposalPolicy>
inline bool UniqueRanker<T, Comp, CompEq, DisposalPolicy>::insert(const T& element)
{
    const uniqueIterator pos = unique.find(element);
    bool success(true);

    if (pos == unique.end())
    {
        iterator it;
        if (success = Inheritance::insert(element, it))
        {
            unique.insert(std::pair<T, iterator>(element, it));
            iterator itAux = Inheritance::ranking.begin();
            while (itAux != Inheritance::ranking.end())
            {
                unique.find(*itAux)->second = itAux;
                ++itAux;
            }
        }
    }
    else
    {
        if (Comp()(element, pos->first))
        {
            iterator it;
            Inheritance::ranking.erase(pos->second);
            success = Inheritance::insert(element, it);
            pos->second = it;
        }
        else
            success = false;
    }

    return success;
}

template<class T, class Comp, class CompEq, class DisposalPolicy>
inline typename UniqueRanker<T, Comp, CompEq, DisposalPolicy>::const_iterator UniqueRanker<T, Comp, CompEq, DisposalPolicy>::find(const T& element)
{
    return (unique.find(element))->second;
}

NAMESPACE_END
#endif

