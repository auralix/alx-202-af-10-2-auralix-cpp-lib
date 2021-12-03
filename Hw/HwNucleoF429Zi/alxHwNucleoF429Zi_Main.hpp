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
#include <alxAssert.hpp>
#include <alxTick.hpp>
#include <alxClk.hpp>
#include <alxDelay.hpp>
#include <alxTrace.hpp>
#include <alxIoPin.hpp>
#include <alxI2c.hpp>
#include <alxI2s.hpp>
#include <alxFifo.hpp>
#include <alxAdc.hpp>
#include <alxPwm.hpp>
#include <alxSerialPort.hpp>
#include <alxSpi.hpp>
#include <alxTimSw.hpp>
#include <alxTempSens.hpp>
#include <alxId.hpp>
#include <alxCan.hpp>
#include <alxLinFun.hpp>
#include <alxParamItem.hpp>
#include <alxBound.h>

#include <alxBts724g.hpp>
#include <alxNtcg103jf103ft1s.h>
#include <alxTpa3255.hpp>
#include <alxAdau1961.hpp>


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_HW_NUCLEO_F429ZI_CPP_TEST)


//******************************************************************************
// Preprocessor
//******************************************************************************
#define ALX_HW_NUCLEO_F429ZI_MAIN_FILE "alxHwNucleoF429Zi_Main.hpp"

// Assert //
#if defined(_ALX_HW_NUCLEO_F429ZI_MAIN_ASSERT_BKPT) || defined(_ALX_HW_NUCLEO_F429ZI_CPP_ASSERT_BKPT_ALL)
	#define ALX_HW_NUCLEO_F429ZI_MAIN_ASSERT(expr) ALX_ASSERT_BKPT(ALX_HW_NUCLEO_F429ZI_MAIN_FILE, expr)
#elif defined(_ALX_HW_NUCLEO_F429ZI_MAIN_ASSERT_TRACE) || defined(_ALX_HW_NUCLEO_F429ZI_ASSERT_TRACE_ALL)
	#define ALX_HW_NUCLEO_F429ZI_MAIN_ASSERT(expr) ALX_ASSERT_TRACE(ALX_HW_NUCLEO_F429ZI_MAIN_FILE, expr)
#elif defined(_ALX_HW_NUCLEO_F429ZI_MAIN_ASSERT_RST) || defined(_ALX_HW_NUCLEO_F429ZI_ASSERT_RST_ALL)
	#define ALX_HW_NUCLEO_F429ZI_MAIN_ASSERT(expr) ALX_ASSERT_RST(ALX_HW_NUCLEO_F429ZI_MAIN_FILE, expr)
#else
	#define ALX_HW_NUCLEO_F429ZI_MAIN_ASSERT(expr) do{} while (false)
#endif

// Trace //
#if defined(_ALX_HW_NUCLEO_F429ZI_MAIN_TRACE) || defined(_ALX_HW_NUCLEO_F429ZI_CPP_TRACE_ALL)
	#define ALX_HW_NUCLEO_F429ZI_MAIN_TRACE(...) ALX_TRACE_STD(ALX_HW_NUCLEO_F429ZI_MAIN_FILE, __VA_ARGS__)
#else
	#define ALX_HW_NUCLEO_F429ZI_MAIN_TRACE(...) do{} while (false)
