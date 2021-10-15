/**
  ******************************************************************************
  * @file alxAdau1961.hpp
  * @brief Auralix C++ Library - ALX Adau1961 Module
  * @version $LastChangedRevision: 4590 $
  * @date $LastChangedDate: 2021-04-04 03:50:47 +0200 (Sun, 04 Apr 2021) $
  ******************************************************************************
  */

#ifndef ALX_ADAU1961_HPP
#define ALX_ADAU1961_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxAdau1961.h>
#include <alxI2s.hpp>
#include <alxI2c.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxAdau1961
	{
		class IAdau1961
		{
			public:
			IAdau1961() {};
			virtual ~IAdau1961() {};
			virtual ::Alx_Status Init(void)								= 0;
			virtual ::Alx_Status DeInit(void)							= 0;
			virtual void Foreground_Handle(void)						= 0;
			virtual ::Alx_Status InDiffL_SetGain(float gain_dB)			= 0;
			virtual ::Alx_Status InDiffR_SetGain(float gain_dB)			= 0;
			virtual ::Alx_Status InAuxL_SetGain_dB(int8_t gain_dB)		= 0;
			virtual ::Alx_Status InAuxR_SetGain_dB(int8_t gain_dB)		= 0;
			virtual ::Alx_Status OutLineL_SetGain_dB(int8_t gain_dB)	= 0;
			virtual ::Alx_Status OutLineR_SetGain_dB(int8_t gain_dB)	= 0;
		};
		class Adau1961 final : public IAdau1961
		{
			public:
				Adau1961
				(
					Alx::AlxI2s::I2s* i2s,
					Alx::AlxI2c::I2c* i2c,
					uint8_t i2cAddr,
					bool i2cCheckWithRead,
					uint8_t i2cNumOfTries,
					uint16_t i2cTimeout_ms
				)
				{
					AlxAdau1961_Ctor
					(
						&me,
						i2s->GetCStructPtr(),
						i2c->GetCStructPtr(),
						i2cAddr,
						i2cCheckWithRead,
						i2cNumOfTries,
						i2cTimeout_ms
					);
				};
				virtual ~Adau1961() {};
				::Alx_Status Init(void) override							{ return AlxAdau1961_Init(&me); }
				::Alx_Status DeInit(void) override							{ return AlxAdau1961_DeInit(&me); }
				void Foreground_Handle(void) override						{ return AlxAdau1961_Foreground_Handle(&me); }
				::Alx_Status InDiffL_SetGain(float gain_dB) override		{ return AlxAdau1961_InDiffL_SetGain_dB(&me, gain_dB); }
				::Alx_Status InDiffR_SetGain(float gain_dB) override		{ return AlxAdau1961_InDiffR_SetGain_dB(&me, gain_dB); }
				::Alx_Status InAuxL_SetGain_dB(int8_t gain_dB) override		{ return AlxAdau1961_InAuxL_SetGain_dB(&me, gain_dB); }
				::Alx_Status InAuxR_SetGain_dB(int8_t gain_dB) override		{ return AlxAdau1961_InAuxR_SetGain_dB(&me, gain_dB); }
				::Alx_Status OutLineL_SetGain_dB(int8_t gain_dB) override	{ return AlxAdau1961_OutLineL_SetGain_dB(&me, gain_dB); }
				::Alx_Status OutLineR_SetGain_dB(int8_t gain_dB) override	{ return AlxAdau1961_OutLineR_SetGain_dB(&me, gain_dB); }
			protected:
				::AlxAdau1961 me = {};
		};
	}
}

#endif // ALX_ADAU1961_HPP
