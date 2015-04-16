# Introduction #

This module provides a circular buffer of fixed length. The type of element to be held and the amount of elements are received as template parameters.

Additionally, you can provide three extra template parameters, used to determine the policy to follow when an attempt is made to dequeue from an empty buffer, enqueue to a full buffer, or discard more elements than those held by the buffer. By default, all these policies are to use assertions; you can make them use exceptions, do nothing, or create your own policies to provide whatever behavior you need.

It provides the following services:
  * isFull(): tells if the buffer is full.
  * isEmpty(): tells if the buffer is empty.
  * flush(): empties the buffer.
  * queue(item): adds item to the buffer. Checks that the buffer is not full.
  * available(): tells how much space is available.
  * used(): tells how much space has been used.
  * size(): tells how large the buffer is.
  * dequeue(): removes the oldest element from the buffer and returns it. Checks that the buffer is not empty.
  * discard(amount): drops the oldest amount elements from the buffer, checks if there are enough elements (i.e., amount <= used).
  * moveFrom(src): moves as many elements as possible from src to this buffer. Stops when either src is empty, or this buffer is full. The amount of elements of the buffer does not need to be the same, but the types contained must be the same.

An example of its usage:
```
    CircBuffer<int, 4u> src;
    CircBuffer<int, 2u> dst;
    src.queue(0);
    src.queue(1);
    src.queue(2);
    dst.moveFrom(src)
```
will move 0 and 1 to dst, leaving 2 in src since dst can only hold 2 elements.