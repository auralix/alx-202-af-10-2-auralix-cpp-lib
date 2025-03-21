/**
  ******************************************************************************
  * @file		alxFtpClient.hpp
  * @brief		Auralix C++ Library - ALX FTP Client Module
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
#ifndef ALX_FTP_CLIENT_HPP
#define ALX_FTP_CLIENT_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxNet.hpp"
#include "alxSocket.hpp"
#include "alxOsMutex.hpp"
#include "alxOsDelay.h"

//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Preprocessor
//******************************************************************************
#define ALX_FTP_CLIENT_FILE "alxFtpClient.hpp"

// Assert //
#if defined(ALX_FTP_CLIENT_ASSERT_BKPT_ENABLE)
	#define ALX_FTP_CLIENT_ASSERT(expr) ALX_ASSERT_BKPT(ALX_FTP_CLIENT_FILE, expr)
#elif defined(ALX_FTP_CLIENT_ASSERT_TRACE_ENABLE)
	#define ALX_FTP_CLIENT_ASSERT(expr) ALX_ASSERT_TRACE(ALX_FTP_CLIENT_FILE, expr)
#elif defined(ALX_FTP_CLIENT_ASSERT_RST_ENABLE)
	#define ALX_FTP_CLIENT_ASSERT(expr) ALX_ASSERT_RST(ALX_FTP_CLIENT_FILE, expr)
#else
	#define ALX_FTP_CLIENT_ASSERT(expr) do{} while (false)
#endif

// Trace //
#if defined(ALX_FTP_CLIENT_TRACE_ENABLE)
	#define ALX_FTP_CLIENT_TRACE(...) ALX_TRACE_WRN(ALX_FTP_CLIENT_FILE, __VA_ARGS__)
#else
	#define ALX_FTP_CLIENT_TRACE(...) do{} while (false)
#endif


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxFtpClient
	{
		//******************************************************************************
		// Class - IFtpClient
		//******************************************************************************
		class IFtpClient
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IFtpClient() {}
				virtual ~IFtpClient() {}
				virtual Alx_Status Login(void) = 0;
				virtual Alx_Status Logout(void) = 0;
				virtual Alx_Status SendFile(const char* rootDir, const char* filename) = 0;
		};


		//******************************************************************************
		// Class - FtpClient
		//******************************************************************************
		template <uint32_t BUFF_LEN = 1460>
		class FtpClient : public IFtpClient
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				FtpClient
				(
					Alx::AlxNet::Net* net,
					char* serverIp,
					uint16_t* serverPort,
					char* username,
					char* password,
					bool* isServerIpHostnameFormat)
					: net(net)
					, serverIp(serverIp)
					, serverPort(serverPort)
					, username(username)
					, password(password)
					, isServerIpHostnameFormat(isServerIpHostnameFormat)
				{}
				virtual ~FtpClient() {}
				Alx_Status Login(void) override
				{
					// #1 Lock mutex
					mutex.Lock();

					// #2 Assert
					ALX_FTP_CLIENT_ASSERT(isLogin == false);

					// #3 Prepare variables
					int nsapiError;
					int  nsapiSizeOrError;
					int nsapiConnectionStatus;
					uint32_t len = 0;

					// Allocate memory
					buff = (char*)calloc(BUFF_LEN, sizeof(char));

					// #4 Check if network is UP
					if (!net->IsConnected())
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiConnectionStatus);
						Reset();
						return Alx_Err;
					}

					// #5.1 Resolve server IP address if it is in hostname format
					if (*isServerIpHostnameFormat)
					{
						if(net->Dns_GetHostByName(serverIp, ctrlSockAddrServer) != Alx_Ok) // FTP server IP is IP of FTP server control socket IP
						{
							ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiError);
							Reset();
							return Alx_Err;
						}
					}
					// #5.2 Else use provided
					else
					{
						strcpy(ctrlSockAddrServer, serverIp);
	//						bool status = ctrlSockAddrServer.set_ip_address(serverIp); // FTP server IP is IP of FTP server control socket IP
	//						if (status == false)
	//						{
	//							ALX_FTP_CLIENT_TRACE("Err: Invalid IP");
	//							Reset();
	//							return Alx_Err;
	//						}
					}

					// #6 Set server control socket port
					ctrlSockAddrServer_Port = *serverPort; // No Return -> FTP server port is port of FTP server control socket port

					// #7 Set control socket timeout
					ctrlSock.SetTimeout_ms(CTRL_SOCK_TIMEOUT_ms); // No Return

					// #8 Open control socket
					if (ctrlSock.Open(net, AlxSocket_Protocol_Tcp) != Alx_Ok)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiError);
						Reset();
						return Alx_Err;
					}

					// #9 Connect control socket
					if (ctrlSock.Connect(ctrlSockAddrServer, ctrlSockAddrServer_Port) != Alx_Ok)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiError);
						Reset();
						return Alx_Err;
					}

					// #10 Receive response from server
					nsapiSizeOrError = ctrlSock.Recv(buff, BUFF_LEN);
					if (nsapiSizeOrError <= 0)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
						Reset();
						return Alx_Err;
					}

					// #11 Expected response: "220" -> Service ready for new user
					if (strncmp(buff, "220", 3) != 0)
					{
						ALX_FTP_CLIENT_TRACE("Err");
						Reset();
						return Alx_Err;
					}

					// #12 Send username
					sprintf(buff, "user %s\r\n", username);
					len = strlen(buff);
					nsapiSizeOrError = ctrlSock.Send(buff, len);
					if (nsapiSizeOrError != len)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
						Reset();
						return Alx_Err;
					}

					// #13 Receive response from server
					nsapiSizeOrError = ctrlSock.Recv(buff, BUFF_LEN);
					if (nsapiSizeOrError <= 0)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
						Reset();
						return Alx_Err;
					}

					// #14 Expected response: "331" -> User name OK, need password
					if (strncmp(buff, "331", 3) != 0)
					{
						ALX_FTP_CLIENT_TRACE("Err");
						Reset();
						return Alx_Err;
					}

					// #15 Send password
					sprintf(buff, "pass %s\r\n", password);
					len = strlen(buff);
					nsapiSizeOrError = ctrlSock.Send(buff, len);
					if (nsapiSizeOrError != len)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
						Reset();
						return Alx_Err;
					}

					// #16 Receive response from server
					nsapiSizeOrError = ctrlSock.Recv(buff, BUFF_LEN);
					if (nsapiSizeOrError <= 0)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
						Reset();
						return Alx_Err;
					}

					// #17 Expected response: "230" -> User logged in, proceed
					if (strncmp(buff, "230", 3) != 0)
					{
						ALX_FTP_CLIENT_TRACE("Err");
						Reset();
						return Alx_Err;
					}

					// #18 Send command to select ASCII type transfer
					sprintf(buff, "type I\r\n");
					len = strlen(buff);
					nsapiSizeOrError = ctrlSock.Send(buff, len);
					if (nsapiSizeOrError != len)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
						Reset();
						return Alx_Err;
					}

					// #19 Receive response from server
					nsapiSizeOrError = ctrlSock.Recv(buff, BUFF_LEN);
					if (nsapiSizeOrError <= 0)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
						Reset();
						return Alx_Err;
					}

					// #20 Set isLogin
					isLogin = true;

					// #21 Unlock mutex
					mutex.Unlock();

					// #22 Retutn OK
					return Alx_Ok;
				}
				Alx_Status Logout(void) override
				{
					// #1 Lock mutex
					mutex.Lock();

					// #2 Assert
					ALX_FTP_CLIENT_ASSERT(isLogin == true);

					// #3 Prepare variables
					int nsapiError;
					int  nsapiSizeOrError;
					uint32_t len = 0;

					// #4 Send command to Quit
					sprintf(buff, "quit\r\n");
					len = strlen(buff);
					nsapiSizeOrError = ctrlSock.Send(buff, len);
					if (nsapiSizeOrError != len)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
						Reset();
						return Alx_Err;
					}

					// #5 Receive response from server
					nsapiSizeOrError = ctrlSock.Recv(buff, BUFF_LEN);
					if (nsapiSizeOrError <= 0)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
						Reset();
						return Alx_Err;
					}

					// #6 Expected response: "221" -> Service closing control connection
					if (strncmp(buff, "221", 3) != 0)
					{
						ALX_FTP_CLIENT_TRACE("Err");
						Reset();
						return Alx_Err;
					}

					// Free memory
					free(buff);

					// #7 Close control socket
					if (ctrlSock.Close() != Alx_Ok)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiError);
						Reset();
						return Alx_Err;
					}

					// #8 Reset isLogin
					isLogin = false;

					// #9 Unlock mutex
					mutex.Unlock();

					// #10 Return OK
					return Alx_Ok;
				}
				Alx_Status SendFile(const char *rootDir, const char* filename) override
				{
					// #1 Lock mutex
					mutex.Lock();

					// #2 Assert
					ALX_FTP_CLIENT_ASSERT(isLogin == true);

					// #3 Prepare variables
					Alx_Status nsapiError;
					int  nsapiSizeOrError;
					char* token = nullptr;
					char* ptr = nullptr;
					uint32_t len = 0;


					//******************************************************************************
					// Handle Open Data Socket
					//******************************************************************************
					// #4 Send command to enter passive mode
					sprintf(buff, "pasv\r\n"); // We will not handle return
					len = strlen(buff);
					nsapiSizeOrError = ctrlSock.Send(buff, len);
					if (nsapiSizeOrError != len)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
						Reset();
						return Alx_Err;
					}

					// #5 Receive response from server
					nsapiSizeOrError = ctrlSock.Recv(buff, BUFF_LEN);
					if (nsapiSizeOrError <= 0)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
						Reset();
						return Alx_Err;
					}

					// #6 Expected response: "227" -> Entering passive mode
					if (strncmp(buff, "227", 3) != 0)
					{
						ALX_FTP_CLIENT_TRACE("Err");
						Reset();
						return Alx_Err;
					}

					// #7 Get IP and port from the recieved message
					token = strchr(buff, '(') + 1;
					for (uint32_t i = 0; i < 4; i++)
					{
						token = strtok_r(token, ",", &ptr);
						dataSockIpArr[i] = (uint8_t)atoi(token);
						token = ptr;
						if (token == nullptr)
						{
							ALX_FTP_CLIENT_TRACE("Err");
							Reset();
							return Alx_Err;
						}
					}
					for (uint32_t i = 0; i < 2; i++)
					{
						token = strtok_r(token, ",)", &ptr);
						dataSockPort <<= 8;
						dataSockPort += atoi(token);
						token = ptr;
						if (token == nullptr)
						{
							ALX_FTP_CLIENT_TRACE("Err");
							Reset();
							return Alx_Err;
						}
					}

					// #8 Set ip addres and port
					sprintf(dataSockIpStr, "%d.%d.%d.%d", dataSockIpArr[0], dataSockIpArr[1], dataSockIpArr[2], dataSockIpArr[3]);
					dataSockAddrServer_Port = dataSockPort; // No Return

					// #9 Set data socket timeout
					dataSock.SetTimeout_ms(DATA_SOCK_TIMEOUT_ms); // No Return

					// #10 Open data socket
					if (dataSock.Open(net, AlxSocket_Protocol_Tcp) != Alx_Ok)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiError);
						Reset();
						return Alx_Err;
					}

					// #11 Connect data socket (retry 20 times)
					nsapiError = Alx_Err;
					for (uint32_t _try = 0; _try < 20; _try++)
					{
						if (dataSock.Connect(dataSockAddrServer, dataSockAddrServer_Port) == Alx_Ok)
						{
							nsapiError = Alx_Ok;
							break;
						}
						AlxOsDelay_ms(&alxOsDelay, 1);
					}
					if (nsapiError != Alx_Ok)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiError);
						Reset();
						return Alx_Err;
					}


					//******************************************************************************
					// Handle Send File
					//******************************************************************************
					// #12 Send command to initiate sending file to the server
					sprintf(buff, "stor %s\r\n", filename);
					len = strlen(buff);
					nsapiSizeOrError = ctrlSock.Send(buff, len);
					if (nsapiSizeOrError != len)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
						Reset();
						return Alx_Err;
					}

					// #13 Receive response from server
					nsapiSizeOrError = ctrlSock.Recv(buff, BUFF_LEN);
					if (nsapiSizeOrError <= 0)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
						Reset();
						return Alx_Err;
					}

					// #14 Expected response: "150" -> File status okay, about to open data connection OR "125" -> Data connection already open, transfer starting
					if ((strncmp(buff, "150", 3) != 0) && (strncmp(buff, "125", 3) != 0))
					{
						ALX_FTP_CLIENT_TRACE("Err");
						Reset();
						return Alx_Err;
					}

					// #15 Open file and get file size
					sprintf(buff, "%s/%s", rootDir, filename); // We will not handle return
					fp = fopen(buff, "r"); // We will not handle return
					if (fseek(fp, 0, SEEK_END) != 0)				// Sets "cursor" at the end of the file
					{
						ALX_FTP_CLIENT_TRACE("Err");
						Reset();
						return Alx_Err;
					}
					lenRemain = ftell(fp); // Returns the current value of the position indicator of the stream - We will not handle return
					if (fseek(fp, 0, SEEK_SET) != 0)				// Sets "cursor" at the beginning of the file
					{
						ALX_FTP_CLIENT_TRACE("Err");
						Reset();
						return Alx_Err;
					}

					// #16 Stay in the loop until the file is sent
					while (lenRemain > 0)
					{
						if (lenRemain > BUFF_LEN)
						{
							lenSend = BUFF_LEN;
						}
						else
						{
							lenSend = lenRemain;
						}
						fread(buff, 1, lenSend, fp); // We will not handle return
						len = strlen(buff);
						nsapiSizeOrError = dataSock.Send(buff, lenSend);
						if (nsapiSizeOrError != lenSend)
						{
							ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
							Reset();
							return Alx_Err;
						}

						lenRemain = lenRemain - lenSend;
					}

					// #17 Close file
					fclose(fp); // We will not handle return


					//******************************************************************************
					// Handle Close Data Socket
					//******************************************************************************
					// #18 Close data socket
					if (dataSock.Close() != Alx_Ok)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiError);
						Reset();
						return Alx_Err;
					}

					// #19 Receive response from server
					nsapiSizeOrError = ctrlSock.Recv(buff, BUFF_LEN);
					if (nsapiSizeOrError <= 0)
					{
						ALX_FTP_CLIENT_TRACE("Err: %d", (int32_t)nsapiSizeOrError);
						Reset();
						return Alx_Err;
					}

					// #20 Expected response: "226" -> Closing data connection, requested file action successful
					if (strncmp(buff, "226", 3) != 0)
					{
						ALX_FTP_CLIENT_TRACE("Err");
						Reset();
						return Alx_Err;
					}

					// #21 Unlock mutex
					mutex.Unlock();

					// #22 Return OK
					return Alx_Ok;
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------

				// Parameters - Const
				const uint32_t RESET_WAIT_TIME_min = 5;
				const int CTRL_SOCK_TIMEOUT_ms = 30000;
				const int DATA_SOCK_TIMEOUT_ms = 30000;

				// Objects - External
				Alx::AlxNet::Net* net =  nullptr;

				// Objects - Internal - Parameters
				char ctrlSockAddrServer[16];
				uint16_t ctrlSockAddrServer_Port;

				// Objects - Internal - Variables
				char dataSockAddrServer[16];
				uint16_t dataSockAddrServer_Port;
				Alx::AlxSocket::Socket ctrlSock;
				Alx::AlxSocket::Socket dataSock;

				// Parameters
				char* serverIp = nullptr;
				uint16_t* serverPort = nullptr;
				char* username = nullptr;
				char* password = nullptr;
				bool* isServerIpHostnameFormat = nullptr;

				// Variables
				char* buff = nullptr;
				uint8_t dataSockIpArr[4] = { };
				char dataSockIpStr[20] = { };
				uint16_t dataSockPort = 0;
				FILE* fp = nullptr;
				uint32_t lenRemain = 0;
				uint32_t lenSend = 0;

				// RTOS
				Alx::AlxOsMutex::AlxOsMutex mutex;

				// Info
				bool isLogin = false;

			private:
				//------------------------------------------------------------------------------
				// Private Functions
				//------------------------------------------------------------------------------
				void Reset(void)
				{
					// #1 Prepare variables
					int nsapiError;

					// #2 Close sockets
					if (dataSock.Close() != Alx_Ok)
					{
						ALX_FTP_CLIENT_TRACE("Err_DataSock: %d", (int32_t)nsapiError);
					}
					if (ctrlSock.Close() != Alx_Ok)
					{
						ALX_FTP_CLIENT_TRACE("Err_CtrlSock: %d", (int32_t)nsapiError);
					}

					// #3 Close file
					fclose(fp); // We will not handle return

					// #4 Reset variables

					// Objects - Internal - Variables
					strcpy(dataSockAddrServer, "000.000.000.000");
					dataSockAddrServer_Port = 0;

					// Variables
					buff = nullptr;
					memset(dataSockIpArr, 0, sizeof(dataSockIpArr));
					memset(dataSockIpStr, 0, sizeof(dataSockIpStr));
					dataSockPort = 0;
					fp = nullptr;
					lenRemain = 0;
					lenSend = 0;

					// Info
					isLogin = false;

					// #5 Unlock mutex
					mutex.Unlock();

					// #6 Sleep for RESET_WAIT_TIME
					AlxOsDelay_min(&alxOsDelay, RESET_WAIT_TIME_min);
				}
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_FTP_CLIENT_HPP
