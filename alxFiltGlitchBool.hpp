/**
  ******************************************************************************
  * @file alxFiltGlitchBool.hpp
  * @brief Auralix C++ Library - ALX Fliter Glitch Bool Module
  * @version $LastChangedRevision: 4304 $
  * @date $LastChangedDate: 2021-03-09 21:22:50 +0100 (Tue, 09 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_FILT_GLITCH_BOOL_HPP
#define ALX_FILT_GLITCH_BOOL_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxFiltGlitchBool.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxFiltGlitchBool
	{
		class IFiltGlitchBool
		{
			public:
				IFiltGlitchBool() {};
				virtual ~IFiltGlitchBool() {};
				virtual bool Process(bool in) = 0;
		};
		class FiltGlitchBool final : public IFiltGlitchBool
		{
			public:
				FiltGlitchBool
				(
					bool valFilteredInitial,
					float stableTrueTime_ms,
					float stableFalseTime_ms
				)
				{
					AlxFiltGlitchBool_Ctor(&me, valFilteredInitial, stableTrueTime_ms, stableFalseTime_ms);
				};
				virtual ~FiltGlitchBool() {};
				bool Process(bool in) override { return AlxFiltGlitchBool_Process(&me, in); }
			protected:
				::AlxFiltGlitchBool me = {};
		};
	}
}

#endif // ALX_FILT_GLITCH_BOOL_HPP
