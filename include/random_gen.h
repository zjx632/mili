/*
random_gen.h: A minimal library for generating random numbers.
    Copyright (C) 2010 Daniel Gutson, FuDePAN

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

#ifndef RANDOM_GEN_H
#define RANDOM_GEN_H

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
    
    Randomizer(T min, T max, unsigned int seed)
        : min(min), width(int(max-min)), seed(seed)
    {
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
    Randomizer(T min, T max, unsigned int seed)     \
        : min(min), factor((max-min)/T(RAND_MAX))   \
        , seed(seed)                                \
    {                                               \
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

NAMESPACE_END

#endif
