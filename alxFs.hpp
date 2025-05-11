/**
  ******************************************************************************
  * @file		alxFs.hpp
  * @brief		Auralix C++ Library - ALX File System Module
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
#ifndef ALX_FS_HPP
#define ALX_FS_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxFs.h"
#include "alxIoPin.hpp"
#include "alxMmc.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxFs
	{
		//******************************************************************************
		// Class - IFs
		//******************************************************************************
		class IFs
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IFs() {}
				virtual ~IFs() {}
				virtual Alx_Status Mount(void) = 0;
				virtual Alx_Status UnMount(void) = 0;
				virtual Alx_Status MountFormat(void) = 0;
				virtual Alx_Status Format(void) = 0;
				virtual Alx_Status Remove(const char* path) = 0;
				virtual Alx_Status Rename(const char* pathOld, const char* pathNew) = 0;
				virtual Alx_Status File_Open(AlxFs_File* file, const char* path, const char* mode) = 0;
				virtual Alx_Status File_Close(AlxFs_File* file) = 0;
				virtual Alx_Status File_Read(AlxFs_File* file, void* data, uint32_t len, uint32_t* lenActual) = 0;
				virtual Alx_Status File_ReadStrUntil(AlxFs_File* file, char* str, const char* delim, uint32_t len, uint32_t* lenActual) = 0;
				virtual Alx_Status File_Write(AlxFs_File* file, void* data, uint32_t len) = 0;
				virtual Alx_Status File_WriteStr(AlxFs_File* file, const char* str) = 0;
				virtual Alx_Status File_Sync(AlxFs_File* file) = 0;
				virtual Alx_Status File_Seek(AlxFs_File* file, int32_t offset, AlxFs_File_Seek_Origin origin, uint32_t* positionNew) = 0;
				virtual Alx_Status File_Tell(AlxFs_File* file, uint32_t* position) = 0;
				virtual Alx_Status File_Rewind(AlxFs_File* file) = 0;
				virtual Alx_Status File_Size(AlxFs_File* file, uint32_t* size) = 0;
				virtual Alx_Status File_Truncate(AlxFs_File* file, uint32_t size) = 0;
				virtual Alx_Status File_Trace(const char* path, bool bin) = 0;
				virtual Alx_Status Dir_Make(const char* path) = 0;
				virtual Alx_Status Dir_Open(AlxFs_Dir* dir, const char* path) = 0;
				virtual Alx_Status Dir_Close(AlxFs_Dir* dir) = 0;
				virtual Alx_Status Dir_Read(AlxFs_Dir* dir, AlxFs_Info* info) = 0;
				virtual Alx_Status Dir_Trace(const char* path, bool fileTrace, bool fileBin) = 0;
				virtual ::AlxFs* GetCStructPtr(void) = 0;
		};


		//******************************************************************************
		// Class - Fs
		//******************************************************************************
		#if defined(ALX_CPP_LIB)
		class Fs : public IFs
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Fs
				(
					::AlxFs_Config config,
					AlxMmc::IMmc* alxMmc,
					Alx::AlxIoPin::IIoPin* do_DBG_ReadBlock,
					Alx::AlxIoPin::IIoPin* do_DBG_WriteBlock,
					Alx::AlxIoPin::IIoPin* do_DBG_EraseBlock,
					Alx::AlxIoPin::IIoPin* do_DBG_SyncBlock
				)
				{
					::AlxMmc* _alxMmc = NULL;
					::AlxIoPin* _do_DBG_ReadBlock = NULL;
					::AlxIoPin* _do_DBG_WriteBlock = NULL;
					::AlxIoPin* _do_DBG_EraseBlock = NULL;
					::AlxIoPin* _do_DBG_SyncBlock = NULL;
					if (alxMmc != nullptr) _alxMmc = alxMmc->GetCStructPtr();
					if (do_DBG_ReadBlock != nullptr) _do_DBG_ReadBlock = do_DBG_ReadBlock->GetCStructPtr();
					if (do_DBG_WriteBlock != nullptr) _do_DBG_WriteBlock = do_DBG_WriteBlock->GetCStructPtr();
					if (do_DBG_EraseBlock != nullptr) _do_DBG_EraseBlock = do_DBG_EraseBlock->GetCStructPtr();
					if (do_DBG_SyncBlock != nullptr) _do_DBG_SyncBlock = do_DBG_SyncBlock->GetCStructPtr();

					AlxFs_Ctor
					(
						&me,
						config,
						_alxMmc,
						_do_DBG_ReadBlock,
						_do_DBG_WriteBlock,
						_do_DBG_EraseBlock,
						_do_DBG_SyncBlock
					);
				}
				virtual ~Fs() {}
				Alx_Status Mount(void) override
				{
					return AlxFs_Mount(&me);
				}
				Alx_Status UnMount(void) override
				{
					return AlxFs_UnMount(&me);
				}
				Alx_Status MountFormat(void) override
				{
					return AlxFs_MountFormat(&me);
				}
				Alx_Status Format(void) override
				{
					return AlxFs_Format(&me);
				}
				Alx_Status Remove(const char* path) override
				{
					return AlxFs_Remove(&me, path);
				}
				Alx_Status Rename(const char* pathOld, const char* pathNew) override
				{
					return AlxFs_Rename(&me, pathOld, pathNew);
				}
				Alx_Status File_Open(AlxFs_File* file, const char* path, const char* mode) override
				{
					return AlxFs_File_Open(&me, file, path, mode);
				}
				Alx_Status File_Close(AlxFs_File* file) override
				{
					return AlxFs_File_Close(&me, file);
				}
				Alx_Status File_Read(AlxFs_File* file, void* data, uint32_t len, uint32_t* lenActual) override
				{
					return AlxFs_File_Read(&me, file, data, len, lenActual);
				}
				Alx_Status File_ReadStrUntil(AlxFs_File* file, char* str, const char* delim, uint32_t len, uint32_t* lenActual) override
				{
					return AlxFs_File_ReadStrUntil(&me, file, str, delim, len, lenActual);
				}
				Alx_Status File_Write(AlxFs_File* file, void* data, uint32_t len) override
				{
					return AlxFs_File_Write(&me, file, data, len);
				}
				Alx_Status File_WriteStr(AlxFs_File* file, const char* str) override
				{
					return AlxFs_File_WriteStr(&me, file, str);
				}
				Alx_Status File_Sync(AlxFs_File* file) override
				{
					return AlxFs_File_Sync(&me, file);
				}
				Alx_Status File_Seek(AlxFs_File* file, int32_t offset, AlxFs_File_Seek_Origin origin, uint32_t* positionNew) override
				{
					return AlxFs_File_Seek(&me, file, offset, origin, positionNew);
				}
				Alx_Status File_Tell(AlxFs_File* file, uint32_t* position) override
				{
					return AlxFs_File_Tell(&me, file, position);
				}
				Alx_Status File_Rewind(AlxFs_File* file) override
				{
					return AlxFs_File_Rewind(&me, file);
				}
				Alx_Status File_Size(AlxFs_File* file, uint32_t* size) override
				{
					return AlxFs_File_Size(&me, file, size);
				}
				Alx_Status File_Truncate(AlxFs_File* file, uint32_t size) override
				{
					return AlxFs_File_Truncate(&me, file, size);
				}
				Alx_Status File_Trace(const char* path, bool bin) override
				{
					return AlxFs_File_Trace(&me, path, bin);
				}
				Alx_Status Dir_Make(const char* path) override
				{
					return AlxFs_Dir_Make(&me, path);
				}
				Alx_Status Dir_Open(AlxFs_Dir* dir, const char* path) override
				{
					return AlxFs_Dir_Open(&me, dir, path);
				}
				Alx_Status Dir_Close(AlxFs_Dir* dir) override
				{
					return AlxFs_Dir_Close(&me, dir);
				}
				Alx_Status Dir_Read(AlxFs_Dir* dir, AlxFs_Info* info) override
				{
					return AlxFs_Dir_Read(&me, dir, info);
				}
				Alx_Status Dir_Trace(const char* path, bool fileTrace, bool fileBin) override
				{
					return AlxFs_Dir_Trace(&me, path, fileTrace, fileBin);
				}
				::AlxFs* GetCStructPtr(void) override
				{
					return &me;
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxFs me = {};
		};
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_FS_HPP
