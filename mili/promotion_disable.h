/*
promotion_disable.h: A minimalistic library to disable undesired
    type promotions in C++.
    Copyright (C) 2009, Daniel Gutson, FuDePAN

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
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PROMOTION_DISABLE_H
#define PROMOTION_DISABLE_H

#include "compile_assert.h"
#include "template_info.h"

NAMESPACE_BEGIN

/* RulesCondition<cond> will only allow conversion when cond==true */
template <bool C>
struct RulesCondition
{
    enum { value = C };
};

/* StrictRules disables any conversion; only T --> T allowed */
template <class T, class U> struct StrictRules : RulesCondition<type_equal<T, U>::value>
{};

/* FloatingPoints allows T-->T, plus Double to Float */
template <class T, class U>
struct FloatingPoints : StrictRules<T, U>
{};

template <>
struct FloatingPoints<float, double>
{
    enum { value = true };
};

//[> disable conversion depending on size <]
template <class T, class U>
struct NotNarrowing : RulesCondition < sizeof(T) <= sizeof(U) >
{};

//[> disable conversion from int to float, if they have the same size <]
template <>
struct NotNarrowing<float, int>
{
    enum { value = false };
};

declare_static_assert(invalid_conversion);

template < class T, template <class X, class Y> class ConversionRules = StrictRules >
class Restrict
{
    const T value;
public:
    template <class U>
    Restrict(U u) : 
        value(u)
    {
        typedef ConversionRules<T, U> ConversionType;
        template_compile_assert(ConversionType::value, invalid_conversion);
    }

    operator T() const
    {
        return value;
    }
};

NAMESPACE_END

#endif
