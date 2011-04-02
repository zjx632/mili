/*
example_variants_set: An example that uses MiLi's Variants Set.
    Copyright (C) 2010  Ezequiel S. Velez

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

using namespace std;

int main()
{
    VariantsSet variantSet;
    int ie = 0;
    string is;
    float f;
    ElementName str = "greeting";
    variantSet.insert("number", 3);
    variantSet.insert(str, "hello");
    variantSet.insert("temperature", 0.1f);

    try
    {
        variantSet.get_element("number", ie);
        cout << "number: " << ie << endl;

        variantSet.get_element(str, is);
        cout << "greeting: " << is << endl;
        cout << "greeting: " << variantSet.get_element<string>(str) << endl;
        variantSet.get_element("float", f);
    }
    catch (const BadElementName&)
    {
        cerr << "Bad Element Name!" << endl;
    }
    catch (const BadElementType&)
    {
        cerr << "BadElementType!" << endl;
    }

    variantSet.erase("temperature");
    cout << "size: " << variantSet.size() << endl;
    return 0;
}
