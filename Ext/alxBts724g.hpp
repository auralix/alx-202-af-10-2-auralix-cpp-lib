/**
  ******************************************************************************
  * @file bts724g.hpp
  * @brief Auralix C++ Library - ALX HighSide Switch BTS724G Module
  * @version $LastChangedRevision: 4584 $
  * @date $LastChangedDate: 2021-04-03 03:11:01 +0200 (Sat, 03 Apr 2021) $
  ******************************************************************************
  */

#ifndef ALX_BTS724G_HPP
#define ALX_BTS724G_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxBts724g.h>
#include <alxIoPin.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxBts724g
	{
		class IBts724g
		{
			public:
				IBts724g() {};
				virtual ~IBts724g() {};
				virtual void Init(void) = 0;
				virtual void DeInit(void) = 0;
				virtual void Handle(void) = 0;
				virtual void SetOut(void) = 0;
				virtual void ResetOut(void) = 0;
				virtual void WriteOut(bool ) = 0;
				virtual bool IsOpenLoadDetected(void) = 0;
				virtual bool IsOverTempDetected(void) = 0;
				virtual bool WasOpenLoadDetected(void) = 0;
				virtual bool WasOverTempDetected(void) = 0;
		};
		class Bts724g : public IBts724g
		{
			public:
				Bts724g
				(
					Alx::AlxIoPin::IIoPin* do_HS_IN, 
					Alx::AlxIoPin::IIoPin* di_HS_ST
				)
				{
					AlxBts724g_Ctor(&me, do_HS_IN->GetCStructPtr(), di_HS_ST->GetCStructPtr());
				};
				virtual ~Bts724g() {};
				void Init(void)override						{ AlxBts724g_Init(&me); };
				void DeInit(void)override					{ AlxBts724g_DeInit(&me); };
				void Handle(void)override					{ AlxBts724g_Handle(&me); };
				void SetOut(void)override					{ AlxBts724g_SetOut(&me); };
				void ResetOut(void)override					{ AlxBts724g_ResetOut(&me); };
				void WriteOut(bool state)override			{ AlxBts724g_WriteOut(&me, state); };
				bool IsOpenLoadDetected(void)override		{ return AlxBts724g_IsOpenLoadDetected(&me); };
				bool IsOverTempDetected(void)override		{ return AlxBts724g_IsOverTempDetected(&me); }; 
				bool WasOpenLoadDetected(void)override		{ return AlxBts724g_WasOpenLoadDetected(&me); };
				bool WasOverTempDetected(void)override		{ return AlxBts724g_WasOverTempDetected(&me); };
			private:
				::AlxBts724g me = {};
		};
	}
}

#endif // ALX_BTS724G_HPP
