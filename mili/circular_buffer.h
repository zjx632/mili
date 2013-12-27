/*
circular_buffer: A type-templetized circular buffer.
    This file is part of the MiLi Minimalistic Library.


    Copyright (C) Pablo Oliva, Franco Riberi, FuDePAN 2009
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt in the root directory or
    copy at http://www.boost.org/LICENSE_1_0.txt)

    MiLi IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#ifndef CIRC_BUFFER_H
#define CIRC_BUFFER_H

#include <stdint.h>

NAMESPACE_BEGIN

/** @brief The type we want to use for circular buffer. */
typedef uint16_t UInt;

/**
 * @brief Circular buffer
 */
template<typename T, UInt Size>
class CircBuffer
{
public:

    /**
     * @brief Constructor.
     */
    CircBuffer();

    /**
     * @brief Checks if the buffer is full.
     * @return true if the buffer is full, false otherwise.
     */
    bool isFull() const;

    /**
     * @brief  Checks if the buffer is empty.
     * @return true if the buffer is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Resets the buffer
     */
    void flush();

    /**
     * @brief Adds the item k to the buffer. Fails if the buffer is full.
     *
     * @param item      The item we want to add.
     */
    void queue(T item);

    /**
     * @brief Tells how much buffer space is available.
     * @return Space available in the buffer.
     */
    UInt available() const;

    /**
     * @brief Tells how much buffer space is used.
     *
     * @return Space used in the buffer.
     */
    UInt used() const;

    /**
     * @brief Tells how large the buffer is.
     *
     * @return Size of the buffer.
     */
    UInt size() const;

    /**
     * @brief Removes the index pointed to by _read and returns it. Fails if the buffer is empty.
     *
     * @return The removed item.
     */
    T dequeue();

    /**
     * @brief Discards amount elements of the buffer, fails if there are too few elements.
     *
     * @param amount The amount of elements we want to discard.
     */
    void discard(UInt amount);

    /**
    * @brief Moves as many items as possible from src to this CircBuffer.
    *
    * @param src    The CircBuffer whose elements we want to move here.
    *
    * @return The amount of elements moved.
    */
    template<UInt SrcSize>
    UInt moveFrom(CircBuffer<T, SrcSize>& src);

private:
    /**
     * @brief Checks if the read index is valid, points it to ParkingLot otherwise.
     */
    void parkReadIndex();

    /**
     * @brief If there are values to read, points the read index to the first of such values; does nothing otherwise.
     */
    void unparkReadIndex();

    /**
     * @brief The write index on the array.
     */
    UInt _write;

    /**
     * @brief The read index on the array; is equal to ParkingLot when there is no data to read.
     */
    UInt _read;

    /**
     * @brief The array of elements where we store our values.
     */
    T _buf[Size];

    /**
     * @brief The place where the read index goes when it has no valid data to point to.
     */
    static const UInt ParkingLot = Size;
};

NAMESPACE_END

#define CIRC_BUFFER_INLINE_H
#include "circular_buffer_inline.h"
#undef CIRC_BUFFER_INLINE_H

#endif
