/**
  ******************************************************************************
  * @file alxInterpLin.hpp
  * @brief Auralix C++ Library - ALX Linear Interpolation Module
  * @version $LastChangedRevision: 4304 $
  * @date $LastChangedDate: 2021-03-09 21:22:50 +0100 (Tue, 09 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_INTERP_LIN_HPP
#define ALX_INTERP_LIN_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxInterpLin.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxInterpLin
	{
		class IInterpLin
		{
			public:
				IInterpLin() {};
				virtual ~IInterpLin() {};
				virtual Alx_Status GetY(float x, float* y) = 0;
				virtual float GetY(float x) = 0;
				virtual::AlxInterpLin* GetCStructPtr(void) = 0;
		};
		class InterpLin final : public IInterpLin
		{
			public:
				InterpLin
				(
					float *xPointArr,
					float *yPointArr,
					uint32_t numOfArrPoints,
					bool isXpointArrRising
				)
				{
					AlxInterpLin_Ctor(&me, xPointArr, yPointArr, numOfArrPoints, isXpointArrRising);
				};
			virtual ~InterpLin() {};
				Alx_Status GetY(float x, float* y) override		{ return AlxInterpLin_GetY_WithStatus	(&me, x, y);}
				float GetY(float x) override					{ return AlxInterpLin_GetY				(&me, x	);	}
				::AlxInterpLin* GetCStructPtr(void) override	{ return &me;	}
			protected:
				::AlxInterpLin me = {};
		};
	}
}

#endif // ALX_FILT_GLITCH_BOOL_HPP
