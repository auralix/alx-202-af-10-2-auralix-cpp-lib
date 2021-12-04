/**
  ******************************************************************************
  * @file alxHwNucleoF429Zi_Main.hpp
  * @brief Auralix HW NUCLEO-F429ZI C++ Library - Main Module
  * @version $LastChangedRevision: 3440 $
  * @date $LastChangedDate: 2021-09-10 17:45:39 +0200 (Fri, 10 Sep 2021) $
  ******************************************************************************
  */

#ifndef ALX_HW_NUCLEO_F429ZI_MAIN_HPP
#define ALX_HW_NUCLEO_F429ZI_MAIN_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxAdc.hpp>
#include <alxAssert.hpp>
#include <alxAudioPlayer.hpp>
#include <alxAudioVol.hpp>
#include <alxBtn.hpp>
#include <alxCan.hpp>
#include <alxClk.hpp>
#include <alxCrc.hpp>
#include <alxDac.hpp>
#include <alxDelay.hpp>
#include <alxFifo.hpp>
#include <alxFiltGlitchBool.hpp>
#include <alxFiltGlitchUint32.hpp>
#include <alxFtpClient.hpp>
#include <alxHys1.hpp>
#include <alxHys2.hpp>
#include <alxI2c.hpp>
#include <alxI2s.hpp>
#include <alxId.hpp>
#include <alxInterpLin.hpp>
#include <alxIoPin.hpp>
#include <alxIoPinIrq.hpp>
#include <alxLinFun.hpp>
#include <alxMemRaw.hpp>
#include <alxMemSafe.hpp>
#include <alxNtpClient.hpp>
#include <alxOsCriticalSection.hpp>
#include <alxOsFlag.hpp>
#include <alxParamGroup.hpp>
#include <alxParamItem.hpp>
#include <alxParamMgmt.hpp>
#include <alxParamStore.hpp>
#include <alxPwm.hpp>
#include <alxRtc.hpp>
#include <alxSerialPort.hpp>
#include <alxSm.hpp>
#include <alxSpi.hpp>
#include <alxTempSens.hpp>
#include <alxTick.hpp>
#include <alxTimSw.hpp>
#include <alxTpl.hpp>
#include <alxTrace.hpp>

