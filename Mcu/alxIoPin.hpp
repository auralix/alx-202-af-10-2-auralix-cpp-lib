/**
  ******************************************************************************
  * @file		alxIoPin.hpp
  * @brief		Auralix C++ Library - ALX IO Pin Module
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
#ifndef ALX_IO_PIN_HPP
#define ALX_IO_PIN_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxIoPin.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxIoPin
	{
		//******************************************************************************
		// Class - IIoPin
		//******************************************************************************
		class IIoPin
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IIoPin() {}
				virtual ~IIoPin() {}
				virtual void Init(void) = 0;
				virtual void DeInit(void) = 0;
				virtual bool Read(void) = 0;
				virtual void Write(bool val) = 0;
				virtual void Set(void) = 0;
				virtual void Reset(void) = 0;
				virtual void Toggle(void) = 0;
				virtual AlxIoPin_TriState Read_TriState(void) = 0;
				virtual ::AlxIoPin* GetCStructPtr(void) = 0;
		};


		//******************************************************************************
		// Class - AIoPin
		//******************************************************************************
		class AIoPin : public IIoPin
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				AIoPin() {}
				virtual ~AIoPin() {}
				void Init(void) override
				{
					AlxIoPin_Init(&me);
				}
				void DeInit(void) override
				{
					AlxIoPin_DeInit(&me);
				}
				bool Read(void) override
				{
					return AlxIoPin_Read(&me);
				}
				void Write(bool val) override
				{
					AlxIoPin_Write(&me, val);
				}
				void Set(void) override
				{
					AlxIoPin_Set(&me);
				}
				void Reset(void) override
				{
					AlxIoPin_Reset(&me);
				}
				void Toggle(void) override
				{
					AlxIoPin_Toggle(&me);
				}
				AlxIoPin_TriState Read_TriState(void) override
				{
					return AlxIoPin_Read_TriState(&me);
				}
				::AlxIoPin* GetCStructPtr(void) override
				{
					return &me;
				}

			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxIoPin me = {};
		};


		//******************************************************************************
		// Class - IoPin
		//******************************************************************************
		#if defined(ALX_STM32F0) || defined(ALX_STM32F1) || defined(ALX_STM32F4) || defined(ALX_STM32F7) || defined(ALX_STM32G4) || defined(ALX_STM32L0) || defined(ALX_STM32L4) || defined(ALX_STM32U5)
		class IoPin : public AIoPin
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IoPin
				(
					GPIO_TypeDef* port,
					uint16_t pin,
					uint32_t mode,
					uint32_t pull,
					uint32_t speed,
					uint32_t alternate,
					bool val
				)
				{
					AlxIoPin_Ctor
					(
						&me,
						port,
						pin,
						mode,
						pull,
						speed,
						alternate,
						val
					);
				}
				virtual ~IoPin() {}
		};
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_IO_PIN_HPP
