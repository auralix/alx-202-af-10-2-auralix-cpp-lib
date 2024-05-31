/**
  ******************************************************************************
  * @file		alxNet.hpp
  * @brief		Auralix C++ Library - ALX Network Module
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
#ifndef ALX_NET_HPP
#define ALX_NET_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxNet.h"
#include "alxSpi.hpp"
#include "alxIoPin.h"

//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxNet
	{
		//******************************************************************************
		// Class - INet
		//******************************************************************************
		class INet
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				INet() {}
				virtual ~INet() {}		
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status Connect(void) = 0;
				virtual Alx_Status Disconnect(void) = 0;
				virtual bool IsConnected(void) = 0;
				virtual void SetMac(const char* mac) = 0;
				virtual void SetIp(const char* ip) = 0;
				virtual void SetNetmask(const char* netmask) = 0;
				virtual void SetGateway(const char* gateway) = 0;
				virtual const char* GetMac(void) = 0;
				virtual const char* GetIp(void) = 0;
				virtual const char* GetNetmask(void) = 0;
				virtual const char* GetGateway(void) = 0;
				virtual void Dns_SetIp(uint8_t dnsId, const char* ip) = 0;
				virtual Alx_Status Dns_GetHostByName(const char* hostname, char* ip) = 0;
				virtual void Dhcp_Enable(bool enable) = 0;
				virtual bool Dhcp_WasAddrSupplied(void) = 0;	
		};


		//******************************************************************************
		// Class - Net
		//******************************************************************************
		class Net : public INet
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Net
				(
					AlxNet_Config config,
					AlxSpi::ISpi* alxSpi,
					AlxIoPin::IIoPin* do_nRST,
					AlxIoPin::IIoPin* di_nINT
				)
				{
					AlxNet_Ctor
					(
						&me,
						config,
						alxSpi->GetCStructPtr(),
						do_nRST->GetCStructPtr(),
						di_nINT->GetCStructPtr()
					);
				}
				virtual ~Net() {}
				Alx_Status Init(void) override
				{
					if (me.config == AlxNet_Config_Wiznet)
					{
						return (AlxNet_Init(&me));
					}
					#if defined(ALX_FREE_RTOS_CELLULAR)
					else if (me.config == AlxNet_Config_FreeRtos_Cellular)
					{
						return AlxNet_Init(&me);
					}
					#endif
					return Alx_Err;
				}
				Alx_Status Connect(void) override
				{
					if (me.config == AlxNet_Config_Wiznet)
					{
						return (AlxNet_Connect(&me));
					}
					else if (me.config == AlxNet_Config_Wiznet)
					{
						// return (modem...);
					}
					return Alx_Err;
				}
				Alx_Status Disconnect(void) override
				{
					if (me.config == AlxNet_Config_Wiznet)
					{
						return (AlxNet_Disconnect(&me));
					}
					else if (me.config == AlxNet_Config_Wiznet)
					{
						// return (modem...);
					}
					return Alx_Err;
				}
				bool IsConnected(void) override
				{
					if (me.config == AlxNet_Config_Wiznet)
					{
						return (AlxNet_IsConnected(&me));
					}
					else if (me.config == AlxNet_Config_Wiznet)
					{
						// return (modem...);
					}
					return false;
				}
				void SetMac(const char* mac) override
				{
					if(me.config == AlxNet_Config_Wiznet)
					{
						AlxNet_SetMac(&me, mac);
					}
					else if (me.config == AlxNet_Config_Wiznet)
					{
						// (modem...);
					}
				}
				void SetIp(const char* ip) override
				{
					if(me.config == AlxNet_Config_Wiznet)
					{
						AlxNet_SetIp(&me, ip) ;
					}
					else if(me.config == AlxNet_Config_Wiznet)
					{
						// (modem...);
					}
				}
				void SetNetmask(const char* netmask) override
				{
					if (me.config == AlxNet_Config_Wiznet)
					{
						AlxNet_SetNetmask(&me, netmask);
					}
					else if (me.config == AlxNet_Config_Wiznet)
					{
						// (modem...);
					}
				}
				void SetGateway(const char* gateway) override
				{
					if (me.config == AlxNet_Config_Wiznet)
					{
						AlxNet_SetGateway(&me, gateway);
					}
					else if (me.config == AlxNet_Config_Wiznet)
					{
						// (modem...);
					}
				}
				const char* GetMac(void) override
				{
					if (me.config == AlxNet_Config_Wiznet)
					{
						return AlxNet_GetMac(&me);
					}
					else if (me.config == AlxNet_Config_Wiznet)
					{
						// return (modem...);
					}
					return NULL;
				}
				const char* GetIp(void) override
				{
					if (me.config == AlxNet_Config_Wiznet)
					{
						return AlxNet_GetIp(&me);
					}
					else if (me.config == AlxNet_Config_Wiznet)
					{
						// return (modem...);
					}
					return NULL;
				}
				const char* GetNetmask(void) override
				{
					if (me.config == AlxNet_Config_Wiznet)
					{
						return AlxNet_GetNetmask(&me);
					}
					else if (me.config == AlxNet_Config_Wiznet)
					{
						// return (modem...);
					}
					return NULL;
				}
				const char* GetGateway(void) override
				{
					if (me.config == AlxNet_Config_Wiznet)
					{
						return AlxNet_GetGateway(&me);
					}
					else if (me.config == AlxNet_Config_Wiznet)
					{
						// return (modem...);
					}
					return NULL;
				}
				void Dns_SetIp(uint8_t dnsId, const char* ip) override
				{
					if (me.config == AlxNet_Config_Wiznet)
					{
						AlxNet_Dns_SetIp(&me, dnsId, ip);
					}
					else if (me.config == AlxNet_Config_Wiznet)
					{
						// (modem...);
					}
				}
				Alx_Status Dns_GetHostByName(const char* hostname, char* ip) override
				{
					if (me.config == AlxNet_Config_Wiznet)
					{
						return AlxNet_Dns_GetHostByName(&me, hostname, ip);
					}
					else if (me.config == AlxNet_Config_Wiznet)
					{
						// return (modem...);
					}
					return Alx_Err;
				}
				void Dhcp_Enable(bool enable) override
				{
					if (me.config == AlxNet_Config_Wiznet)
					{
						AlxNet_Dhcp_Enable(&me, enable);
					}
					else if (me.config == AlxNet_Config_Wiznet)
					{
						// (modem...);
					}
				}
				bool Dhcp_WasAddrSupplied(void) override
				{
					if (me.config == AlxNet_Config_Wiznet)
					{
						return AlxNet_Dhcp_WasAddrSupplied(&me);
					}
					else if (me.config == AlxNet_Config_Wiznet)
					{
						// return (modem...);
					}
					return false;
				}
			//private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxNet me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_NET_HPP
