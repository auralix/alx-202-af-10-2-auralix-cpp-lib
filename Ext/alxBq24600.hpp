/**
  ******************************************************************************
  * @file alxBq24600.hpp
  * @brief Auralix C Library - ALX Battery Charger BQ24600 Module
  * @version $LastChangedRevision: 4271 $
  * @date $LastChangedDate: 2021-03-05 19:03:28 +0100 (Fri, 05 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_BQ24600_HPP
#define ALX_BQ24600_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxBq24600.h>
#include <alxIoPin.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxBq24600
	{
		class IBq24600
		{
			public:
				IBq24600() {};
				virtual ~IBq24600() {};
				virtual void Init(void) = 0;
				virtual void DeInit(void) = 0;
				virtual void Handle(void) = 0;
				virtual void Enable(void) = 0;
				virtual void Disable(void) = 0;
				virtual bool IsBatCharging(void) = 0;
				virtual bool IsBatFull(void) = 0;
				virtual bool IsSleep(void) = 0;
				virtual bool IsErr(void) = 0;
		};
		class Bq24600 : public IBq24600
		{
			public:
				Bq24600
				(
					Alx::AlxIoPin::IIoPin* di_EN,
					Alx::AlxIoPin::IIoPin* do_nPG,
				 	Alx::AlxIoPin::IIoPin* do_STAT
				)
				{
					AlxBq24600_Ctor(&me, di_EN->GetCStructPtr(), do_nPG->GetCStructPtr(), do_STAT->GetCStructPtr());
				};
				virtual ~Bq24600() {};
				virtual void Init(void)				{ AlxBq24600_Init(&me); };
				virtual void DeInit(void)			{ AlxBq24600_DeInit(&me); };
				virtual void Handle(void)			{ AlxBq24600_Handle(&me); };
				virtual void Enable(void)			{ AlxBq24600_Enable(&me); };
				virtual void Disable(void)			{ AlxBq24600_Disable(&me); };
				virtual bool IsBatCharging(void)	{ return AlxBq24600_IsBatCharging(&me); };
				virtual bool IsBatFull(void)		{ return AlxBq24600_IsBatFull(&me); };
				virtual bool IsSleep(void)			{ return AlxBq24600_IsSleep(&me); };
				virtual bool IsErr(void)			{ return AlxBq24600_IsErr(&me); };
			private:
				::AlxBq24600 me = {0};
		};
	}
}

#endif // ALX_BQ24600_HPP
