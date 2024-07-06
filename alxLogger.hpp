/**
  ******************************************************************************
  * @file		alxLogger.hpp
  * @brief		Auralix C++ Library - ALX Logger Module
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
#ifndef ALX_LOGGER_HPP
#define ALX_LOGGER_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxLogger.h"
#include "alxIoPin.hpp"
#include "alxFs.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxLogger
	{
		//******************************************************************************
		// Class - ILogger
		//******************************************************************************
		class ILogger
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ILogger() {}
				virtual ~ILogger() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status Format(void) = 0;
				virtual Alx_Status Read(char* logs, uint32_t numOfLogs, uint32_t* numOfLogsActual) = 0;
				virtual Alx_Status Write(const char* logs, uint32_t numOfLogs) = 0;
				virtual uint32_t GetNumOfLogsToReadAvailable(void) = 0;
				virtual Alx_Status StoreMetadata(AlxLogger_StoreMetadata_Config config) = 0;
				virtual AlxLogger_Metadata GetMetadataCurrent(void) = 0;
				virtual AlxLogger_Metadata GetMetadataStored(void) = 0;
				virtual AlxMath_Data GetMath_Data_ReadTime_ms(void) = 0;
				virtual AlxMath_Data GetMath_Data_WriteTime_ms(void) = 0;
				virtual ::AlxLogger* GetCStructPtr(void) = 0;
		};


		//******************************************************************************
		// Class - Logger
		//******************************************************************************
		class Logger : public ILogger
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Logger
				(
					AlxFs::IFs* alxFs,
					uint32_t numOfDir,
					uint32_t numOfFilesPerDir,
					uint32_t numOfLogsPerFile,
					const char* logDelim,
					Alx::AlxIoPin::IIoPin* do_DBG_Read,
					Alx::AlxIoPin::IIoPin* do_DBG_Write,
					Alx::AlxIoPin::IIoPin* do_DBG_StoreReadMetadata,
					Alx::AlxIoPin::IIoPin* do_DBG_StoreWriteMetadata
				)
				{
					AlxLogger_Ctor
					(
						&me,
						alxFs->GetCStructPtr(),
						numOfDir,
						numOfFilesPerDir,
						numOfLogsPerFile,
						logDelim,
						do_DBG_Read->GetCStructPtr(),
						do_DBG_Write->GetCStructPtr(),
						do_DBG_StoreReadMetadata->GetCStructPtr(),
						do_DBG_StoreWriteMetadata->GetCStructPtr()
					);
				}
				virtual ~Logger() {}
				Alx_Status Init(void) override
				{
					return AlxLogger_Init(&me);
				}
				Alx_Status Format(void) override
				{
					return AlxLogger_Format(&me);
				}
				Alx_Status Read(char* logs, uint32_t numOfLogs, uint32_t* numOfLogsActual) override
				{
					return AlxLogger_Read(&me, logs, numOfLogs, numOfLogsActual);
				}
				Alx_Status Write(const char* logs, uint32_t numOfLogs) override
				{
					return AlxLogger_Write(&me, logs, numOfLogs);
				}
				Alx_Status StoreMetadata(AlxLogger_StoreMetadata_Config config) override
				{
					return AlxLogger_StoreMetadata(&me, config);
				}
				uint32_t GetNumOfLogsToReadAvailable(void) override
				{
					return AlxLogger_GetNumOfLogsToReadAvailable(&me);
				}
				AlxLogger_Metadata GetMetadataCurrent(void) override
				{
					return AlxLogger_GetMetadataCurrent(&me);
				}
				AlxLogger_Metadata GetMetadataStored(void) override
				{
					return AlxLogger_GetMetadataStored(&me);
				}
				AlxMath_Data GetMath_Data_ReadTime_ms(void) override
				{
					return AlxLogger_GetMath_Data_ReadTime_ms(&me);
				}
				AlxMath_Data GetMath_Data_WriteTime_ms(void) override
				{
					return AlxLogger_GetMath_Data_WriteTime_ms(&me);
				}
				::AlxLogger* GetCStructPtr(void) override
				{
					return &me;
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxLogger me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_LOGGER_HPP
