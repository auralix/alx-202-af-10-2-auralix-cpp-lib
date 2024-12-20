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
				virtual Alx_Status Restart(void) = 0;
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
				virtual AlxNet_Config GetNetInterface(void) = 0;
				#if defined(ALX_FREE_RTOS_CELLULAR)
				virtual void GetCellularSignalInfo(int8_t *rssi, uint8_t *ber) = 0;
				#endif
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
						alxSpi != nullptr ? alxSpi->GetCStructPtr() : nullptr,
						do_nRST != nullptr ? do_nRST->GetCStructPtr() : nullptr,
						di_nINT != nullptr ? di_nINT->GetCStructPtr() : nullptr
					);
				}
				virtual ~Net() {}
				Alx_Status Init(void) override
				{
					return (AlxNet_Init(&me));
				}
				Alx_Status Connect(void) override
				{
					return (AlxNet_Connect(&me));
				}
				Alx_Status Disconnect(void) override
				{
					return (AlxNet_Disconnect(&me));
				}
				Alx_Status Restart(void) override
				{
					return (AlxNet_Restart(&me));
				}
				bool IsConnected(void) override
				{
					return (AlxNet_IsConnected(&me));
				}
				void SetMac(const char* mac) override
				{
					AlxNet_SetMac(&me, mac);
				}
				void SetIp(const char* ip) override
				{
					AlxNet_SetIp(&me, ip) ;
				}
				void SetNetmask(const char* netmask) override
				{
					AlxNet_SetNetmask(&me, netmask);
				}
				void SetGateway(const char* gateway) override
				{
					AlxNet_SetGateway(&me, gateway);
				}
				const char* GetMac(void) override
				{
					return AlxNet_GetMac(&me);
				}
				const char* GetIp(void) override
				{
					return AlxNet_GetIp(&me);
				}
				const char* GetNetmask(void) override
				{
					return AlxNet_GetNetmask(&me);
				}
				const char* GetGateway(void) override
				{
					return AlxNet_GetGateway(&me);
				}
				void Dns_SetIp(uint8_t dnsId, const char* ip) override
				{
					AlxNet_Dns_SetIp(&me, dnsId, ip);
				}
				Alx_Status Dns_GetHostByName(const char* hostname, char* ip) override
				{
					return AlxNet_Dns_GetHostByName(&me, hostname, ip);
				}
				void Dhcp_Enable(bool enable) override
				{
					AlxNet_Dhcp_Enable(&me, enable);
				}
				bool Dhcp_WasAddrSupplied(void) override
				{
					return AlxNet_Dhcp_WasAddrSupplied(&me);
				}
				AlxNet_Config GetNetInterface(void) override
				{
					return Alx_GetNetInterface(&me);
				}
				#if defined(ALX_FREE_RTOS_CELLULAR)
				void GetCellularSignalInfo(int8_t *rssi, uint8_t *ber) override
				{
					return Alx_GetCellularSignalQuality(&me, rssi, ber);
				}
				#endif
				::AlxNet* GetMePtr(void)
				{
					return &me;
				}
			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxNet me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_NET_HPP
