/**
  ******************************************************************************
  * @file		alxAdc.hpp
  * @brief		Auralix C++ Library - ALX ADC Module
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
#ifndef ALX_ADC_HPP
#define ALX_ADC_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxAdc.h"
#include "alxClk.hpp"
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
	namespace AlxAdc
	{
		//******************************************************************************
		// Class - IAdc
		//******************************************************************************
		class IAdc
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IAdc() {}
				virtual ~IAdc() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual float GetVoltage_V(Alx_Ch ch) = 0;
				virtual float TempSens_GetTemp_degC(void) = 0;
				virtual ::AlxAdc* GetCStructPtr(void) = 0;
		};


		//******************************************************************************
		// Class - AAdc
		//******************************************************************************
		class AAdc : public IAdc
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				AAdc() {}
				virtual ~AAdc() {}
				Alx_Status Init(void) override
				{
					return AlxAdc_Init(&me);
				}
				Alx_Status DeInit(void) override
				{
					return AlxAdc_DeInit(&me);
				}
				float GetVoltage_V(Alx_Ch ch) override
				{
					return AlxAdc_GetVoltage_V(&me, ch);
				}
				float TempSens_GetTemp_degC(void) override
				{
					return AlxAdc_TempSens_GetTemp_degC(&me);
				}
				::AlxAdc* GetCStructPtr(void) override
				{
					return &me;
				}

			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxAdc me = {};
		};


		//******************************************************************************
		// Class - Adc
		//******************************************************************************
		#if defined(ALX_STM32F0) || defined(ALX_STM32F1) || defined(ALX_STM32F4) || defined(ALX_STM32F7) || defined(ALX_STM32G4) || defined(ALX_STM32L0) || defined(ALX_STM32L4) || defined(ALX_STM32U5)
		class Adc : public AAdc
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Adc
				(
					ADC_TypeDef* adc,
					AlxIoPin::IIoPin** ioPinArr,
					uint8_t numOfIoPins,
					Alx_Ch* chArr,
					uint8_t numOfCh,
					AlxClk::IClk* clk,
					AlxAdc_Clk adcClk,
					uint32_t samplingTime,
				 	bool isVrefInt_V,
					float vrefExt_V
				)
				{
					for (uint32_t i = 0; i < numOfIoPins; i++)
					{
						AlxIoPin::IIoPin* temp = *(ioPinArr + i);
						adcIoPinArr[i] = temp->GetCStructPtr();
					}

					AlxAdc_Ctor
					(
						&me,
						adc,
						adcIoPinArr,
						numOfIoPins,
						chArr,
						numOfCh,
						clk->GetCStructPtr(),
						adcClk,
						samplingTime,
						isVrefInt_V,
						vrefExt_V
					);
				}
				virtual ~Adc() {}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxIoPin* adcIoPinArr[ALX_ADC_BUFF_LEN] = {};
		};
		#endif


		//******************************************************************************
		// Class - MockAdc
		//******************************************************************************
		#if defined(ALX_GTEST)
		class MockAdc : public IAdc
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				MOCK_METHOD(Alx_Status, Init, (), (override));
				MOCK_METHOD(Alx_Status, DeInit, (), (override));
				MOCK_METHOD(float, GetVoltage_V, (Alx_Ch ch), (override));
				MOCK_METHOD(float, TempSens_GetTemp_degC, (), (override));
		};
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_ADC_HPP
