/**
  ******************************************************************************
  * @file		alxSd.hpp
  * @brief		Auralix C++ Library - ALX SD Card Module
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
#ifndef ALX_SD_HPP
#define ALX_SD_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxSd.h"
#include "alxSpi.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxSd
	{
		//******************************************************************************
		// Class - ISd
		//******************************************************************************
		class ISd
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ISd() {}
				virtual ~ISd() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual Alx_Status ReadBlock(uint32_t numOfBlocks, uint32_t addr, uint8_t* data, uint32_t len, uint8_t numOfTries) = 0;
				virtual Alx_Status WriteBlock(uint32_t numOfBlocks, uint32_t addr, uint8_t* data, uint32_t len, uint8_t numOfTries) = 0;
		};


		//******************************************************************************
		// Class - Sd
		//******************************************************************************
		class Sd : public ISd
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Sd
				(
					AlxSpi::ISpi* alxSpi,
					uint8_t spiNumOfTries,
					uint16_t spiTimeout_ms,
					uint8_t initDeInitNumOfTries,
					uint16_t initDeInitInitialAndNewTryWaitTime_ms,
					uint16_t cmdRespTimeout_ms,
					uint16_t acmd41Timeout_ms,
					uint16_t blockReadTokenFeTimeout_ms,
					uint16_t blockWriteDataAcceptedTokenTimeout_ms,
					uint16_t blockWriteSdBusyTimeout_ms
				)
				{
					AlxSd_Ctor
					(
						&me,
						alxSpi->GetCStructPtr(),
						spiNumOfTries,
						spiTimeout_ms,
						initDeInitNumOfTries,
						initDeInitInitialAndNewTryWaitTime_ms,
						cmdRespTimeout_ms,
						acmd41Timeout_ms,
						blockReadTokenFeTimeout_ms,
						blockWriteDataAcceptedTokenTimeout_ms,
						blockWriteSdBusyTimeout_ms
					);
				}
				virtual ~Sd() {}
				Alx_Status Init(void) override
				{
					return AlxSd_Init(&me);
				}
				Alx_Status DeInit(void) override
				{
					return AlxSd_DeInit(&me);
				}
				Alx_Status ReadBlock(uint32_t numOfBlocks, uint32_t addr, uint8_t* data, uint32_t len, uint8_t numOfTries) override
				{
					return AlxSd_ReadBlock(&me, numOfBlocks, addr, data, len, numOfTries);
				}
				Alx_Status WriteBlock(uint32_t numOfBlocks, uint32_t addr, uint8_t* data, uint32_t len, uint8_t numOfTries) override
				{
					return AlxSd_WriteBlock(&me, numOfBlocks, addr, data, len, numOfTries);
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxSd me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_SD_HPP
