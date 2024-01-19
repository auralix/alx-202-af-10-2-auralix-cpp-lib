/**
  ******************************************************************************
  * @file		alxWdt.hpp
  * @brief		Auralix C++ Library - ALX Watchdog Timer Module
  * @copyright	Copyright (C) 2020-2022 Auralix d.o.o. All rights reserved.
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
#ifndef ALX_WDT_HPP
#define ALX_WDT_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxWdt.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxWdt
	{
		//******************************************************************************
		// Class - IWdt
		//******************************************************************************
		class IWdt
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IWdt() {}
				virtual ~IWdt() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status Refresh(void) = 0;
		};


		//******************************************************************************
		// Class - AWdt
		//******************************************************************************
		class AWdt : public IWdt
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				AWdt() {}
				virtual ~AWdt() {}
				Alx_Status Init(void) override
				{
					return AlxWdt_Init(&me);
				}
				Alx_Status Refresh(void) override
				{
					return AlxWdt_Refresh(&me);
				}

			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxWdt me = {};
		};


		//******************************************************************************
		// Class - Wdt
		//******************************************************************************
		#if defined(ALX_STM32F4) || defined(ALX_STM32F7) || defined(ALX_STM32L4) || defined(ALX_STM32U5)
		class Wdt : public AWdt
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Wdt
				(
					AlxWdt_Config config
				)
				{
					AlxWdt_Ctor
					(
						&me,
						config
					);
				}
				virtual ~Wdt() {}
		};
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_WDT_HPP
