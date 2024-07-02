/**
  ******************************************************************************
  * @file		alxSocket.hpp
  * @brief		Auralix C++ Library - ALX Socket Module
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
#ifndef ALX_SOCKET_HPP
#define ALX_SOCKET_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxNet.hpp"
#include "alxNet.h"
#include "alxSocket.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxSocket
	{
		//******************************************************************************
		// Class - ISocket
		//******************************************************************************
		class ISocket
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ISocket() {}
				virtual ~ISocket() {}
				virtual Alx_Status Open(AlxNet::Net* network, AlxSocket_Protocol protocol) = 0;
				virtual Alx_Status Close(void) = 0;
				virtual Alx_Status Connect(const char* ip, uint16_t port) = 0;
				virtual Alx_Status Bind(uint16_t port) = 0;
				virtual Alx_Status Listen(uint8_t backlog) = 0;
				virtual ISocket* Accept(void) = 0;
				virtual int32_t Send(void* data, uint32_t len) = 0;
				virtual int32_t Recv(void* data, uint32_t len) = 0;
				virtual void SetTimeout_ms(uint32_t timeout_ms) = 0;
				#if defined(ALX_MBEDTLS)
				virtual Alx_Status InitTls(
					const char *server_cn,
					const unsigned char *ca_cert,
					const unsigned char *cl_cert,
					const unsigned char *cl_key
				) = 0;
				#endif
		};


		//******************************************************************************
		// Class - Socket
		//******************************************************************************
		class Socket : public ISocket
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Socket
				(
				)
				{
					AlxSocket_Ctor
					(
						&me
					);
				}
				Socket
				(
					::AlxSocket *sock
				)
				{
					memcpy(&me, sock, sizeof(me));
				}
				virtual ~Socket() {
					Close();
				}
			Alx_Status Open(AlxNet::Net* network, AlxSocket_Protocol protocol) override
				{
					return AlxSocket_Open(&me, network->GetMePtr(), protocol);
				}
				Alx_Status Close(void) override
				{
					return AlxSocket_Close(&me);
				}
				Alx_Status Connect(const char* ip, uint16_t port) override
				{
					return AlxSocket_Connect(&me, ip, port);
				}
				Alx_Status Bind(uint16_t port) override
				{
					return AlxSocket_Bind(&me, port);
				}
				Alx_Status Listen(uint8_t backlog) override
				{
					return AlxSocket_Listen(&me, backlog);
				}
				Socket* Accept(void) override
				{
					::AlxSocket* sock = AlxSocket_Accept(&me);
					if (sock)
					{
						return new Socket(sock);
					}
					return NULL;
				}
				int32_t Send(void* data, uint32_t len) override
				{
					return AlxSocket_Send(&me, data, len);
				}
				int32_t Recv(void* data, uint32_t len) override
				{
					return AlxSocket_Recv(&me, data, len);
				}
				void SetTimeout_ms(uint32_t timeout_ms) override
				{
					AlxSocket_SetTimeout_ms(&me, timeout_ms);
				}
				#if defined(ALX_MBEDTLS)
				Alx_Status InitTls(
					const char *server_cn,
					const unsigned char *ca_cert,
					const unsigned char *cl_cert,
					const unsigned char *cl_key
				) override
				{
					return AlxSocket_InitTls(
						&me,
						server_cn,
						ca_cert,
						cl_cert,
						cl_key);
				}
				#endif
			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxSocket me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_SOCKET_HPP
