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

NAMESPACE_BEGIN

template<class T, class Comp = std::less<T> >
class Ranker
{
private:
    typedef std::list<T> Ranking;

    Ranking ranking;                           //! Contenedor de elementos rankeados 
    const size_t TOP;                          //! cantidad max de elementos

public:
    //! Definiciones que me permiten usar mili
    typedef typename Ranking::const_iterator const_iterator;
    typedef typename Ranking::value_type value_type;
    typedef typename Ranking::reference reference;
    typedef typename Ranking::const_reference const_reference;
    //! Constructor
    Ranker(size_t top): ranking(), TOP(top)
    {}

    //! Operadores
    inline bool insert(const T& element);       //! inserta el elemento
    inline void remove(const T& element);       //! remueve el elemento
    inline bool empty() const;                  //! indica si esta vacio
    inline size_t size() const;                 //! indica el tamaño
    inline void clear() const;                  //! elimina todos los elementos
    inline const_iterator begin() const;        //! retorna iterador const al peor rankeado elemento
    inline const_iterator end() const;          //! retorna iterador const al mejor rankeado elemento
    inline const T& upper() const;              //! retorna el elemento mejor rankeado
    inline const T& lower() const;              //! retorna el elemento peor rankeado
};

template<class T, class Comp>
inline bool Ranker<T, Comp>::insert(const T& element)
{
    const bool success (ranking.size() < TOP);
    if(success)
    {
        ranking.push_back(element);
        ranking.sort(Comp());
    }
    return success;   
}

template<class T, class Comp>
inline void Ranker<T, Comp>::remove(const T& element)
{
    ranking.remove(element);
}

template<class T, class Comp>
inline bool Ranker<T, Comp>::empty() const
{
    return ranking.empty();
}

template<class T, class Comp>
inline size_t Ranker<T, Comp>::size() const
{
    return ranking.size();
}

template<class T, class Comp>
inline void Ranker<T, Comp>::clear() const
{
    ranking.clear();
}

template<class T, class Comp>
inline typename std::list<T>::const_iterator Ranker<T, Comp>::begin() const
{
    return ranking.begin();
}

template<class T, class Comp>
inline typename std::list<T>::const_iterator Ranker<T, Comp>::end() const
{
    return ranking.end();
}

template<class T, class Comp>
inline const T& Ranker<T, Comp>::upper() const
{
    return *(ranking.begin());
}

template<class T, class Comp>
inline const T& Ranker<T, Comp>::lower() const
{
    return *(ranking.end());
}

NAMESPACE_END

#endif
