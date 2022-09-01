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
#ifndef ALX_I2C_HPP
#define ALX_I2C_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxI2c.h"
#include "alxIoPin.hpp"


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxI2c
	{
		class II2c
		{
			public:
				II2c() {};
				virtual ~II2c() {};
				virtual void Init (void) = 0;
				virtual void DeInit	(void) = 0;
				virtual ::Alx_Status Master_StartRead			(uint16_t slaveAddr, uint8_t* data, uint16_t len = 1, uint16_t timeout_ms = 10)																													= 0;
				virtual ::Alx_Status Master_StartReadStop		(uint16_t slaveAddr, uint8_t* data, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10)																							= 0;
				virtual ::Alx_Status Master_StartReadMemStop	(uint16_t slaveAddr, uint16_t memAddr, ::AlxI2c_Master_MemAddrLen memAddrLen, uint8_t* data, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10)								= 0;
				virtual ::Alx_Status Master_StartWrite			(uint16_t slaveAddr, const uint8_t* data, uint16_t len = 1, uint16_t timeout_ms = 10)																											= 0;
				virtual ::Alx_Status Master_StartWriteStop		(uint16_t slaveAddr, const uint8_t* data, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10)																					= 0;
				virtual ::Alx_Status Master_StartWriteMemStop	(uint16_t slaveAddr, uint16_t memAddr, ::AlxI2c_Master_MemAddrLen memAddrLen, uint8_t data, bool checkWithRead = false, uint8_t numOfTries = 3, uint16_t timeout_ms = 10)						= 0;
				virtual ::Alx_Status Master_StartWriteMemStop	(uint16_t slaveAddr, uint16_t memAddr, ::AlxI2c_Master_MemAddrLen memAddrLen, const uint8_t* data, uint16_t len, bool checkWithRead = false, uint8_t numOfTries = 3, uint16_t timeout_ms = 10)	= 0;
				virtual ::Alx_Status Master_Stop				(uint16_t timeout_ms = 10)																																										= 0;
				virtual ::Alx_Status Master_IsSlaveReady		(uint16_t slaveAddr, uint8_t numOfTries = 3, uint16_t timeout_ms = 10)																															= 0;
				virtual ::AlxI2c* GetCStructPtr					(void)																																															= 0;
		};
		class AI2c : public II2c
		{
			public:
				AI2c() {};
				virtual ~AI2c() {};
				void Init(void) override
				{
					AlxI2c_Init(&me);
				}
				void DeInit(void) override
				{
					AlxI2c_DeInit(&me);
				}
				::Alx_Status Master_StartRead(uint16_t slaveAddr, uint8_t* data, uint16_t len = 1, uint16_t timeout_ms = 10) override
				{
					return AlxI2c_Master_StartRead(&me, slaveAddr, data, len, timeout_ms);
				}
				::Alx_Status Master_StartReadStop(uint16_t slaveAddr, uint8_t* data, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) override
				{
					return AlxI2c_Master_StartReadStop(&me, slaveAddr, data, len, numOfTries, timeout_ms);
				}
				::Alx_Status Master_StartReadMemStop(uint16_t slaveAddr, uint16_t memAddr, ::AlxI2c_Master_MemAddrLen memAddrLen, uint8_t* data, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) override
				{
					return AlxI2c_Master_StartReadMemStop(&me, slaveAddr, memAddr, memAddrLen, data, len, numOfTries, timeout_ms);
				}
				::Alx_Status Master_StartWrite(uint16_t slaveAddr, const uint8_t* data, uint16_t len = 1, uint16_t timeout_ms = 10) override
				{
					return AlxI2c_Master_StartWrite(&me, slaveAddr, data, len, timeout_ms);
				}
				::Alx_Status Master_StartWriteStop(uint16_t slaveAddr, const uint8_t* data, uint16_t len = 1, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) override
				{
					return AlxI2c_Master_StartWriteStop(&me, slaveAddr, data, len, numOfTries, timeout_ms);
				}
				::Alx_Status Master_StartWriteMemStop(uint16_t slaveAddr, uint16_t memAddr, ::AlxI2c_Master_MemAddrLen memAddrLen, uint8_t data, bool checkWithRead = false, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) override
				{
					return AlxI2c_Master_StartWriteMemStop_Single(&me, slaveAddr, memAddr, memAddrLen, data, checkWithRead, numOfTries, timeout_ms);
				}
				::Alx_Status Master_StartWriteMemStop(uint16_t slaveAddr, uint16_t memAddr, ::AlxI2c_Master_MemAddrLen memAddrLen, const uint8_t* data, uint16_t len, bool checkWithRead = false, uint8_t numOfTries = 3, uint16_t timeout_ms = 10) override
				{
					return AlxI2c_Master_StartWriteMemStop_Multi(&me, slaveAddr, memAddr, memAddrLen, data, len, checkWithRead, numOfTries, timeout_ms);
				}
				::Alx_Status Master_Stop(uint16_t timeout_ms = 10) override
				{
					return AlxI2c_Master_Stop(&me, timeout_ms);
				}
				::Alx_Status Master_IsSlaveReady(uint16_t slaveAddr, uint8_t numOfTries = 3, uint16_t timeout_ms = 10)override
				{
					return AlxI2c_Master_IsSlaveReady(&me, slaveAddr, numOfTries, timeout_ms);
				}
				::AlxI2c* GetCStructPtr(void) override
				{
					return &me;
				}
			protected:
				::AlxI2c me = {};
		};
		#if defined(ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)
		class I2c : public AI2c
		{
			public:
				I2c
				(
					I2C_TypeDef* i2c,
					AlxIoPin::IIoPin* io_SCL,
					AlxIoPin::IIoPin* io_SDA,
					::AlxI2c_Clk clk = AlxI2c_Clk_400kHz
				)
				{
					AlxI2c_Ctor(&me, i2c, io_SCL->GetCStructPtr(), io_SDA->GetCStructPtr(), clk);
				};
				virtual ~I2c() {};
		};
		#endif
		#if defined (ALX_GTEST)
		class MockI2c final : public II2c
		{
			public:
				MOCK_METHOD(void, Init,								(), (override));
				MOCK_METHOD(void, DeInit,							(), (override));
				MOCK_METHOD(::Alx_Status, Master_StartRead,			(uint16_t slvAddr, uint8_t* data, uint16_t len, uint16_t timeout_ms), (override));
				MOCK_METHOD(::Alx_Status, Master_StartReadStop,		(uint16_t slvAddr, uint8_t* data, uint16_t len, uint8_t numOfTries, uint16_t timeout_ms), (override));
				MOCK_METHOD(::Alx_Status, Master_StartReadMemStop,	(uint16_t slvAddr, uint16_t memAddr, ::AlxI2c_Master_MemAddrLen memAddrLen, uint8_t* data, uint16_t len, uint8_t numOfTries, uint16_t timeout_ms), (override));
				MOCK_METHOD(::Alx_Status, Master_StartWrite,		(uint16_t slvAddr, const uint8_t* data, uint16_t len, uint16_t timeout_ms), (override));
				MOCK_METHOD(::Alx_Status, Master_StartWriteStop,	(uint16_t slvAddr, const uint8_t* data, uint16_t len, uint8_t numOfTries, uint16_t timeout_ms), (override));
				MOCK_METHOD(::Alx_Status, Master_StartWriteMemStop,	(uint16_t slvAddr, uint16_t memAddr, ::AlxI2c_Master_MemAddrLen memAddrLen, uint8_t data, bool checkWithRead, uint8_t numOfTries, uint16_t timeout_ms), (override));
				MOCK_METHOD(::Alx_Status, Master_StartWriteMemStop,	(uint16_t slvAddr, uint16_t memAddr, ::AlxI2c_Master_MemAddrLen memAddrLen, const uint8_t* data, uint16_t len, bool checkWithRead, uint8_t numOfTries, uint16_t timeout_ms), (override));
				MOCK_METHOD(::Alx_Status, Master_Stop,				(uint16_t timeout_ms), (override));
				MOCK_METHOD(::Alx_Status, Master_IsSlaveReady,		(uint16_t slvAddr, uint8_t numOfTries, uint16_t timeout_ms), (override));
		};
		#endif
	}
}

#endif // ALX_I2C_HPP
