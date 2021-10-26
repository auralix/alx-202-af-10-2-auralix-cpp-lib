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
//#include <alxMemSafe.hpp> waiting for GH to do this


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
				virtual const char*			GetName(void) =							0;
		};
		template<uint32_t numOfParamItems, uint32_t dataRawLen>
		class ParamGroup : public IParamGroup
		{
			public:
				//******************************************************************************
				// Public Functions
				//******************************************************************************
				// #1 Uint8
				ParamGroup
				(
				AlxParamItem::IParamItem* memSafe,
				const char* name,
				AlxParamItem::IParamItem** paramItemArr,
				uint8_t initNumOfTries
				)
				{
					// Get valBuff size for all items
					uint8_t valbuffSize = 0;
					for(uint32_t i = 0; i < numOfParamItems; i++)
					{
						valbuffSize = valbuffSize + paramItemArr[i]->GetValLen();
					}

					// Create buffers

					// Create array of pointers for items c structures
					for(uint32_t i = 0 ; i < numOfParamItems ; i++)
					{
						// Get pointer value from arrays of pointers for object item[i]
						AlxParamItem::IParamItem* temp = *(paramItemArr + i);
						// Get C structure pointer from object[i]
						paramGroupParamItemArr[i] = temp->GetCStructPtr();
					}


//					AlxParamGroup_Ctor( me,
//										memSafe->GetCStructPtr(), // Waiting for GH to commit
//										name,	// OK
//										valbuffSize, // OK
//										valBuff, // OK
//										valStoredBuff,	// OK
//										valToStoreBuff, // OK
//										paramItemArr, // OK
//										numOfParamItems, // OK
//										initNumOfTries); // OK
				};

				virtual ~ParamGroup() {};
				//const char*			GetName(void) override							{ return AlxParamItem_GetName(&me); }

			private:
			::AlxParamItem* paramGroupParamItemArr[numOfParamItems] = {}; // TO DO: Note max 2048 bytes fit into page on G4

			protected :
				//******************************************************************************
				// Protected Variables
				//******************************************************************************
				::AlxParamGroup me = {} ;
				uint8_t valBuff[dataRawLen];		// user has to calculate. Safe way: 8bytes * numOfParamItems
				uint8_t valStoredBuff[dataRawLen];
				uint8_t valToStoreBuff[dataRawLen];

		};
	}
}
#endif // ALX_PARAM_GROUP_HPP