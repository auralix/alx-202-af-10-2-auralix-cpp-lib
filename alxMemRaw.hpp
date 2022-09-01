/**
  ******************************************************************************
  * @file		alxMemRaw.hpp
  * @brief		Auralix C++ Library - ALX Memory Raw Module
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
#ifndef ALX_MEM_RAW_HPP
#define ALX_MEM_RAW_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxMemRaw.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxMemRaw
	{
		class IMemRaw
		{
			public:
				IMemRaw() {};
				virtual ~IMemRaw() {};
				virtual ::Alx_Status Init(void) = 0;
				virtual ::Alx_Status DeInit(void) = 0;
				virtual ::Alx_Status Read(uint32_t addr, uint8_t* data, uint32_t len, uint8_t numOfTries, uint16_t timeout_ms) = 0;
				virtual ::Alx_Status Write(uint32_t addr, uint8_t* data, uint32_t len, bool checkWithReadEnable, uint8_t numOfTries, uint16_t timeout_ms) = 0;
				virtual ::AlxMemRaw* GetCStructPtr(void) = 0;
		};
		class MemRaw : public IMemRaw
		{
			public:
				MemRaw()
				{
					AlxMemRaw_Ctor(&me);
				};
				virtual ~MemRaw() {};
				::Alx_Status Init(void) override																											{ return AlxMemRaw_Init(&me); }
				::Alx_Status DeInit(void) override																											{ return AlxMemRaw_DeInit(&me); }
				::Alx_Status Read(uint32_t addr, uint8_t* data, uint32_t len, uint8_t numOfTries, uint16_t timeout_ms) override								{ return AlxMemRaw_Read(&me, addr, data, len, numOfTries, timeout_ms); }
				::Alx_Status Write(uint32_t addr, uint8_t* data, uint32_t len, bool checkWithReadEnable, uint8_t numOfTries, uint16_t timeout_ms) override	{ return AlxMemRaw_Write(&me, addr, data, len, checkWithReadEnable, numOfTries, timeout_ms); }
				::AlxMemRaw* GetCStructPtr(void) override																									{ return &me; }
			protected:
				::AlxMemRaw me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_MEM_RAW_HPP
