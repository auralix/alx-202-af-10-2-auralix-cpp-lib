/**
  ******************************************************************************
  * @file		alxA352.hpp
  * @brief		Auralix C++ Library - ALX Accelerometer Epson A352 Module
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
#ifndef ALX_A352_HPP
#define ALX_A352_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxA352.h"
#include "alxIoPin.hpp"
#include "alxSpi.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxA352
	{
		//******************************************************************************
		// Class - IA352
		//******************************************************************************
		class IA352
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IA352() {}
				virtual ~IA352() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual Alx_Status Configure(void) = 0;
				virtual Alx_Status GetProdId(void) = 0;
				virtual Alx_Status GetAccData(void) = 0;
				virtual Alx_Status GetTempData(void) = 0;
				virtual ::AlxA352* GetCStructPtr(void) = 0;
		};


		//******************************************************************************
		// Class - A352
		//******************************************************************************
		class A352 : public IA352
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				A352
				(
					Alx::AlxSpi::Spi* spi,
					uint8_t spiNumOfTries,
					uint16_t spiTimeout_ms
				)
				{
					AlxA352_Ctor
					(
						&me,
						spi->GetCStructPtr(),
						spiNumOfTries,
						spiTimeout_ms
					);
				}
				virtual ~A352() {}
				Alx_Status Init(void) override
				{
					return AlxA352_Init(&me);
				}
				Alx_Status DeInit(void) override
				{
					return AlxA352_DeInit(&me);
				}
				Alx_Status Configure(void) override
				{
					return AlxA352_Configure(&me);
				}
				Alx_Status GetProdId(void) override
				{
					return AlxA352_GetProdId(&me);
				}
				Alx_Status GetAccData(void) override
				{
					return AlxA352_GetAccData(&me);
				}
				Alx_Status GetTempData(void) override
				{
					return AlxA352_GetTempData(&me);
				}
				::AlxA352* GetCStructPtr(void) override
				{
					return &me;
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxA352 me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_ADXL355_HPP
