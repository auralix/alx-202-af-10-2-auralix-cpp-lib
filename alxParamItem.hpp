/**
  ******************************************************************************
  * @file alxParamItem.hpp
  * @brief Auralix C++ Library - ALX Parameter Item Module
  * @version $LastChangedRevision: 4304 $
  * @date $LastChangedDate: 2021-03-09 21:22:50 +0100 (Tue, 09 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_PARAM_ITEM_HPP
#define ALX_PARAM_ITEM_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxParamItem.h>
//#include <typeinfo>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxParamItem
	{
		class IParamItem
		{
			public:
				IParamItem() {};
				virtual ~IParamItem() {};
				virtual const char*			GetName(void) =							0;
				virtual uint32_t			GetId(void) =							0;
				virtual uint32_t			GetGroupId(void) =						0;
				virtual AlxParamItem_Type	GetType(void) =							0;
				virtual void*				GetValPtr(void) =						0;
				virtual uint32_t			GetValLen(void) =						0;
				virtual void				SetValToDef(void) =						0;

				virtual uint8_t				GetValUint8(void) =						0;
				virtual uint16_t			GetValUint16(void) =					0;
				virtual uint32_t			GetValUint32(void) =					0;
				virtual uint64_t			GetValUint64(void) =					0;
				virtual int8_t				GetValInt8(void) =						0;
				virtual int16_t				GetValInt16(void) =						0;
				virtual int32_t				GetValInt32(void) =						0;
				virtual int64_t				GetValInt64(void) =						0;
				virtual float				GetValFloat(void) =						0;
				virtual double				GetValDouble(void) =					0;
				virtual bool				GetValBool(void) =						0;

				virtual ::Alx_Status		SetValUint8(uint8_t val) =				0;
				virtual ::Alx_Status		SetValUint16(uint16_t val) =			0;
				virtual ::Alx_Status		SetValUint32(uint32_t val) =			0;
				virtual ::Alx_Status		SetValUint64(uint64_t val) =			0;
				virtual ::Alx_Status		SetValInt8(int8_t val) =				0;
				virtual ::Alx_Status		SetValInt16(int16_t val) =				0;
				virtual ::Alx_Status		SetValInt32(int32_t val) =				0;
				virtual ::Alx_Status		SetValInt64(int64_t val) =				0;
				virtual ::Alx_Status		SetValFloat(float val) =				0;
				virtual ::Alx_Status		SetValDouble(double val) =				0;
				virtual ::Alx_Status		SetValBool(bool val) =					0;

				virtual void				GetValArr(void* val) =					0;
				virtual void				SetValArr(void* val) =					0;
				virtual void				GetValStr(char* val) =					0;
				virtual ::Alx_Status		SetValStr(char* val) =					0;
				virtual::AlxParamItem*		GetCStructPtr(void)	=					0;
		};
		template<uint32_t arrBuffLen = 1, uint32_t strMaxLen = 1>
		class ParamItem : public IParamItem
		{
			public:
				//******************************************************************************
				// Public Functions
				//******************************************************************************
				// #1 Uint8
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					uint8_t valDef,
					uint8_t valMin,
					uint8_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorUint8(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				};
				// #2 Uint16
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					uint16_t valDef,
					uint16_t valMin,
					uint16_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorUint16(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				};
				// #3 Uint32
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					uint32_t valDef,
					uint32_t valMin,
					uint32_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorUint32(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				};
				// #4 Uint64
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					uint64_t valDef,
					uint64_t valMin,
					uint64_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorUint64(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				};
				// #5 Int8
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					int8_t valDef,
					int8_t valMin,
					int8_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorInt8(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				};
				// #6 Int16
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					int16_t valDef,
					int16_t valMin,
					int16_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorInt16(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				};
				// #7 Int32
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					int32_t valDef,
					int32_t valMin,
					int32_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
					)
				{
					AlxParamItem_CtorInt32(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				};
				// #8 Int64
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					int64_t valDef,
					int64_t valMin,
					int64_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorInt64(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				};
				// #9 Float
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					float valDef,
					float valMin,
					float valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorFloat(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				};
				// #10 Double
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					double valDef,
					double valMin,
					double valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorDouble(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				};
				// #11 Bool
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					bool valDef,
					bool valMin,
					bool valMax
				)
				{
					AlxParamItem_CtorBool(&me, name, id, groupId, valDef);
				};
				// #12 Arr
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					void* valDefBuff,
					//uint32_t valBuffLen, This is calculated from tempalte
					//uint32_t valBuffDefLen, // Arrays msut be always the same length, defined in template
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorArr(&me, name, id, groupId, valDefBuff, arrValBuff, arrValDeffBuff, arrBuffLen, valOutOfRangeHandle);
				};
				// #13 Str
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					const char* valDef,
					//uint32_t valMaxLen,	// This is defined with a template
					// uint32_t valBuffDefLen, // String are null terminated, no need for lenght
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorStr(&me, name, id, groupId, valDef, strValBuff, strValDefBuff, strMaxLen, valOutOfRangeHandle);
				};
				virtual ~ParamItem() {};
				const char*			GetName(void) override							{ return AlxParamItem_GetName(&me); }
				uint32_t			GetId(void) override							{ return AlxParamItem_GetId(&me); }
				uint32_t			GetGroupId(void) override						{ return AlxParamItem_GetGroupId(&me); }
				AlxParamItem_Type	GetType(void) override							{ return AlxParamItem_GetType(&me); }
				void*				GetValPtr(void) override						{ return AlxParamItem_GetValPtr(&me); }
				uint32_t			GetValLen(void) override						{ AlxParamItem_GetValLen(&me); }
				void				SetValToDef(void) override						{ AlxParamItem_SetValToDef(&me); }

				uint8_t				GetValUint8(void) override						{ return AlxParamItem_GetValUint8(&me); }
				uint16_t			GetValUint16(void) override						{ return AlxParamItem_GetValUint16(&me); }
				uint32_t			GetValUint32(void) override						{ return AlxParamItem_GetValUint32(&me); }
				uint64_t			GetValUint64(void) override						{ return AlxParamItem_GetValUint64(&me); }
				int8_t				GetValInt8(void) override						{ return AlxParamItem_GetValInt8(&me); }
				int16_t				GetValInt16(void) override						{ return AlxParamItem_GetValInt16(&me); }
				int32_t				GetValInt32(void) override						{ return AlxParamItem_GetValInt32(&me); }
				int64_t				GetValInt64(void) override						{ return AlxParamItem_GetValInt64(&me); }
				float				GetValFloat(void) override						{ return AlxParamItem_GetValFloat(&me); }
				double				GetValDouble(void) override						{ return AlxParamItem_GetValDouble(&me); }
				bool				GetValBool(void) override						{ return AlxParamItem_GetValBool(&me); }

				::Alx_Status		SetValUint8(uint8_t val) override				{ return AlxParamItem_SetValUint8(&me, val); }
				::Alx_Status		SetValUint16(uint16_t val) override				{ return AlxParamItem_SetValUint16(&me, val); }
				::Alx_Status		SetValUint32(uint32_t val) override				{ return AlxParamItem_SetValUint32(&me, val); }
				::Alx_Status		SetValUint64(uint64_t val) override				{ return AlxParamItem_SetValUint64(&me, val); }
				::Alx_Status		SetValInt8(int8_t val) override					{ return AlxParamItem_SetValInt8(&me, val); }
				::Alx_Status		SetValInt16(int16_t val) override				{ return AlxParamItem_SetValInt16(&me, val); }
				::Alx_Status		SetValInt32(int32_t val) override				{ return AlxParamItem_SetValInt32(&me, val); }
				::Alx_Status		SetValInt64(int64_t val) override				{ return AlxParamItem_SetValInt64(&me, val); }
				::Alx_Status		SetValFloat(float val) override					{ return AlxParamItem_SetValFloat(&me, val); }
				::Alx_Status		SetValDouble(double val) override				{ return AlxParamItem_SetValDouble(&me, val); }
				::Alx_Status		SetValBool(bool val) override					{ return AlxParamItem_SetValBool(&me, val); }

				void				GetValArr(void* val) override					{ AlxParamItem_GetValArr(&me, val); }
				void				SetValArr(void* val) override					{ AlxParamItem_SetValArr(&me, val); }
				void				GetValStr(char* val) override					{ AlxParamItem_GetValStr(&me, val); }
				::Alx_Status		SetValStr(char* val) override					{ return AlxParamItem_SetValStr(&me, val); }
				::AlxParamItem*		GetCStructPtr(void) override					{ return &me; }
			protected:
			//******************************************************************************
			// Protected Variables
			//******************************************************************************
			uint8_t arrValBuff		[arrBuffLen] = {};
			uint8_t arrValDeffBuff	[arrBuffLen] = {};
			char	strValBuff		[strMaxLen + 1]	 = {}; // + 1 is for nullchar
			char	strValDefBuff	[strMaxLen + 1]	 = {};
			::AlxParamItem me = {} ;
		};
	}
}








//namespace Alx
//{
//	namespace AlxParamItem
//	{
//		class IParamItem
//		{
//			public:
//				IParamItem() {};
//				virtual ~IParamItem() {};
//				virtual const char* GetName(void) = 0;
//				virtual uint32_t GetId(void) = 0;
//				virtual uint32_t GetGroupId(void) = 0;
//				virtual double GetVal(void) = 0;
//				virtual void GetVal(char* val, uint32_t len) = 0;
//				virtual ::Alx_Status SetVal(double val) = 0;
//				virtual ::Alx_Status SetVal(char* val, uint32_t len) = 0;
//				virtual void SetValToDef(void) = 0;
//				virtual void SetValToDef(char* val, uint32_t len) = 0;
//		};
//		template <typename T, uint32_t valStrBuffLen = 1>
//		class ParamItem : public IParamItem
//		{
//			public:
//				//******************************************************************************
//				// Public Functions
//				//******************************************************************************
//				ParamItem	// Non-String Item
//				(
//					const char* name,
//					uint32_t id,
//					uint32_t groupId,
//					T valDef,
//					T valMin,
//					T valMax,
//					bool valOutOfRangeBoundEnable
//				)
//				{
////					AlxParamItem_Ctor
////					(
////						me,
////						name,
////						id,
////						groupId,
////						GetType(),
////						valDef,
////						valMin,
////						valMax,
////						sizeof(T),
////						valOutOfRangeBoundEnable,
////						ALX_NULL_PTR,
////						ALX_NULL_PTR,
////						ALX_NULL_PTR
////					);
//				};
//				ParamItem	// String Item
//				(
//					const char* name,
//					uint32_t id,
//					uint32_t groupId,
//					char* valStrDef,
//					uint32_t valStrLen
//				)
//				{
////					AlxParamItem_Ctor
////					(
////						me,
////						name,
////						id,
////						groupId,
////						AlxParamItemType_String,
////						ALX_NULL,
////						ALX_NULL,
////						ALX_NULL,
////						valStrLen,
////						valStrBuff,
////						valStrDefBuff,
////						valStrDef
////					);
//				};
//				virtual ~ParamItem() {};
//				const char* GetName(void) override
//				{
//				}
//				uint32_t GetId(void) override
//				{
//				}
//				uint32_t GetGroupId(void) override
//				{
//				}
//				double GetVal(void) override
//				{
//					//return AlxParamItem_GetVal(&me);
//				}
//				void GetVal(char* val, uint32_t len) override
//				{
//				}
//				::Alx_Status SetVal(double val) override
//				{
//				}
//				::Alx_Status SetVal(char* val, uint32_t len) override
//				{
//				}
//				void SetValToDef(void) override
//				{
//				}
//				void SetValToDef(char* val, uint32_t len) override
//				{
//				}
//
//			protected:
//				//******************************************************************************
//				// Protected Variables
//				//******************************************************************************
//				::AlxParamItem me = {};
//				char valStrBuff[valStrBuffLen] = {};
//				char valStrDefBuff[valStrBuffLen] = {};
//
//			private:
//				//******************************************************************************
//				// Private Functions
//				//******************************************************************************
//				::AlxParamItem_Type GetType(void)
//				{
////					if(typeid(T) == typeid(uint8_t))	return AlxParamItemType_Uint8;
////					if(typeid(T) == typeid(uint16_t))	return AlxParamItemType_Uint16;
////					if(typeid(T) == typeid(uint32_t))	return AlxParamItemType_Uint32;
////					if(typeid(T) == typeid(uint64_t))	return AlxParamItemType_Uint64;
////					if(typeid(T) == typeid(int8_t))		return AlxParamItemType_Int8;
////					if(typeid(T) == typeid(int16_t))	return AlxParamItemType_Int16;
////					if(typeid(T) == typeid(int32_t))	return AlxParamItemType_Int32;
////					if(typeid(T) == typeid(int64_t))	return AlxParamItemType_Int64;
////					if(typeid(T) == typeid(float))		return AlxParamItemType_Float;
////					if(typeid(T) == typeid(double))		return AlxParamItemType_Double;
////					if(typeid(T) == typeid(bool))		return AlxParamItemType_Bool;
////
////					if(sizeof(T) == 1)					return AlxParamItemType_MyType8;
////					if(sizeof(T) == 2)					return AlxParamItemType_MyType16;
////					if(sizeof(T) == 4)					return AlxParamItemType_MyType32;
////					if(sizeof(T) == 8)					return AlxParamItemType_MyType64;
//
//					ALX_PARAM_ITEM_ASSERT(false);	// We should not get here
//					return (AlxParamItem_Type)ALX_NULL;
//				}
//		};
//	}
//}

#endif // ALX_PARAM_ITEM_HPP
