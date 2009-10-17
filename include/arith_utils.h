/*
arith_utils.h: A minimal library with arithmetic utilities.
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

#ifndef ARITH_UTILS_H
#define ARITH_UTILS_H

#include <stdlib.h>
#include <sys/time.h>

NAMESPACE_BEGIN

template <class T>
class Randomizer
{
    unsigned int seed;
    const T min;
    const int width;
public:
    Randomizer(T min, T max)
        : min(min), width(int(max-min))
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        seed = tv.tv_usec;
    }

    T get()
    {
        return T(rand_r(&seed) % width) + min;
    }
};

#define SPECIALIZE_RND(T)                           \
template <>                                         \
class Randomizer<T>                                 \
{                                                   \
    unsigned int seed;                              \
    const T min;                                    \
    const T factor;                                 \
public:                                             \
    Randomizer(T min, T max)                        \
        : min(min), factor((max-min)/T(RAND_MAX))   \
    {                                               \
        struct timeval tv;                          \
        gettimeofday(&tv, NULL);                    \
        seed = tv.tv_usec;                          \
    }                                               \
                                                    \
    T get()                                         \
    {                                               \
        return T(rand_r(&seed)) * factor + min;     \
    }                                               \
}

SPECIALIZE_RND(float);
SPECIALIZE_RND(double);

#undef SPECIALIZE_RND

template <class T>
class _bchain
{
    const T _last_value;
    bool    _last_eval;

    _bchain(T value, bool last_eval)
        : _last_value(value), _last_eval(last_eval)
    {}
public:
    _bchain(T value)
        : _last_value(value), _last_eval(true)
    {}

    _bchain(const _bchain<T>& other)
        : _last_value(other._last_value), _last_eval(other._last_eval)
    {}

    operator bool() const
    {
        return _last_eval;
    }

    bool operator!() const
    {
        return !_last_eval;
    }

#define BCHAIN_OPERATOR(op)                                                 \
    _bchain<T> operator op (T rvalue) const                                 \
    {                                                                       \
        return _bchain<T>(rvalue, _last_eval && (_last_value op rvalue));   \
    }

    BCHAIN_OPERATOR(<);
    BCHAIN_OPERATOR(<=);
    BCHAIN_OPERATOR(>);
    BCHAIN_OPERATOR(>=);
    BCHAIN_OPERATOR(==);
    BCHAIN_OPERATOR(!=);

#undef BCHAIN_OPERATOR
};

#define BCHAIN_NONMEMBER_OPERATOR(op, rop)                      \
template <class T>                                              \
inline _bchain<T> operator op (T value, const _bchain<T>& bch)  \
{                                                               \
    return bch rop value;                                       \
}

BCHAIN_NONMEMBER_OPERATOR(<,>);
BCHAIN_NONMEMBER_OPERATOR(>,<);
BCHAIN_NONMEMBER_OPERATOR(<=,>=);
BCHAIN_NONMEMBER_OPERATOR(>=,<=);
BCHAIN_NONMEMBER_OPERATOR(==,==);
BCHAIN_NONMEMBER_OPERATOR(!=,!=);

#undef BCHAIN_NONMEMBER_OPERATOR

template <class T>
inline _bchain<T> bchain(T value) { return _bchain<T>(value); }

template <class T>
inline bool in_range(T val, T min, T max)
{
    return min <= bchain(val) <= max;
}

class FirstTimeFlag
{
    bool value;
public:
    FirstTimeFlag() : value(true){}

    operator bool()
    {
        const bool ret(value);
        value = false;
        return ret;
    }

    bool operator!()
    {
        return !operator bool();
    }
};

template <class T>
inline T square(T t)
{
    return t*t;
} 

template <class T>
inline T maximize(T& t, T value)
{
    if (t < value)
        t = value;

    return t;
}

template <class T>
inline T minimize(T& t, T value)
{
    if (t > value)
        t = value;

    return t;
}

NAMESPACE_END

#endif
