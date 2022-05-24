//******************************************************************************
// @file alxMemRaw.hpp
// @brief Auralix C++ Library - ALX Memory Raw Module
// @copyright Copyright (C) 2022 Auralix d.o.o. All rights reserved.
//******************************************************************************

#ifndef ALX_MEM_RAW_HPP
#define ALX_MEM_RAW_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxMemRaw.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxMemRaw
	{
		class IMemRaw
		{
			public:
				IMemRaw() {};
				virtual ~IMemRaw() {};
				virtual ::Alx_Status Init(void) = 0;
				virtual ::Alx_Status DeInit(void) = 0;
				virtual ::Alx_Status Read(uint32_t addr, uint8_t* data, uint32_t len, uint8_t numOfTries, uint16_t timeout_ms) = 0;
				virtual ::Alx_Status Write(uint32_t addr, uint8_t* data, uint32_t len, bool checkWithReadEnable, uint8_t numOfTries, uint16_t timeout_ms) = 0;
				virtual ::AlxMemRaw* GetCStructPtr(void) = 0;
		};
		class MemRaw : public IMemRaw
		{
			public:
				MemRaw()
				{
					AlxMemRaw_Ctor(&me);
				};
				virtual ~MemRaw() {};
				::Alx_Status Init(void) override																											{ return AlxMemRaw_Init(&me); }
				::Alx_Status DeInit(void) override																											{ return AlxMemRaw_DeInit(&me); }
				::Alx_Status Read(uint32_t addr, uint8_t* data, uint32_t len, uint8_t numOfTries, uint16_t timeout_ms) override								{ return AlxMemRaw_Read(&me, addr, data, len, numOfTries, timeout_ms); }
				::Alx_Status Write(uint32_t addr, uint8_t* data, uint32_t len, bool checkWithReadEnable, uint8_t numOfTries, uint16_t timeout_ms) override	{ return AlxMemRaw_Write(&me, addr, data, len, checkWithReadEnable, numOfTries, timeout_ms); }
				::AlxMemRaw* GetCStructPtr(void) override																									{ return &me; }
			protected:
				::AlxMemRaw me = {};
		};
	}
}

#endif	// #ifndef ALX_MEM_RAW_HPP
