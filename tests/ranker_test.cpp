/*
    Copyright (C) 2011 Hugo Arregui, FuDePAN

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

using namespace std;
using namespace mili;

struct Player
{
    string name;
    float  score;

    Player(string name, float score) : 
        name(name), 
        score(score)
    {}
};

/* Compare two Players' names */
struct PlayerUnique
{
    bool operator()(const Player& p1, const Player& p2)
    {
        if ((p1.name).compare(p2.name) > 0)
            return true;
        else
            return false;
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

typedef UniqueRanker<Player, PlayerRanking, PlayerUnique> PlayersRanking;

bool isSorted(CAutonomousIterator<PlayersRanking> it)
{
    bool sorted = true;
    float score = it->score;
    while (!it.end() && sorted)
    {
        ++it;
        sorted = score >= it->score;
        score = it->score;
    }
    return sorted;
}

TEST(UniqueRankerTest, test)
{
    PlayersRanking UR(5);

    ASSERT_TRUE(UR.insert(Player("Umpa lumpa A", .1)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa B", .3)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa C", .3)));
    ASSERT_FALSE(UR.insert(Player("Umpa lumpa B", .2)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa D", .5)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa E", .6)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa B", .5)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa F", .8)));

    CAutonomousIterator<PlayersRanking> it(UR);
    ASSERT_TRUE(isSorted(it));

    ASSERT_EQ("Umpa lumpa F", UR.top().name);
    ASSERT_EQ("Umpa lumpa C", UR.bottom().name);

    UR.remove(Player("Umpa lumpa E", .6));
    CAutonomousIterator<PlayersRanking> it2(UR);
    ASSERT_TRUE(isSorted(it2));
}

typedef Ranker<int, AddBeforeEqual> Ranking;

bool isSorted(CAutonomousIterator<Ranking> it)
{
    bool sorted = true;
    int score = *it;
    while (!it.end() && sorted)
    {
        ++it;
        sorted = score >= *it;
        score = *it;
    }
    return sorted;
}

TEST(RankerTest, test)
{
    const size_t TOP = 5;
    const int I = -10;
    Ranking R(TOP);

    R.insert(10);
    R.insert(30);
    R.insert(I);
    R.insert(20);
    R.insert(I);

    CAutonomousIterator<Ranking> it(R);
    isSorted(it);

    R.insert(0);
    R.insert(50);
    CAutonomousIterator<Ranking> it1(R);
    isSorted(it1);

    R.remove_all(I);
    CAutonomousIterator<Ranking> it2(R);
    isSorted(it2);

    ASSERT_EQ(3, R.size());
    ASSERT_EQ(0, R.top());
    ASSERT_EQ(20, R.bottom());

    R.clear();
    ASSERT_EQ(0, R.size());
}
