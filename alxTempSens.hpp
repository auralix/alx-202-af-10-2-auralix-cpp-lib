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
#ifndef ALX_TEMP_SENS_HPP
#define ALX_TEMP_SENS_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxAdc.hpp"
#include "alxInterpLin.hpp"
#include "alxTempSens_Mcu.h"
#include "alxTempSens.h"
#include "alxTempSens_RtdVdiv.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxTempSens
	{
		class ITempSens
		{
			public:
				ITempSens() {};
				virtual ~ITempSens() {};
				virtual ::Alx_Status Init(void) = 0;
				virtual ::Alx_Status DeInit(void) = 0;
				virtual ::Alx_Status GetTemp_degC(float *temp_degC) = 0;
		};
		class ATempSens : public ITempSens
		{
			public:
				ATempSens() {};
				virtual ~ATempSens() {};
				::Alx_Status Init(void) override
				{
					return AlxTempSens_Init(&tempSens);
				}
				::Alx_Status DeInit(void) override
				{
					return AlxTempSens_DeInit(&tempSens);
				}
				::Alx_Status GetTemp_degC(float *temp_degC) override
				{
					return AlxTempSens_GetTemp_degC(&tempSens, temp_degC);
				}
			protected:
				::AlxTempSens tempSens = {};
		};
		class TempSensRtd : public ATempSens
		{
			public:
				TempSensRtd
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
					AlxTempSens_Ctor
					(
						&tempSens,
						AlxTempSens_Submodule_Rtd_Vdiv,
						&me
					);
				};
				virtual ~TempSensRtd() {};
			private:
			::AlxTempSensRtdVdiv me = {};
		};

		#if defined(ALX_GTEST)
		class MockTempSens final : public ITempSens
		{
			public:
				MOCK_METHOD(::Alx_Status, Init, (), (override));
				MOCK_METHOD(::Alx_Status, DeInit, (), (override));
				MOCK_METHOD(float, GetTemp_degC, (void), (override));
		};
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif // ALX_TEMP_SENS_HPP
