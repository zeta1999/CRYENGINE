// Copyright 2001-2019 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include "Single.h"

class CDetonate :
	public CSingle
{
private:
	
	typedef CSingle BaseClass;
	struct ExplodeAction;
	struct DropRemoveAction;

public:
	CRY_DECLARE_GTI(CDetonate);

	CDetonate();
	virtual ~CDetonate();

	//IFireMode
	virtual void Update(float frameTime, uint32 frameId) override;
	virtual void GetMemoryUsage(ICrySizer * s) const override
	{ 
		s->AddObject(this, sizeof(*this));	
		CSingle::GetInternalMemoryUsage(s);		// collect memory of parent class
	}

	virtual void Activate(bool activate) override;

	virtual bool CanReload() const override;

	virtual bool CanFire(bool considerAmmo = true) const override;
	virtual void StartFire() override;

	virtual void NetShoot(const Vec3 &hit, int ph) override;
	//~IFireMode

	virtual void SetCanDetonate(bool canDet);
	virtual const char *GetCrosshair() const override;

	bool ClientCanDetonate() { return m_canDetonate; }

	void OutOfAmmoExplode();
	void DropRemoveItem();

protected:
	bool Detonate(bool net=false);
	void SelectLast();

	float	m_detonationTimer;
	bool	m_canDetonate;
};
