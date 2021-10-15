/**
  ******************************************************************************
  * @file alxTpa3255.hpp
  * @brief Auralix C++ Library - ALX Speaker Amplifier TPA3255 Module
  * @version $LastChangedRevision: 4590 $
  * @date $LastChangedDate: 2021-04-04 03:50:47 +0200 (Sun, 04 Apr 2021) $
  ******************************************************************************
  */

#ifndef ALX_TPA3255_HPP
#define ALX_TPA3255_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxTpa3255.h>
#include <alxIoPin.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxTpa3255
	{
		class ITpa3255
		{
			public:
			ITpa3255() {};
			virtual ~ITpa3255() {};
			virtual void Init()						= 0;
			virtual void DeInit()					= 0;
			virtual void Handle()					= 0;
			virtual void Enable()					= 0;
			virtual void Disable()					= 0;
			virtual bool IsErrAsserted()			= 0;
			virtual bool IsWarningAsserted()		= 0;
			virtual bool WasErrAsserted()			= 0;
			virtual bool WasWarningAsserted()		= 0;
			virtual void ClearWasErrAsserted()		= 0;
			virtual void ClearWasWarningAsserted()	= 0;
		};
		class Tpa3255 final : public ITpa3255
		{
			public:
			Tpa3255
				(
					Alx::AlxIoPin::IIoPin* di_nRESET,
					Alx::AlxIoPin::IIoPin* do_nFAULT,
					Alx::AlxIoPin::IIoPin* do_nCLIP_OTW,
					float waitTime_ReEnable_ms
				)
				{
					AlxTpa3255_Ctor
					(
						&me,
						di_nRESET->GetCStructPtr(),
						do_nFAULT->GetCStructPtr(),
						do_nCLIP_OTW->GetCStructPtr(),
						waitTime_ReEnable_ms
					);
				};
				virtual ~Tpa3255() {};
				void Init() override { AlxTpa3255_Init(&me); }
				void DeInit() override { AlxTpa3255_DeInit(&me); }
				void Handle() override { AlxTpa3255_Handle(&me); }
				void Enable() override { AlxTpa3255_Enable(&me); }
				void Disable() override { AlxTpa3255_Disable(&me); }
				bool IsErrAsserted() override { return AlxTpa3255_IsErrAsserted(&me); }
				bool IsWarningAsserted() override { return AlxTpa3255_IsWarningAsserted(&me); }
				bool WasErrAsserted() override { return AlxTpa3255_WasErrAsserted(&me); }
				bool WasWarningAsserted() override { return AlxTpa3255_WasWarningAsserted(&me); }
				void ClearWasErrAsserted() override { AlxTpa3255_ClearWasErrAsserted(&me); }
				void ClearWasWarningAsserted() override { AlxTpa3255_ClearWasWarningAsserted(&me); }
			protected:
			::AlxTpa3255 me = {};
		};
	}
}

#endif // ALX_TPA3255_HPP
