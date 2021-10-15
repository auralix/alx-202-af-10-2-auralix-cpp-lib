/**
  ******************************************************************************
  * @file alxParamMgmt.hpp
  * @brief Auralix C++ Library - ALX Parameter Management Module
  * @version $LastChangedRevision: 4304 $
  * @date $LastChangedDate: 2021-03-09 21:22:50 +0100 (Tue, 09 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_PARAM_MGMT_HPP
#define ALX_PARAM_MGMT_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxParamMgmt.h>
#include <alxParamItem.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxParamMgmt
	{
		class IParamMgmt
		{
			public:
				IParamMgmt() {};
				virtual ~IParamMgmt() {};
				virtual double Get(const char* name) = 0;
				virtual double Get(uint32_t id) = 0;
				virtual ::Alx_Status Set(const char* name, double val) = 0;
				virtual ::Alx_Status Set(uint32_t id, double val) = 0;
				virtual void Get(const char* name, char* val, uint32_t len) = 0;
				virtual void Get(uint32_t id, char* val, uint32_t len) = 0;
				virtual ::Alx_Status Set(const char* name, char* val, uint32_t len) = 0;
				virtual ::Alx_Status Set(uint32_t id, char* val, uint32_t len) = 0;
				virtual void SeToDef(const char* name) = 0;
				virtual void SeToDef(uint32_t id) = 0;
				virtual void SeToDefGroup(uint32_t groupId) = 0;
				virtual void SeToDefAll(uint32_t groupId) = 0;
		};
		class ParamMgmt : public IParamMgmt
		{
			public:
				ParamMgmt
				(
					Alx::AlxParamItem::IParamItem** paramItemArr,
					uint32_t numOfParamItems
				)
				{
//					AlxParamMgmt_Ctor
//					(
//						&me,
//						paramItemArr,
//						numOfParamItems
//					);
				};
				virtual ~ParamMgmt() {};
				double Get(const char* name) override
				{
				}
				double Get(uint32_t id) override
				{
				}
				::Alx_Status Set(const char* name, double val) override
				{
				}
				::Alx_Status Set(uint32_t id, double val) override
				{
				}
				void Get(const char* name, char* val, uint32_t len) override
				{
				}
				void Get(uint32_t id, char* val, uint32_t len) override
				{
				}
				::Alx_Status Set(const char* name, char* val, uint32_t len) override
				{
				}
				::Alx_Status Set(uint32_t id, char* val, uint32_t len) override
				{
				}
				void SeToDef(const char* name) override
				{
				}
				void SeToDef(uint32_t id) override
				{
				}
				void SeToDefGroup(uint32_t groupId) override
				{
				}
				void SeToDefAll(uint32_t groupId) override
				{
				}
			protected:
				::AlxParamMgmt me = {};
		};
	}
}

#endif // ALX_PARAM_MGMT_HPP
