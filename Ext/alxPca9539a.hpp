/**
  ******************************************************************************
  * @file		alxPca9539a.hpp
  * @brief		Auralix C Library - ALX Battery Charger PCA9539A Module
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
#ifndef ALX_PCA9539A_HPP
#define ALX_PCA9539A_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxPca9539a.h"
#include "alxIoPin.hpp"
#include "alxI2c.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxPca9539a
	{
		//******************************************************************************
		// Class - IPca9539a
		//******************************************************************************
		class IPca9539a
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IPca9539a() {}
				virtual ~IPca9539a() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual Alx_Status Handle(void) = 0;
				virtual bool ReadPin(uint8_t port, uint8_t pin) = 0;
				virtual uint8_t ReadPort(uint8_t port) = 0;
				virtual void WritePin(uint8_t port, uint8_t pin, bool val) = 0;
				virtual void TogglePin(uint8_t port, uint8_t pin) = 0;
		};


		//******************************************************************************
		// Class - Pca9539a
		//******************************************************************************
		class Pca9539a : public IPca9539a
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Pca9539a
				(
					Alx::AlxI2c::II2c *i2c,
					uint8_t i2cAddr,
					bool i2cCheckWithRead,
					uint8_t i2cNumOfTries,
					uint16_t i2cTimeout_ms
				)
				{
					AlxPca9539a_Ctor
					(
						&me,
						i2c->GetCStructPtr(),
						i2cAddr,
						i2cCheckWithRead,
						i2cNumOfTries,
						i2cTimeout_ms
					);
				}
				virtual ~Pca9539a() {}
				virtual Alx_Status Init(void)
				{
					return AlxPca9539a_Init(&me);
				}
				virtual Alx_Status DeInit(void)
				{
					return AlxPca9539a_DeInit(&me);
				}
				virtual Alx_Status Handle(void)
				{
					return AlxPca9539a_Handle(&me);
				}
				virtual bool ReadPin(uint8_t port, uint8_t pin)
				{
					return AlxPca9539a_IoPin_Read(&me, port, pin);
				}
				virtual uint8_t ReadPort(uint8_t port)
				{
					return AlxPca9539a_Read_Port_Raw(&me, port);
				}
				virtual void WritePin(uint8_t port, uint8_t pin, bool val)
				{
					AlxPca9539a_IoPin_Write(&me, port, pin, val);
				}
				virtual void TogglePin(uint8_t port, uint8_t pin)
				{
					AlxPca9539a_IoPin_Toggle(&me, port, pin);
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxPca9539a me = {};
			public:

				Alx::AlxI2c::II2c *i2c = nullptr;
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_PCA9539A_HPP
