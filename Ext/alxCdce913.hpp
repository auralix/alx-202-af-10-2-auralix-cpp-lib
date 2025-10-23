/**
  ******************************************************************************
  * @file		alxCdce913.hpp
  * @brief		Auralix C++ Library - ALX CDCE913 PLL Module
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
#ifndef ALX_CDCE913_HPP
#define ALX_CDCE913_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxCdce913.h"
#include "alxI2c.hpp"
#include "alxDac.hpp"
#include "alxIoPin.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxCdce913
	{
		//******************************************************************************
		// Class - ICdce913
		//******************************************************************************
		class ICdce913
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ICdce913() {}
				virtual Alx_Status Init
				(
					float xtalFrequency,
					AlxCdce913_RegEnum_INCLK xtalSource,
					uint8_t xtalCapacitance_pF
				) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual Alx_Status SetY1OutputFreq(AlxCdce913_OutputY1 freq) = 0;
				virtual Alx_Status SetVctrl(float vctrl_V) = 0;
				virtual Alx_Status EnableY1(void) = 0;
				virtual Alx_Status DisableY1(void) = 0;
				virtual void* GetCStructPtr(void) = 0;
				virtual ~ICdce913() {}
		};

		//******************************************************************************
		// Class - CDCE913
		//******************************************************************************
		class Cdce913 : public ICdce913
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Cdce913
				(
					Alx::AlxI2c::II2c* i2c,
					Alx::AlxDac::IDac* dac,
					float dacReference_V,
					Alx_Ch dacChannel,
					Alx::AlxIoPin::IIoPin* pllEnable
				)
				{
					AlxCdce913_Ctor(
						&me,
						i2c->GetCStructPtr(),
						dac->GetCStructPtr(),
						dacReference_V,
						dacChannel,
						pllEnable->GetCStructPtr());
				}
				virtual ~Cdce913() {}
				Alx_Status Init
				(
					float xtalFrequency,
					AlxCdce913_RegEnum_INCLK xtalSource,
					uint8_t xtalCapacitance_pF
				) override
				{
					return AlxCdce913_Init(&me, xtalFrequency, xtalSource, xtalCapacitance_pF);
				}
				Alx_Status DeInit(void) override
				{
					return AlxCdce913_DeInit(&me);
				}
				Alx_Status SetY1OutputFreq(AlxCdce913_OutputY1 freq) override
				{
					return AlxCdce913_SetY1OutputFreq(&me, freq);
				}
				Alx_Status SetVctrl(float vctrl_V) override
				{
					return AlxCdce913_SetVctrl(&me, vctrl_V);
				}
				Alx_Status EnableY1(void) override
				{
					return AlxCdce913_EnableY1(&me);
				}
				Alx_Status DisableY1(void) override
				{
					return AlxCdce913_DisableY1(&me);
				}
				void* GetCStructPtr(void) override
				{
					return &me;
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxCdce913 me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_CDCE913_HPP
