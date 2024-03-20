﻿/**
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
				virtual Alx_Status Trace_ReadLog(char* log, uint32_t numOfLogs) = 0;
				virtual Alx_Status Trace_WriteLog(const char* log, uint32_t numOfLogs, bool appendLogDelim) = 0;
				virtual Alx_Status Data_ReadLog(char* log, uint32_t numOfLogs) = 0;
				virtual Alx_Status Data_WriteLog(const char* log, uint32_t numOfLogs, bool appendLogDelim) = 0;
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
					const char* logDelim
				)
				{
					AlxLogger_Ctor
					(
						&me,
						alxFs->GetCStructPtr(),
						numOfDir,
						numOfFilesPerDir,
						numOfLogsPerFile,
						logDelim
					);
				}
				virtual ~Logger() {}
				Alx_Status Init(void) override
				{
					return AlxLogger_Init(&me);
				}
				Alx_Status Trace_ReadLog(char* log, uint32_t numOfLogs) override
				{
					return AlxLogger_Trace_ReadLog(&me, log, numOfLogs);
				}
				Alx_Status Trace_WriteLog(const char* log, uint32_t numOfLogs, bool appendLogDelim) override
				{
					return AlxLogger_Trace_WriteLog(&me, log, numOfLogs, appendLogDelim);
				}
				Alx_Status Data_ReadLog(char* log, uint32_t numOfLogs) override
				{
					return AlxLogger_Data_ReadLog(&me, log, numOfLogs);
				}
				Alx_Status Data_WriteLog(const char* log, uint32_t numOfLogs, bool appendLogDelim) override
				{
					return AlxLogger_Data_WriteLog(&me, log, numOfLogs, appendLogDelim);
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
