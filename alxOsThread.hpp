/**
  ******************************************************************************
  * @file		alxOsThread.hpp
  * @brief		Auralix C++ Library - ALX OS Thread Module
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
#ifndef ALX_OS_THREAD_HPP
#define ALX_OS_THREAD_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxOsThread.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxOsThread
	{
		//******************************************************************************
		// Class - IAlxOsThread
		//******************************************************************************
		class IAlxOsThread
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IAlxOsThread() {}
				virtual ~IAlxOsThread() {}
				virtual Alx_Status Start(void) = 0;
				virtual void Yield(void) = 0;
		};


		//******************************************************************************
		// Class - AlxOsThread
		//******************************************************************************
		class AlxOsThread : public IAlxOsThread
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				AlxOsThread
				(
					void (*func)(void*),
					const char* name,
					uint32_t stackLen_byte,
					void* param,
					uint32_t priority
				)
				{
					AlxOsThread_Ctor
					(
						&me,
						func,
						name,
						stackLen_byte,
						param,
						priority
					);
				}
				virtual ~AlxOsThread() {}
				Alx_Status Start(void) override
				{
					return AlxOsThread_Start(&me);
				}
				void Yield(void) override
				{
					AlxOsThread_Yield(&me);
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxOsThread me = {};
		};
	}
}


#endif	// #if defined(ALX_C_LIB)

#endif	// #ifndef ALX_OS_THREAD_HPP
