/**
  ******************************************************************************
  * @file		alxIoPinIrq.hpp
  * @brief		Auralix C++ Library - ALX IO Pin Module
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
#ifndef ALX_IO_PIN_IRQ_HPP
#define ALX_IO_PIN_IRQ_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxIoPinIrq.h"
#include "alxIoPin.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxIoPinIrq
	{
		//******************************************************************************
		// Class - IIoPinIrq
		//******************************************************************************
		class IIoPinIrq
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IIoPinIrq() {}
				virtual ~IIoPinIrq() {}
				virtual void Init(void) = 0;
				virtual void DeInit(void) = 0;
		};


		//******************************************************************************
		// Class - AIoPinIrq
		//******************************************************************************
		class AIoPinIrq : public IIoPinIrq
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				AIoPinIrq() {}
				virtual ~AIoPinIrq() {}
				void Init(void) override
				{
					return AlxIoPinIrq_Init(&me);
				}
				void DeInit(void) override
				{
					return AlxIoPinIrq_DeInit(&me);
				}
			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxIoPinIrq me = {};
		};


		//******************************************************************************
		// Class - IoPinIrq
		//******************************************************************************
		#if defined(ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)
		class IoPinIrq : public AIoPinIrq
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IoPinIrq
				(
					AlxIoPin::IIoPin** ioPinArr,
					uint8_t numOfIoPins,
					Alx_IrqPriority* irqPriorityArr
				)
				{
					for (uint32_t i = 0; i < numOfIoPins; i++)
					{
						AlxIoPin::IIoPin* temp = *(ioPinArr + i);
						ioPinIrqIoPinArr[i] = temp->GetCStructPtr();
					}

					AlxIoPinIrq_Ctor
					(
						&me,
						ioPinIrqIoPinArr,
						numOfIoPins,
						irqPriorityArr
					);
				}
				virtual ~IoPinIrq() {}
			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxIoPin* ioPinIrqIoPinArr[ALX_IO_PIN_IRQ_BUFF_LEN] = {};
		};
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif // ALX_IO_PIN_IRQ_HPP
