/**
  ******************************************************************************
  * @file		alxSerialPort.hpp
  * @brief		Auralix C++ Library - ALX Serial Port Module
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
#ifndef ALX_SERIAL_PORT_HPP
#define ALX_SERIAL_PORT_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxSerialPort.h"
#include "alxIoPin.hpp"
#include "alxFifo.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxSerialPort
	{
		//******************************************************************************
		// Class - ISerialPort
		//******************************************************************************
		class ISerialPort
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ISerialPort() {}
				virtual ~ISerialPort() {}
				virtual ::Alx_Status Init(void) = 0;
				virtual ::Alx_Status DeInit(void) = 0;
				virtual ::Alx_Status Read(uint8_t* data, uint32_t len) = 0;
				virtual ::Alx_Status ReadStrUntil(char* str, const char* delim, uint32_t maxLen, uint32_t* numRead) = 0;
				virtual ::Alx_Status Write(uint8_t data) = 0;
				virtual ::Alx_Status Write(const uint8_t* data, uint32_t len) = 0;
				virtual ::Alx_Status WriteStr(const char* str) = 0;
				virtual void Foreground_Handle(void) = 0;
		};


		//******************************************************************************
		// Class - ASerialPort
		//******************************************************************************
		template <uint32_t rxFifoBuffLen>
		class ASerialPort : public ISerialPort
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ASerialPort() {}
				virtual ~ASerialPort() {}
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
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxSerialPort me = {};
				AlxFifo::Fifo<rxFifoBuffLen> rxFifo = {};
		};


		//******************************************************************************
		// Class - SerialPort
		//******************************************************************************
		#if defined(ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)
		template <uint32_t rxFifoBuffLen>
		class SerialPort : public ASerialPort <rxFifoBuffLen>
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
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
				}
				virtual ~SerialPort() {}
		};
		#endif


		//******************************************************************************
		// Class - MockSerialPort
		//******************************************************************************
		#if defined (ALX_GTEST_TODO)
		class MockSerialPort final : public ISerialPort
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
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


#endif	// #if defined(ALX_CPP_LIB)

#endif	// ALX_SERIAL_PORT_HPP
