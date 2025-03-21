﻿/**
  ******************************************************************************
  * @file		alxGlobal.hpp
  * @brief		Auralix C++ Library - ALX Global Module
  * @copyright	Copyright (C) Auralix d.o.o. All rights reserved.
  *
  * @section License
  *
  * SPDX-License-Identifier: GPL-3.0-or-later
  *
  * This file is part of Auralix C++ Library.
  *
  * Auralix C++ Library is free software: you can redistribute it and/or
  * modify it under the terms of the GNU General Public License
  * as published by the Free Software Foundation, either version 3
  * of the License, or (at your option) any later version.
  *
  * Auralix C++ Library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with Auralix C++ Library. If not, see <https://www.gnu.org/licenses/>.
  ******************************************************************************
  **/

//******************************************************************************
// Include Guard
//******************************************************************************
#ifndef ALX_GLOBAL_HPP
#define ALX_GLOBAL_HPP


//******************************************************************************
// Includes - ALX Config
//******************************************************************************
#include "alxConfig.h"


//******************************************************************************
// Includes - Google Test
//******************************************************************************
#if defined(ALX_GTEST)
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#endif


//******************************************************************************
// Includes - Auralix C Library Globals
//******************************************************************************
#include "alxGlobal.h"
#include "alxTrace.h"
#include "alxAssert.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxGlobal
	{
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_GLOBAL_HPP
