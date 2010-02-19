/*
fast_list: A minimal library that implements very high performant fast lists.
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
*/

#ifndef FAST_LIST_H
#define FAST_LIST_H

#include <new>
#include <list>

NAMESPACE_BEGIN

template <class T, size_t CHUNK_SIZE = 10 /*, bool auto_delete_chunks = false NOT YET IMPLEMENTED*/ >
class FastList
{
    struct Node;

    struct PhysicalList
    {
        Node* first;
        Node* last;

        PhysicalList() : first(NULL), last(NULL) {}

        bool empty() const
        {
            return first == NULL;
        }
    };

    typedef char Placeholder[sizeof(T)];

    struct Node
    {
        Node*       previous;
        Node*       next;
        Placeholder placeholder;

        T& get_data()
        {
            return *reinterpret_cast<T*>(&placeholder[0]);
        }

        const T& get_data() const
        {
            return *reinterpret_cast<const T*>(&placeholder[0]);
        }

        void destroy()
        {
            get_data().~T();
        }

        void make_last()
        {
            next = NULL;
        }

        void make_first()
        {
            previous = NULL;
        }

        bool is_last() const
        {
            return next == NULL;
        }

        bool is_first() const
        {
            return previous == NULL;
        }

        void link_next(Node* new_next)
        {
            next = new_next;
            if (new_next != NULL)
                new_next->previous = this;
        }

        void link_previous(Node* new_prev)
        {
            previous = new_prev;
            if (new_prev != NULL)
                new_prev->next = this;
        }

        void detach_from_list(PhysicalList& old_list) // this is for implementation reasons. Assumes that the node belongs to this list.
        {
            if (is_first())
                old_list.first = next;
            else    // update my prev neighbor
                previous->link_next(next);

            if (is_last())
                old_list.last = previous;
            else    // update my next neighbor
                next->link_previous(previous);
        }

        void attach_to_list(PhysicalList& new_list)
        {
            if (new_list.empty())
            {
                make_first();
                new_list.first = new_list.last = this;
            }
            else
            {
                link_previous(new_list.last);
                new_list.last = this;
            }

            make_last();
        }
    };

    struct Chunk
    {
        size_t  used_nodes;
        Node    nodes[CHUNK_SIZE];

        // do nothing here
        Chunk()
        {}

        // node 0 is for immediate use. Nodes 1..CHUNK_SIZE-1 are free.
        Chunk(const Chunk& other) : used_nodes(1)
        {
            if (CHUNK_SIZE > 1)
            {
                for(size_t i=1; i < (CHUNK_SIZE - 1); ++i)
                    nodes[i].link_next(&nodes[i+1]);

                nodes[1].make_first();
                nodes[CHUNK_SIZE-1].make_last();
            }
        }
    };

    PhysicalList        empty_nodes;
    PhysicalList        used_nodes;
    std::list<Chunk>    chunks;

    Node* allocate_node()
    {
        Node* ret;
        if (empty_nodes.empty())
        {
            // allocate new chunk:
            chunks.push_back(Chunk());
            Chunk& new_chunk = chunks.back(); 
            ret = &new_chunk.nodes[0];
            if (CHUNK_SIZE > 1)
            {
                empty_nodes.first = &new_chunk.nodes[1];
                empty_nodes.last  = &new_chunk.nodes[CHUNK_SIZE-1];
            }
        }
        else
        {
            ret = empty_nodes.last;
            ret->detach_from_list(empty_nodes);
            // should update Chunk
        }

        ret->make_last();
        ret->attach_to_list(used_nodes);

        return ret;
    }
public:
    template <class NodePtr>
    class BasicHandler
    {
    protected:
        NodePtr node;
    public:
        BasicHandler()
            : node(NULL)
        {}

        BasicHandler(NodePtr node)
            : node(node)
        {}

        BasicHandler(const BasicHandler<NodePtr>& other)
            : node(other.node)
        {}

        BasicHandler<NodePtr>& operator = (const BasicHandler& other)
        {
            node = other.node;
            return *this;
        }

        const T& operator*() const
        {
            return node->get_data();
        }

        const T& operator ->() const
        {
            return operator*();
        }

