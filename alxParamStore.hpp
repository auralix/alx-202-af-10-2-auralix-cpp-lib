/**
  ******************************************************************************
  * @file alxParamStore.hpp
  * @brief Auralix C++ Library - ALX Parameter Management Module
  * @version $LastChangedRevision: 4304 $
  * @date $LastChangedDate: 2021-03-09 21:22:50 +0100 (Tue, 09 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_PARAM_STORE_HPP
#define ALX_PARAM_STORE_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxParamStore.h>
#include <alxParamGroup.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxParamStore
	{
		class IParamStore
		{
			public:
				IParamStore() {};
				virtual ~IParamStore() {};
				virtual Alx_Status		Init(Alx_Status* status)	= 0;
				virtual void			Handle(void)				= 0;
				virtual bool			IsErr(void)					= 0;
				virtual::AlxParamStore*	GetCStructPtr(void)			= 0;
		};
		template<uint32_t numOfParamGroups>
		class ParamStore : public IParamStore
		{
			public:
				ParamStore
				(
					Alx::AlxParamGroup::IParamGroup** paramGroupsArr
				)
				{
					// #1 Create array of pointers for groups c structures
					for(uint32_t i = 0 ; i < numOfParamGroups ; i++)
					{
						// #2.1 Get pointer value from arrays of pointers for object item[i]
						AlxParamGroup::IParamGroup* temp = *(paramGroupsArr + i);
						// #2.2 Get C structure pointer from object[i]
						paramStoreParamGroupArr[i] = temp->GetCStructPtr();
					}

					AlxParamStore_Ctor(&me,
										paramStoreParamGroupArr,
										numOfParamGroups);
				};
				virtual ~ParamStore() {};
				Alx_Status			Init(Alx_Status* status) override	{AlxParamStore_Init(&me, status, numOfParamGroups);}; // staus??
				void				Handle(void) override				{AlxParamStore_Handle(&me);};
				bool				IsErr(void) override				{AlxParamStore_IsErr(&me);};
				::AlxParamStore*	GetCStructPtr(void)					{return &me;};
			private:
			::AlxParamGroup* paramStoreParamGroupArr[numOfParamGroups] = {};
				protected :
					::AlxParamStore me = { } ;

		};
	}
}

#endif // ALX_PARAM_STORE_HPP
