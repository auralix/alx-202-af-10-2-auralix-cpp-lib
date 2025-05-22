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
#include "alxAccelerometer.hpp"
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
		// Class - A352
		//******************************************************************************
		class A352 : public AlxAccelerometer::IAccelerometer
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
				Alx_Status Init(float sampleRate) override
				{
					return AlxA352_Init(&me, sampleRate);
				}
				Alx_Status DeInit(void) override
				{
					return AlxA352_DeInit(&me);
				}
				Alx_Status Enable(void) override
				{
					return AlxA352_Enable(&me);
				}
				Alx_Status Disable(void) override
				{
					return AlxA352_Disable(&me);
				}
				Alx_Status GetData(AccDataPoint* data, uint8_t len) override
				{
					return AlxA352_GetData(&me, data, len);
				}
				uint8_t GetFifoLen(void) override
				{
					return AlxA352_GetFifoLen(&me);
				}
				void* GetCStructPtr(void) override
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
