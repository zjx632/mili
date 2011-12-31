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

class Mock 
{
public:
    MOCK_METHOD1(mocked_set_celcius, void(float));
    MOCK_CONST_METHOD0(mocked_get_celcius, void());
};

class TemperatureSensor
{
private:
    float get_celcius() const
    {
        mock.mocked_get_celcius();
        return _celcius;
    };

    void set_celcius(float val)
    {
        _celcius = val;
        mock.mocked_set_celcius(val);
    }

public:
    PROPERTIES
    {
        PropertyRW<TemperatureSensor, float, &TemperatureSensor::get_celcius, &TemperatureSensor::set_celcius>   celcius;
    };
    Mock mock;
private:
    float _celcius;
};

TEST(Properties, test)
{
    TemperatureSensor s;
    EXPECT_CALL(s.mock, mocked_set_celcius(0));
    s.celcius = 0;
    EXPECT_CALL(s.mock, mocked_get_celcius());
    float f = s.celcius;
    ASSERT_EQ(f, 0);
}
