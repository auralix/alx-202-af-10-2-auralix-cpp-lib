/**
  ******************************************************************************
  * @file alxSpi.hpp
  * @brief Auralix C++ Library - ALX SPI Module
  * @version $LastChangedRevision: 5451 $
  * @date $LastChangedDate: 2021-06-18 23:31:45 +0200 (Fri, 18 Jun 2021) $
  ******************************************************************************
  */

#ifndef ALX_SPI_HPP
#define ALX_SPI_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxSpi.h>
#include <alxIoPin.hpp>
#include <alxClk.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxSpi
	{
		class ISpi
		{
			public:
				ISpi() {};
				virtual ~ISpi() {};
				virtual ::Alx_Status Init(void) = 0;
				virtual ::Alx_Status DeInit(void) = 0;
				virtual ::Alx_Status Master_WriteRead(uint8_t* writeData, uint8_t* readData, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) = 0;
				virtual ::Alx_Status Master_Write(uint8_t* writeData, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) = 0;
				virtual ::Alx_Status Master_Read(uint8_t* readData, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) = 0;
				virtual void Master_AssertCs(void) = 0;
				virtual void Master_DeAssertCs(void) = 0;
				virtual ::AlxSpi* GetCStructPtr(void) = 0;
		};
		class ASpi : public ISpi
		{
			public:
				ASpi() {};
				virtual ~ASpi() {};
				::Alx_Status Init(void) override
				{
					return AlxSpi_Init(&me);
				}
				::Alx_Status DeInit(void) override
				{
					return AlxSpi_DeInit(&me);
				}
				::Alx_Status Master_WriteRead(uint8_t* writeData, uint8_t* readData, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) override
				{
					return AlxSpi_Master_WriteRead(&me, writeData, readData, len, numOfTries, timeout_ms);
				}
				::Alx_Status Master_Write(uint8_t* writeData, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) override
				{
					return AlxSpi_Master_Write(&me, writeData, len, numOfTries, timeout_ms);
				}
				::Alx_Status Master_Read(uint8_t* readData, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) override
				{
					return AlxSpi_Master_Read(&me, readData, len, numOfTries, timeout_ms);
				}
				void Master_AssertCs(void) override
				{
					AlxSpi_Master_AssertCs(&me);
				}
				void Master_DeAssertCs(void) override
				{
					AlxSpi_Master_DeAssertCs(&me);
				}
				::AlxSpi* GetCStructPtr(void) override
				{
					return &me;
				}
			protected:
				::AlxSpi me = {};
		};
		#if defined(ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)
		class Spi : public ASpi
		{
			public:
				Spi
				(
					SPI_TypeDef* spi,
					AlxIoPin::IIoPin* do_SCK,
					AlxIoPin::IIoPin* do_MOSI,
					AlxIoPin::IIoPin* di_MISO,
					AlxIoPin::IIoPin* do_nCS,
					AlxSpi_Mode mode,
					AlxClk::IClk* clk,
					AlxSpi_Clk spiClk
				)
				{
					AlxSpi_Ctor
					(
						&me,
						spi,
						do_SCK->GetCStructPtr(),
						do_MOSI->GetCStructPtr(),
						di_MISO->GetCStructPtr(),
						do_nCS->GetCStructPtr(),
						mode,
						clk->GetCStructPtr(),
						spiClk
					);
				};
				virtual ~Spi() {};
		};
		#endif
		#if defined (ALX_GTEST)
		class MockSpi final : public ISpi
		{
			public:
				MOCK_METHOD(::Alx_Status, Init,				(), (override));
				MOCK_METHOD(::Alx_Status, DeInit,			(), (override));
				MOCK_METHOD(::Alx_Status, Master_WriteRead,	(const uint8_t* writeData, uint8_t* readData, uint16_t len, uint8_t numOfTries, uint16_t timeout_ms), (override));
				MOCK_METHOD(void, Master_AssertCs,			(), (override));
				MOCK_METHOD(void, Master_DeAssertCs,		(), (override));
		};
		#endif
	}
}

#endif // ALX_SPI_HPP
