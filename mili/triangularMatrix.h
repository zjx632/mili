/*
TriangularMatrix: implementation of a triangular matrix with main diagonal include.
    Copyright (C) 2011  Jorge E. A. Atala
                        FuDePAN
    This file is part of the mili Proyect.

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


#ifndef TRIANGULAR_MATRIX_H
#define TRIANGULAR_MATRIX_H

#include "generic_exception.h"

NAMESPACE_BEGIN

class TriangularMatrixExceptionHierarchy {};

typedef GenericException<TriangularMatrixExceptionHierarchy> TriangularMatrixException;

DEFINE_SPECIFIC_EXCEPTION_TEXT(OutOfBoundsTriangularMatrix,
                               TriangularMatrixExceptionHierarchy,
                               "The value of the coords is out of bound.");

template<class Item>
class TriangularMatrix
{
private:
    Item* matrix;
    const size_t sideLength;
    inline size_t getIndex(const size_t firstCoord, const size_t secondCoord)const;
    inline size_t gaussNumber(const size_t n)
    {
        return (n * (n + 1)) / 2;
    }

public:
    TriangularMatrix(const size_t sideLength);
    inline Item getItem(const size_t firstCoord, const size_t secondCoord) const;
    inline void setItem(const Item& newItem, const size_t firstCoord, const size_t secondCoord);
    ~TriangularMatrix();
};

template<class Item>
TriangularMatrix<Item>::TriangularMatrix(const size_t sideLength)
{
    this->sideLength = sideLength;
    matrix = new Item [gaussNumber(sideLength)];
//hacer init list
}

template<class Item>
inline size_t TriangularMatrix<Item>::getIndex(const size_t firstCoord, const size_t secondCoord) const
{
    size_t row;
    size_t column;

    if (firstCoord >= sideLength || secondCoord >= sideLength)
        throw OutOfBoundsTriangularMatrix();

    if (firstCoord > secondCoord)
    {
        row = firstCoord;
        column = secondCoord;
    }
    else
    {
        row = secondCoord;
        column = firstCoord;
    }
    return gaussNumber(column) + row;
}

template<class Item>
inline Item TriangularMatrix<Item>::getItem(const size_t firstCoord, const size_t secondCoord) const
{
    return matrix[getIndex(firstCoord, secondCoord)];
}

template<class Item>
void TriangularMatrix<Item>::setItem(const Item& newItem, const size_t firstCoord, const size_t secondCoord)
{
    matrix[getIndex(firstCoord, secondCoord)] = newItem;
}

template<class Item>
TriangularMatrix<Item>::~TriangularMatrix()
{
    delete [] matrix;
}

NAMESPACE_END

#endif

