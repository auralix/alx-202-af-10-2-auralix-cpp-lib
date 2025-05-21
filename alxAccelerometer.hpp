/**
  ******************************************************************************
  * @file		alxAccelerometer.hpp
  * @brief		Auralix C++ Library - ALX Accelerometer Module
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
#ifndef ALX_ACCELEROMETER_HPP
#define ALX_ACCELEROMETER_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxAccelerometer.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxAccelerometer
	{	
		//******************************************************************************
		// Class - IAudioPlayer
		//******************************************************************************
		class IAccelerometer
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IAccelerometer() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual Alx_Status Enable(void) = 0;
				virtual Alx_Status Disable(void) = 0;
				virtual Alx_Status GetData(AccDataPoint* data, uint8_t len) = 0;
				virtual uint8_t GetFifoLen(void) = 0;
				virtual void* GetCStructPtr(void) = 0;
				virtual ~IAccelerometer() {}
		};
		
		class AccDummy: public IAccelerometer
		{
		public:
			AccDummy() {}
			virtual ~AccDummy() {}
			Alx_Status Init(void) override
			{
				return Alx_Err;
			}
			Alx_Status DeInit(void) override
			{
				return Alx_Err;
			}
			Alx_Status Enable(void) override
			{
				return Alx_Err;
			}
			Alx_Status Disable(void) override
			{
				return Alx_Err;
			}
			Alx_Status GetData(AccDataPoint* data, uint8_t len) override
			{
				return Alx_Err;
			}
			uint8_t GetFifoLen(void) override
			{
				return 0;
			}
			void* GetCStructPtr(void) override
			{
				return nullptr;
			}
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_ACCELEROMETER_HPP
