//******************************************************************************
// @file alxCrc.hpp
// @brief Auralix C++ Library - ALX CRC Module
// @copyright Copyright (C) 2022 Auralix d.o.o. All rights reserved.
//******************************************************************************

#ifndef ALX_CRC_HPP
#define ALX_CRC_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxCrc.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxCrc
	{
		class ICrc
		{
			public:
				ICrc() {};
				virtual ~ICrc() {};
				virtual uint32_t Calc(uint8_t* data, uint32_t len) = 0;
				virtual bool IsOk(uint8_t* dataWithCrc, uint32_t lenWithCrc, uint32_t* validatedCrc) = 0;
				virtual uint32_t GetLen(void) = 0;
				virtual ::AlxCrc* GetCStructPtr(void) = 0;
		};
		class Crc : public ICrc
		{
			public:
				Crc
				(
					AlxCrc_Config config
				)
				{
					AlxCrc_Ctor(&me, config);
				};
				virtual ~Crc() {};
				uint32_t Calc(uint8_t* data, uint32_t len) override										{ return AlxCrc_Calc(&me, data, len); }
				bool IsOk(uint8_t* dataWithCrc, uint32_t lenWithCrc, uint32_t* validatedCrc) override	{ return AlxCrc_IsOk(&me, dataWithCrc, lenWithCrc, validatedCrc); }
				uint32_t GetLen(void) override															{ return AlxCrc_GetLen(&me); }
				::AlxCrc* GetCStructPtr(void) override													{ return &me; }
			protected:
				::AlxCrc me = {};
		};
	}
}

#endif	// #ifndef ALX_CRC_HPP
