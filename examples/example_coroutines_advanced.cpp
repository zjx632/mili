/*
example_coroutines_advanced: An advanced example that uses coroutines.
    Copyright (C) 2010  Daniel Gutson, FuDePAN

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
#include <set>
#include "mili/mili.h"

using namespace mili;
using namespace std;

// Example2: implementing an iterator for a tree walker.

struct TreeNode
{
    TreeNode* left;
    TreeNode* right;
    const bool is_white;
    const int data;
    static int last;

    TreeNode(bool is_white)
        : left(NULL), right(NULL), is_white(is_white), data(last++)
    {
        cout << data << ": " << boolalpha << is_white << endl;
    }
    ~TreeNode()
    {
        delete left;
        delete right;
    }
};

static TreeNode* build_sample_tree();

class WhiteNodesIterator : public Coroutine
{
    TreeNode*           current;
    WhiteNodesIterator* child_iterator;
public:
    TreeNode* operator()(TreeNode* start)
    {
        TreeNode* child;    // non persistent data: re-assigned on every yield.

        BEGIN_COROUTINE
        {
            current = start;
            if (current != NULL)
            {
                if (current->is_white)
                    mili_yield(current);

                child_iterator = new WhiteNodesIterator;

                do
                {
                    child = (*child_iterator)(current->left);
                    if (child != NULL) mili_yield(child);
                }
                while (child != NULL);

                do
                {
                    child = (*child_iterator)(current->right);
                    if (child != NULL) mili_yield(child);
                }
                while (child != NULL);

                delete child_iterator;
            }

        }
        END_COROUTINE(NULL);
    }
};

// Example3: all the triples of a set.
template <class T>
class SetTriplets : public Coroutine
{
    typename set<T>::const_iterator t1;
    typename set<T>::const_iterator t2;
    typename set<T>::const_iterator t3;
public:
    bool operator()(const set<T>& s, T& elem1, T& elem2, T& elem3)
    {
        BEGIN_COROUTINE
        {
            // assumption: the set 's' is always the same.
            for (t1 = s.begin(); t1 != s.end(); ++t1)
            {
                for (t2 = s.begin(); t2 != s.end(); ++t2)
                {
                    if (t2 != t1)
                    {
                        for (t3 = s.begin(); t3 != s.end(); ++t3)
                        {
                            if (t3 != t1 && t3 != t2)
                            {
                                elem1 = *t1;
                                elem2 = *t2;
                                elem3 = *t3;
                                mili_yield(true);
                            }
                        }
                    }
                }
            }
        }
        END_COROUTINE(false);
    }
};

int main()
{
    // Example2:
    TreeNode* root = build_sample_tree();
    TreeNode* node = root;
    WhiteNodesIterator iter;
    while (node != NULL)
    {
        node = iter(node);
        if (node != NULL)
            cout << node->data << endl;
    }
    delete root;

    // Example3:
    set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    SetTriplets<int> st;
    int e1, e2, e3;
    while (st(s, e1, e2, e3))
        cout << e1 << "," << e2 << "," << e3 << endl;

    return 0;
}

TreeNode* build_sample_tree()
{
    TreeNode* const root = new TreeNode(true);

    root->left = new TreeNode(false);

    root->right = new TreeNode(true);

    root->right->left = new TreeNode(true);
    root->right->right = new TreeNode(false);

    root->right->left->left = new TreeNode(true);
    root->right->left->right = new TreeNode(true);

    return root;
}

int TreeNode::last(0);

