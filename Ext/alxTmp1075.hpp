/**
  ******************************************************************************
  * @file		alxTmp1075.hpp
  * @brief		Auralix C++ Library - ALX Temperature Sensor TMP1075 Module
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
#ifndef ALX_TMP1075_HPP
#define ALX_TMP1075_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxTmp1075.h"
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
	namespace AlxTmp1075
	{
		//******************************************************************************
		// Class - ITmp1075
		//******************************************************************************
		class ITmp1075
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ITmp1075() {};
				virtual ~ITmp1075() {};
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual float GetTemp_degC(void) = 0;
		};


		//******************************************************************************
		// Class - Tmp1075
		//******************************************************************************
		class Tmp1075 final : public ITmp1075
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Tmp1075
				(
					Alx::AlxI2c::I2c* i2c,
					uint8_t i2cAddr,
					bool i2cCheckWithRead,
					uint8_t i2cNumOfTries,
					uint16_t i2cTimeout_ms
				)
				{
					AlxTmp1075_Ctor
					(
						&me,
						i2c->GetCStructPtr(),
						i2cAddr,
						i2cCheckWithRead,
						i2cNumOfTries,
						i2cTimeout_ms
					);
				};
				virtual ~Tmp1075() {};
				Alx_Status Init(void) override		{ return AlxTmp1075_Init(&me); }
				Alx_Status DeInit(void) override	{ return AlxTmp1075_DeInit(&me); }
				float GetTemp_degC(void) override	{ return AlxTmp1075_GetTemp_degC(&me); }
			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxTmp1075 me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif // ALX_TMP1075_HPP
