// Copyright 2001-2019 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include <CryDynamicResponseSystem/IDynamicResponseCondition.h>
#include <CryDynamicResponseSystem/IDynamicResponseSystem.h>

namespace DRS
{
	struct IResponseActor;
	struct IVariableCollection;
}

class CConditionDistanceToEntity final : public Cry::DRS::IResponseCondition
{
public:
	CConditionDistanceToEntity();
	CConditionDistanceToEntity(const string& actorName);
	virtual ~CConditionDistanceToEntity();

	//////////////////////////////////////////////////////////
	// IResponseCondition implementation
	virtual bool IsMet(Cry::DRS::IResponseInstance* pResponseInstance) override;
	virtual void Serialize(Serialization::IArchive& ar) override;
	virtual string GetVerboseInfo() const override;
	virtual const char* GetType() const override { return "Distance to Entity"; }
	//////////////////////////////////////////////////////////

private:
	float m_squaredDistance;
	string m_entityName;
};
