/**
  ******************************************************************************
  * @file alxLinFun.hpp
  * @brief Auralix C++ Library - ALX Linear Interpolation Module
  * @version $LastChangedRevision: 5176 $
  * @date $LastChangedDate: 2021-05-19 21:10:16 +0200 (Wed, 19 May 2021) $
  ******************************************************************************
  */

#ifndef ALX_LIN_FUN_HPP
#define ALX_LIN_FUN_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxLinFun.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxLinFun
	{
		class ILinFun
		{
			public:
				ILinFun() {};
				virtual ~ILinFun() {};
				virtual Alx_Status GetY(float x, float* y) = 0;
				virtual Alx_Status GetX(float y, float* x) = 0;
				virtual float GetY(float x) = 0;
				virtual float GetX(float y) = 0;
		};
		class LinFun final : public ILinFun
		{
			public:
				LinFun
				(
					float point1_x,
					float point1_y,
					float point2_x,
					float point2_y,
					float min,
					float max,
					bool isLimitOnX
				)
				{
					AlxLinFun_Ctor(&me, point1_x, point1_y, point2_x, point2_y, min, max, isLimitOnX);
				};
			virtual ~LinFun() {};
				Alx_Status GetY(float x, float* y) override	{ return AlxLinFun_GetY_WithStatus	(&me, x, y);	}
				Alx_Status GetX(float y, float* x) override	{ return AlxLinFun_GetX_WithStatus	(&me, y, x);	}
				float GetY (float x) override				{ return AlxLinFun_GetY				(&me, x);		}
				float GetX (float y) override				{ return AlxLinFun_GetX				(&me, y);		}
			protected:
				::AlxLinFun me = {};
		};
	}
}

#endif // ALX_LIN_FUN_HPP
