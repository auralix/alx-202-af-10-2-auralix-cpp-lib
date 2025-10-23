/**
  ******************************************************************************
  * @file		alxAdxl35x.hpp
  * @brief		Auralix C++ Library - ALX Accelerometer ADXL355/357 Module
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
#ifndef ALX_ADXL35X_HPP
#define ALX_ADXL35X_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxAccelerometer.hpp"
#include "alxAdxl35x.h"
#include "alxIoPin.hpp"
#include "alxSpi.hpp"
#include "alxFifo.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxAdxl35x
	{
		//******************************************************************************
		// Class - Adxl35x
		//******************************************************************************
		class Adxl35x : public AlxAccelerometer::IAccelerometer
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Adxl35x
				(
					Alx::AlxSpi::Spi* spi,
					uint8_t spiNumOfTries,
					uint16_t spiTimeout_ms
				)
				{
					AlxAdxl35x_Ctor
					(
						&me,
						spi->GetCStructPtr(),
						spiNumOfTries,
						spiTimeout_ms
					);
				}
				virtual ~Adxl35x() {}
				Alx_Status Init
				(
					AlxAccDevice device,
					AlxAccRange range,
					float sampleRate,
					AlxAccSyncMode syncMode
				) override
				{
					return AlxAdxl35x_Init(&me, device, range, sampleRate, syncMode);
				}
				Alx_Status DeInit(void) override
				{
					return AlxAdxl35x_DeInit(&me);
				}
				Alx_Status Enable(void) override
				{
					return AlxAdxl35x_Enable(&me);
				}
				Alx_Status Disable(void) override
				{
					return AlxAdxl35x_Disable(&me);
				}
				Alx_Status GetData(AccDataPoint* data, uint8_t len) override
				{
					return AlxAdxl35x_GetData(&me, data, len);
				}
				uint8_t GetFifoLen(void) override
				{
					return AlxAdxl35x_GetFifoLen(&me);
				}
				void* GetCStructPtr(void) override
				{
					return &me;
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxAdxl35x me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_ADXL35X_HPP
