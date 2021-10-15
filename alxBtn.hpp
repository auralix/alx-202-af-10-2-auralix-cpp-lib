/**
  ******************************************************************************
  * @file alxBtn.hpp
  * @brief Auralix C++ Library - ALX Button Module
  * @version $LastChangedRevision: 4669 $
  * @date $LastChangedDate: 2021-04-10 00:57:50 +0200 (Sat, 10 Apr 2021) $
  ******************************************************************************
  */

#ifndef ALX_BTN_HPP
#define ALX_BTN_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxBtn.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxBtn
	{
		class IBtn
		{
			public:
				IBtn() {};
				virtual ~IBtn() {};
				virtual void Handle(bool in) = 0;
				virtual bool IsPressed()					= 0;
				virtual bool WasPressed()					= 0;
				virtual bool WasReleased()					= 0;
				virtual bool IsPressedShort()				= 0;
				virtual bool WasPressedShort()				= 0;
				virtual bool IsPressedLong()				= 0;
				virtual bool WasPressedLong()				= 0;
				virtual void ClearWasPressed()				= 0;
				virtual void ClearWasReleased()				= 0;
				virtual void ClearWasPressedShort()			= 0;
				virtual void ClearWasPressedLong()			= 0;
		};
		class Btn final : public IBtn
		{
			public:
				Btn
				(
					bool valInitial,
					float longTime_ms,	// min time of long button press [ms]
					float debounceTime_ms	// time of stable button status to change it's state [ms]
				)
				{
					AlxBtn_Ctor(&me, valInitial, longTime_ms, debounceTime_ms);
				};
				virtual ~Btn() {};
				void Handle(bool in) override { return AlxBtn_Handle(&me, in); }
				bool IsPressed()					override { return AlxBtn_IsPressed(&me);			}
				bool WasPressed()					override { return AlxBtn_WasPressed(&me);			}
				bool WasReleased()					override { return AlxBtn_WasReleased(&me);			}
				bool IsPressedShort()				override { return AlxBtn_IsPressedShort(&me);		}
				bool WasPressedShort()				override { return AlxBtn_WasPressedShort(&me);		}
				bool IsPressedLong()				override { return AlxBtn_IsPressedLong(&me);		}
				bool WasPressedLong()				override { return AlxBtn_WasPressedLong(&me);		}
				void ClearWasPressed()				override { AlxBtn_ClearWasPressed(&me);				}
				void ClearWasReleased()				override { AlxBtn_ClearWasReleased(&me);			}
				void ClearWasPressedShort()			override { AlxBtn_ClearWasPressedShort(&me);		}
				void ClearWasPressedLong()			override { AlxBtn_ClearWasPressedLong(&me);			}
			protected:
				::AlxBtn me = {};
		};
	}
}

#endif // ALX_BTN_HPP
