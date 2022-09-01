/**
  ******************************************************************************
  * @file		alxNtpClient.hpp
  * @brief		Auralix C++ Library - ALX NTP Client Module
  * @copyright	Copyright (C) 2020-2022 Auralix d.o.o. All rights reserved.
  *
  * @section License
  *
  * SPDX-License-Identifier: GPL-3.0-or-later
  *
  * This file is part of Auralix C Library.
  *
  * Auralix C Library is free software: you can redistribute it and/or
  * modify it under the terms of the GNU General Public License
  * as published by the Free Software Foundation, either version 3
  * of the License, or (at your option) any later version.
  *
  * Auralix C Library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with Auralix C Library. If not, see <https://www.gnu.org/licenses/>.
  ******************************************************************************
  **/

//******************************************************************************
// Include Guard
//******************************************************************************
#ifndef ALX_NTP_CLIENT_HPP
#define ALX_NTP_CLIENT_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxRtc.hpp>
#include <alxOsCriticalSection.hpp>


//******************************************************************************
// Preprocessor
//******************************************************************************
#define ALX_NTP_CLIENT_FILE "alxNtpClient.hpp"

// Assert //
#if defined(_ALX_NTP_CLIENT_ASSERT_BKPT) || defined(_ALX_ASSERT_BKPT_ALL)
	#define ALX_NTP_CLIENT_ASSERT(expr) ALX_ASSERT_BKPT(ALX_NTP_CLIENT_FILE, expr)
#elif defined(_ALX_NTP_CLIENT_ASSERT_TRACE) || defined(_ALX_ASSERT_TRACE_ALL)
	#define ALX_NTP_CLIENT_ASSERT(expr) ALX_ASSERT_TRACE(ALX_NTP_CLIENT_FILE, expr)
#elif defined(_ALX_NTP_CLIENT_ASSERT_RST) || defined(_ALX_ASSERT_RST_ALL)
	#define ALX_NTP_CLIENT_ASSERT(expr) ALX_ASSERT_RST(ALX_NTP_CLIENT_FILE, expr)
#else
	#define ALX_NTP_CLIENT_ASSERT(expr) do{} while (false)
#endif

// Trace //
#if defined(_ALX_NTP_CLIENT_TRACE) || defined(_ALX_TRACE_ALL)
	#define ALX_NTP_CLIENT_TRACE(...) ALX_TRACE_STD(ALX_NTP_CLIENT_FILE, __VA_ARGS__)
#else
	#define ALX_NTP_CLIENT_TRACE(...) do{} while (false)
