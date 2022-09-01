/**
  ******************************************************************************
  * @file		alxAdc.hpp
  * @brief		Auralix C++ Library - ALX ADC Module
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
#ifndef ALX_ADC_HPP
#define ALX_ADC_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxAdc.h>
#include <alxIoPin.hpp>
#include <alxClk.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxAdc
	{
		class IAdc
		{
			public:
				IAdc() {};
				virtual ~IAdc() {};
				virtual ::Alx_Status Init(void) = 0;
				virtual ::Alx_Status DeInit(void) = 0;
				virtual float GetVoltage_V(::Alx_Ch ch) = 0;
				virtual float TempSens_GetTemp_degC(void) = 0;
				virtual ::AlxAdc* GetCStructPtr(void) = 0;
		};
		class AAdc : public IAdc
		{
			public:
				AAdc() {};
				virtual ~AAdc() {};
				::Alx_Status Init(void) override
				{
					return AlxAdc_Init(&me);
				}
				::Alx_Status DeInit(void) override
				{
					return AlxAdc_DeInit(&me);
				}
				float GetVoltage_V(::Alx_Ch ch) override
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
				::AlxAdc me = {};
		};
		#if defined(ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)
		class Adc : public AAdc
		{
			public:
				Adc
				(
					ADC_TypeDef* adc,
					AlxIoPin::IIoPin** ioPinArr,
					uint8_t numOfIoPins,
					::Alx_Ch* chArr,
					uint8_t numOfCh,
					AlxClk::IClk* clk,
					::AlxAdc_Clk adcClk,
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

					AlxAdc_Ctor(&me, adc, adcIoPinArr, numOfIoPins, chArr, numOfCh, clk->GetCStructPtr(), adcClk, samplingTime, isVrefInt_V, vrefExt_V);
				};
				virtual ~Adc() {};
			private:
				::AlxIoPin* adcIoPinArr[ALX_ADC_BUFF_LEN] = {};
		};
		#endif
		#if defined(ALX_GTEST)
		class MockAdc final : public IAdc
		{
			public:
				MOCK_METHOD(::Alx_Status, Init, (), (override));
				MOCK_METHOD(::Alx_Status, DeInit, (), (override));
				MOCK_METHOD(float, GetVoltage_V, (::Alx_Ch ch), (override));
				MOCK_METHOD(float, TempSens_GetTemp_degC, (), (override));
		};
		#endif
	}
}

#endif // ALX_ADC_HPP
