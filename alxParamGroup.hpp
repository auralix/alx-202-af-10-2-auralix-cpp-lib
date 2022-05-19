//******************************************************************************
// @file alxParamGroup.hpp
// @brief Auralix C++ Library - ALX Parameter Group Module
// @copyright Copyright (C) 2022 Auralix d.o.o. All rights reserved.
//******************************************************************************

#ifndef ALX_PARAM_GROUP_HPP
#define ALX_PARAM_GROUP_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxParamGroup.h>
#include <alxParamItem.hpp>
#include <alxMemSafe.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxParamGroup
	{
		class IParamGroup
		{
			public:
				IParamGroup() {};
				virtual ~IParamGroup() {};
				virtual Alx_Status Init(void) = 0;
				virtual void Write(void) = 0;
				virtual bool IsWriteDone(void) = 0;
				virtual bool IsWriteErr(void) = 0;
				virtual bool IsValStoredBuffDiff(void) = 0;
				virtual void ValBuffToValToStoreBuff(void) = 0;
				virtual void ValToStoreBuffToValStoredBuff(void) = 0;
				virtual void ParamItemsValToValBuff(void) = 0;
				virtual::AlxParamGroup*	GetCStructPtr(void)	= 0;
		};
		template<uint32_t numOfParamItems, uint32_t len>
		class ParamGroup : public IParamGroup
		{
			public:
				ParamGroup
				(
					AlxMemSafe::IMemSafe* memSafe,
					const char* name,
					AlxParamItem::IParamItem** paramItemArr,
					uint8_t initNumOfTries
				)
				{
					// #1 Create array of pointers for paramItemArr
					for(uint32_t i = 0; i < numOfParamItems; i++)
					{
						// #1.1 Get pointer value from arrays of pointers for object item[i]
						AlxParamItem::IParamItem* temp = *(paramItemArr + i);

						// #1.2 Get C structure pointer from object[i]
						this->paramItemArr[i] = temp->GetCStructPtr();
					}

					// #2 Ctor
					AlxParamGroup_Ctor
					(
						&me,
						memSafe->GetCStructPtr(),
						name,
						len,
						valBuff,
						valStoredBuff,
						valToStoreBuff,
						this->paramItemArr,
						numOfParamItems,
						initNumOfTries
					);
				};
				virtual ~ParamGroup() {};
				Alx_Status Init(void) override						{ return AlxParamGroup_Init(&me); }
				void Write(void) override							{ AlxParamGroup_Write(&me); }
				bool IsWriteDone(void) override						{ return AlxParamGroup_IsWriteDone(&me); }
				bool IsWriteErr(void) override						{ return AlxParamGroup_IsWriteErr(&me); }
				bool IsValStoredBuffDiff(void) override				{ return AlxParamGroup_IsValStoredBuffDiff(&me); }
				void ValBuffToValToStoreBuff(void) override			{ AlxParamGroup_ValBuffToValToStoreBuff(&me); }
				void ValToStoreBuffToValStoredBuff(void) override	{ AlxParamGroup_ValToStoreBuffToValStoredBuff(&me); }
				void ParamItemsValToValBuff(void) override			{ AlxParamGroup_ParamItemsValToValBuff(&me); }
				::AlxParamGroup* GetCStructPtr(void) override		{ return &me; }
			protected:
				uint8_t valBuff[len];		// JK: User has to calculate. Safe way: 8bytes * numOfParamItems
				uint8_t valStoredBuff[len];
				uint8_t valToStoreBuff[len];
				::AlxParamItem* paramItemArr[numOfParamItems] = {};
				::AlxParamGroup me = {};
		};
	}
}

#endif	// #ifndef ALX_PARAM_GROUP_HPP
