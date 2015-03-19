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
#include <map>
#include "mili/mili.h"

using namespace mili;

TEST(StringUtilsTest, lstring_test)
{
    lstring ls("helLO");
    ls[1] = 'E';

    ASSERT_TRUE(ls[2] == 'L');
    ASSERT_TRUE(ls == "HELLO");

    std::map<lstring, int> m;
    m["Hello"] = 3;
    m["Goodbye"] = 5;
    ASSERT_EQ(3, m["hELLo"]);

    ASSERT_TRUE(begins_with(ls, "HE"));
    ASSERT_TRUE(ends_with(ls, "Ello"));
}

TEST(StringUtilsTest, toupper)
{
    ASSERT_EQ("HELLO WORLD!", toupper("Hello World!"));
}

/** to_string short int */
TEST(StringUtilsTest, to_string_sInt)
{
    ASSERT_EQ("123654", to_string(123654));
}

TEST(StringUtilsTest, to_string_sIntNegative)
{
    ASSERT_EQ("-123654", to_string(-123654));
}

/** to_string unsigned short int */
TEST(StringUtilsTest, to_string_uSInt)
{
    ASSERT_EQ("65535", to_string(65535));
}

/** to_string int */
TEST(StringUtilsTest, to_string_Int)
{
    ASSERT_EQ("2147563", to_string(2147563));
}

TEST(StringUtilsTest, to_string_IntNegative)
{
    ASSERT_EQ("-2147563", to_string(-2147563));
}

/** to_string unsigned int */
TEST(StringUtilsTest, to_string_uInt)
{
    ASSERT_EQ("2147561", to_string(2147561));
}

/** to_string long int */
TEST(StringUtilsTest, to_string_lInt)
{
    ASSERT_EQ("2147999", to_string(2147999));
}

TEST(StringUtilsTest, to_string_lIntNegative)
{
    ASSERT_EQ("-2147999", to_string(-2147999));
}

/** to_string unsigned long int */
TEST(StringUtilsTest, to_string_ulInt)
{
    ASSERT_EQ("2147483647", to_string(2147483647));
}

/** to_string long long int */
TEST(StringUtilsTest, to_string_llInt)
{
    ASSERT_EQ("9223372036854775807", to_string(9223372036854775807));
}

TEST(StringUtilsTest, to_string_llIntNegative)
{
    ASSERT_EQ("-9223372036854775807", to_string(-9223372036854775807));
}

/** to_string unsigned long long int */
TEST(StringUtilsTest, to_string_ullInt)
{
    ASSERT_EQ("9223372036854775805", to_string(9223372036854775805));
}

/** from_string to unsigned short int */
TEST(StringUtilsTest, from_string_usi_invalide)
{
    unsigned short int usInt;
    ASSERT_FALSE(from_string("-15", usInt));
    ASSERT_FALSE(from_string("", usInt));
    ASSERT_FALSE(from_string("aaaaaaaaaa", usInt));
    ASSERT_THROW(from_string<unsigned short int>("asdasd"), SscanfFailure);
    ASSERT_THROW(from_string<unsigned short int>(""), SscanfFailure);
}

TEST(StringUtilsTest, from_string_usi_valide)
{
    unsigned short int usInt;
    ASSERT_TRUE(from_string("15", usInt));
    ASSERT_NO_THROW(from_string<unsigned short int>("15"));
}

/** from_string to short int */
TEST(StringUtilsTest, from_string_si_empty)
{
    short int sInt;
    ASSERT_FALSE(from_string("", sInt));
    ASSERT_FALSE(from_string("aaaaaaaaaa", sInt));
    ASSERT_THROW(from_string<short int>("asdasd"), SscanfFailure);
    ASSERT_THROW(from_string<short int>(""), SscanfFailure);
}

TEST(StringUtilsTest, from_string_si_valide)
{
    short int sInt;
    ASSERT_TRUE(from_string("15", sInt));
    ASSERT_NO_THROW(from_string<short int>("32365"));
}

