/*
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Hugo Arregui, FuDePAN 2011
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

    This is a test file.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mili/mili.h"

using namespace mili;

TEST(RandomGenTest, rnd)
{
    const float max = 11.0f;
    const float min = 10.0f;

    Randomizer<float> rnd(min, max);

    for (unsigned int i = 0; i < 100; ++i)
    {
        const float r = rnd.get();
        ASSERT_LE(r, max);
        ASSERT_GE(r, min);
    }
}

TEST(RandomGenTest, rndSameSeed)
{
    const unsigned int max = 20u;
    const unsigned int min = 10u;
    const unsigned int seed = 5u;

    Randomizer<unsigned int> randOne(min, max, seed);
    Randomizer<unsigned int> randTwo(min, max, seed);

    for(unsigned int i(0u); i < 100u; ++i)
    {
        ASSERT_EQ(randOne.get(), randTwo.get());
    }
}

TEST(RandomGenTest, getMethod)
{
    const unsigned int max = 100u;
    const unsigned int min = 1u;
    const unsigned int seed = 20u;

    Randomizer<unsigned int> rnd(min, max, seed);

    const unsigned int value1 = rnd.get();
    const unsigned int value2 = rnd.get();

    ASSERT_NE(value1, value2);
}
