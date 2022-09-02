/**
  ******************************************************************************
  * @file		alxCrc.hpp
  * @brief		Auralix C++ Library - ALX CRC Module
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
#ifndef ALX_CRC_HPP
#define ALX_CRC_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxCrc.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxCrc
	{
		//******************************************************************************
		// Class - ICrc
		//******************************************************************************
		class ICrc
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ICrc() {}
				virtual ~ICrc() {}
				virtual uint32_t Calc(uint8_t* data, uint32_t len) = 0;
				virtual bool IsOk(uint8_t* dataWithCrc, uint32_t lenWithCrc, uint32_t* validatedCrc) = 0;
				virtual uint32_t GetLen(void) = 0;
				virtual ::AlxCrc* GetCStructPtr(void) = 0;
		};


		//******************************************************************************
		// Class - Crc
		//******************************************************************************
		class Crc : public ICrc
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Crc
				(
					AlxCrc_Config config
				)
				{
					AlxCrc_Ctor(&me, config);
				}
				virtual ~Crc() {}
				uint32_t Calc(uint8_t* data, uint32_t len) override
				{
					return AlxCrc_Calc(&me, data, len);
				}
				bool IsOk(uint8_t* dataWithCrc, uint32_t lenWithCrc, uint32_t* validatedCrc) override
				{
					return AlxCrc_IsOk(&me, dataWithCrc, lenWithCrc, validatedCrc);
				}
				uint32_t GetLen(void) override
				{
					return AlxCrc_GetLen(&me);
				}
				::AlxCrc* GetCStructPtr(void) override
				{
					return &me;
				}
			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxCrc me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_CRC_HPP
