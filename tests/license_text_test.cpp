/*
    Copyright (C) 2012 Leandro Ramos, FuDePAN

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
using namespace std;

TEST(GPLv3Disclaimer, correctOutputTest)
{
    const string correctDisclaimer = "ViSi 1.0\n"
                                     "Copyright (C) 2012 Leandro Ramos, Pablo Oliva\n"
                                     "This program comes with ABSOLUTELY NO WARRANTY; for details see http://www.gnu.org/licenses/gpl-3.0.html\n"
                                     "ViSi is free software, and you are welcome to redistribute it under certain conditions; for more information visit http://www.gnu.org/licenses/gpl-3.0.html\n\n";
    const string returnDisclaimer = getGPL3LicenseText("ViSi", "1.0", "Leandro Ramos, Pablo Oliva", "2012");                                  
    ASSERT_EQ(correctDisclaimer, returnDisclaimer);
}
