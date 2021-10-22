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
		// template<typename T> mislim da ne pride vpoštev, ker ma lahko vsak item drugi tip podatka
		class ParamGroup : public IParamGroup
		{
			public:
				//******************************************************************************
				// Public Functions
				//******************************************************************************
				// #1 Uint8
				ParamGroup
				(
				AlxParamItem::IParamItem memSafe,	// Replace with actual memSafe object!
				const char* name,
				uint32_t len, // Uporablja se za memSafe pisanje, branje. Mogoče dolžina podatkov v itemParam. Vlka verjetnost da se to v cpp izračuna in da ne bo v cpp konstrukturju
				AlxParamItem::IParamItem** paramItemArr,
				uint32_t numOfParamItems,
				uint8_t initNumOfTries
				)
				{
					// Get valBuff size
					uint8_t valbuffSize = 0;
					for(uint32_t i = 0; i < numOfParamItems; i++)
					{

						valbuffSize = valbuffSize + paramItemArr[i]->GetValLen();
					}


					me->valBuff[valbuffSize];		// Treba nardit buffer ki bo tolk vlek da grejo not podatki iz vseh itemov.. nek for stavek ko vsakemu itemu vzame dolžino podatkov...
					me->valStoredBuff[valbuffSize]; // Isto dolg ko prvi
					me->valToStoreBuff[valbuffSize]; // Isto dolg ko prvi.

					for(uint32_t i = 0 ; i < numOfParamItems ; i++)
					{
						AlxParamItem::IParamItem* temp = *(paramItemArr + i);
						//paramGroupParamItemArr[i] = temp->GetCStructPtr();
					}

					/*
					AlxParamGroup_Ctor( me,
										memSafe->GetCStructPtr();,
										name,
										len,
										uint8_t* valBuff,
										uint8_t* valStoredBuff,
										uint8_t* valToStoreBuff,
										AlxParamItem** paramItemArr,
										uint32_t numOfParamItems,
										uint8_t initNumOfTries);*/
				};

				virtual ~ParamGroup() {};
				//const char*			GetName(void) override							{ return AlxParamItem_GetName(&me); }

			private:
			::AlxParamItem* paramGroupParamItemArr[2048] = {}; // TO DO: Note max 2048 bytes fit into page on G4

			protected :
				//******************************************************************************
				// Protected Variables
				//******************************************************************************
				::AlxParamGroup* me = {} ;

		};
	}
}
#endif // ALX_PARAM_GROUP_HPP