/** from_string to unsigned int */
TEST(StringUtilsTest, from_string_ui_invalide)
{
    unsigned int uInt;
    ASSERT_FALSE(from_string("-10", uInt));
    ASSERT_FALSE(from_string("", uInt));
    ASSERT_FALSE(from_string("asdfasfas", uInt));
    ASSERT_THROW(from_string<unsigned int>("bgcdbcdvb"), SscanfFailure);
    ASSERT_THROW(from_string<unsigned int>(""), SscanfFailure);
}

TEST(StringUtilsTest, from_string_ui_valide)
{
    unsigned int uInt;
    ASSERT_TRUE(from_string("20", uInt));
    ASSERT_NO_THROW(from_string<unsigned int>("1236542"));
}

/** from_string to int */
TEST(StringUtilsTest, from_string_i_invalide)
{
    int i;
    ASSERT_FALSE(from_string("", i));
    ASSERT_FALSE(from_string("qweqwewq", i));
    ASSERT_THROW(from_string<int>("ghkhjl"), SscanfFailure);
    ASSERT_THROW(from_string<int>(""), SscanfFailure);
}

TEST(StringUtilsTest, from_string_i_valide)
{
    int i;
    ASSERT_TRUE(from_string("32", i));
    ASSERT_NO_THROW(from_string<int>("21365465"));
}

/** from_string to unsigned long int */
TEST(StringUtilsTest, from_string_uli_empty)
{
    unsigned long int ulInt;
    ASSERT_FALSE(from_string("-3", ulInt));
    ASSERT_FALSE(from_string("qweqweqw", ulInt));
    ASSERT_FALSE(from_string("", ulInt));
    ASSERT_THROW(from_string<unsigned long int>("ghkhjk"), SscanfFailure);
    ASSERT_THROW(from_string<unsigned long int>(""), SscanfFailure);
}

TEST(StringUtilsTest, from_string_uli_valide)
{
    unsigned long int ulInt;
    ASSERT_TRUE(from_string("98", ulInt));
    ASSERT_NO_THROW(from_string<unsigned long int>("22365421"));
}

/** from_string to long int */
TEST(StringUtilsTest, from_string_li_garbage)
{
    long int lInt;
    ASSERT_FALSE(from_string("", lInt));
    ASSERT_FALSE(from_string("klhklh", lInt));
    ASSERT_THROW(from_string<long int>("asdasd"), SscanfFailure);
    ASSERT_THROW(from_string<long int>(""), SscanfFailure);
}

TEST(StringUtilsTest, from_string_li_valide)
{
    long int lInt;
    ASSERT_TRUE(from_string("56", lInt));
    ASSERT_NO_THROW(from_string<long int>("12354863"));
}

TEST(StringUtilsTest, from_string_double)
{
    double d;
    ASSERT_TRUE(from_string("132048.988", d));
    from_string("132048.988", d);
    ASSERT_DOUBLE_EQ(132048.988, d);
    double d1;
    from_string("-62.235643", d1);
    ASSERT_DOUBLE_EQ(-62.235643, d1);

}

TEST(StringUtilsTest, from_string_long_double)
{
    long double d;
    ASSERT_TRUE(from_string("132048.988654", d));
    from_string("132048.988654", d);
    ASSERT_DOUBLE_EQ(132048.988654, d);
    long double d1;
    from_string("-62.235643", d1);
    ASSERT_DOUBLE_EQ(-62.235643, d1);
}

TEST(StringUtilsTest, from_string_float_valide)
{
    float f;
    ASSERT_TRUE(from_string("6410.671356", f));
    from_string("6410.671356", f);
    ASSERT_FLOAT_EQ(6410.671356, f);
}

TEST(StringUtilsTest, ensure_found)
{
    std::string str = "Why?";
    ASSERT_TRUE(ensure_found(str.find_first_of("h", 0)));
    ASSERT_THROW(ensure_found(str.find_first_of(" ", 0)), StringNotFound);
    ASSERT_EQ(str.size(), ensure_found(str.find_first_of(" ", 0), str.size()));
}

TEST(StringUtilsTest, substr)
{
    ASSERT_EQ("llo Wo", substr("Hello World", Pos_(2), Count_(6)));
    ASSERT_EQ("llo W", substr("Hello World", Pos_(2), Pos_(6)));
}

