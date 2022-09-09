/**
  ******************************************************************************
  * @file		alxMemSafe.hpp
  * @brief		Auralix C++ Library - ALX Memory Safe Module
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
#ifndef ALX_MEM_SAFE_HPP
#define ALX_MEM_SAFE_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxMemSafe.h"
#include "alxCrc.hpp"
#include "alxMemRaw.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxMemSafe
	{
		//******************************************************************************
		// Class - IMemSafe
		//******************************************************************************
		class IMemSafe
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IMemSafe() {}
				virtual ~IMemSafe() {}
				virtual ::Alx_Status Read(uint8_t* data, uint32_t len) = 0;
				virtual ::Alx_Status Write(uint8_t* data, uint32_t len) = 0;
				virtual bool IsReadDone(void) = 0;
				virtual bool IsReadErr(void) = 0;
				virtual bool IsWriteDone(void) = 0;
				virtual bool IsWriteErr(void) = 0;
				virtual ::AlxMemSafe* GetCStructPtr(void) = 0;
		};


		//******************************************************************************
		// Class - MemSafe
		//******************************************************************************
		template <uint32_t buff1Len, uint32_t buff2Len>
		class MemSafe : public IMemSafe
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				MemSafe
				(
					AlxMemRaw::MemRaw* memRaw,
					AlxCrc::Crc* crc,
					uint32_t copyAddrA,
					uint32_t copyAddrB,
					uint32_t copyLen,
					bool nonBlockingEnable,
					uint8_t memSafeReadWriteNumOfTries,
					uint8_t memRawReadWriteNumOfTries,
					uint16_t memRawReadWriteTimeout_ms
				)
				{
					AlxMemSafe_Ctor
					(
						&me,
						memRaw->GetCStructPtr(),
						crc->GetCStructPtr(),
						copyAddrA,
						copyAddrB,
						copyLen,
						nonBlockingEnable,
						memSafeReadWriteNumOfTries,
						memRawReadWriteNumOfTries,
						memRawReadWriteTimeout_ms,
						buff1,
						buff1Len,
						buff2,
						buff2Len
					);
				}
				virtual ~MemSafe() {}
				::Alx_Status Read(uint8_t* data, uint32_t len) override
				{
					return AlxMemSafe_Read(&me, data, len);
				}
				::Alx_Status Write(uint8_t* data, uint32_t len) override
				{
					return AlxMemSafe_Write(&me, data, len);
				}
				bool IsReadDone(void) override
				{
					return AlxMemSafe_IsReadDone(&me);
				}
				bool IsReadErr(void) override
				{
					return AlxMemSafe_IsReadErr(&me);
				}
				bool IsWriteDone(void) override
				{
					return AlxMemSafe_IsWriteDone(&me);
				}
				bool IsWriteErr(void) override
				{
					return AlxMemSafe_IsWriteErr(&me);
				}
				::AlxMemSafe* GetCStructPtr(void) override
				{
					return &me;
				}
			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxMemSafe me = {};
				uint8_t buff1[buff1Len] ={};
				uint8_t buff2[buff2Len] ={};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_MEM_SAFE_HPP
