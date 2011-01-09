/*
example_ranker: An example that uses MiLi's Ranker.
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

    This is an example file.
*/

#include <iostream>
#include "include/mili.h"

using namespace std;

template <class T>
void print(CAutonomousIterator<T> it)
{
    while (!it.end())
    {
        cout << *it << endl;
        ++it;
    }
}
//------------------------------

struct Player
{
    string name;
    float  score;

    Player(string name, float score): name(name), score(score)
    {}

    void print () const
    {
        cout << name << " - " << score << endl;
    }
};

/* Compare two Players' names */
struct PlayerUnique
{
    bool operator()(const Player& p1, const Player& p2)
    {
        if((p1.name).compare(p2.name) > 0)
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

void print_classes (CAutonomousIterator<PlayersRanking> it)
{
    while (!it.end())
    {
        it->print();
        ++it;
    }
    cout << "_______________________" << endl;
}

void unique_ranker_test()
{
    PlayersRanking UR(5);

    cout << UR.insert(Player("Umpa lumpa A", .1)) << endl;;
    cout << UR.insert(Player("Umpa lumpa B", .3)) << endl;
    cout << UR.insert(Player("Umpa lumpa C", .3)) << endl;
    cout << UR.insert(Player("Umpa lumpa B", .2)) << endl;
    cout << UR.insert(Player("Umpa lumpa D", .5)) << endl;
    cout << UR.insert(Player("Umpa lumpa E", .6)) << endl;
    cout << UR.insert(Player("Umpa lumpa B", .5)) << endl;
    cout << UR.insert(Player("Umpa lumpa F", .8)) << endl;

    CAutonomousIterator<PlayersRanking> it(UR);
    print_classes(it);

    UR.top().print();                     // Print the top Umpa Lumpa
    UR.bottom().print();                  // Print the bottom Umpa Lumpa

    cout << "-------- remove Umpa lumpa E --------" << endl;
    UR.remove(Player("Umpa lumpa E", .6));
    CAutonomousIterator<PlayersRanking> it2(UR);
    print_classes(it2);
}

//-------------------------------------------
typedef Ranker<int, AddBeforeEqual> Ranking;

void ranker_test()
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
    print<Ranking> (it);

    cout << "-- Insert 0 and 50 --" << endl;
    R.insert(0);
    R.insert(50);

    CAutonomousIterator<Ranking> it1(R);
    print<Ranking> (it1);

    R.remove_all(I);
    cout << "-- Remove All " << I << " --" << endl;

    CAutonomousIterator<Ranking> it2(R);
    print<Ranking> (it2);
    cout << "----- size: " << R.size() << endl;
    cout << "top: " << R.top() << " - bottom: " << R.bottom() << endl;

    if (!R.empty()) R.clear();

    cout << "size after clear: " << R.size() << endl;
}

//------------------------------------------------------
int main()
{
    string test;
    cout << "Indicate which library you want to test. (R = Ranker ; UR = Unique Ranker):" << endl;
    cin >> test;

    if (test == "R")
        ranker_test();
    else if (test == "UR")
        unique_ranker_test();
    else
        cout << "Error: you must choose R or UR" << endl;
    return 0;
}

