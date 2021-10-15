/**
  ******************************************************************************
  * @file alxAudioVol.hpp
  * @brief Auralix C++ Library - ALX Audio Volume Module
  * @version $LastChangedRevision: 5176 $
  * @date $LastChangedDate: 2021-05-19 21:10:16 +0200 (Wed, 19 May 2021) $
  ******************************************************************************
  */

#ifndef ALX_AUDIO_VOL_HPP
#define ALX_AUDIO_VOL_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxAudioVol.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxAudioVol
	{
		class IAudioVol
		{
			public:
				IAudioVol() {};
				virtual ~IAudioVol() {};
				virtual float Process(float inSample) = 0;
				virtual void Set_pct(float vol_pct) = 0;
				virtual void Set_dB(float gain_dB) = 0;
		};
		class AudioVol final : public IAudioVol
		{
			public:
				AudioVol
				(
						float volMin_dB,
						float volMax_dB
				)
				{
					AlxAudioVol_Ctor(&me, volMin_dB, volMax_dB);
				}
				virtual ~AudioVol() {}
				float Process(float inSample) override	{ return AlxAudioVol_Process(&me, inSample); }
				void Set_pct(float vol_pct) override	{ AlxAudioVol_Set_pct(&me, vol_pct); }
				void Set_dB(float gain_dB) override		{ AlxAudioVol_Set_dB(&me, gain_dB); }
			protected:
				::AlxAudioVol me = {};
		};
	}
}

#endif // ALX_AUDIO_VOL_HPP
