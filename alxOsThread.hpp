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
					TaskFunction_t pxTaskCode,
					const char* const pcName,
					uint32_t usStackDepth_byte,
					void* const pvParameters,
					UBaseType_t uxPriority
				)
				{
					AlxOsThread_Ctor
					(
						&me,
						pxTaskCode,
						pcName,
						usStackDepth_byte,
						pvParameters,
						uxPriority
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


#endif	// #if defined(ALX_C_LIB) && defined(ALX_FREE_RTOS)

#endif	// #ifndef ALX_OS_THREAD_HPP
