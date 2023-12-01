/**
  ******************************************************************************
  * @file		alxI2c.hpp
  * @brief		Auralix C++ Library - ALX I2C Module
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
#ifndef ALX_I2C_HPP
#define ALX_I2C_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxI2c.h"
#include "alxIoPin.hpp"
#include "alxClk.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxI2c
	{
		//******************************************************************************
		// Class - II2c
		//******************************************************************************
		class II2c
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				II2c() {}
				virtual ~II2c() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual Alx_Status Master_StartRead(uint16_t slaveAddr, uint8_t* data, uint16_t len = 1, uint16_t timeout_ms = 10) = 0;
				virtual Alx_Status Master_StartReadStop(uint16_t slaveAddr, uint8_t* data, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) = 0;
				virtual Alx_Status Master_StartReadMemStop(uint16_t slaveAddr, uint16_t memAddr, AlxI2c_Master_MemAddrLen memAddrLen, uint8_t* data, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) = 0;
				virtual Alx_Status Master_StartWrite(uint16_t slaveAddr, const uint8_t* data, uint16_t len = 1, uint16_t timeout_ms = 10) = 0;
				virtual Alx_Status Master_StartWriteStop(uint16_t slaveAddr, const uint8_t* data, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) = 0;
				virtual Alx_Status Master_StartWriteMemStop(uint16_t slaveAddr, uint16_t memAddr, AlxI2c_Master_MemAddrLen memAddrLen, uint8_t data, bool checkWithRead = false, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) = 0;
				virtual Alx_Status Master_StartWriteMemStop(uint16_t slaveAddr, uint16_t memAddr, AlxI2c_Master_MemAddrLen memAddrLen, const uint8_t* data, uint16_t len, bool checkWithRead = false, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) = 0;
				virtual Alx_Status Master_Stop(uint16_t timeout_ms = 10) = 0;
				virtual Alx_Status Master_IsSlaveReady(uint16_t slaveAddr, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) = 0;
				virtual ::AlxI2c* GetCStructPtr(void) = 0;
		};


		//******************************************************************************
		// Class - AI2c
		//******************************************************************************
		class AI2c : public II2c
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				AI2c() {}
				virtual ~AI2c() {}
				Alx_Status Init(void) override
				{
					return AlxI2c_Init(&me);
				}
				Alx_Status DeInit(void) override
				{
					return AlxI2c_DeInit(&me);
				}
				Alx_Status Master_StartRead(uint16_t slaveAddr, uint8_t* data, uint16_t len = 1, uint16_t timeout_ms = 10) override
				{
					return AlxI2c_Master_StartRead(&me, slaveAddr, data, len, timeout_ms);
				}
				Alx_Status Master_StartReadStop(uint16_t slaveAddr, uint8_t* data, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) override
				{
					return AlxI2c_Master_StartReadStop(&me, slaveAddr, data, len, numOfTries, timeout_ms);
				}
				Alx_Status Master_StartReadMemStop(uint16_t slaveAddr, uint16_t memAddr, AlxI2c_Master_MemAddrLen memAddrLen, uint8_t* data, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) override
				{
					return AlxI2c_Master_StartReadMemStop(&me, slaveAddr, memAddr, memAddrLen, data, len, numOfTries, timeout_ms);
				}
				Alx_Status Master_StartWrite(uint16_t slaveAddr, const uint8_t* data, uint16_t len = 1, uint16_t timeout_ms = 10) override
				{
					return AlxI2c_Master_StartWrite(&me, slaveAddr, data, len, timeout_ms);
				}
				Alx_Status Master_StartWriteStop(uint16_t slaveAddr, const uint8_t* data, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) override
				{
					return AlxI2c_Master_StartWriteStop(&me, slaveAddr, data, len, numOfTries, timeout_ms);
				}
				Alx_Status Master_StartWriteMemStop(uint16_t slaveAddr, uint16_t memAddr, AlxI2c_Master_MemAddrLen memAddrLen, uint8_t data, bool checkWithRead = false, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) override
				{
					return AlxI2c_Master_StartWriteMemStop_Single(&me, slaveAddr, memAddr, memAddrLen, data, checkWithRead, numOfTries, timeout_ms);
				}
				Alx_Status Master_StartWriteMemStop(uint16_t slaveAddr, uint16_t memAddr, AlxI2c_Master_MemAddrLen memAddrLen, const uint8_t* data, uint16_t len, bool checkWithRead = false, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) override
				{
					return AlxI2c_Master_StartWriteMemStop_Multi(&me, slaveAddr, memAddr, memAddrLen, data, len, checkWithRead, numOfTries, timeout_ms);
				}
				Alx_Status Master_Stop(uint16_t timeout_ms = 10) override
				{
					return AlxI2c_Master_Stop(&me, timeout_ms);
				}
				Alx_Status Master_IsSlaveReady(uint16_t slaveAddr, uint8_t numOfTries = 3, uint16_t timeout_ms = 10)override
				{
					return AlxI2c_Master_IsSlaveReady(&me, slaveAddr, numOfTries, timeout_ms);
				}
				::AlxI2c* GetCStructPtr(void) override
				{
					return &me;
				}

			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxI2c me = {};
		};


		//******************************************************************************
		// Class - I2c
		//******************************************************************************
		#if defined(ALX_STM32F0) || defined(ALX_STM32F4) || defined(ALX_STM32F7) || defined(ALX_STM32G4) || defined(ALX_STM32L0) || defined(ALX_STM32L4) || defined(ALX_STM32U5)
		class I2c : public AI2c
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				I2c
				(
					I2C_TypeDef* i2c,
					AlxIoPin::IIoPin* io_SCL,
					AlxIoPin::IIoPin* io_SDA,
					AlxClk::IClk* clk,
					AlxI2c_Clk i2cClk
				)
				{
					AlxI2c_Ctor
					(
						&me,
						i2c,
						io_SCL->GetCStructPtr(),
						io_SDA->GetCStructPtr(),
						clk->GetCStructPtr(),
						i2cClk
					);
				}
				virtual ~I2c() {}
		};
		#endif


		//******************************************************************************
		// Class - MockI2c
		//******************************************************************************
		#if defined(ALX_GTEST)
		class MockI2c : public II2c
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				MOCK_METHOD(void, Init, (), (override));
				MOCK_METHOD(void, DeInit, (), (override));
				MOCK_METHOD(Alx_Status, Master_StartRead, (uint16_t slvAddr, uint8_t* data, uint16_t len, uint16_t timeout_ms), (override));
				MOCK_METHOD(Alx_Status, Master_StartReadStop, (uint16_t slvAddr, uint8_t* data, uint16_t len, uint8_t numOfTries, uint16_t timeout_ms), (override));
				MOCK_METHOD(Alx_Status, Master_StartReadMemStop, (uint16_t slvAddr, uint16_t memAddr, AlxI2c_Master_MemAddrLen memAddrLen, uint8_t* data, uint16_t len, uint8_t numOfTries, uint16_t timeout_ms), (override));
				MOCK_METHOD(Alx_Status, Master_StartWrite, (uint16_t slvAddr, const uint8_t* data, uint16_t len, uint16_t timeout_ms), (override));
				MOCK_METHOD(Alx_Status, Master_StartWriteStop, (uint16_t slvAddr, const uint8_t* data, uint16_t len, uint8_t numOfTries, uint16_t timeout_ms), (override));
				MOCK_METHOD(Alx_Status, Master_StartWriteMemStop, (uint16_t slvAddr, uint16_t memAddr, AlxI2c_Master_MemAddrLen memAddrLen, uint8_t data, bool checkWithRead, uint8_t numOfTries, uint16_t timeout_ms), (override));
				MOCK_METHOD(Alx_Status, Master_StartWriteMemStop, (uint16_t slvAddr, uint16_t memAddr, AlxI2c_Master_MemAddrLen memAddrLen, const uint8_t* data, uint16_t len, bool checkWithRead, uint8_t numOfTries, uint16_t timeout_ms), (override));
				MOCK_METHOD(Alx_Status, Master_Stop, (uint16_t timeout_ms), (override));
				MOCK_METHOD(Alx_Status, Master_IsSlaveReady, (uint16_t slvAddr, uint8_t numOfTries, uint16_t timeout_ms), (override));
		};
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_I2C_HPP
