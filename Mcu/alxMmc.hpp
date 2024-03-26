/**
  ******************************************************************************
  * @file		alxMmc.hpp
  * @brief		Auralix C++ Library - ALX MMC Module
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
#ifndef ALX_MMC_HPP
#define ALX_MMC_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxMmc.h"
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
	namespace AlxMmc
	{
		//******************************************************************************
		// Class - IMmc
		//******************************************************************************
		class IMmc
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IMmc() {}
				virtual ~IMmc() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual Alx_Status ReadBlock(uint32_t numOfBlocks, uint32_t addr, uint8_t* data, uint32_t len, uint8_t numOfTries, uint16_t newTryWaitTime_ms) = 0;
				virtual Alx_Status WriteBlock(uint32_t numOfBlocks, uint32_t addr, uint8_t* data, uint32_t len, uint8_t numOfTries, uint16_t newTryWaitTime_ms) = 0;
				virtual ::AlxMmc* GetCStructPtr(void) = 0;
		};


		//******************************************************************************
		// Class - AMmc
		//******************************************************************************
		class AMmc : public IMmc
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				AMmc() {}
				virtual ~AMmc() {}
				Alx_Status Init(void) override
				{
					return AlxMmc_Init(&me);
				}
				Alx_Status DeInit(void) override
				{
					return AlxMmc_DeInit(&me);
				}
				Alx_Status ReadBlock(uint32_t numOfBlocks, uint32_t addr, uint8_t* data, uint32_t len, uint8_t numOfTries, uint16_t newTryWaitTime_ms) override
				{
					return AlxMmc_ReadBlock(&me, numOfBlocks, addr, data, len, numOfTries, newTryWaitTime_ms);
				}
				Alx_Status WriteBlock(uint32_t numOfBlocks, uint32_t addr, uint8_t* data, uint32_t len, uint8_t numOfTries, uint16_t newTryWaitTime_ms) override
				{
					return AlxMmc_WriteBlock(&me, numOfBlocks, addr, data, len, numOfTries, newTryWaitTime_ms);
				}
				::AlxMmc* GetCStructPtr(void) override
				{
					return &me;
				}

			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxMmc me = {};
		};


		//******************************************************************************
		// Class - Mmc
		//******************************************************************************
		#if defined(ALX_STM32L4)
		class Mmc : public AMmc
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Mmc
				(
					MMC_TypeDef* mmc,
					AlxIoPin::IIoPin* do_nRST,
					AlxIoPin::IIoPin* do_CLK,
					AlxIoPin::IIoPin* do_CMD,
					AlxIoPin::IIoPin* io_DAT0,
					AlxIoPin::IIoPin* io_DAT1,
					AlxIoPin::IIoPin* io_DAT2,
					AlxIoPin::IIoPin* io_DAT3,
					AlxIoPin::IIoPin* io_DAT4,
					AlxIoPin::IIoPin* io_DAT5,
					AlxIoPin::IIoPin* io_DAT6,
					AlxIoPin::IIoPin* io_DAT7,
					uint16_t blockReadWriteTimeout_ms,
					uint16_t waitForTransferStateTimeout_ms
				)
				{
					AlxMmc_Ctor
					(
						&me,
						mmc,
						do_nRST->GetCStructPtr(),
						do_CLK->GetCStructPtr(),
						do_CMD->GetCStructPtr(),
						io_DAT0->GetCStructPtr(),
						io_DAT1->GetCStructPtr(),
						io_DAT2->GetCStructPtr(),
						io_DAT3->GetCStructPtr(),
						io_DAT4->GetCStructPtr(),
						io_DAT5->GetCStructPtr(),
						io_DAT6->GetCStructPtr(),
						io_DAT7->GetCStructPtr(),
						blockReadWriteTimeout_ms,
						waitForTransferStateTimeout_ms
					);
				}
				virtual ~Mmc() {}
		};
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_MMC_HPP
