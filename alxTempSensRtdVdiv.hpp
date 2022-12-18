/**
  ******************************************************************************
  * @file		alxTempSens.hpp
  * @brief		Auralix C++ Library - ALX Temperature Sensor Module
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
#ifndef ALX_TEMP_SENS_RTD_VDIV_HPP
#define ALX_TEMP_SENS_RTD_VDIV_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxAdc.hpp"
#include "alxInterpLin.hpp"
#include "alxTempSensRtdVdiv.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxTempSensRtdVdiv
	{
		//******************************************************************************
		// Class - ITempSensRtdVdiv
		//******************************************************************************
		class ITempSensRtdVdiv
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ITempSensRtdVdiv() {}
				virtual ~ITempSensRtdVdiv() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual Alx_Status GetTemp_degC(float *temp_degC) = 0;
		};


		//******************************************************************************
		// Class - TempSensRtdVdiv
		//******************************************************************************
		class TempSensRtdVdiv : public ITempSensRtdVdiv
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				TempSensRtdVdiv
				(
					AlxAdc::IAdc* adc,
					AlxInterpLin::IInterpLin* interpLin,
					Alx_Ch chAdc_Vin,
					Alx_Ch chAdc_Vout,
					bool isResRtdLow,
					float resOther_kOhm
				)
				{
					AlxTempSensRtdVdiv_Ctor
					(
						&me,
						adc->GetCStructPtr(),
						interpLin->GetCStructPtr(),
						chAdc_Vin,
						chAdc_Vout,
						isResRtdLow,
						resOther_kOhm
					);
				}
				virtual ~TempSensRtdVdiv() {}
				Alx_Status Init(void) override
				{
					return AlxTempSensRtdVdiv_Init(&me);
				}
				Alx_Status DeInit(void) override
				{
					return AlxTempSensRtdVdiv_DeInit(&me);
				}
				Alx_Status GetTemp_degC(float *temp_degC) override
				{
					return AlxTempSensRtdVdiv_GetTemp_degC(&me, temp_degC);
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxTempSensRtdVdiv me = {};
		};


		//******************************************************************************
		// Class - MockTempSens
		//******************************************************************************
		#if defined(ALX_GTEST)
		class MockTempSens : public ITempSens
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				MOCK_METHOD(Alx_Status, Init, (), (override));
				MOCK_METHOD(Alx_Status, DeInit, (), (override));
				MOCK_METHOD(float, GetTemp_degC, (void), (override));
		};
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_TEMP_SENS_RTD_VDIV_HPP
