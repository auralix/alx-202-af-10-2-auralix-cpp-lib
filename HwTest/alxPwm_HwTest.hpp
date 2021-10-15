/**
  ******************************************************************************
  * @file alxPwm_HwTest.hpp
  * @brief Auralix C++ Library - ALX PWM Module - Test
  * @version $LastChangedRevision: 4271 $
  * @date $LastChangedDate: 2021-03-05 19:03:28 +0100 (Fri, 05 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_PWM_HW_TEST_HPP
#define ALX_PWM_HW_TEST_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxTick.hpp>
#include <alxClk.hpp>
#include <alxTrace.hpp>
#include <alxIoPin.hpp>
#include <alxPwm.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxPwmHwTest
	{
		#if defined(ALX_STM32F4)
		class PwmHwTest_Mcu
		{
			public:
				PwmHwTest_Mcu() {};
				virtual ~PwmHwTest_Mcu() {};
				void T01_BasicExample()
				{
					pwm.Init(); // Init module, starts PWM on all channels with default duty setting
					
					pwm.SetDuty_pct(Alx_Ch_1, 50.5); // set duty to 50.5%
					pwm.SetDuty_pct(Alx_Ch_2, 25.7); // set duty to 25.7%

					pwm.DeInit(); // DeInit module
				}
			public:
				// Common Tick, Clk and Trace objects init, not part of example
				AlxTick::Tick tick = { &alxTick };
				AlxClk::Clk clk = { &alxClk, AlxClk_Config_McuStm32F4_Sysclk_180MHz_Pclk1Apb1_45MHz_Pclk2Apb2_90MHz_Hsi_16MHz };
				AlxTrace::Trace trace = { &alxTrace, GPIOA, GPIO_PIN_9, GPIO_AF7_USART1, USART1, AlxGlobal_BaudRate_115200 };
			public:
				AlxIoPin::IoPin do_PA0 = { GPIOA,	GPIO_PIN_0,		GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF1_TIM2,		ALX_NULL };
				AlxIoPin::IoPin do_PA1 = { GPIOA,	GPIO_PIN_1,		GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF1_TIM2,		ALX_NULL };
				AlxIoPin::IIoPin* pwmIoPinArr[2] = // This array of pointers to IoPins used by pwm module
				{
					&do_PA0,  // It is recommended to allignd ioPins Array to channel array.. so that it is easier to se on which pin is which channel
					&do_PA1
				};
				Alx_Ch pwmChArr[2] = // This array of channels used by pwm module
				{
					Alx_Ch_1, // Channels must be from low number to high number.. channel number must also match STM32 channel number
					Alx_Ch_2
				};
				float pwmDutyDefaultArr_pct[2] =  // This is array of default values for duty cycle, which are used after Init function is called
				{ 
					50.f,
					50.f
				};
				AlxPwm::Pwm pwm =
				{
					TIM2,
					pwmIoPinArr,
					pwmChArr,
					pwmDutyDefaultArr_pct,
					ALX_ARR_LEN(pwmChArr),
					&clk,
					0, // TODO for freq
					0xFFFE // TODO for freq
				};
		};
		#endif
	}
}

#endif // ALX_PWM_HW_TEST_HPP
