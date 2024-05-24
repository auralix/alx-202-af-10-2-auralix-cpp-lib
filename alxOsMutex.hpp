/**
  ******************************************************************************
  * @file		alxOsMutex.hpp
  * @brief		Auralix C++ Library - ALX OS Mutex Module
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
#ifndef ALX_OS_MUTEX_HPP
#define ALX_OS_MUTEX_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxOsMutex.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_C_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxOsMutex
	{
		//******************************************************************************
		// Class - IAlxOsMutex
		//******************************************************************************
		class IAlxOsMutex
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IAlxOsMutex() {}
				virtual ~IAlxOsMutex() {}
				virtual void Lock(void) = 0;
				virtual void Unlock(void) = 0;
				virtual bool IsUnlocked(void) = 0;
		};


		//******************************************************************************
		// Class - AlxOsMutex
		//******************************************************************************
		class AlxOsMutex : public IAlxOsMutex
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				AlxOsMutex()
				{
					AlxOsMutex_Ctor(&me);
				}
				virtual ~AlxOsMutex() {}
				void Lock(void) override
				{
					AlxOsMutex_Lock(&me);
				}
				void Unlock(void) override
				{
					AlxOsMutex_Unlock(&me);
				}
				bool IsUnlocked(void) override
				{
					return AlxOsMutex_IsUnlocked(&me);
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxOsMutex me = {};
		};
	}
}


#endif	// #if defined(ALX_C_LIB)

#endif	// #ifndef ALX_OS_MUTEX_HPP
