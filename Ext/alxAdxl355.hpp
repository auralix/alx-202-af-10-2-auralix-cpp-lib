/**
  ******************************************************************************
  * @file		alxAdxl355.hpp
  * @brief		Auralix C++ Library - ALX Accelerometer ADXL355 Module
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
#ifndef ALX_ADXL355_HPP
#define ALX_ADXL355_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxAdxl355.h"
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
	namespace AlxAdxl355
	{
		//******************************************************************************
		// Class - IAdxl355
		//******************************************************************************
		class IAdxl355
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IAdxl355() {}
				virtual ~IAdxl355() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual Alx_Status Enable(void) = 0;
				virtual Alx_Status Disable(void) = 0;
				virtual Alx_Status GetXyz_g(AlxAdxl355_Xyz_g* xyz_g, uint32_t len) = 0;
				virtual Alx_Status GetXyz_g(AlxAdxl355_Xyz_g* xyz_g) = 0;
				virtual float GetTemp_degC(void) = 0;
				virtual Alx_Status Foreground_Handle(void) = 0;
		};


		//******************************************************************************
		// Class - Adxl355
		//******************************************************************************
		template <uint32_t fifoBuffLen>
		class Adxl355 : public IAdxl355
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Adxl355
				(
					Alx::AlxSpi::Spi* spi,
					uint8_t spiNumOfTries,
					uint16_t spiTimeout_ms
				)
				{
					AlxAdxl355_Ctor
					(
						&me,
						spi->GetCStructPtr(),
						spiNumOfTries,
						spiTimeout_ms,
						this->fifo.GetBuffPtr(),
						fifoBuffLen * sizeof(AlxAdxl355_Xyz_g)
					);
				}
				virtual ~Adxl355() {}
				Alx_Status Init(void) override
				{
					return AlxAdxl355_Init(&me);
				}
				Alx_Status DeInit(void) override
				{
					return AlxAdxl355_DeInit(&me);
				}
				Alx_Status Enable(void) override
				{
					return AlxAdxl355_Enable(&me);
				}
				Alx_Status Disable(void) override
				{
					return AlxAdxl355_Disable(&me);
				}
				Alx_Status GetXyz_g(AlxAdxl355_Xyz_g* xyz_g, uint32_t len) override
				{
					#if defined(ALX_MBED)
					ALX_ADXL355_ASSERT(me.isInit == true);
					ALX_ADXL355_ASSERT(me.wasCtorCalled == true);
					ALX_ADXL355_ASSERT((0 < len) && (len <= me.fifoBuffLen));

					// #1 Prepare variables
					Alx_Status status = Alx_Err;

					// #2 Read acceleration from FIFO
					for (uint32_t i = 0; i < len; i++)
					{
						uint32_t xyzLen = sizeof(AlxAdxl355_Xyz_g);
						uint8_t* ptr = (uint8_t*)&xyz_g[i * xyzLen];

						mbed::CriticalSectionLock::enable();
						status = AlxFifo_Read(&me.fifo, ptr, xyzLen);
						mbed::CriticalSectionLock::disable();

						if(status == AlxFifo_ErrEmpty)
						{
							break;	// We break if there are no more messages in ALX RX FIFO
						}
						else if(status != Alx_Ok)
						{
							ALX_ADXL355_ASSERT(false);	// We should never get here
							break;
						}
					}

					// #3 Return status
					return status;
					#else
					return AlxAdxl355_GetXyzMulti_g(&me, xyz_g, len);
					#endif
				}
				Alx_Status GetXyz_g(AlxAdxl355_Xyz_g* xyz_g) override
				{
					#if defined(ALX_MBED)
					return GetXyz_g(xyz_g, 1);
					#else
					return AlxAdxl355_GetXyz_g(&me, xyz_g);
					#endif
				}
				float GetTemp_degC(void) override
				{
					return AlxAdxl355_GetTemp_degC(&me);
				}
				Alx_Status Foreground_Handle(void) override
				{
					return AlxAdxl355_Foreground_Handle(&me);
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxAdxl355 me = {};
				AlxFifo::Fifo<fifoBuffLen * sizeof(AlxAdxl355_Xyz_g)> fifo = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_ADXL355_HPP
