/*
properties: A minimal library that implements object properties.
    Copyright (C) 2009  Daniel Gutson, FuDePAN

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

    This is an example file.
*/


#include <iostream>
#include "mili/mili.h"

using namespace mili;
using namespace std;

class TemperatureSensor
{
private:
    float get_celcius() const
    {
        return _celcius;
    };

    void set_celcius(float val)
    {
        _celcius = val;
    }

    float get_farenheit() const
    {
        return _celcius * (9.0f / 5.0f) + 32.0f;
    }

    void set_farenheit(float f)
    {
        _celcius = (f - 32.0f) * (5.0f / 9.0f);
    }

    float get_kelvin() const
    {
        return _celcius + 273.15f;
    }

    void set_kelvin(float k)
    {
        _celcius = k - 273.15f;
    }

public:
    PROPERTIES
    {
        PropertyRW<TemperatureSensor, float, &TemperatureSensor::get_celcius,   &TemperatureSensor::set_celcius>   celcius;
        PropertyRW<TemperatureSensor, float, &TemperatureSensor::get_farenheit, &TemperatureSensor::set_farenheit> farenheit;
        PropertyRW<TemperatureSensor, float, &TemperatureSensor::get_kelvin,    &TemperatureSensor::set_kelvin>    kelvin;
    };
private:
    float _celcius;
};

int main()
{
    TemperatureSensor s;
    s.kelvin = 0;
    float f = s.celcius;

    std::cout << f << std::endl;
    std::cout << sizeof(s) << std::endl;

    return 0;
}
