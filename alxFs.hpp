﻿/**
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
				virtual Alx_Status File_Read(AlxFs_File* file, void* data, uint32_t lenMax, uint32_t* lenActual) = 0;
				virtual Alx_Status File_ReadStrUntil(AlxFs_File* file, char* str, const char* delim, uint32_t lenMax, uint32_t* lenActual) = 0;
				virtual Alx_Status File_Write(AlxFs_File* file, void* data, uint32_t len) = 0;
				virtual Alx_Status File_WriteStr(AlxFs_File* file, char* str) = 0;
				virtual Alx_Status File_Sync(AlxFs_File* file) = 0;
				virtual Alx_Status File_Seek(AlxFs_File* file, uint32_t offset, AlxFs_File_Seek_Origin origin, uint32_t* filePositionNew) = 0;
				virtual Alx_Status File_Tell(AlxFs_File* file, uint32_t* filePositionCurrent) = 0;
				virtual Alx_Status File_Size(AlxFs_File* file, uint32_t* fileSize) = 0;
				virtual Alx_Status Dir_Make(const char* path) = 0;
				virtual Alx_Status Dir_Open(AlxFs_Dir* dir, const char* path) = 0;
				virtual Alx_Status Dir_Close(AlxFs_Dir* dir) = 0;
				virtual Alx_Status Dir_Read(AlxFs_Dir* dir, AlxFs_Info* info) = 0;
				virtual Alx_Status Dir_Trace(AlxFs_Dir* dir) = 0;
				virtual ::AlxFs* GetCStructPtr(void) = 0;
		};


		//******************************************************************************
		// Class - Fs
		//******************************************************************************
		#if defined(ALX_CPP_LIB) && defined(ALX_LFS)
		class Fs : public IFs
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Fs
				(
					::AlxFs_Config config,
					AlxMmc::IMmc* alxMmc
				)
				{
					if (config == AlxFs_Config_Lfs_FlashInt)
					{
						AlxFs_Ctor
						(
							&me,
							config,
							NULL
						);
					}
					else if	(config == AlxFs_Config_Lfs_Mmc)
					{
						AlxFs_Ctor
						(
							&me,
							config,
							alxMmc->GetCStructPtr()
						);
					}
					else
					{
						ALX_FS_ASSERT(false);	// We should never get here
					}
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
				Alx_Status File_Read(AlxFs_File* file, void* data, uint32_t lenMax, uint32_t* lenActual) override
				{
					return AlxFs_File_Read(&me, file, data, lenMax, lenActual);
				}
				Alx_Status File_ReadStrUntil(AlxFs_File* file, char* str, const char* delim, uint32_t lenMax, uint32_t* lenActual) override
				{
					return AlxFs_File_ReadStrUntil(&me, file, str, delim, lenMax, lenActual);
				}
				Alx_Status File_Write(AlxFs_File* file, void* data, uint32_t len) override
				{
					return AlxFs_File_Write(&me, file, data, len);
				}
				Alx_Status File_WriteStr(AlxFs_File* file, char* str) override
				{
					return AlxFs_File_WriteStr(&me, file, str);
				}
				Alx_Status File_Sync(AlxFs_File* file) override
				{
					return AlxFs_File_Sync(&me, file);
				}
				Alx_Status File_Seek(AlxFs_File* file, uint32_t offset, AlxFs_File_Seek_Origin origin, uint32_t* filePositionNew) override
				{
					return AlxFs_File_Seek(&me, file, offset, origin, filePositionNew);
				}
				Alx_Status File_Tell(AlxFs_File* file, uint32_t* filePositionCurrent) override
				{
					return AlxFs_File_Tell(&me, file, filePositionCurrent);
				}
				Alx_Status File_Size(AlxFs_File* file, uint32_t* fileSize) override
				{
					return AlxFs_File_Size(&me, file, fileSize);
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
				Alx_Status Dir_Trace(AlxFs_Dir* dir) override
				{
					return AlxFs_Dir_Trace(&me, dir);
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
