/**
  ******************************************************************************
  * @file		alxDac.hpp
  * @brief		Auralix C++ Library - ALX DAC Module
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
#ifndef ALX_DAC_HPP
#define ALX_DAC_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxDac_Mcu.h"
#include "alxDac.h"
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
	namespace AlxDac
	{
		//******************************************************************************
		// Class - IDac
		//******************************************************************************
		class IDac
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IDac() {}
				virtual ~IDac() {}
				virtual ::Alx_Status Init(void) = 0;
				virtual ::Alx_Status Init(float vref_V) = 0;
				virtual ::Alx_Status DeInit(void) = 0;
				virtual ::Alx_Status SetVoltage_V(::Alx_Ch ch, float voltage_V) = 0;
				virtual ::Alx_Status SetVoltage_V(::Alx_Ch ch, float voltage_V, float vref_V) = 0;
		};


		//******************************************************************************
		// Class - ADac
		//******************************************************************************
		class ADac : public IDac
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ADac() {}
				virtual ~ADac() {}
				::Alx_Status Init(void) override
				{
					return AlxDac_Init(&dac);
				}
				::Alx_Status Init(float vref_V) override
				{
					return AlxDac_Init_CalibrateVref(&dac, vref_V);
				}
				::Alx_Status DeInit(void) override
				{
					return AlxDac_DeInit(&dac);
				}
				::Alx_Status SetVoltage_V(::Alx_Ch ch, float voltage_V) override
				{
					return AlxDac_SetVoltage_V(&dac, ch, voltage_V);
				}
				::Alx_Status SetVoltage_V(::Alx_Ch ch, float voltage_V, float vref_V) override
				{
					return AlxDac_SetVoltage_V_CalibrateVref(&dac, ch, voltage_V, vref_V);
				}

			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxDac dac = {};
		};


		//******************************************************************************
		// Class - DacMcu
		//******************************************************************************
		#if defined(ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)
		class DacMcu : public ADac
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				DacMcu
				(
					DAC_TypeDef* dac,
					AlxIoPin::IIoPin** ioPinArr,
					::Alx_Ch* chArr,
					float* setVoltageDefaultArr_V,
					uint8_t numOfCh,
					bool isVrefInt_V,
					float vrefExt_V
				)
				{
					for (uint32_t i = 0; i < numOfCh; i++)
					{
						AlxIoPin::IIoPin* temp = *(ioPinArr + i);
						dacIoPinArr[i] = temp->GetCStructPtr();
					}

					AlxDacMcu_Ctor
					(
						&dacMcu,
						dac,
						dacIoPinArr,
						chArr,
						setVoltageDefaultArr_V,
						numOfCh,
						isVrefInt_V,
						vrefExt_V
					);
					AlxDac_Ctor
					(
						&this->dac,
						AlxDac_Submodule_Mcu,
						&dacMcu
					);
				}
				virtual ~DacMcu() {}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxDac_Mcu dacMcu = {};
				::AlxIoPin* dacIoPinArr[ALX_DAC_BUFF_LEN] = {0};
		};
		#endif
		#if defined(ALX_GTEST)
		class MockDac final : public IDac
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				MOCK_METHOD(::Alx_Status, Init, (), (override));
				MOCK_METHOD(::Alx_Status, Init, (float voltage_V), (override));
				MOCK_METHOD(::Alx_Status, DeInit, (), (override));
				MOCK_METHOD(::Alx_Status, SetVoltage_V, (::Alx_Ch ch, float voltage_V), (override));
				MOCK_METHOD(::Alx_Status, SetVoltage_V, (::Alx_Ch ch, float voltage_V, float vref_V), (override));
		};
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// ALX_DAC_HPP