#include <alxAdau1961.hpp>
#include <alxAdxl355.hpp>
#include <alxBq24600.hpp>
#include <alxBts724g.hpp>
#include <alxTmp1075.hpp>
#include <alxTpa3255.hpp>


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_HW_NUCLEO_F429ZI_CPP_TEST)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxHwNucleoF429Zi_Main
	{
		class Main
		{
			public:
				Main() {};
				virtual ~Main() {};
			public:
				//******************************************************************************
				// ALX - IoPin
				//******************************************************************************
				class AlxIoPin
				{
					public:
						//******************************************************************************
						// Port A
						//******************************************************************************
						// PA0	- Unused
						// PA1	- Unused
						// PA2	- Unused
						// PA3	- Unused
						// PA4	- Unused
						// PA5	- Unused
						// PA6	- Unused
						// PA7	- Unused
						// PA8	- Unused
						// PA9	- Unused
						// PA10	- Unused
						// PA11	- Unused
						// PA12	- Unused
						// PA13	- SWD_IO
						// PA14	- SWD_CLK
						// PA15	- Unused


						//******************************************************************************
						// Port B
						//******************************************************************************
						Alx::AlxIoPin::IoPin do_PB0_LED1_GR		= { GPIOB,	GPIO_PIN_0,		GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,		false		};
						// PB1	- Unused
						// PB2	- Unused
						// PB3	- Unused
						// PB4	- Unused
						// PB5	- Unused
						// PB6	- Unused
						Alx::AlxIoPin::IoPin do_PB7_LED2_BL		= { GPIOB,	GPIO_PIN_7,		GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,		false		};
						// PB8	- Unused
						// PB9	- Unused
						Alx::AlxIoPin::IoPin do_PB10_I2C2_SCL	= { GPIOB,	GPIO_PIN_10,	GPIO_MODE_AF_OD,		GPIO_PULLUP,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF4_I2C2,	ALX_NULL	};
						Alx::AlxIoPin::IoPin io_PB11_I2C2_SDA	= { GPIOB,	GPIO_PIN_11,	GPIO_MODE_AF_OD,		GPIO_PULLUP,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF4_I2C2,	ALX_NULL	};
						// PB12	- Unused
						// PB13	- Unused
						Alx::AlxIoPin::IoPin do_PB14_LED3_RD	= { GPIOB,	GPIO_PIN_14,	GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,		false		};
						// PB15	- Unused


						//******************************************************************************
						// Port C
						//******************************************************************************
						// PC0	- Unused
						// PC1	- Unused
						// PC2	- Unused
						// PC3	- Unused
						// PC4	- Unused
						// PC5	- Unused
						// PC6	- Unused
						// PC7	- Unused
						// PC8	- Unused
						// PC9	- Unused
						// PC10	- Unused
						// PC11	- Unused
						// PC12	- Unused
						// PC13	- Unused
						// PC14	- LSE
						// PC15	- LSE


						//******************************************************************************
						// Port D
						//******************************************************************************
						// PD0	- Unused
						// PD1	- Unused
						// PD2	- Unused
						// PD3	- Unused
						// PD4	- Unused
						// PD5	- DBG_UART_TX	-> ALX Trace Handle
						// PD6	- Unused
						// PD7	- Unused
						// PD8	- Unused
						// PD9	- Unused
						// PD10	- Unused
						// PD11	- Unused
						// PD12	- Unused
						// PD13	- Unused
						// PD14	- Unused
						// PD15	- Unused


						//******************************************************************************
						// Port E
						//******************************************************************************
						// PE0	- Unused
						// PE1	- Unused
						// PE2	- Unused
						// PE3	- Unused
						// PE4	- Unused
						// PE5	- Unused
						// PE6	- Unused
						// PE7	- Unused
						// PE8	- Unused
						// PE9	- Unused
						// PE10	- Unused
						// PE11	- Unused
						// PE12	- Unused
						// PE13	- Unused
						// PE14	- Unused
						// PE15	- Unused


						//******************************************************************************
						// Port F
						//******************************************************************************
						// PF0	- Unused
						// PF1	- Unused
						// PF2	- Unused
						// PF3	- Unused
						// PF4	- Unused
						// PF5	- Unused
						// PF6	- Unused
						// PF7	- Unused
						// PF8	- Unused
						// PF9	- Unused
						// PF10	- Unused
						// PF11	- Unused
						// PF12	- Unused
						// PF13	- Unused
						// PF14	- Unused
						// PF15	- Unused


						//******************************************************************************
						// Port G
						//******************************************************************************
						// PG0	- Unused
						// PG1	- Unused
						// PG2	- Unused
						// PG3	- Unused
						// PG4	- Unused
						// PG5	- Unused
						// PG6	- Unused
						// PG7	- Unused
						// PG8	- Unused
						// PG9	- Unused
						// PG10	- Unused
						// PG11	- Unused
						// PG12	- Unused
						// PG13	- Unused
						// PG14	- Unused
						// PG15	- Unused


						//******************************************************************************
						// Port H
						//******************************************************************************
						// PH0 - HSE
						// PH1 - HSE
				} alxIoPin;


				//******************************************************************************
				// ALX - Clock
				//******************************************************************************
				Alx::AlxClk::Clk alxClkObj =
				{
					&alxClk,
					AlxClk_Config_McuStm32F4_Sysclk_180MHz_Pclk1Apb1_45MHz_Pclk2Apb2_90MHz_Hsi_16MHz
				};


				//******************************************************************************
				// ALX - Trace
				//******************************************************************************
				Alx::AlxTrace::Trace alxTraceObj =
				{
					&alxTrace,
					GPIOD,
					GPIO_PIN_5,
					GPIO_AF7_USART2,
					USART2,
					AlxGlobal_BaudRate_115200
				};


				//******************************************************************************
				// ALX - I2C
				//******************************************************************************
				Alx::AlxI2c::I2c alxI2c_I2C2_Master =
				{
					I2C2,
					&alxIoPin.do_PB10_I2C2_SCL,
					&alxIoPin.io_PB11_I2C2_SDA,
					AlxI2c_Clk_400kHz
				};
		};
	}
}


#endif // #if defined(ALX_HW_NUCLEO_F429ZI_CPP_TEST)

#endif // ALX_HW_NUCLEO_F429ZI_MAIN_HPP