#endif


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxNtpClient
	{
		enum class RxPacket_Header_LI
		{
			NTP_NoWarning      = 0b00,
			NTP_LastMinute61s  = 0b01,
			NTP_LastMinute59s  = 0b10,
			NTP_AlarmCondition = 0b11
		};
		enum class RxPacket_Header_VN
		{
			NTP_V0 = 0b000,
			NTP_V1 = 0b001,
			NTP_V2 = 0b010,
			NTP_V3 = 0b011,
			NTP_V4 = 0b100,
			NTP_V5 = 0b101,
			NTP_V6 = 0b110,
			NTP_V7 = 0b111,
		};
		enum class RxPacket_Header_Mode
		{
			NTP_Mode_reserved0 = 0b000,
			NTP_Mode_SymetricActive = 0b001,
			NTP_Mode_SymetricPassive = 0b010,
			NTP_Mode_Client = 0b011,
			NTP_Mode_Server = 0b100,
			NTP_Mode_Broadcast = 0b101,
			NTP_Mode_NtpControl = 0b110,
			NTP_Mode_reserved7 = 0b111,
		};
		union RxPacket_Header
		{
			struct __attribute__((packed))
			{
				RxPacket_Header_LI LI : 2;
				RxPacket_Header_VN VN : 3;
				RxPacket_Header_Mode MODE : 3;
				uint8_t STRAT : 8;
				uint8_t POLL : 8;
				uint8_t PREC : 8;
			};
			uint32_t raw;
		};
		struct RxPacket
		{
			RxPacket_Header header;
			uint32_t rootDelay;
			uint32_t rootDispersion;
			uint32_t refId;
			uint32_t refTimestamp_sec;
			uint32_t refTimestamp_fractSec;
			uint32_t origTimestamp_sec;
			uint32_t origTimestamp_fractSec;
			uint32_t recTimestamp_sec;
			uint32_t recTimestamp_fractSec;
			uint32_t transTimestamp_sec;
			uint32_t transTimestamp_fractSec;
		};

		class INtpClient
		{
			public:
				INtpClient() {};
				virtual ~INtpClient() {};
				virtual uint64_t GetUnixTime_ns(void) = 0;
				virtual uint64_t GetUnixTime_us(void) = 0;
				virtual uint64_t GetUnixTime_ms(void) = 0;
				virtual uint64_t GetUnixTime_sec(void) = 0;
				virtual Alx_Status GetRtcUnixTimeOffset_ns(int64_t* rtcUnixTimeOffset_ns) = 0;
				virtual Alx_Status GetRtcUnixTimeOffset_us(int64_t* rtcUnixTimeOffset_us) = 0;
				virtual Alx_Status GetRtcUnixTimeOffset_ms(int64_t* rtcUnixTimeOffset_ms) = 0;
				virtual Alx_Status GetRtcUnixTimeOffset_sec(int64_t* rtcUnixTimeOffset_sec) = 0;
		};
		#if defined(ALX_MBED)
		class NtpClient final : public INtpClient
		{
			public:
				//******************************************************************************
				// Public Functions
				//******************************************************************************
				NtpClient
				(
					Alx::AlxRtc::IRtc* rtc,
					NetworkInterface* net,
					char** serverIp,
					uint16_t* serverPort,
					bool* isServerIpHostnameFormat
				) :
					rtc(rtc),
					net(net),
					serverIp(serverIp),
					serverPort(serverPort),
					isServerIpHostnameFormat(isServerIpHostnameFormat)
				{};
				virtual ~NtpClient() {};
				uint64_t GetUnixTime_ns(void) override
				{
					ALX_NTP_CLIENT_ASSERT(false);
					return 0;
				}
				uint64_t GetUnixTime_us(void) override
				{
					return GetUnixTime_ns() / 1000;
				}
				uint64_t GetUnixTime_ms(void) override
				{
					return GetUnixTime_ns() / 1000000;
				}
				uint64_t GetUnixTime_sec(void) override
				{
					return GetUnixTime_ns() / 1000000000;
				}
				Alx_Status GetRtcUnixTimeOffset_ns(int64_t* rtcUnixTimeOffset_ns) override
				{
					// #1 Lock mutex
					mutex.lock();

					// #2 Assert
					ALX_NTP_CLIENT_ASSERT(net != nullptr);

					// #3 Prepare variables
					nsapi_error_t nsapiError = NSAPI_ERROR_NO_CONNECTION;
					nsapi_size_or_error_t  nsapiSizeOrError = NSAPI_ERROR_NO_CONNECTION;
					nsapi_connection_status_t nsapiConnectionStatus = NSAPI_STATUS_ERROR_UNSUPPORTED;

					// #4 Check if network is UP
					nsapiConnectionStatus = net->get_connection_status();
					if
					(
						(nsapiConnectionStatus != NSAPI_STATUS_LOCAL_UP) &&
						(nsapiConnectionStatus != NSAPI_STATUS_GLOBAL_UP)
					)
					{
						ALX_NTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiConnectionStatus);
						Reset();
						return Alx_Err;
					}

					// #5.1 Resolve server IP address if it is in hostname format
					if(*isServerIpHostnameFormat)
					{
						nsapiError = net->gethostbyname(*serverIp, &sockAddrServer);
						if (nsapiError != NSAPI_ERROR_OK)
						{
							ALX_NTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiError);
							Reset();
							return Alx_Err;
						}
					}
					// #5.2 Else use provided
					else
					{
						bool status = sockAddrServer.set_ip_address(*serverIp);
						if(status == false)
						{
							ALX_NTP_CLIENT_TRACE("Err: Invalid IP");
							Reset();
							return Alx_Err;
						}
					}

					// #6 Set server port
					sockAddrServer.set_port(*serverPort);	// No Return

					// #7 Set socket timeout
					sock.set_timeout(SOCK_TIMEOUT_ms);		// No Return

					// #8 Open socket
					nsapiError = sock.open(net);
					if (nsapiError != NSAPI_ERROR_OK)
					{
						ALX_NTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiError);
						Reset();
						return Alx_Err;
					}

					// #9 Connect socket
					nsapiError = sock.connect(sockAddrServer);
					if(nsapiError != NSAPI_ERROR_OK)
					{
						ALX_NTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiError);
						Reset();
						return Alx_Err;
					}

					// #10 Send request to server to get time
					Alx::AlxOsCriticalSection::Enter();
					ut.T1_ns = rtc->GetUnixTime_ns();
					Alx::AlxOsCriticalSection::Exit();
					nsapiSizeOrError = sock.send(txPacket, sizeof(txPacket));
					if (nsapiSizeOrError != sizeof(txPacket))
					{
						ALX_NTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
						Reset();
						return Alx_Err;
					}

					// #11 Receive data from server
					nsapiSizeOrError = sock.recv((void*)&rxPacket, sizeof(rxPacket));
					if (nsapiSizeOrError != 48)
					{
						ALX_NTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
						Reset();
						return Alx_Err;
					}
					Alx::AlxOsCriticalSection::Enter();
					ut.T4_ns = rtc->GetUnixTime_ns();
					Alx::AlxOsCriticalSection::Exit();

					// #12 Close Socket
					nsapiError = sock.close();
					if (nsapiError != NSAPI_ERROR_OK)
					{
						ALX_NTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiError);
						Reset();
						return Alx_Err;
					}

					// #13 Process raw data
					rxPacket.header.raw					= AlxGlobal_Ntohl(rxPacket.header.raw);
					rxPacket.rootDelay					= AlxGlobal_Ntohl(rxPacket.rootDelay);
					rxPacket.rootDispersion				= AlxGlobal_Ntohl(rxPacket.rootDispersion);
					rxPacket.refId						= AlxGlobal_Ntohl(rxPacket.refId);
					rxPacket.refTimestamp_sec			= AlxGlobal_Ntohl(rxPacket.refTimestamp_sec) - TIME_FROM_1900_TO_1970_sec;
					rxPacket.refTimestamp_fractSec		= AlxGlobal_Ntohl(rxPacket.refTimestamp_fractSec);
					rxPacket.origTimestamp_sec			= AlxGlobal_Ntohl(rxPacket.origTimestamp_sec) - TIME_FROM_1900_TO_1970_sec;
					rxPacket.origTimestamp_fractSec		= AlxGlobal_Ntohl(rxPacket.origTimestamp_fractSec);
					rxPacket.recTimestamp_sec			= AlxGlobal_Ntohl(rxPacket.recTimestamp_sec) - TIME_FROM_1900_TO_1970_sec;
					rxPacket.recTimestamp_fractSec		= AlxGlobal_Ntohl(rxPacket.recTimestamp_fractSec);
					rxPacket.transTimestamp_sec			= AlxGlobal_Ntohl(rxPacket.transTimestamp_sec) - TIME_FROM_1900_TO_1970_sec;
					rxPacket.transTimestamp_fractSec	= AlxGlobal_Ntohl(rxPacket.transTimestamp_fractSec);

					// #14 Calculate unix time offset in ns
					uint64_t T2_WholeNum_ns = (uint64_t)rxPacket.recTimestamp_sec * 1000000000ull;
					uint64_t T2_FractNum_ns = ((uint64_t)rxPacket.recTimestamp_fractSec * 1000000000ull) / 0xFFFFFFFFull;
					ut.T2_ns = T2_WholeNum_ns + T2_FractNum_ns;

					uint64_t T3_WholeNum_ns = (uint64_t)rxPacket.transTimestamp_sec * 1000000000ull;
					uint64_t T3_FractNum_ns = ((uint64_t)rxPacket.transTimestamp_fractSec * 1000000000ull) / 0xFFFFFFFFull;
					ut.T3_ns = T3_WholeNum_ns + T3_FractNum_ns;

					ut.offset_ns = (((int64_t)ut.T2_ns - (int64_t)ut.T1_ns) + ((int64_t)ut.T3_ns - (int64_t)ut.T4_ns)) / 2;
					ut.delay_ns = ((int64_t)ut.T4_ns - (int64_t)ut.T1_ns) - ((int64_t)ut.T3_ns - (int64_t)ut.T2_ns);

					// #15 Unlock mutex
					mutex.unlock();

					// #16 Return
					*rtcUnixTimeOffset_ns = ut.offset_ns;
					return Alx_Ok;
				}
				Alx_Status GetRtcUnixTimeOffset_us(int64_t* rtcUnixTimeOffset_us) override
				{
					int64_t offset_ns = 0;
					if(GetRtcUnixTimeOffset_ns(&offset_ns) != Alx_Ok) { return Alx_Err; };
					*rtcUnixTimeOffset_us = offset_ns / 1000;

					return Alx_Ok;
				}
				Alx_Status GetRtcUnixTimeOffset_ms(int64_t* rtcUnixTimeOffset_ms) override
				{
					int64_t offset_ns = 0;
					if(GetRtcUnixTimeOffset_ns(&offset_ns) != Alx_Ok) { return Alx_Err; };
					*rtcUnixTimeOffset_ms = offset_ns / 1000000;

					return Alx_Ok;
				}
				Alx_Status GetRtcUnixTimeOffset_sec(int64_t* rtcUnixTimeOffset_sec) override
				{
					int64_t offset_ns = 0;
					if(GetRtcUnixTimeOffset_ns(&offset_ns) != Alx_Ok) { return Alx_Err; };
					*rtcUnixTimeOffset_sec = offset_ns / 1000000000;

					return Alx_Ok;
				}
			private:
				//******************************************************************************
				// Private Variables
				//******************************************************************************
				// Parameters - Const
				const Kernel::Clock::duration_u32 RESET_WAIT_TIME_ms = 5000ms;	// TODO, UDP reset PCB duration, figure out?
				const int SOCK_TIMEOUT_ms = 30000;

				const uint32_t txPacket[12] = { '\x1b' };
				const uint64_t TIME_FROM_1900_TO_1970_sec = 2208988800;

				// Objects - External
				Alx::AlxRtc::IRtc* rtc = nullptr;
				NetworkInterface* net =  nullptr;

				// Objects - Internal
				SocketAddress sockAddrServer;
				UDPSocket sock;

				// Parameters
				char** serverIp = nullptr;
				uint16_t* serverPort = nullptr;
				bool* isServerIpHostnameFormat = nullptr;

				// Variables
				RxPacket rxPacket = {};
				struct UnixTime
				{
					uint64_t T1_ns = 0;
					uint64_t T2_ns = 0;
					uint64_t T3_ns = 0;
					uint64_t T4_ns = 0;
					int64_t offset_ns = 0;
					int64_t delay_ns = 0;
				} ut;

				// RTOS
				Mutex mutex;

				// Info

			private:
				//******************************************************************************
				// Private Functions
				//******************************************************************************
				void Reset(void)
				{
					// #1 Prepare variables
					nsapi_error_t nsapiError = NSAPI_ERROR_NO_CONNECTION;

					// #2 Close socket
					nsapiError = sock.close();
					if (nsapiError != NSAPI_ERROR_OK)
					{
						ALX_NTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiError);
					}

					// #3 Reset variables
					sockAddrServer.set_ip_address("000.000.000.000");
					sockAddrServer.set_port(0);
					memset(&rxPacket, 0, sizeof(rxPacket));
					ut.T1_ns = 0;
					ut.T2_ns = 0;
					ut.T3_ns = 0;
					ut.T4_ns = 0;
					ut.offset_ns = 0;
					ut.delay_ns = 0;

					// #4 Unlock mutex
					mutex.unlock();

					// #5 Sleep for RESET_WAIT_TIME
					ThisThread::sleep_for(RESET_WAIT_TIME_ms);
				};
		};
		#endif
	}
}

#endif // ALX_NTP_CLIENT_HPP
