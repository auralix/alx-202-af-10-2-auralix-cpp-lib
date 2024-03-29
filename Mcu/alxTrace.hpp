﻿/**
  ******************************************************************************
  * @file		alxTrace.hpp
  * @brief		Auralix C++ Library - ALX Trace Module
  * @copyright	Copyright (C) Auralix d.o.o. All rights reserved.
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
#ifndef ALX_TRACE_HPP
#define ALX_TRACE_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxTrace.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxTrace
	{
		//******************************************************************************
		// Class - ITrace
		//******************************************************************************
		class ITrace
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ITrace() {}
				virtual ~ITrace() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual Alx_Status WriteStr(const char* str) = 0;
				virtual void WriteFormat(const char* format, ...) = 0;
				virtual void WriteStd(const char* file, uint32_t line, const char* fun, const char* format, ...) = 0;
				virtual void WriteSm(uint8_t smLevel, const char* smName, const char* stName, const char* acName) = 0;
		};


		//******************************************************************************
		// Class - ATrace
		//******************************************************************************
		class ATrace : public ITrace
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ATrace(::AlxTrace* me) : me(me) {}
				virtual ~ATrace() {}
				Alx_Status Init(void) override
				{
					return AlxTrace_Init(me);
				}
				Alx_Status DeInit(void) override
				{
					return AlxTrace_DeInit(me);
				}
				Alx_Status WriteStr(const char* str) override
				{
					return AlxTrace_WriteStr(me, str);
				}
				void WriteFormat(const char* format, ...) override
				{
					char buff[256] = {};
					va_list args = {};

					va_start(args, format);
					vsnprintf(buff, 256, format, args);
					va_end(args);

					WriteStr(buff);
				}
				void WriteStd(const char* file, uint32_t line, const char* fun, const char* format, ...) override
				{
					char buff[256] = {};
					va_list args = {};

					AlxGlobal_Ulltoa(AlxTick_Get_ms(&alxTick), buff);
					WriteFormat("trace;%s;%s;%lu;%s;", buff, file, line, fun);

					va_start(args, format);
					vsnprintf(buff, 256, format, args);
					va_end(args);

					WriteFormat("%s\r\n", buff);
				}
				void WriteSm(uint8_t smLevel, const char* smName, const char* stName, const char* acName) override
				{
					if ((smName != NULL) && (stName != NULL) && (acName != NULL))
					{
						char smLevelStr[50] = {};
						AlxTrace_GetSmLevelStr(smLevel, smLevelStr);

						char tickStr[50] = {};
						AlxGlobal_Ulltoa(AlxTick_Get_ms(&alxTick), tickStr);

						WriteFormat("traceSm;%s;%s%s_%s_%s\r\n", tickStr, smLevelStr, smName, stName, acName);
					}
				}

			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxTrace* me = nullptr;
		};


		//******************************************************************************
		// Class - Trace - STM32
		//******************************************************************************
		#if defined(ALX_STM32F0) || defined(ALX_STM32F1) || defined(ALX_STM32F4) || defined(ALX_STM32F7) || defined(ALX_STM32G4) || defined(ALX_STM32L0) || defined(ALX_STM32L4) || defined(ALX_STM32U5)
		class Trace : public ATrace
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Trace
				(
					::AlxTrace* me,
					GPIO_TypeDef* port,
					uint16_t pin,
					#if defined(ALX_STM32F0) || defined(ALX_STM32F4) || defined(ALX_STM32F7) || defined(ALX_STM32G4) || defined(ALX_STM32L0) || defined(ALX_STM32L4) || defined(ALX_STM32U5)
					uint32_t alternate,
					#endif
					USART_TypeDef* usart,
					AlxGlobal_BaudRate baudRate
				) : ATrace(me)
				{
					AlxTrace_Ctor
					(
						me,
						port,
						pin,
						#if defined(ALX_STM32F0) || defined(ALX_STM32F4) || defined(ALX_STM32F7) || defined(ALX_STM32G4) || defined(ALX_STM32L0) || defined(ALX_STM32L4) || defined(ALX_STM32U5)
						alternate,
						#endif
						usart,
						baudRate
					);
				}
				virtual ~Trace() {}
		};
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_TRACE_HPP
