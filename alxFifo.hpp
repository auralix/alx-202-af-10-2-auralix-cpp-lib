/**
  ******************************************************************************
  * @file		alxFifo.hpp
  * @brief		Auralix C++ Library - ALX FIFO Module
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
#ifndef ALX_FIFO_HPP
#define ALX_FIFO_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxFifo.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxFifo
	{
		//******************************************************************************
		// Class - IFifo
		//******************************************************************************
		class IFifo
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IFifo() {}
				virtual ~IFifo() {}
				virtual void Flush(void) = 0;
				virtual Alx_Status Read(uint8_t* data, uint32_t len = 1) = 0;
				virtual Alx_Status ReadStrUntil(char* str, const char* delim, uint32_t maxLen, uint32_t *numRead = nullptr) = 0;
				virtual Alx_Status Write(uint8_t data) = 0;
				virtual Alx_Status Write(const uint8_t* data, uint32_t len) = 0;
				virtual Alx_Status WriteStr(const char* str) = 0;
				virtual uint32_t GetNumOfEntries(void) = 0;
				virtual uint8_t* GetBuffPtr(void) = 0;
		};


		//******************************************************************************
		// Class - Fifo
		//******************************************************************************
		template <uint32_t buffLen>
		class Fifo : public IFifo
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Fifo()
				{
					AlxFifo_Ctor(&me, buff, buffLen);
				}
				Fifo(uint8_t* buffCLib, uint32_t buffLenCLib)
				{
					// Assert
					ALX_FIFO_ASSERT(buffLen == 1);	// TV: If we want to use C lib sytle Ctor, then template argument buffLen must be 1

					// Ctor
					AlxFifo_Ctor(&me, buffCLib, buffLenCLib);
				}
				virtual ~Fifo() {}
				void Flush(void) override
				{
					AlxFifo_Flush(&me);
				}
				Alx_Status Read(uint8_t* data, uint32_t len = 1) override
				{
					return AlxFifo_Read(&me, data, len);
				}
				Alx_Status ReadStrUntil(char* str, const char* delim, uint32_t maxLen, uint32_t *numRead = nullptr) override
				{
					return AlxFifo_ReadStrUntil(&me, str, delim, maxLen, numRead);
				}
				Alx_Status Write(uint8_t data) override
				{
					return AlxFifo_Write(&me, data);
				}
				Alx_Status Write(const uint8_t* data, uint32_t len) override
				{
					return AlxFifo_WriteMulti(&me, data, len);
				}
				Alx_Status WriteStr(const char* str) override
				{
					return AlxFifo_WriteStr(&me, str);
				}
				uint32_t GetNumOfEntries(void) override
				{
					return AlxFifo_GetNumOfEntries(&me);
				}
				uint8_t* GetBuffPtr(void) override
				{
					return (uint8_t*)buff;
				}

			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxFifo me = {};
				uint8_t buff[buffLen] = {};
		};


		//******************************************************************************
		// Class - FifoTest
		//******************************************************************************
		template <uint32_t buffLen>
		class FifoTest : public Fifo <buffLen>
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				FifoTest() : Fifo <buffLen>() {}
				virtual ~FifoTest() {}
				uint32_t GetHead(void)
				{
					return this->me.head;
				}
				uint32_t GetTail(void)
				{
					return this->me.tail;
				}
				bool IsFull(void)
				{
					return this->me.isFull;
				}
				bool IsEmpty(void)
				{
					return this->me.isEmpty;
				}
				uint32_t GetBuffLen(void)
				{
					return this->me.buffLen;
				}
				uint8_t* GetHeadPtr(void)
				{
					return (uint8_t*)this->buff + this->me.head;
				}
				uint8_t* GetTailPtr(void)
				{
					return (uint8_t*)this->buff + this->me.tail;
				}
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_FIFO_HPP
