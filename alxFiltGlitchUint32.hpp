/**
  ******************************************************************************
  * @file alxFiltGlitchUint32.hpp
  * @brief Auralix C++ Library - ALX Fliter Glitch Uint32 Module
  * @version $LastChangedRevision: 4304 $
  * @date $LastChangedDate: 2021-03-09 21:22:50 +0100 (Tue, 09 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_FILT_GLITCH_UINT32_HPP
#define ALX_FILT_GLITCH_UINT32_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxFiltGlitchUint32.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxFiltGlitchUint32
	{
		class IFiltGlitchUint32
		{
			public:
				IFiltGlitchUint32() {};
				virtual ~IFiltGlitchUint32() {};
				virtual uint32_t Process(uint32_t in) = 0;
		};
		class FiltGlitchUint32 final : public IFiltGlitchUint32
		{
			public:
				FiltGlitchUint32
				(
					uint32_t valInitial,
					float stableTime_ms
				)
				{
					AlxFiltGlitchUint32_Ctor(&me, valInitial, stableTime_ms);
				};
				virtual ~FiltGlitchUint32() {};
				uint32_t Process(uint32_t in) override { return AlxFiltGlitchUint32_Process(&me, in); }
			protected:
				::AlxFiltGlitchUint32 me = {};
		};
	}
}

#endif // ALX_FILT_GLITCH_UINT32_HPP
