/**
  ******************************************************************************
  * @file alxHys2.hpp
  * @brief Auralix C++ Library - ALX Hysteresis Module
  * @version $LastChangedRevision: 4304 $
  * @date $LastChangedDate: 2021-03-09 21:22:50 +0100 (Tue, 09 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_HYS2_HPP
#define ALX_HYS2_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxHys2.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxHys2
	{
		class IHys2
		{
			public:
				IHys2() {};
				virtual ~IHys2() {};
				virtual ::AlxHys2_St Process(float in) = 0;
		};
		class Hys2 final : public IHys2
		{
			public:
				Hys2
				(
					float topHigh,
					float topLow,
					float botHigh,
					float botLow
				)
				{
					AlxHys2_Ctor(&me, topHigh, topLow, botHigh, botLow);
				};
				virtual ~Hys2() {};
				::AlxHys2_St Process(float in) override { return AlxHys2_Process(&me, in); }
			protected:
				::AlxHys2 me = {};
		};
	}
}

#endif // ALX_HYS2_HPP