        bool is_last() const
        {
            return node->is_last();
        }

        bool is_first() const
        {
            return node->is_first();
        }

        BasicHandler<NodePtr>& operator++()
        {
            node = node->next;
            return *this;
        }

        BasicHandler<NodePtr>& operator--()
        {
            node = node->previous;
            return *this;
        }

        BasicHandler<NodePtr> operator++(int)
        {
            BasicHandler<NodePtr> ret(*this);
            operator++();
            return ret;
        }

        BasicHandler<NodePtr> operator--(int)
        {
            BasicHandler<NodePtr> ret(*this);
            operator--();
            return ret;
        }

        bool is_valid() const
        {
            return node != NULL;
        }
    };

    typedef BasicHandler<const Node*> ConstElementHandler;

    class ElementHandler : public BasicHandler<Node*>
    {
    public:
        ElementHandler()
            : BasicHandler<Node*>(NULL)
        {}

        ElementHandler(Node* node)
            : BasicHandler<Node*>(node)
        {}

        ElementHandler(const ElementHandler& other)
            : BasicHandler<Node*>(other)
        {}

        ElementHandler& operator = (const ElementHandler& other)
        {
            //node = other.node;
            BasicHandler<Node*>::operator=(other);
            return *this;
        }

        T& operator*()
        {
            return this->node->get_data();
        }

        T& operator ->()
        {
            return operator*();
        }
    };

    class RemovableElementHandler : public ElementHandler
    {
        PhysicalList* empty_nodes_list;
        PhysicalList* used_nodes_list;
    public:
        RemovableElementHandler()
            : ElementHandler(), empty_nodes_list(NULL), used_nodes_list(NULL)
        {}

        RemovableElementHandler(Node* node, PhysicalList* empty_nodes_list, PhysicalList* used_nodes_list)
            : ElementHandler(node), empty_nodes_list(empty_nodes_list), used_nodes_list(used_nodes_list)
        {}

        RemovableElementHandler(const RemovableElementHandler& other)
            : ElementHandler(other),
              empty_nodes_list(other.empty_nodes_list),
              used_nodes_list(other.used_nodes_list)
        {}

        RemovableElementHandler& operator = (const RemovableElementHandler& other)
        {
            ElementHandler::operator=(other);
            empty_nodes_list = other.empty_nodes_list;
            used_nodes_list = other.used_nodes_list;
            return *this;
        }

        bool destroy()
        {
            Node* const new_node = this->node->next;
            this->node->detach_from_list(*used_nodes_list);
            this->node->attach_to_list(*empty_nodes_list);
            this->node->destroy();
            this->node = new_node;
            // should update Chunk
            return this->is_valid();
        }
    };

    template <class Constructor>
    RemovableElementHandler new_node_generic(Constructor& c)
    {
        Node* node = allocate_node();
        c(node->get_data());
        return RemovableElementHandler(node, &empty_nodes, &used_nodes);
    }

    RemovableElementHandler new_node() // default constructor
    {
        Node* node = allocate_node();
        new(&node->get_data()) T();
        return RemovableElementHandler(node, &empty_nodes, &used_nodes);
    }

    RemovableElementHandler new_node(const T& other) // copy constructor
    {
        Node* node = allocate_node();
        new(&node->get_data()) T(other);
        return RemovableElementHandler(node, &empty_nodes, &used_nodes);
    }

    void shrink(){} // not yet implemented

    bool empty() const
    {
        return used_nodes.empty();
    }

    RemovableElementHandler first()
    {
        return RemovableElementHandler(used_nodes.first, &empty_nodes, &used_nodes);
    }

    ConstElementHandler first() const
    {
        return ConstElementHandler(used_nodes.first);
    }

    RemovableElementHandler last()
    {
        return RemovableElementHandler(used_nodes.last, &empty_nodes, &used_nodes);
    }

    ConstElementHandler last() const
    {
        return ConstElementHandler(used_nodes.last);
    }

    void clear()
    {
        if (!empty())
        {
            RemovableElementHandler h(first());
            while(h.destroy())
                ;
        }
    }

    ~FastList()
    {
        clear();
    }
};

NAMESPACE_END

#endif

