/**
  ******************************************************************************
  * @file		alxGlobal.hpp
  * @brief		Auralix C++ Library - ALX Global Module
  * @copyright	Copyright (C) 2020-2022 Auralix d.o.o. All rights reserved.
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
#ifndef ALX_GLOBAL_HPP
#define ALX_GLOBAL_HPP


//******************************************************************************
// Includes - ALX Config
//******************************************************************************
#include "alxConfig.h"


//******************************************************************************
// Includes - Google Test
//******************************************************************************
#if defined(ALX_GTEST)
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#endif


//******************************************************************************
// Includes - Mbed
//******************************************************************************
#if defined(ALX_MBED)
#include <mbed.h>
#include <EthernetInterface.h>
#include <SDBlockDevice.h>
#include <FATFileSystem.h>
#include <DeviceKey.h>
#include <kv_config.h>
#include "KVStore.h"
#include "kvstore_global_api.h"
#include <mbed_trace.h>
#endif
#if defined(ALX_MBED_CLOUD_CLIENT)
#include <mbed-cloud-client/MbedCloudClient.h>
#include <factory_configurator_client.h>
#endif


//******************************************************************************
// Includes - Auralix C Library Globals
//******************************************************************************
#include "alxGlobal.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxGlobal
	{
		//******************************************************************************
		// Functions
		//******************************************************************************
		static inline void DisableIrq(void)
		{
			#if defined(ALX_MBED)
			mbed::CriticalSectionLock::enable();
			#else
			AlxGlobal_DisableIrq();
			#endif
		}
		static inline void EnableIrq(void)
		{
			#if defined(ALX_MBED)
			mbed::CriticalSectionLock::disable();
			#else
			AlxGlobal_EnableIrq();
			#endif
		}
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_GLOBAL_HPP
