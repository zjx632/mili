/*
    Copyright (C) 2012 Daniel Muñoz, FuDePAN

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
#include "mili/mili.h"

TEST(PlatformDetectionTest, OperatingSystem)
{
    ASSERT_EQ(MILI_OS_LINUX,	1);
    ASSERT_EQ(MILI_OS_WINDOWS,	2);
    ASSERT_EQ(MILI_OS_MAC,	3);
    ASSERT_EQ(MILI_OS_UNKNOWN,	4);

    ASSERT_TRUE( (MILI_OS == MILI_OS_LINUX)	\
               ^ (MILI_OS == MILI_OS_WINDOWS)	\
               ^ (MILI_OS == MILI_OS_MAC)	\
               ^ (MILI_OS == MILI_OS_UNKNOWN) );
}

TEST(PlatformDetectionTest, Compiler)
{
    ASSERT_EQ(MILI_COMPILER_VS,		1);
    ASSERT_EQ(MILI_COMPILER_GCC,	2);
    ASSERT_EQ(MILI_COMPILER_ICC,	3);
    ASSERT_EQ(MILI_COMPILER_UNKNOWN,	4);

    ASSERT_TRUE( (MILI_COMPILER == MILI_COMPILER_VS)	\
               ^ (MILI_COMPILER == MILI_COMPILER_GCC)	\
               ^ (MILI_COMPILER == MILI_COMPILER_ICC)	\
               ^ (MILI_COMPILER == MILI_COMPILER_UNKNOWN) );
}

