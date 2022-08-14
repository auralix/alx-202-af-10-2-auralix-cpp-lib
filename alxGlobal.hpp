/**
  ******************************************************************************
  * @file alxGlobal.hpp
  * @brief Auralix C++ Library - ALX Global Module
  * @version $LastChangedRevision: 5720 $
  * @date $LastChangedDate: 2021-08-02 23:21:08 +0200 (Mon, 02 Aug 2021) $
  ******************************************************************************
  */

#ifndef ALX_GLOBAL_HPP
#define ALX_GLOBAL_HPP

//******************************************************************************
// Includes - ALX Config
//******************************************************************************
#include "alxConfig.h"


//******************************************************************************
// Includes - Google Test
//******************************************************************************
#if defined (ALX_GTEST)
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
#include <alxGlobal.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxGlobal
	{
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

#endif // ALX_GLOBAL_HPP
