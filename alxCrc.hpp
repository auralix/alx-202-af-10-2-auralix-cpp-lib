/**
  ******************************************************************************
  * @file alxCrc.hpp
  * @brief Auralix C++ Library - ALX Crc Module
  * @version $LastChangedRevision: 4304 $
  * @date $LastChangedDate: 2021-03-09 21:22:50 +0100 (Tue, 09 Mar 2021) $
  ******************************************************************************
  */

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
				virtual uint32_t	Calc(uint8_t* data, uint32_t len) = 0;
				virtual bool		IsOk(uint8_t* dataWithCrc, uint32_t lenWithCrc, uint32_t* validatedCrc) = 0;
				virtual uint32_t	GetLen(void) = 0;
				virtual ::AlxCrc*	GetCStructPtr(void) = 0;
		};
		class Crc : public ICrc
		{
			public:
				//******************************************************************************
				// Public Functions
				//******************************************************************************
				Crc(AlxCrc_Config config)
				{
					AlxCrc_Ctor(&me, config);
				};
				virtual		~Crc() {};
				uint32_t	Calc(uint8_t* data, uint32_t len) override											{ return AlxCrc_Calc(&me, data, len); }
				bool		IsOk(uint8_t* dataWithCrc, uint32_t lenWithCrc, uint32_t* validatedCrc) override	{ return AlxCrc_IsOk(&me, dataWithCrc, lenWithCrc, validatedCrc); }
				uint32_t	GetLen(void) override																{ return AlxCrc_GetLen(&me); }
				::AlxCrc*	GetCStructPtr(void) override														{ return &me; }
			protected:
				//******************************************************************************
				// Protected Variables
				//******************************************************************************
				::AlxCrc me = { };
		};
	}
}

#endif // ALX_CRC_HPP
