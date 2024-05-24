/**
  ******************************************************************************
  * @file		alxPwr.hpp
  * @brief		Auralix C++ Library - ALX Power Module
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
#ifndef ALX_PWR_HPP
#define ALX_PWR_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxPwr.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxPwr
	{
		//******************************************************************************
		// Class - IPwr
		//******************************************************************************
		class IPwr
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IPwr() {}
				virtual ~IPwr() {}
				virtual bool Process(float adcVal_V) = 0;
		};


		//******************************************************************************
		// Class - Pwr
		//******************************************************************************
		class Pwr : public IPwr
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Pwr
				(
					float vdiv_ResHigh_kOhm,
					float vdiv_ResLow_kOhm,
					float hys2_TopHigh_V,
					float hys2_TopLow_V,
					float hys2_BotHigh_V,
					float hys2_BotLow_V,
					bool filtGlitchBool_valInitial,
					float filtGlitchBool_StableTrueTime_ms,
					float filtGlitchBool_StableFalseTime_ms
				)
				{
					AlxPwr_Ctor
					(
						&me,
						vdiv_ResHigh_kOhm,
						vdiv_ResLow_kOhm,
						hys2_TopHigh_V,
						hys2_TopLow_V,
						hys2_BotHigh_V,
						hys2_BotLow_V,
						filtGlitchBool_valInitial,
						filtGlitchBool_StableTrueTime_ms,
						filtGlitchBool_StableFalseTime_ms
					);
				}
				virtual ~Pwr() {}
				bool Process(float adcVal_V) override
				{
					return AlxPwr_Process(&me, adcVal_V);
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxPwr me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_PWR_HPP
