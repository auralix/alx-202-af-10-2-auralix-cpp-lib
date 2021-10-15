/**
  ******************************************************************************
  * @file alxPwm.hpp
  * @brief Auralix C++ Library - ALX PWM Module
  * @version $LastChangedRevision: 5255 $
  * @date $LastChangedDate: 2021-05-28 00:29:47 +0200 (Fri, 28 May 2021) $
  ******************************************************************************
  */

#ifndef ALX_PWM_HPP
#define ALX_PWM_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxPwm.h>
#include <alxIoPin.hpp>
#include <alxClk.hpp>

//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxPwm
	{
		class IPwm
		{
			public:
				IPwm() {};
				virtual ~IPwm() {};
				virtual ::Alx_Status Init(void) = 0;
				virtual ::Alx_Status DeInit(void) = 0;
				virtual ::Alx_Status SetDuty_pct(::Alx_Ch ch, float duty_pct) = 0;
		};
		class APwm : public IPwm
		{
			public:
				APwm() {};
				virtual ~APwm() {};
				::Alx_Status Init(void) override
				{
					return AlxPwm_Init(&me);
				}
				::Alx_Status DeInit(void) override
				{
					return AlxPwm_DeInit(&me);
				}
				::Alx_Status SetDuty_pct(::Alx_Ch ch, float duty_pct) override
				{
					return AlxPwm_SetDuty_pct(&me, ch, duty_pct);
				}
			protected:
				::AlxPwm me = {};
		};
		#if defined(ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)
		class Pwm : public APwm
		{
			public:
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
					
					AlxPwm_Ctor(&me, tim, pwmIoPinArr, chArr, dutyDefaultArr_pct, numOfCh, clk->GetCStructPtr(), prescaler, period);
				};
				virtual ~Pwm() {};
			private:
				::AlxIoPin* pwmIoPinArr[ALX_PWM_BUFF_LEN] = {0};
		};
		#endif
		#if defined(ALX_GTEST)
		class MockPwm final : public IPwm
		{
			public:
				MOCK_METHOD(::Alx_Status, Init, (), (override));
				MOCK_METHOD(::Alx_Status, DeInit, (), (override));
				MOCK_METHOD(::Alx_Status, SetDuty_pct, (::Alx_Ch ch, float duty_pct), (override));
		};
		#endif
	}
}

#endif // ALX_PWM_HPP
