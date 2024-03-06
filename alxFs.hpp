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
				virtual Alx_Status Format(void) = 0;
				virtual Alx_Status Remove(const char* path) = 0;
				virtual Alx_Status File_Open(AlxFs_File* file, const char* path, int32_t flags) = 0;
				virtual Alx_Status File_Close(AlxFs_File* file) = 0;
				virtual int32_t File_Read(AlxFs_File* file, void* buff, uint32_t len) = 0;
				virtual int32_t File_Write(AlxFs_File* file, void* buff, uint32_t len) = 0;
				virtual Alx_Status File_Sync(AlxFs_File* file) = 0;
				virtual int32_t File_Seek(AlxFs_File* file, int32_t offset, int32_t whence) = 0;
				virtual int32_t File_Tell(AlxFs_File* file) = 0;
				virtual int32_t File_Size(AlxFs_File* file) = 0;
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
				Fs()
				{
					AlxFs_Ctor(&me);
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
				Alx_Status Format(void) override
				{
					return AlxFs_Format(&me);
				}
				Alx_Status Remove(const char* path) override
				{
					return AlxFs_Remove(&me, path);
				}
				Alx_Status File_Open(AlxFs_File* file, const char* path, int32_t flags) override
				{
					return AlxFs_File_Open(&me, file, path, flags);
				}
				Alx_Status File_Close(AlxFs_File* file) override
				{
					return AlxFs_File_Close(&me, file);
				}
				int32_t File_Read(AlxFs_File* file, void* buff, uint32_t len) override
				{
					return AlxFs_File_Read(&me, file, buff, len);
				}
				int32_t File_Write(AlxFs_File* file, void* buff, uint32_t len) override
				{
					return AlxFs_File_Write(&me, file, buff, len);
				}
				Alx_Status File_Sync(AlxFs_File* file) override
				{
					return AlxFs_File_Sync(&me, file);
				}
				int32_t File_Seek(AlxFs_File* file, int32_t offset, int32_t whence) override
				{
					return AlxFs_File_Seek(&me, file, offset, whence);
				}
				int32_t File_Tell(AlxFs_File* file) override
				{
					return AlxFs_File_Tell(&me, file);
				}
				int32_t File_Size(AlxFs_File* file) override
				{
					return AlxFs_File_Size(&me, file);
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
