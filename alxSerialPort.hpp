/**
  ******************************************************************************
  * @file alxSerialPort.hpp
  * @brief Auralix C++ Library - ALX Serial Port Module
  * @version $LastChangedRevision: 4271 $
  * @date $LastChangedDate: 2021-03-05 19:03:28 +0100 (Fri, 05 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_SERIAL_PORT_HPP
#define ALX_SERIAL_PORT_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxSerialPort.h>
#include <alxIoPin.hpp>
#include <alxFifo.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxSerialPort
	{
		class ISerialPort
		{
			public:
				ISerialPort() {};
				virtual ~ISerialPort() {};
				virtual ::Alx_Status Init(void) = 0;
				virtual ::Alx_Status DeInit(void) = 0;
				virtual ::Alx_Status Read(uint8_t* data, uint32_t len) = 0;
				virtual ::Alx_Status ReadStrUntil(char* str, const char* delim, uint32_t maxLen, uint32_t* numRead) = 0;
				virtual ::Alx_Status Write(uint8_t data) = 0;
				virtual ::Alx_Status Write(const uint8_t* data, uint32_t len) = 0;
				virtual ::Alx_Status WriteStr(const char* str) = 0;
				virtual void Foreground_Handle(void) = 0;
		};
		
		template <uint32_t rxFifoBuffLen>
		class ASerialPort : public ISerialPort
		{
			public:
				ASerialPort() {};
				virtual ~ASerialPort() {};
				::Alx_Status Init(void) override
				{
					return AlxSerialPort_Init(&me);
				}
				::Alx_Status DeInit(void) override
				{
					return AlxSerialPort_DeInit(&me);
				}
				::Alx_Status Read(uint8_t* data, uint32_t len) override
				{
					return AlxSerialPort_Read(&me, data, len);
				}
				::Alx_Status ReadStrUntil(char* str, const char* delim, uint32_t maxLen, uint32_t* numRead) override
				{
					return AlxSerialPort_ReadStrUntil(&me, str, delim, maxLen, numRead);
				}
				::Alx_Status Write(uint8_t data) override
				{
					return AlxSerialPort_Write(&me, data);
				}
				::Alx_Status Write(const uint8_t* data, uint32_t len) override
				{
					return AlxSerialPort_WriteMulti(&me, data, len);
				}
				::Alx_Status WriteStr(const char* str) override
				{
					return AlxSerialPort_WriteStr(&me, str);
				}
				void Foreground_Handle(void) override
				{
					AlxSerialPort_Foreground_Handle(&me);
				}
			protected:
				::AlxSerialPort me = {};
				AlxFifo::Fifo<rxFifoBuffLen> rxFifo = {};
		};
		
		#if defined(ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)
		template <uint32_t rxFifoBuffLen>
		class SerialPort : public ASerialPort <rxFifoBuffLen>
		{
			public:
				SerialPort
				(
					USART_TypeDef* uart,
					AlxIoPin::IIoPin* do_TX,
					AlxIoPin::IIoPin* di_RX,
					AlxGlobal_BaudRate baudRate,
					uint32_t dataWidth,
					uint32_t stopBits,
					uint32_t parity,
					uint16_t txTimeout_ms,
					Alx_IrqPriority rxIrqPriority
				) : ASerialPort<rxFifoBuffLen>()
				{
					AlxSerialPort_Ctor
					(
						&this->me,
						uart,
						do_TX->GetCStructPtr(),
						di_RX->GetCStructPtr(),
						baudRate,
						dataWidth,
						stopBits,
						parity,
						txTimeout_ms,
						this->rxFifo.GetBuffPtr(),
						rxFifoBuffLen,
						rxIrqPriority
					 );
				};
				virtual ~SerialPort() {};
		};
		#endif
		
		#if defined (ALX_GTEST_TODO)
		class MockSerialPort final : public ISerialPort
		{
			public:
				MOCK_METHOD(::Alx_Status, Init, (), (override));
				MOCK_METHOD(::Alx_Status, DeInit, (), (override));
				MOCK_METHOD(::Alx_Status, Read, (uint8_t* data, uint32_t len), (override));
				MOCK_METHOD(::Alx_Status, ReadStrUntil, (char* str, const char* delim, uint32_t maxLen, uint32_t* numRead), (override));
				MOCK_METHOD(::Alx_Status, Write, (uint8_t data), (override));
				MOCK_METHOD(::Alx_Status, Write, (const uint8_t* data, uint32_t len), (override));
				MOCK_METHOD(::Alx_Status, WriteStr, (const char* str), (override));
				MOCK_METHOD(::Alx_Status, Foreground_Handle, (), (override));
		};
		#endif
	}
}

#endif // ALX_SERIAL_PORT_HPP
