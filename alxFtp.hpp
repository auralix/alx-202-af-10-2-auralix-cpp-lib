/**
  ******************************************************************************
  * @file		alxFtp.hpp
  * @brief		Auralix C++ Library - ALX FTP Module
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
#ifndef ALX_FTP_HPP
#define ALX_FTP_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxFtp.h"
#include "alxNet.hpp"
#include "alxFs.hpp"
#include "alxOsMutex.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxFtp
	{
		//******************************************************************************
		// Class - IFtp
		//******************************************************************************
		class IFtp
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IFtp() {}
				virtual ~IFtp() {}
				virtual void Client_SetServerAddr(const char* serverAddr) = 0;
				virtual void Client_SetServerAddrIsHostname(bool serverAddrIsHostname) = 0;
				virtual void Client_SetServerPort(uint16_t serverPort) = 0;
				virtual void Client_SetClientUsername(const char* clientUsername) = 0;
				virtual void Client_SetClientPassword(const char* clientPassword) = 0;
				virtual void Client_SetExtraFileHeader(const char* extraFileHeader) = 0;
				virtual Alx_Status Client_Login(void) = 0;
				virtual Alx_Status Client_Logout(void) = 0;
				virtual Alx_Status Client_ChangeDir(const char* path) = 0;
				virtual Alx_Status Client_MakeDir(const char* path) = 0;
				virtual Alx_Status Client_UploadFile(const char* localFilePath, const char* remoteFilePath, uint32_t* fileSize, Alx::AlxOsMutex::IAlxOsMutex* alxOsMutex_UploadFileInChunks) = 0;
				virtual ::AlxFtp* GetCStructPtr(void) = 0;
		};


		//******************************************************************************
		// Class - Ftp
		//******************************************************************************
		class Ftp : public IFtp
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Ftp
				(
					AlxNet::INet* alxNet,
					AlxFs::IFs* alxFs
				)
				{
					AlxFtp_Ctor
					(
						&me,
						alxNet->GetCStructPtr(),
						alxFs->GetCStructPtr()
					);
				}
				virtual ~Ftp() {}
				void Client_SetServerAddr(const char* serverAddr) override
				{
					AlxFtp_Client_SetServerAddr(&me, serverAddr);
				}
				void Client_SetServerAddrIsHostname(bool serverAddrIsHostname) override
				{
					AlxFtp_Client_SetServerAddrIsHostname(&me, serverAddrIsHostname);
				}
				void Client_SetServerPort(uint16_t serverPort) override
				{
					AlxFtp_Client_SetServerPort(&me, serverPort);
				}
				void Client_SetClientUsername(const char* clientUsername) override
				{
					AlxFtp_Client_SetClientUsername(&me, clientUsername);
				}
				void Client_SetClientPassword(const char* clientPassword) override
				{
					AlxFtp_Client_SetClientPassword(&me, clientPassword);
				}
				void Client_SetExtraFileHeader(const char* extraFileHeader) override
				{
					AlxFtp_Client_SetExtraFileHeader(&me, extraFileHeader);
				}
				Alx_Status Client_Login(void) override
				{
					return AlxFtp_Client_Login(&me);
				}
				Alx_Status Client_Logout(void) override
				{
					return AlxFtp_Client_Logout(&me);
				}
				Alx_Status Client_ChangeDir(const char* path) override
				{
					return AlxFtp_Client_ChangeDir(&me, path);
				}
				Alx_Status Client_MakeDir(const char* path) override
				{
					return AlxFtp_Client_MakeDir(&me, path);
				}
				Alx_Status Client_UploadFile(const char* localFilePath, const char* remoteFilePath, uint32_t* fileSize, Alx::AlxOsMutex::IAlxOsMutex* alxOsMutex_UploadFileInChunks) override
				{
					::AlxOsMutex* _alxOsMutex_UploadFileInChunks = NULL;
					if (alxOsMutex_UploadFileInChunks != nullptr) _alxOsMutex_UploadFileInChunks = alxOsMutex_UploadFileInChunks->GetCStructPtr();
					return AlxFtp_Client_UploadFile(&me, localFilePath, remoteFilePath, fileSize, _alxOsMutex_UploadFileInChunks);
				}
				::AlxFtp* GetCStructPtr(void) override
				{
					return &me;
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxFtp me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_FTP_HPP
