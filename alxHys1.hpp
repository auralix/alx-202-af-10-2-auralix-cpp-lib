/**
  ******************************************************************************
  * @file alxHys2.hpp
  * @brief Auralix C++ Library - ALX Hysteresis Module
  * @version $LastChangedRevision: 4304 $
  * @date $LastChangedDate: 2021-03-09 21:22:50 +0100 (Tue, 09 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_HYS1_HPP
#define ALX_HYS1_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxHys1.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxHys1
	{
		class IHys1
		{
			public:
				IHys1() {};
				virtual ~IHys1() {};
				virtual ::AlxHys1_St Process(float in) = 0;
		};
		class Hys1 final : public IHys1
		{
			public:
				Hys1
				(
					float high,
					float low
				)
				{
					AlxHys1_Ctor(&me, high, low);
				};
				virtual ~Hys1() {};
				::AlxHys1_St Process(float in) override { return AlxHys1_Process(&me, in); }
			protected:
				::AlxHys1 me = {};
		};
	}
}

#endif // ALX_HYS1_HPP
