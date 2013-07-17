/*
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Lucas Besso, FuDePAN 2013
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
#include <string>
#include "mili/mili.h"


struct Person
{
    std::string name;
    unsigned int age;
};

typedef Person Family[3];

Family mariaFamily;
Family mariaCpy;

TEST(CCallImprovedTest, copyPersons)
{
    mariaFamily[0].name = "Lucas";
    mariaFamily[0].age = 27;
    mariaFamily[1].name = "Pepe";
    mariaFamily[1].age = 22;
    mariaFamily[2].name = "Juan";
    mariaFamily[2].age = 23;

    mili::safecpy(mariaCpy, mariaFamily, sizeof(mariaFamily));

    EXPECT_EQ(mariaCpy[0].name, mariaFamily[0].name);
    EXPECT_EQ(mariaCpy[0].age, mariaFamily[0].age);

    EXPECT_EQ(mariaCpy[1].name, mariaFamily[1].name);
    EXPECT_EQ(mariaCpy[1].age, mariaFamily[1].age);

    EXPECT_EQ(mariaCpy[2].name, mariaFamily[2].name);
    EXPECT_EQ(mariaCpy[2].age, mariaFamily[2].age);
}


TEST(CCallImprovedTest, copyChars)
{
    typedef char MyTypeBuf[5];
    MyTypeBuf myTypeBuf;
    myTypeBuf[0] = 'h';
    myTypeBuf[1] = 'e';
    myTypeBuf[2] = 'l';
    myTypeBuf[3] = 'l';
    myTypeBuf[4] = 'o';

    char buf2[5];
    mili::safecpy(buf2, myTypeBuf, 6);

    EXPECT_STREQ(myTypeBuf, buf2);
}
