/**
  ******************************************************************************
  * @file alxTpl.hpp
  * @brief Auralix C++ Library - ALX Template Module
  * @version $LastChangedRevision: 4271 $
  * @date $LastChangedDate: 2021-03-05 19:03:28 +0100 (Fri, 05 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_TPL_HPP
#define ALX_TPL_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxTpl.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxTpl
	{
		class ITpl
		{
			public:
				ITpl() {};
				virtual ~ITpl() {};
				virtual bool Process(bool in) = 0;
		};
		class Tpl final : public ITpl
		{
			public:
				Tpl
				(
					bool valFilteredInitial,
					float stableTrueTime_ms,
					float stableFalseTime_ms
				)
				{
					AlxTpl_Ctor(&me, valFilteredInitial, stableTrueTime_ms, stableFalseTime_ms);
				};
				virtual ~Tpl() {};
				bool Process(bool in) override { return AlxTpl_Process(&me, in); }
			protected:
				::AlxTpl me = {0};
		};
	}
}

#endif // ALX_TPL_HPP
