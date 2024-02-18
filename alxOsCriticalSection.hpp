/**
  ******************************************************************************
  * @file		alxOsCriticalSection.hpp
  * @brief		Auralix C++ Library - ALX OS Critical Section Module
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
#ifndef ALX_OS_CRITICAL_SECTION_HPP
#define ALX_OS_CRITICAL_SECTION_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxOsCriticalSection
	{
		//******************************************************************************
		// Functions
		//******************************************************************************
		static inline void Enter(void)
		{
			#if defined(ALX_MBED)
			mbed::CriticalSectionLock::enable();
			#endif
		}
		static inline void Exit(void)
		{
			#if defined(ALX_MBED)
			mbed::CriticalSectionLock::disable();
			#endif
		}
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_OS_CRITICAL_SECTION_HPP
