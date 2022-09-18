/**
  ******************************************************************************
  * @file		alxPwm.hpp
  * @brief		Auralix C++ Library - ALX PWM Module
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
#ifndef ALX_PWM_HPP
#define ALX_PWM_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxPwm.h"
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
	namespace AlxPwm
	{
		//******************************************************************************
		// Class - IPwm
		//******************************************************************************
		class IPwm
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IPwm() {}
				virtual ~IPwm() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual Alx_Status SetDuty_pct(Alx_Ch ch, float duty_pct) = 0;
		};


		//******************************************************************************
		// Class - APwm
		//******************************************************************************
		class APwm : public IPwm
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				APwm() {}
				virtual ~APwm() {}
				Alx_Status Init(void) override
				{
					return AlxPwm_Init(&me);
				}
				Alx_Status DeInit(void) override
				{
					return AlxPwm_DeInit(&me);
				}
				Alx_Status SetDuty_pct(Alx_Ch ch, float duty_pct) override
				{
					return AlxPwm_SetDuty_pct(&me, ch, duty_pct);
				}

			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxPwm me = {};
		};


		//******************************************************************************
		// Class - Pwm
		//******************************************************************************
		#if defined(ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)
		class Pwm : public APwm
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Pwm
				(
					TIM_TypeDef* tim,
					AlxIoPin::IIoPin** ioPinArr,
					Alx_Ch* chArr,
					float* dutyDefaultArr_pct,
					uint8_t numOfCh,
 					AlxClk::IClk* clk,
					uint32_t prescaler,
					uint32_t period
				)
				{
					for (uint32_t i = 0; i < numOfCh; i++)
					{
						AlxIoPin::IIoPin* temp = *(ioPinArr + i);
						pwmIoPinArr[i] = temp->GetCStructPtr();
					}

					AlxPwm_Ctor
					(
						&me,
						tim,
						pwmIoPinArr,
						chArr,
						dutyDefaultArr_pct,
						numOfCh,
						clk->GetCStructPtr(),
						prescaler,
						period
					);
				}
				virtual ~Pwm() {}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxIoPin* pwmIoPinArr[ALX_PWM_BUFF_LEN] = {};
		};
		#endif


		//******************************************************************************
		// Class - MockPwm
		//******************************************************************************
		#if defined(ALX_GTEST)
		class MockPwm : public IPwm
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				MOCK_METHOD(Alx_Status, Init, (), (override));
				MOCK_METHOD(Alx_Status, DeInit, (), (override));
				MOCK_METHOD(Alx_Status, SetDuty_pct, (Alx_Ch ch, float duty_pct), (override));
		};
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_PWM_HPP
