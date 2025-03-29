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
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				//------------------------------------------------------------------------------
				ILogger() {}
				virtual ~ILogger() {}
				virtual ::AlxLogger* GetCStructPtr(void) = 0;



				//------------------------------------------------------------------------------
				//------------------------------------------------------------------------------
				// General
				//------------------------------------------------------------------------------
				//------------------------------------------------------------------------------


				//------------------------------------------------------------------------------
				// Setup
				//------------------------------------------------------------------------------
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status Format(void) = 0;


				//------------------------------------------------------------------------------
				// Metadata
				//------------------------------------------------------------------------------
				virtual AlxLogger_Metadata Metadata_GetCurrent(void) = 0;
				virtual AlxLogger_Metadata Metadata_GetStored(void) = 0;
				virtual Alx_Status Metadata_Store(AlxLogger_StoreMetadata_Config config) = 0;


				//------------------------------------------------------------------------------
				// Debug
				//------------------------------------------------------------------------------
				virtual AlxMath_Data Debug_GetReadTime_ms(void) = 0;
				virtual AlxMath_Data Debug_GetWriteTime_ms(void) = 0;




				//------------------------------------------------------------------------------
				//------------------------------------------------------------------------------
				// Log Level
				//------------------------------------------------------------------------------
				//------------------------------------------------------------------------------


				//------------------------------------------------------------------------------
				// Read/Write
				//------------------------------------------------------------------------------
				virtual Alx_Status Log_Read(char* logs, uint32_t numOfLogs, uint32_t* numOfLogsActual, bool mdUpdate, uint64_t idStart) = 0;
				virtual Alx_Status Log_Write(const char* logs, uint32_t numOfLogs) = 0;


				//------------------------------------------------------------------------------
				// Status
				//------------------------------------------------------------------------------
				virtual uint64_t Log_GetNumOfLogsToProcess(void) = 0;
				virtual uint64_t Log_GetNumOfLogsStored(void) = 0;
				virtual Alx_Status Log_GetIdOldest(uint64_t* idOldest) = 0;
				virtual Alx_Status Log_GetIdNewest(uint64_t* idNewest) = 0;


				//------------------------------------------------------------------------------
				// Management
				//------------------------------------------------------------------------------
				virtual Alx_Status Log_DiscardLogsToProcess(void) = 0;




				//------------------------------------------------------------------------------
				//------------------------------------------------------------------------------
				// File Level
				//------------------------------------------------------------------------------
				//------------------------------------------------------------------------------


				//------------------------------------------------------------------------------
				// Read/Write
				//------------------------------------------------------------------------------
				virtual Alx_Status File_Read(const char* path, uint8_t* chunkBuff, uint32_t chunkLen, Alx_Status(*chunkRead_Callback)(void* chunkData, uint32_t chunkLenActual)) = 0;
				virtual Alx_Status File_ReadFirstLog(const char* path, char* log) = 0;



				//------------------------------------------------------------------------------
				// Status
				//------------------------------------------------------------------------------
				virtual Alx_Status GetFileSize(const char* path, uint32_t* fileSize) = 0;
				virtual Alx_Status GetFilePathOldest(char* filePathOldest) = 0;
				virtual Alx_Status GetFilePathNewest(char* filePathNewest) = 0;


				//------------------------------------------------------------------------------
				// Management
				//------------------------------------------------------------------------------
				virtual Alx_Status RewindLogsToProcessFiles(uint32_t numOfFiles) = 0;
				virtual Alx_Status ForwardLogsToProcessFiles(uint32_t numOfFiles) = 0;
		};


		//******************************************************************************
		// Class - Logger
		//******************************************************************************
		class Logger : public ILogger
		{
			public:
				//------------------------------------------------------------------------------
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
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
					::AlxIoPin* _do_DBG_Read = NULL;
					::AlxIoPin* _do_DBG_Write = NULL;
					::AlxIoPin* _do_DBG_StoreReadMetadata = NULL;
					::AlxIoPin* _do_DBG_StoreWriteMetadata = NULL;
					if (do_DBG_Read != nullptr) _do_DBG_Read = do_DBG_Read->GetCStructPtr();
					if (do_DBG_Write != nullptr) _do_DBG_Write = do_DBG_Write->GetCStructPtr();
					if (do_DBG_StoreReadMetadata != nullptr) _do_DBG_StoreReadMetadata = do_DBG_StoreReadMetadata->GetCStructPtr();
					if (do_DBG_StoreWriteMetadata != nullptr) _do_DBG_StoreWriteMetadata = do_DBG_StoreWriteMetadata->GetCStructPtr();

					AlxLogger_Ctor
					(
						&me,
						alxFs->GetCStructPtr(),
						numOfDir,
						numOfFilesPerDir,
						numOfLogsPerFile,
						logDelim,
						_do_DBG_Read,
						_do_DBG_Write,
						_do_DBG_StoreReadMetadata,
						_do_DBG_StoreWriteMetadata
					);
				}
				virtual ~Logger() {}
				::AlxLogger* GetCStructPtr(void) override
				{
					return &me;
				}




				//------------------------------------------------------------------------------
				//------------------------------------------------------------------------------
				// General
				//------------------------------------------------------------------------------
				//------------------------------------------------------------------------------


				//------------------------------------------------------------------------------
				// Setup
				//------------------------------------------------------------------------------
				Alx_Status Init(void) override
				{
					return AlxLogger_Init(&me);
				}
				Alx_Status Format(void) override
				{
					return AlxLogger_Format(&me);
				}


				//------------------------------------------------------------------------------
				// Metadata
				//------------------------------------------------------------------------------
				AlxLogger_Metadata Metadata_GetCurrent(void) override
				{
					return AlxLogger_Metadata_GetCurrent(&me);
				}
				AlxLogger_Metadata Metadata_GetStored(void) override
				{
					return AlxLogger_Metadata_GetStored(&me);
				}
				Alx_Status Metadata_Store(AlxLogger_StoreMetadata_Config config) override
				{
					return AlxLogger_Metadata_Store(&me, config);
				}


				//------------------------------------------------------------------------------
				// Debug
				//------------------------------------------------------------------------------
				AlxMath_Data Debug_GetReadTime_ms(void) override
				{
					return AlxLogger_Debug_GetReadTime_ms(&me);
				}
				AlxMath_Data Debug_GetWriteTime_ms(void) override
				{
					return AlxLogger_Debug_GetWriteTime_ms(&me);
				}




				//------------------------------------------------------------------------------
				//------------------------------------------------------------------------------
				// Log Level
				//------------------------------------------------------------------------------
				//------------------------------------------------------------------------------


				//------------------------------------------------------------------------------
				// Read/Write
				//------------------------------------------------------------------------------
				Alx_Status Log_Read(char* logs, uint32_t numOfLogs, uint32_t* numOfLogsActual, bool mdUpdate, uint64_t idStart) override
				{
					return AlxLogger_Log_Read(&me, logs, numOfLogs, numOfLogsActual, mdUpdate, idStart);
				}
				Alx_Status Log_Write(const char* logs, uint32_t numOfLogs) override
				{
					return AlxLogger_Log_Write(&me, logs, numOfLogs);
				}


				//------------------------------------------------------------------------------
				// Status
				//------------------------------------------------------------------------------
				uint64_t Log_GetNumOfLogsToProcess(void) override
				{
					return AlxLogger_Log_GetNumOfLogsToProcess(&me);
				}
				uint64_t Log_GetNumOfLogsStored(void) override
				{
					return AlxLogger_Log_GetNumOfLogsStored(&me);
				}
				Alx_Status Log_GetIdOldest(uint64_t* idOldest) override
				{
					return AlxLogger_Log_GetIdOldest(&me, idOldest);
				}
				Alx_Status Log_GetIdNewest(uint64_t* idNewest) override
				{
					return AlxLogger_Log_GetIdNewest(&me, idNewest);
				}


				//------------------------------------------------------------------------------
				// Management
				//------------------------------------------------------------------------------
				Alx_Status Log_DiscardLogsToProcess(void) override
				{
					return AlxLogger_Log_DiscardLogsToProcess(&me);
				}




				//------------------------------------------------------------------------------
				//------------------------------------------------------------------------------
				// File Level
				//------------------------------------------------------------------------------
				//------------------------------------------------------------------------------


				//------------------------------------------------------------------------------
				// Read/Write
				//------------------------------------------------------------------------------
				Alx_Status File_Read(const char* path, uint8_t* chunkBuff, uint32_t chunkLen, Alx_Status(*chunkRead_Callback)(void* chunkData, uint32_t chunkLenActual)) override
				{
					return AlxLogger_File_Read(&me, path, chunkBuff, chunkLen, chunkRead_Callback);
				}
				Alx_Status File_ReadFirstLog(const char* path, char* log) override
				{
					return AlxLogger_File_ReadFirstLog(&me, path, log);
				}


				//------------------------------------------------------------------------------
				// Status
				//------------------------------------------------------------------------------
				Alx_Status GetFileSize(const char* path, uint32_t* fileSize) override
				{
					return AlxLogger_GetFileSize(&me, path, fileSize);
				}
				Alx_Status GetFilePathOldest(char* filePathOldest) override
				{
					return AlxLogger_GetFilePathOldest(&me, filePathOldest);
				}
				Alx_Status GetFilePathNewest(char* filePathNewest) override
				{
					return AlxLogger_GetFilePathNewest(&me, filePathNewest);
				}


				//------------------------------------------------------------------------------
				// Management
				//------------------------------------------------------------------------------
				Alx_Status RewindLogsToProcessFiles(uint32_t numOfFiles) override
				{
					return AlxLogger_RewindLogsToProcessFiles(&me, numOfFiles);
				}
				Alx_Status ForwardLogsToProcessFiles(uint32_t numOfFiles) override
				{
					return AlxLogger_ForwardLogsToProcessFiles(&me, numOfFiles);
				}



			private:
				//------------------------------------------------------------------------------
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				//------------------------------------------------------------------------------
				::AlxLogger me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_LOGGER_HPP
