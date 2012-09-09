/*
    Copyright (C) 2011 Hugo Arregui, Emmanuel Teisaire, FuDePAN

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

    This is a test file.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mili/mili.h"

using std::string;
using namespace mili;

struct Player
{
    string name;
    float  score;

    Player(string name, float score)
        : name(name),
          score(score)
    {}

    bool operator==(const Player& aPlayer) const
    {
        return name == aPlayer.name;
    }
};

/* Compare two Players' names */
struct PlayerUnique
{
    bool operator()(const Player& p1, const Player& p2)
    {
        return p1.name > p2.name;
    }
};

/* Compare two Players' scores */
struct PlayerRanking
{
    bool operator()(const Player& p1, const Player& p2)
    {
        return p1.score > p2.score;
    }
};

template <class T>
struct PlayerPointerAdapter
{
    bool operator()(const Player* const p1, const Player* const p2)
    {
        T c;
        return p1 != NULL && p2 != NULL && c.operator()(*p1, *p2);
    }
};

template <class ScoreT, class T>
struct GetScore
{};

template<class T, class Iterator>
bool isSorted(Iterator it)
{
    GetScore<T, Iterator> f;
    bool sorted = true;
    T score = f(it);
    while (!it.end() && sorted)
    {
        sorted = (score >= f(it));
        score = f(it);
        ++it;
    }
    return sorted;
}

