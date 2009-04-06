/*
MiLi: A set of minimal libraries composed only by 1 header file each.
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

    This is the main include file.
*/

#ifndef MILI_H
#define MILI_H

#ifdef MILI_NAMESPACE
namespace mili
{
#endif

#ifndef NO_BITWISE_ENUMS
#include "bitwise_enums.h"
#endif

#ifndef NO_PREPOS_CALLER
#include "prepos_caller.h"
#endif

#ifndef NO_DELETE_CONTAINER
#include "delete_container.h"
#endif

#ifndef NO_PROMOTION_DISABLE
#include "promotion_disable.h"
#endif

#ifndef NO_FACTORY
#include "factory.h"
#endif

#ifdef MILI_NAMESPACE
}
#endif

#endif
