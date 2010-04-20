/*
Ranker: A minimal library that implements a set of variables.
    Copyright (C) 2010  Daniel Gutson, FuDePAN
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

#ifndef VARIANTS_SET_H
#define VARIANTS_SET_H

#include <string>
#include <map>

NAMESPACE_BEGIN

struct VariantsSetException : std::exception {};
struct BadElementType : VariantsSetException {};
struct BadElementName : VariantsSetException {};

typedef std::string ElementName;

class VariantsSet
{
    std::map<ElementName, std::string> elements;  //! Atributos de la politica

public:
    //! Retorna el atributo con el nombre attr
    template <class T>
    void get_element(const ElementName& name, T& element) const throw (BadElementType, BadElementName)
    {
        const std::map<ElementName, std::string>::const_iterator it = elements.find(name);
        if (it != elements.end())
            element = from_string<T>(it->second);
        else
            throw BadElementName();
    }

    //! incorpora un atributo a la politica
    template <class T>
    void insert(const ElementName& name, const T& element)
    {
        elements[name] = to_string(element);
    }

    bool empty()
    {
        return elements.empty();
    }
    
    void erase(const ElementName& name)
    {
        elements.erase(name);
    }

    void clear()
    {
        return elements.clear();
    }

    size_t size()
    {
        return elements.size();
    }

    VariantsSet()
    : elements()
    {}
};

NAMESPACE_END

#endif
