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

using namespace mili;

TEST(PromotionDisable, StrictRules)
{
    ASSERT_TRUE(bool(StrictRules<float, float>::value));
    ASSERT_FALSE(bool(StrictRules<int, float>::value));
}

TEST(PromotionDisable, FloatingPoints)
{
    ASSERT_TRUE(bool(FloatingPoints<float, float>::value));
    ASSERT_TRUE(bool(FloatingPoints<float, double>::value));
    ASSERT_FALSE(bool(FloatingPoints<int, float>::value));
}

TEST(PromotionDisable, RulesCondition)
{
    ASSERT_TRUE(bool(RulesCondition<true>::value));
    ASSERT_FALSE(bool(RulesCondition<false>::value));
}

TEST(PromotionDisable, NotNarrowing)
{
    ASSERT_FALSE(bool(NotNarrowing<int, char>::value));
    ASSERT_TRUE(bool(NotNarrowing<char, int>::value));
    ASSERT_FALSE(bool(NotNarrowing<float, int>::value));
    ASSERT_TRUE(bool(NotNarrowing<float, float>::value));
}

float f(Restrict<float> rf)
{
    return rf + 1.0f;
}

TEST(PromotionDisable, test)
{
    f(1.0f);
    //f(1); cannot test this
}
