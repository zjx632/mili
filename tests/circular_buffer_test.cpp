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

// These macros should not be used outside of testing code
#define private public
#define protected public

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mili/mili.h"

using namespace mili;

TEST(CircularBuffer, AvailableAndUsed)
{
    CircBuffer<int, 4> cBuf;

    EXPECT_EQ(4, cBuf.size());
    EXPECT_EQ(4, cBuf.available());
    EXPECT_EQ(0, cBuf.used());
    cBuf.queue(0);

    EXPECT_EQ(3, cBuf.available());
    EXPECT_EQ(1, cBuf.used());

    cBuf.queue(1);
    cBuf.queue(2);
    cBuf.queue(3);
    EXPECT_EQ(0, cBuf.available());

    EXPECT_EQ(0, cBuf.dequeue());

    EXPECT_EQ(1, cBuf.available());

    EXPECT_EQ(1, cBuf.dequeue());

    EXPECT_EQ(2, cBuf.available());
    cBuf.queue(4);
    cBuf.queue(5);
    EXPECT_EQ(0, cBuf.available());
    EXPECT_EQ(4, cBuf.used());

    EXPECT_EQ(2, cBuf.dequeue());
    EXPECT_EQ(3, cBuf.dequeue());
    EXPECT_EQ(4, cBuf.dequeue());

    EXPECT_EQ(3, cBuf.available());
    EXPECT_EQ(4, cBuf.size());
}

TEST(CircularBuffer, EmptyingQueue)
{
    CircBuffer<int, 4> cBuf;

    cBuf.queue(0);
    cBuf.queue(1);
    cBuf.queue(2);
    cBuf.queue(3);

    EXPECT_EQ(0, cBuf.dequeue());
    EXPECT_EQ(1, cBuf.dequeue());
    EXPECT_EQ(2, cBuf.dequeue());
    EXPECT_EQ(3, cBuf.dequeue());

    EXPECT_EQ(4, cBuf.available());

    EXPECT_EQ(4, cBuf._read);
}

TEST(CircularBuffer, Flushing)
{
    CircBuffer<int, 4> cBuf;

    cBuf.queue(0);
    cBuf.queue(1);
    EXPECT_EQ(2, cBuf.available());

    cBuf.flush();
    EXPECT_EQ(4, cBuf.available());
    EXPECT_EQ(4, cBuf._read);

    cBuf.queue(3);
    cBuf.queue(4);

    EXPECT_EQ(3, cBuf.dequeue());
    EXPECT_EQ(4, cBuf.dequeue());
}

TEST(CircularBuffer, IsEmptyAndIsFull)
{
    CircBuffer<int, 4> cBuf;

    EXPECT_TRUE(cBuf.isEmpty());

    cBuf.queue(0);
    EXPECT_FALSE(cBuf.isEmpty());
    cBuf.queue(1);
    cBuf.queue(2);
    EXPECT_FALSE(cBuf.isFull());
    cBuf.queue(3);

    EXPECT_TRUE(cBuf.isFull());
}

TEST(CircularBuffer, EmptyDequeueDeathTest)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    CircBuffer<int, 4> cBuf;

    EXPECT_DEATH(cBuf.dequeue(), "");
}

TEST(CircularBuffer, FullQueueDeathTest)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    CircBuffer<int, 4> cBuf;

    cBuf.queue(0);
    cBuf.queue(1);
    cBuf.queue(2);
    cBuf.queue(3);
    EXPECT_EQ(0, cBuf.available());

    EXPECT_DEATH(cBuf.queue(4), "");
}

TEST(CircularBuffer, IteratingQueueDequeue)
{
    CircBuffer<int, 4> cBuf;

    cBuf.queue(0);
    cBuf.queue(1);

    for (auto i = 2u; i < 200; ++i)
    {
        cBuf.queue(i);
        EXPECT_EQ(i - 2, cBuf.dequeue());
    }
}

TEST(CircularBuffer, FillUpAndEmpty)
{
    CircBuffer<int, 4> cBuf;
    for (auto i = 1u; i < 500; ++i)
    {
        if ((i % 2) == 1)
        {
            for (auto j = 0u; j < 4 ; ++j)
            {
                cBuf.queue(j);
            }
        }
        else
        {
            for (auto j = 0u; j < 4 ; ++j)
            {
                EXPECT_EQ(j, cBuf.dequeue());
            }
        }
    }
}

TEST(CircularBuffer, MoveFromSameSizes)
{
    CircBuffer<int, 4> src;
    CircBuffer<int, 4> dst;

    src.queue(0);
    src.queue(1);
    src.queue(2);
    src.queue(3);

    EXPECT_EQ(0, src.available());
    EXPECT_EQ(4, dst.available());

    EXPECT_EQ(4, dst.moveFrom(src));

    EXPECT_EQ(0, dst.available());
    EXPECT_EQ(4, src.available());

    EXPECT_EQ(0, dst.dequeue());
    EXPECT_EQ(1, dst.dequeue());
    EXPECT_EQ(2, dst.dequeue());
    EXPECT_EQ(3, dst.dequeue());
}


TEST(CircularBuffer, MoveFromSrcGreaterThanDst)
{
    CircBuffer<int, 4> src;
    CircBuffer<int, 3> dst;

    src.queue(0);
    src.queue(1);
    src.queue(2);
    src.queue(3);

    EXPECT_EQ(0, src.available());
    EXPECT_EQ(3, dst.available());

    EXPECT_EQ(3, dst.moveFrom(src));

    EXPECT_EQ(0, dst.available());
    EXPECT_EQ(3, src.available());

    EXPECT_EQ(0, dst.dequeue());
    EXPECT_EQ(1, dst.dequeue());
    EXPECT_EQ(2, dst.dequeue());

}

TEST(CircularBuffer, MoveFromSrcLessThanDst)
{
    CircBuffer<int, 3> src;
    CircBuffer<int, 4> dst;

    src.queue(0);
    src.queue(1);
    src.queue(2);

    EXPECT_EQ(0, src.available());
    EXPECT_EQ(4, dst.available());

    EXPECT_EQ(3, dst.moveFrom(src));

    EXPECT_EQ(1, dst.available());
    EXPECT_EQ(3, src.available());

    EXPECT_EQ(0, dst.dequeue());
    EXPECT_EQ(1, dst.dequeue());
    EXPECT_EQ(2, dst.dequeue());

}

TEST(CircularBuffer, Discard)
{
    CircBuffer<int, 4> cBuf;

    cBuf.queue(0);
    cBuf.queue(1);
    cBuf.queue(2);
    cBuf.queue(3);
    EXPECT_EQ(0, cBuf.available());

    cBuf.discard(2);
    EXPECT_EQ(2, cBuf.available());
    EXPECT_EQ(2, cBuf.dequeue());
    cBuf.queue(4);
    cBuf.discard(2);
    EXPECT_EQ(4, cBuf.available());

    cBuf.queue(0);
    cBuf.queue(1);
    cBuf.queue(2);
    cBuf.queue(3);

    EXPECT_EQ(0, cBuf.available());
    cBuf.discard(4);
    EXPECT_EQ(4, cBuf.available());
}

TEST(CircularBuffer, DiscardDeathTest)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    CircBuffer<int, 4> cBuf;

    cBuf.queue(0);
    cBuf.queue(1);
    cBuf.queue(2);

    EXPECT_DEATH(cBuf.discard(4), "");
}

