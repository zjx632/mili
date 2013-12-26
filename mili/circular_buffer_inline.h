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

NAMESPACE_BEGIN

#ifndef CIRC_BUFFER_INLINE_H
#error UInternal header file, DO NOT include this.
#endif

#include <cassert>

template<typename T, UInt Size>
inline bool CircBuffer<T, Size>::isFull() const
{
    return (_read == _write);
}

template<typename T, UInt Size>
inline void CircBuffer<T, Size>::flush()
{
    _read = Size;
}

template<typename T, UInt Size>
inline void CircBuffer<T, Size>::parkReadIndex()
{
    if (isFull())
    {
        flush();
    }
}

template<typename T, UInt Size>
inline  bool CircBuffer<T, Size>::isEmpty() const
{
    return (_read == Size);
}

template<typename T, UInt Size>
inline void CircBuffer<T, Size>::unparkReadIndex()
{
    if (isEmpty())
    {
        _read = _write;
    }
}

template<typename T, UInt Size>
inline CircBuffer<T, Size>::CircBuffer()
    : _write(0), _read(Size)
{}

template<typename T, UInt Size>
inline void CircBuffer<T, Size>::queue(const T item)
{
    assert(!isFull());
    _buf[_write] = item;
    unparkReadIndex();
    ++_write;
    _write %= Size;
}

template<typename T, UInt Size>
inline UInt CircBuffer<T, Size>::available() const
{
    UInt result;
    if (isEmpty())
    {
        result = Size;
    }
    else    // if isFull() we should return 0, but the formula below delivers exactly that.
    {
        result = (Size - _write + _read) % Size;
    }
    return result;
}

template<typename T, UInt Size>
inline T CircBuffer<T, Size>::dequeue()
{
    assert(!isEmpty());
    const T result = _buf[_read];
    ++_read;
    _read %= Size;
    parkReadIndex();
    return result;
}

template<typename T, UInt Size>
template<UInt SrcSize>
inline UInt CircBuffer<T, Size>::moveFrom(CircBuffer<T, SrcSize>& src)
{
    UInt result = 0;

    while (!src.isEmpty() && !isFull())
    {
        queue(src.dequeue());
        ++result;
    }
    return result;
}

template<typename T, UInt Size>
inline UInt CircBuffer<T, Size>::used() const
{
    return Size - available();
}

template<typename T, UInt Size>
inline UInt CircBuffer<T, Size>::size() const
{
    return Size;
}

template<typename T, UInt Size>
inline void CircBuffer<T, Size>::discard(UInt amount)
{
    assert(amount <= used());
    _read = (_read + amount) % Size;
    parkReadIndex();
}

NAMESPACE_END