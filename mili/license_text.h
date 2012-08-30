/*
    license_text: A library that implements functions to show software licenses.
    Copyright (C) 2012 Leandro Ramos , FuDePAN

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
*/

#ifndef LICENSE_TEXT_H
#define LICENSE_TEXT_H
#include <string>
NAMESPACE_BEGIN

inline std::string getGPL3LicenseText(const std::string& project_name, const std::string& version, const std::string& copyright_names, 
                          const std::string& years_from_to)
{
    return project_name + " " + version + "\n"
           + "Copyright (C) " + years_from_to + " " + copyright_names + "\n"
           + "This program comes with ABSOLUTELY NO WARRANTY; for details see http://www.gnu.org/licenses/gpl-3.0.html\n"
           +  project_name + " is free software, and you are welcome to redistribute it under certain conditions; for more information visit http://www.gnu.org/licenses/gpl-3.0.html\n\n";
}

NAMESPACE_END

#endif

