/**
  ******************************************************************************
  * @file alxParamItem.hpp
  * @brief Auralix C++ Library - ALX Parameter Item Module
  * @version $LastChangedRevision: 4304 $
  * @date $LastChangedDate: 2021-03-09 21:22:50 +0100 (Tue, 09 Mar 2021) $
  ******************************************************************************
  */

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
		template<uint32_t numOfParamItems, uint32_t dataRawLen>
		class ParamGroup : public IParamGroup
		{
			public:
				//******************************************************************************
				// Public Functions
				//******************************************************************************
				ParamGroup
				(
				AlxMemSafe::IMemSafe* memSafe,
				AlxParamItem::IParamItem** paramItemArr,
				const char* name,
				uint8_t initNumOfTries
				)
				{
					// #1 Get valBuff size for all items
					uint8_t valbuffSize = 0;
					for(uint32_t i = 0; i < numOfParamItems; i++)
					{
						valbuffSize = valbuffSize + paramItemArr[i]->GetValLen();
					}

					// #2 Create array of pointers for items c structures
					for(uint32_t i = 0 ; i < numOfParamItems ; i++)
					{
						// #2.1 Get pointer value from arrays of pointers for object item[i]
						AlxParamItem::IParamItem* temp = *(paramItemArr + i);

						// #2.2 Get C structure pointer from object[i]
						paramGroupParamItemArr[i] = temp->GetCStructPtr();
					}

					// #3 C Constructor
					AlxParamGroup_Ctor	(&me,
										memSafe->GetCStructPtr(),
										name,
										valbuffSize,
										valBuff,
										valStoredBuff,
										valToStoreBuff,
										paramGroupParamItemArr,
										numOfParamItems,
										initNumOfTries);
				};
				virtual ~ParamGroup() {};
				Alx_Status Init(void) override						{AlxParamGroup_Init(&me); }
				void Write(void) override							{AlxParamGroup_Write(&me); }
				bool IsWriteDone(void) override						{AlxParamGroup_IsWriteDone(&me); }
				bool IsWriteErr(void) override						{AlxParamGroup_IsWriteErr(&me); }
				bool IsValStoredBuffDiff(void) override				{AlxParamGroup_IsValStoredBuffDiff(&me); }
				void ValBuffToValToStoreBuff(void) override			{AlxParamGroup_ValBuffToValToStoreBuff(&me); }
				void ValToStoreBuffToValStoredBuff(void) override	{AlxParamGroup_ValToStoreBuffToValStoredBuff(&me); }
				void ParamItemsValToValBuff(void) override			{AlxParamGroup_ParamItemsValToValBuff(&me); }
				::AlxParamGroup* GetCStructPtr(void) override		{ return &me; }

			private:
				::AlxParamItem* paramGroupParamItemArr[numOfParamItems] = {};

			protected :
				//******************************************************************************
				// Protected Variables
				//******************************************************************************
				::AlxParamGroup me = {} ;
				uint8_t valBuff[dataRawLen];		// User has to calculate. Safe way: 8bytes * numOfParamItems
				uint8_t valStoredBuff[dataRawLen];
				uint8_t valToStoreBuff[dataRawLen];

		};
	}
}

#endif // ALX_PARAM_GROUP_HPP