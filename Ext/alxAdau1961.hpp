/**
  ******************************************************************************
  * @file		alxAdau1961.hpp
  * @brief		Auralix C++ Library - ALX Adau1961 Module
  * @copyright	Copyright (C) 2020-2022 Auralix d.o.o. All rights reserved.
  *
  * @section License
  *
  * SPDX-License-Identifier: GPL-3.0-or-later
  *
  * This file is part of Auralix C Library.
  *
  * Auralix C Library is free software: you can redistribute it and/or
  * modify it under the terms of the GNU General Public License
  * as published by the Free Software Foundation, either version 3
  * of the License, or (at your option) any later version.
  *
  * Auralix C Library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with Auralix C Library. If not, see <https://www.gnu.org/licenses/>.
  ******************************************************************************
  **/

//******************************************************************************
// Include Guard
//******************************************************************************
#ifndef ALX_ADAU1961_HPP
#define ALX_ADAU1961_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxAdau1961.h"
#include "alxI2s.hpp"
#include "alxI2c.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxAdau1961
	{
		//******************************************************************************
		// Class - IAdau1961
		//******************************************************************************
		class IAdau1961
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IAdau1961() {}
				virtual ~IAdau1961() {}
				virtual ::Alx_Status Init(void) = 0;
				virtual ::Alx_Status DeInit(void) = 0;
				virtual void Foreground_Handle(void) = 0;
				virtual ::Alx_Status InDiffL_SetGain(float gain_dB) = 0;
				virtual ::Alx_Status InDiffR_SetGain(float gain_dB) = 0;
				virtual ::Alx_Status InAuxL_SetGain_dB(int8_t gain_dB) = 0;
				virtual ::Alx_Status InAuxR_SetGain_dB(int8_t gain_dB) = 0;
				virtual ::Alx_Status OutLineL_SetGain_dB(int8_t gain_dB) = 0;
				virtual ::Alx_Status OutLineR_SetGain_dB(int8_t gain_dB) = 0;
		};


		//******************************************************************************
		// Class - Adau1961
		//******************************************************************************
		class Adau1961 final : public IAdau1961
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Adau1961
				(
					Alx::AlxI2s::II2s* i2s,
					Alx::AlxI2c::II2c* i2c,
					uint8_t i2cAddr,
					bool i2cCheckWithRead,
					uint8_t i2cNumOfTries,
					uint16_t i2cTimeout_ms
				)
				{
					AlxAdau1961_Ctor
					(
						&me,
						i2s->GetCStructPtr(),
						i2c->GetCStructPtr(),
						i2cAddr,
						i2cCheckWithRead,
						i2cNumOfTries,
						i2cTimeout_ms
					);
				}
				virtual ~Adau1961() {}
				::Alx_Status Init(void) override
				{
					return AlxAdau1961_Init(&me);
				}
				::Alx_Status DeInit(void) override
				{
					return AlxAdau1961_DeInit(&me);
				}
				void Foreground_Handle(void) override
				{
					return AlxAdau1961_Foreground_Handle(&me);
				}
				::Alx_Status InDiffL_SetGain(float gain_dB) override
				{
					return AlxAdau1961_InDiffL_SetGain_dB(&me, gain_dB);
				}
				::Alx_Status InDiffR_SetGain(float gain_dB) override
				{
					return AlxAdau1961_InDiffR_SetGain_dB(&me, gain_dB);
				}
				::Alx_Status InAuxL_SetGain_dB(int8_t gain_dB) override
				{
					return AlxAdau1961_InAuxL_SetGain_dB(&me, gain_dB);
				}
				::Alx_Status InAuxR_SetGain_dB(int8_t gain_dB) override
				{
					return AlxAdau1961_InAuxR_SetGain_dB(&me, gain_dB);
				}
				::Alx_Status OutLineL_SetGain_dB(int8_t gain_dB) override
				{
					return AlxAdau1961_OutLineL_SetGain_dB(&me, gain_dB);
				}
				::Alx_Status OutLineR_SetGain_dB(int8_t gain_dB) override
				{
					return AlxAdau1961_OutLineR_SetGain_dB(&me, gain_dB);
				}
			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxAdau1961 me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif // ALX_ADAU1961_HPP
