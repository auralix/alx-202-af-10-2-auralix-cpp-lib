/**
  ******************************************************************************
  * @file alxTmp1075.hpp
  * @brief Auralix C++ Library - ALX Temperature Sensor TMP1075 Module
  * @version $LastChangedRevision: 5745 $
  * @date $LastChangedDate: 2021-08-08 19:52:52 +0200 (ned., 08 avg. 2021) $
  ******************************************************************************
  */

#ifndef ALX_TMP1075_HPP
#define ALX_TMP1075_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxTmp1075.h>
#include <alxIoPin.hpp>
#include <alxI2c.hpp>

//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxTmp1075
	{
		class ITmp1075
		{
			public:
			ITmp1075() {};
			virtual ~ITmp1075() {};
			virtual Alx_Status Init(void) = 0;
			virtual Alx_Status DeInit(void) = 0;
			virtual bool IsInit(void) = 0;
			virtual float GetTemp_degC(void) = 0;
		};
		class Tmp1075 final : public ITmp1075
		{
			public:
				Tmp1075
				(
					Alx::AlxI2c::I2c* i2c,
					uint8_t i2cAddr,
					bool i2cCheckWithRead,
					uint8_t i2cNumOfTries,
					uint16_t i2cTimeout_ms
				)
				{
					AlxTmp1075_Ctor
					(
						&me,
						i2c->GetCStructPtr(),
						i2cAddr,
						i2cCheckWithRead,
						i2cNumOfTries,
						i2cTimeout_ms
					);
				};
				virtual ~Tmp1075() {};
				Alx_Status Init(void) override		{ return AlxTmp1075_Init(&me); }
				Alx_Status DeInit(void) override	{ return AlxTmp1075_DeInit(&me); }
				bool IsInit(void) override			{ return AlxTmp1075_IsInit(&me); }
				float GetTemp_degC(void) override	{ return AlxTmp1075_GetTemp_degC(&me); }
			protected:
				::AlxTmp1075 me = {};
		};
	}
}

#endif // ALX_TMP1075_HPP