#endif


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
						Alx::AlxIoPin::IoPin do_HS_IN1				= { GPIOA,	GPIO_PIN_0,		GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};
						Alx::AlxIoPin::IoPin do_HS_IN2				= { GPIOA,	GPIO_PIN_1,		GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};
						Alx::AlxIoPin::IoPin ai_HORN_SENS			= { GPIOA,	GPIO_PIN_2,		GPIO_MODE_ANALOG,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};	// ADC1_CH2
						Alx::AlxIoPin::IoPin ai_HORN_PULL_SENS		= { GPIOA,	GPIO_PIN_3,		GPIO_MODE_ANALOG,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};	// ADC1_CH3
						Alx::AlxIoPin::IoPin ai_5V_SENS				= { GPIOA,	GPIO_PIN_4,		GPIO_MODE_ANALOG,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};	// ADC1_CH4
						Alx::AlxIoPin::IoPin ai_5V4_SENS			= { GPIOA,	GPIO_PIN_5,		GPIO_MODE_ANALOG,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};	// ADC1_CH5
						Alx::AlxIoPin::IoPin ai_10V_SENS			= { GPIOA,	GPIO_PIN_6,		GPIO_MODE_ANALOG,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};	// ADC1_CH6
						Alx::AlxIoPin::IoPin ai_11V_SENS			= { GPIOA,	GPIO_PIN_7,		GPIO_MODE_ANALOG,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};	// ADC1_CH7
						Alx::AlxIoPin::IoPin do_CODEC_MCLK			= { GPIOA,	GPIO_PIN_8,		GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF0_MCO,		ALX_NULL	};
						Alx::AlxIoPin::IoPin do_DBG_UART_TX			= { GPIOA,	GPIO_PIN_9,		GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF7_USART1,	ALX_NULL	};
						Alx::AlxIoPin::IoPin di_DBG_UART_RX			= { GPIOA,	GPIO_PIN_10,	GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF7_USART1,	ALX_NULL	};
						Alx::AlxIoPin::IoPin di_CAN_RX				= { GPIOA,	GPIO_PIN_11,	GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF9_CAN1,		ALX_NULL	};
						Alx::AlxIoPin::IoPin do_CAN_TX				= { GPIOA,	GPIO_PIN_12,	GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF9_CAN1,		ALX_NULL	};
						// PA13 - JTAG_TMS, SWD_IO
						// PA14 - JTAG_TCK, SWD_CLK
						// PA15 - JTAG_TDI


						//******************************************************************************
						// Port B
						//******************************************************************************
						Alx::AlxIoPin::IoPin ai_48V_SENS			= { GPIOB,	GPIO_PIN_0,		GPIO_MODE_ANALOG,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};	// ADC1_CH8
						Alx::AlxIoPin::IoPin ai_PWR_RAW_SENS		= { GPIOB,	GPIO_PIN_1,		GPIO_MODE_ANALOG,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};	// ADC1_CH9
						// PB2 - Unused
						// PB3 - JTAG_TDO
						// PB4 - JTAG_nTRST
						// PB5 - Unused
						// PB6 - Unused
						Alx::AlxIoPin::IoPin do_EEPROM_WP			= { GPIOB,	GPIO_PIN_7,		GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			true		};	// Eeprom WP asserted
						Alx::AlxIoPin::IoPin do_EEPROM_I2C_SCL		= { GPIOB,	GPIO_PIN_8,		GPIO_MODE_AF_OD,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF4_I2C1,		ALX_NULL	};
						Alx::AlxIoPin::IoPin io_EEPROM_I2C_SDA		= { GPIOB,	GPIO_PIN_9,		GPIO_MODE_AF_OD,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF4_I2C1,		ALX_NULL	};
						Alx::AlxIoPin::IoPin do_CODEC_I2C_SCL		= { GPIOB,	GPIO_PIN_10,	GPIO_MODE_AF_OD,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF4_I2C2,		ALX_NULL	};
						Alx::AlxIoPin::IoPin io_CODEC_I2C_SDA		= { GPIOB,	GPIO_PIN_11,	GPIO_MODE_AF_OD,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF4_I2C2,		ALX_NULL	};
						// PB12 - Unused
						Alx::AlxIoPin::IoPin do_FLASH_SPI_SCK		= { GPIOB,	GPIO_PIN_13,	GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF5_SPI2,		ALX_NULL	};
						Alx::AlxIoPin::IoPin di_FLASH_SPI_MISO		= { GPIOB,	GPIO_PIN_14,	GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF5_SPI2,		ALX_NULL	};
						Alx::AlxIoPin::IoPin do_FLASH_SPI_MOSI		= { GPIOB,	GPIO_PIN_15,	GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF5_SPI2,		ALX_NULL	};


						//******************************************************************************
						// Port C
						//******************************************************************************
						Alx::AlxIoPin::IoPin ai_DIN_SENS			= { GPIOC,	GPIO_PIN_0,		GPIO_MODE_ANALOG,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};	// ADC1_CH10
						Alx::AlxIoPin::IoPin ai_NTC_SENS			= { GPIOC,	GPIO_PIN_1,		GPIO_MODE_ANALOG,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};	// ADC1_CH11
						Alx::AlxIoPin::IoPin ai_MIC1_PTT_SENS		= { GPIOC,	GPIO_PIN_2,		GPIO_MODE_ANALOG,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};	// ADC1_CH12
						Alx::AlxIoPin::IoPin ai_MIC2_PTT_SENS		= { GPIOC,	GPIO_PIN_3,		GPIO_MODE_ANALOG,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};	// ADC1_CH13
						Alx::AlxIoPin::IoPin do_BOOST_EN			= { GPIOC,	GPIO_PIN_4,		GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			false		};	// Boost disabled
						Alx::AlxIoPin::IoPin di_BOOST_PGOOD			= { GPIOC,	GPIO_PIN_5,		GPIO_MODE_INPUT,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};
						Alx::AlxIoPin::IoPin do_LED_RUN_nBL			= { GPIOC,	GPIO_PIN_6,		GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF2_TIM3,		ALX_NULL	};
						Alx::AlxIoPin::IoPin do_LED_RUN_nGR			= { GPIOC,	GPIO_PIN_7,		GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF2_TIM3,		ALX_NULL	};
						Alx::AlxIoPin::IoPin do_LED_RUN_nGR_Assert	= { GPIOC,	GPIO_PIN_7,		GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			true		};
						Alx::AlxIoPin::IoPin do_LED_RUN_nRD			= { GPIOC,	GPIO_PIN_8,		GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF2_TIM3,		ALX_NULL	};
						// PC9 - Unused
						Alx::AlxIoPin::IoPin di_HW_ID0				= { GPIOC,	GPIO_PIN_10,	GPIO_MODE_INPUT,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};
						Alx::AlxIoPin::IoPin di_HW_ID1				= { GPIOC,	GPIO_PIN_11,	GPIO_MODE_INPUT,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};
						Alx::AlxIoPin::IoPin di_HW_ID2				= { GPIOC,	GPIO_PIN_12,	GPIO_MODE_INPUT,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};
						Alx::AlxIoPin::IoPin do_SPK_AMP_nRESET		= { GPIOC,	GPIO_PIN_13,	GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			false		};	// Speaker Amp disabled
						Alx::AlxIoPin::IoPin di_SPK_AMP_nFAULT		= { GPIOC,	GPIO_PIN_14,	GPIO_MODE_INPUT,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};
						Alx::AlxIoPin::IoPin di_SPK_AMP_nCLIP_OTW	= { GPIOC,	GPIO_PIN_15,	GPIO_MODE_INPUT,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};


						//******************************************************************************
						// Port D
						//******************************************************************************
						Alx::AlxIoPin::IoPin do_FLASH_nRESET		= { GPIOD,	GPIO_PIN_0,		GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			false		};	// Flash reset asserted
						Alx::AlxIoPin::IoPin do_FLASH_nWP			= { GPIOD,	GPIO_PIN_1,		GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			false		};	// Flash WP asserted
						Alx::AlxIoPin::IoPin do_FLASH_nHOLD			= { GPIOD,	GPIO_PIN_2,		GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			true		};	// Flash HOLD de-asserted
						Alx::AlxIoPin::IoPin do_FLASH_SPI_nCS		= { GPIOD,	GPIO_PIN_3,		GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			true		};	// Flash CS de-asserted
						Alx::AlxIoPin::IoPin do_RS485_DIR			= { GPIOD,	GPIO_PIN_4,		GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			false		};	// RS485 RX Enabled
						Alx::AlxIoPin::IoPin do_RS485_UART_TX		= { GPIOD,	GPIO_PIN_5,		GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF7_USART2,	ALX_NULL	};
						Alx::AlxIoPin::IoPin di_RS485_UART_RX		= { GPIOD,	GPIO_PIN_6,		GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF7_USART2,	ALX_NULL	};
						Alx::AlxIoPin::IoPin do_11V_EN				= { GPIOD,	GPIO_PIN_7,		GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			false		};	// 11V disabled
						// PD8 - Unused
						Alx::AlxIoPin::IoPin do_HORN_nEN			= { GPIOD,	GPIO_PIN_9,		GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			false		};	// HORN enabled
						// PD10 - Unused
						// PD11 - Unused
						Alx::AlxIoPin::IoPin do_LED_ERR_nBL			= { GPIOD,	GPIO_PIN_12,	GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF2_TIM3,		ALX_NULL	};
						Alx::AlxIoPin::IoPin do_LED_ERR_nGR			= { GPIOD,	GPIO_PIN_13,	GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF2_TIM3,		ALX_NULL	};
						Alx::AlxIoPin::IoPin do_LED_ERR_nRD			= { GPIOD,	GPIO_PIN_14,	GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF2_TIM3,		ALX_NULL	};
						Alx::AlxIoPin::IoPin do_LED_ERR_nRD_Assert	= { GPIOD,	GPIO_PIN_14,	GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			true		};
						// PD15 - Unused


						//******************************************************************************
						// Port E
						//******************************************************************************
						Alx::AlxIoPin::IoPin di_HS_ST12				= { GPIOE,	GPIO_PIN_0,		GPIO_MODE_INPUT,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};
						Alx::AlxIoPin::IoPin di_HS_ST34				= { GPIOE,	GPIO_PIN_1,		GPIO_MODE_INPUT,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};
						Alx::AlxIoPin::IoPin do_CODEC_I2S_MCLK		= { GPIOE,	GPIO_PIN_2,		GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF6_SAI1,		ALX_NULL	};
						Alx::AlxIoPin::IoPin di_CODEC_I2S_SDI		= { GPIOE,	GPIO_PIN_3,		GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF6_SAI1,		ALX_NULL	};
						Alx::AlxIoPin::IoPin do_CODEC_I2S_LRCLK		= { GPIOE,	GPIO_PIN_4,		GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF6_SAI1,		ALX_NULL	};
						Alx::AlxIoPin::IoPin do_CODEC_I2S_BCLK		= { GPIOE,	GPIO_PIN_5,		GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF6_SAI1,		ALX_NULL	};
						Alx::AlxIoPin::IoPin do_CODEC_I2S_SDO		= { GPIOE,	GPIO_PIN_6,		GPIO_MODE_AF_PP,		GPIO_NOPULL,	GPIO_SPEED_FREQ_HIGH,	GPIO_AF6_SAI1,		ALX_NULL	};
						// PE7 - Unused
						// PE8 - Unused
						// PE9 - Unused
						Alx::AlxIoPin::IoPin di_DIP_S8				= { GPIOE,	GPIO_PIN_10,	GPIO_MODE_INPUT,		GPIO_PULLUP,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};
						Alx::AlxIoPin::IoPin di_DIP_S7				= { GPIOE,	GPIO_PIN_11,	GPIO_MODE_INPUT,		GPIO_PULLUP,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};
						Alx::AlxIoPin::IoPin di_DIP_S6				= { GPIOE,	GPIO_PIN_12,	GPIO_MODE_INPUT,		GPIO_PULLUP,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};
						Alx::AlxIoPin::IoPin di_DIP_S5				= { GPIOE,	GPIO_PIN_13,	GPIO_MODE_INPUT,		GPIO_PULLUP,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};
						Alx::AlxIoPin::IoPin di_DIP_S4				= { GPIOE,	GPIO_PIN_14,	GPIO_MODE_INPUT,		GPIO_PULLUP,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};
						Alx::AlxIoPin::IoPin di_DIP_S3				= { GPIOE,	GPIO_PIN_15,	GPIO_MODE_INPUT,		GPIO_PULLUP,	GPIO_SPEED_FREQ_HIGH,	ALX_NULL,			ALX_NULL	};


						//******************************************************************************
						// Port H
						//******************************************************************************
						// PH0 - HSE Crystal
						// PH0 - HSE Crystal
				} alxIoPin;


				//******************************************************************************
				// ALX - Clock
				//******************************************************************************
				Alx::AlxClk::Clk alxClkObj =
				{
					&alxClk,
					AlxClk_Config_McuStm32F4_Sysclk_180MHz_Pclk1Apb1_45MHz_Pclk2Apb2_90MHz_Hsi_16MHz	// MF: Doesn't Work -> AlxClk_Config_McuStm32F4_Sysclk_180MHz_Pclk1Apb1_45MHz_Pclk2Apb2_90MHz_Hse_12MHz
				};


				//******************************************************************************
				// ALX - Trace
				//******************************************************************************
				Alx::AlxTrace::Trace alxTraceObj =
				{
					&alxTrace,
					GPIOA,
					GPIO_PIN_9,
					GPIO_AF7_USART1,
					USART1,
					AlxGlobal_BaudRate_115200
				};


				//******************************************************************************
				// ALX - Serial Port Debug
				//******************************************************************************
				Alx::AlxSerialPort::SerialPort<8> alxSerialPortDebug = // RX fifo buffer length = 512 bytes
				{
					USART1,
					&alxIoPin.do_DBG_UART_TX,
					&alxIoPin.di_DBG_UART_RX,
					AlxGlobal_BaudRate_115200,
					UART_WORDLENGTH_8B,
					UART_STOPBITS_1,
					UART_PARITY_NONE,
					1000,	// TX timeout_ms
					Alx_IrqPriority_1
				};


				//******************************************************************************
				// ALX - Serial Port RS485
				//******************************************************************************
				Alx::AlxSerialPort::SerialPort<8> alxSerialPortRs485 = // RX fifo buffer length = 512 bytes
				{
					USART2,
					&alxIoPin.do_RS485_UART_TX,
					&alxIoPin.di_RS485_UART_RX,
					AlxGlobal_BaudRate_115200,
					UART_WORDLENGTH_8B,
					UART_STOPBITS_1,
					UART_PARITY_NONE,
					1000, // TX timeout_ms
					Alx_IrqPriority_1
				};


				//******************************************************************************
				// ALX - SPI Flash
				//******************************************************************************
				Alx::AlxSpi::Spi alxSpi =
				{
					SPI2,
					&alxIoPin.do_FLASH_SPI_SCK,
					&alxIoPin.do_FLASH_SPI_MOSI,
					&alxIoPin.di_FLASH_SPI_MISO,
					&alxIoPin.do_FLASH_SPI_nCS,
					AlxSpi_Mode_0,
					&alxClkObj,
					AlxSpi_Clk_McuStm32F4_Spi2_Spi3_SpiClk_1MHz4_Pclk1Apb1_45MHz
				};


				//******************************************************************************
				// ALX - I2C EEPROM
				//******************************************************************************
				Alx::AlxI2c::I2c alxI2cEeprom =
				{
					I2C1,
					&alxIoPin.do_EEPROM_I2C_SCL,
					&alxIoPin.io_EEPROM_I2C_SDA,
					AlxI2c_Clk_400kHz
				};


				//******************************************************************************
				// ALX - I2C Codec
				//******************************************************************************
				Alx::AlxI2c::I2c alxI2cCodec =
				{
					I2C2,
					&alxIoPin.do_CODEC_I2C_SCL,
					&alxIoPin.io_CODEC_I2C_SDA,
					AlxI2c_Clk_400kHz
				};


				//******************************************************************************
				// ALX - I2S Codec
				//******************************************************************************
				Alx::AlxI2s::I2s alxI2sCodec =
				{
					SAI1_Block_A,
					&alxIoPin.do_CODEC_I2S_MCLK,
					&alxIoPin.do_CODEC_I2S_BCLK,
					&alxIoPin.do_CODEC_I2S_LRCLK,
					&alxIoPin.do_CODEC_I2S_SDO,
					&alxIoPin.di_CODEC_I2S_SDI,
					&alxClkObj,
					AlxI2s_Clk_McuStm32F4_SampleFreq_16kHz_SaiClk_49MHz143_MainPllInputClk_2MHz,
					SAI_MODEMASTER_TX,
					SAI_PROTOCOL_DATASIZE_16BIT,
					true,
					Alx_IrqPriority_0
				};


				//******************************************************************************
				// ALX - CAN
				//******************************************************************************
				Alx::AlxCan::Can<512, 512> alxCan = // TX & RX fifo buffer length = 512 messages
				{
					CAN1,
					&alxIoPin.do_CAN_TX,
					&alxIoPin.di_CAN_RX,
					&alxClkObj,
					AlxCan_Clk_McuStm32F4_CanClk_250kbps_Pclk1Apb1_45MHz,
					Alx_IrqPriority_1,
					Alx_IrqPriority_1
				};


				//******************************************************************************
				// ALX - ADC
				//******************************************************************************
				Alx::AlxIoPin::IIoPin* alxAdcIoPinArr[12] =
				{
					&alxIoPin.ai_HORN_SENS,
					&alxIoPin.ai_HORN_PULL_SENS,
					&alxIoPin.ai_5V_SENS,
					&alxIoPin.ai_5V4_SENS,
					&alxIoPin.ai_10V_SENS,
					&alxIoPin.ai_11V_SENS,
					&alxIoPin.ai_48V_SENS,
					&alxIoPin.ai_PWR_RAW_SENS,
					&alxIoPin.ai_DIN_SENS,
					&alxIoPin.ai_NTC_SENS,
					&alxIoPin.ai_MIC1_PTT_SENS,
					&alxIoPin.ai_MIC2_PTT_SENS,
				};
				Alx_Ch alxAdcChArr[14] =
				{
					Alx_Ch_2,
					Alx_Ch_3,
					Alx_Ch_4,
					Alx_Ch_5,
					Alx_Ch_6,
					Alx_Ch_7,
					Alx_Ch_8,
					Alx_Ch_9,
					Alx_Ch_10,
					Alx_Ch_11,
					Alx_Ch_12,
					Alx_Ch_13,
					Alx_Ch_McuStm32_Vref,
					Alx_Ch_McuStm32_TempSens
				};
				Alx::AlxAdc::Adc alxAdc =
				{
					ADC1,
					alxAdcIoPinArr,
					ALX_ARR_LEN(alxAdcIoPinArr),
					alxAdcChArr,
					ALX_ARR_LEN(alxAdcChArr),
					&alxClkObj,
					AlxAdc_Clk_McuStm32F4_AdcClk_22MHz5_Pclk2Apb2_90MHz,
					ADC_SAMPLETIME_480CYCLES,
					true,		// We will use vrefInt_V
					ALX_NULL	// vrefExt_V not applicable
				};


				//******************************************************************************
				// ALX - PWM LED Run
				//******************************************************************************
				Alx::AlxIoPin::IIoPin* alxPwmLedRunIoPinArr[3] =
				{
					&alxIoPin.do_LED_RUN_nBL,
					&alxIoPin.do_LED_RUN_nGR,
					&alxIoPin.do_LED_RUN_nRD
				};
				Alx_Ch alxPwmLedRunChArr[3] =
				{
					Alx_Ch_1,
					Alx_Ch_2,
					Alx_Ch_3
				};
				float alxPwmLedRunDutyDefaultArr_pct[3]=
				{
					100.f,
					100.f,
					100.f
				};
				Alx::AlxPwm::Pwm alxPwmLedRun =
				{
					TIM3,
					alxPwmLedRunIoPinArr,
					alxPwmLedRunChArr,
					alxPwmLedRunDutyDefaultArr_pct,
					ALX_ARR_LEN(alxPwmLedRunChArr),
					&alxClkObj,
					0,
					0xFFFE
				};


				//******************************************************************************
				// ALX - PWM LED Error
				//******************************************************************************
				Alx::AlxIoPin::IIoPin* alxPwmLedErrIoPinArr[3] =
				{
					&alxIoPin.do_LED_ERR_nBL,
					&alxIoPin.do_LED_ERR_nGR,
					&alxIoPin.do_LED_ERR_nRD
				};
				Alx_Ch alxPwmLedErrChArr[3] =
				{
					Alx_Ch_1,
					Alx_Ch_2,
					Alx_Ch_3
				};
				float alxPwmLedErrDutyDefaultArr_pct[3] =
				{
					100.f,
					100.f,
					100.f
				};
				Alx::AlxPwm::Pwm alxPwmLedErr =
				{
					TIM4,
					alxPwmLedErrIoPinArr,
					alxPwmLedErrChArr,
					alxPwmLedErrDutyDefaultArr_pct,
					ALX_ARR_LEN(alxPwmLedErrChArr),
					&alxClkObj,
					0,
					0xFFFE
				};


				//******************************************************************************
				// ALX - ID
				//******************************************************************************
				AlxId_HwInstance alxHwInstanceKnownArr[5] =
				{
					//******************************************************************************
					// ID = 0
					//******************************************************************************
					{
						0,									// id

						"EMI-09-AF-001-1 // 2-118-01X1",	// pcbArtf
						"PAS100/200",						// pcbName
						0,									// pcbVerMajor
						1,									// pcbVerMinor
						0,									// pcbVerPatch
						2012231500,							// pcbVerDate
						0,									// pcbVer - Will be calculated by AlxId

						"EMI-09-AF-001-2 // 2-118-02X1",	// bomArtf
						"PAS100/200",						// bomName
						0,									// bomVerMajor
						1,									// bomVerMinor
						0,									// bomVerPatch
						2012231500,							// bomVerDate
						0,									// bomVer- Will be calculated by AlxId
					},
					//******************************************************************************
					// ID = 1
					//******************************************************************************
					{
						1,									// id

						"EMI-09-AF-002-1 // 2-118-01V1",	// pcbArtf
						"PAS200(100)",						// pcbName
						0,									// pcbVerMajor
						1,									// pcbVerMinor
						1,									// pcbVerPatch
						2102111700,							// pcbVerDate
						0,									// pcbVer - Will be calculated by AlxId

						"EMI-09-AF-002-2 // 2-118-02V1",	// bomArtf
						"PAS100_S",							// bomName
						0,									// bomVerMajor
						1,									// bomVerMinor
						1,									// bomVerPatch
						2103042100,							// bomVerDate
						0									// bomVer- Will be calculated by AlxId
					},
					//******************************************************************************
					// ID = 2
					//******************************************************************************
					{
						2,									// id

						"EMI-09-AF-002-1 // 2-118-01V1",	// pcbArtf
						"PAS200(100)",						// pcbName
						0,									// pcbVerMajor
						1,									// pcbVerMinor
						1,									// pcbVerPatch
						2102111700,							// pcbVerDate
						0,									// pcbVer - Will be calculated by AlxId

						"EMI-09-AF-002-3 // 2-118-03V1",	// bomArtf
						"PAS200_S",							// bomName
						0,									// bomVerMajor
						1,									// bomVerMinor
						1,									// bomVerPatch
						2102111700,							// bomVerDate
						0									// bomVer- Will be calculated by AlxId
					},
					//******************************************************************************
					// ID = 3
					//******************************************************************************
					{
						3,									// id

						"EMI-09-AF-002-1 // 2-118-01V1",	// pcbArtf
						"PAS200(100)",						// pcbName
						0,									// pcbVerMajor
						1,									// pcbVerMinor
						1,									// pcbVerPatch
						2102111700,							// pcbVerDate
						0,									// pcbVer - Will be calculated by AlxId

						"EMI-09-AF-002-4 // 2-118-06V1",	// bomArtf
						"PAS100_F",							// bomName
						0,									// bomVerMajor
						1,									// bomVerMinor
						1,									// bomVerPatch
						2103042100,							// bomVerDate
						0									// bomVer- Will be calculated by AlxId
					},
					//******************************************************************************
					// ID = 4
					//******************************************************************************
					{
						4,									// id

						"EMI-09-AF-002-1 // 2-118-01V1",	// pcbArtf
						"PAS200(100)",						// pcbName
						0,									// pcbVerMajor
						1,									// pcbVerMinor
						1,									// pcbVerPatch
						2102111700,							// pcbVerDate
						0,									// pcbVer - Will be calculated by AlxId

						"EMI-09-AF-002-5 // 2-118-07V1",	// bomArtf
						"PAS200_F",							// bomName
						0,									// bomVerMajor
						1,									// bomVerMinor
						1,									// bomVerPatch
						2102111700,							// bomVerDate
						0									// bomVer- Will be calculated by AlxId
					},
				};
				uint8_t alxHwInstanceHwIdSupportedArr[3] =
				{
					0,
					1,
					2
				};
				Alx::AlxIoPin::IIoPin* alxHwIdIoPinArr[3] =
				{
					&alxIoPin.di_HW_ID0,
					&alxIoPin.di_HW_ID1,
					&alxIoPin.di_HW_ID2
				};
				Alx::AlxId::Id alxId =
				{
					"EMI-09-AF-006-3",							// swAppArtf
					"PAS200(100)",								// swAppName
					0,											// swAppVerMajor
					1,											// swAppVerMinor
					0,											// swAppVerPatch
					false,										// swAppIsBuildJobUsed
					false,										// swIsBootloader
					alxHwInstanceKnownArr,
					ALX_ARR_LEN(alxHwInstanceKnownArr),
					alxHwInstanceHwIdSupportedArr,
					ALX_ARR_LEN(alxHwInstanceHwIdSupportedArr),
					alxHwIdIoPinArr,
					ALX_ARR_LEN(alxHwIdIoPinArr),
					"STM32F427VI // STM32F437VI"				// hwMcuName
				};


				//******************************************************************************
				// ALX - Temperature Sensor RTD - Linear Interpolation
				//******************************************************************************
				Alx::AlxInterpLin::InterpLin alxTemSensRtdInterpLin =
				{
					(float*) alxNtcg103jf103ft1s.xPointRes_kOhm,
					(float*) alxNtcg103jf103ft1s.yPointTemp_degC,
					alxNtcg103jf103ft1s.numOfPoints,
					false,
				};


				//******************************************************************************
				// ALX - Temperature Sensor RTD
				//******************************************************************************
				Alx::AlxTempSens::TempSensRtd alxTempSensRtd =
				{
					&alxAdc,
					&alxTemSensRtdInterpLin,
					Alx_Ch_McuStm32_Vref,
					Alx_Ch_11,
					true,			// Other resistor is
					10				// Resistor Other
				};


				//******************************************************************************
				// ALX - Audio Codec ADAU1961
				//******************************************************************************
				Alx::AlxAdau1961::Adau1961 alxAdau1961 =
				{
					&alxI2sCodec,
					&alxI2cCodec,
					0x70,		// i2cAddr,
					true,		// i2cCheckWithRead,
					3,			// i2cNumOfTries,
					1000		// i2cTimeout_ms
				};


				//******************************************************************************
				// ALX - HighSide Switch BTS724G - Out 1
				//******************************************************************************
				Alx::AlxBts724g::Bts724g alxBts724g_Out1 =
				{
					&alxIoPin.do_HS_IN1,
					&alxIoPin.di_HS_ST12
				};


				//******************************************************************************
				// ALX - HighSide Switch BTS724G - Out 2
				//******************************************************************************
				Alx::AlxBts724g::Bts724g alxBts724g_Out2 =
				{
					&alxIoPin.do_HS_IN2,
					&alxIoPin.di_HS_ST34
				};


				//******************************************************************************
				// ALX - Speaker Amplifier TPA3255
				//******************************************************************************
				Alx::AlxTpa3255::Tpa3255 alxTpa3255 =
				{
					&alxIoPin.do_SPK_AMP_nRESET,
					&alxIoPin.di_SPK_AMP_nFAULT,
					&alxIoPin.di_SPK_AMP_nCLIP_OTW,
					2000	// waitTime_ReEnable_ms
				};
		};

		extern Main main;

	}
}

#endif // #if defined(ALX_HW_NUCLEO_F429ZI_CPP_TEST)

#endif // ALX_HW_NUCLEO_F429ZI_MAIN_HPP
