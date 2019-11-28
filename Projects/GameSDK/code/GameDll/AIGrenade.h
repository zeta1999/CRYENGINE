// Copyright 2001-2019 Crytek GmbH / Crytek Group. All rights reserved.


#pragma once

#include "Weapon.h"

class CAIGrenade : public CWeapon, public IWeaponFiringLocator
{
	struct FinishGrenadeAction;
	typedef CWeapon BaseClass;

public:
	CAIGrenade();
	virtual ~CAIGrenade();

	//IWeapon
	virtual void StartFire();
	virtual void StartFire(const SProjectileLaunchParams& launchParams);
	virtual void OnAnimationEventShootGrenade(const AnimEventInstance &event);
	virtual int  GetAmmoCount(IEntityClass* pAmmoType) const { return 1; } //Always has ammo
	virtual void OnReset();
	virtual void SetCurrentFireMode(int idx);

	virtual void GetMemoryUsage(ICrySizer * s) const
	{
		s->AddObject(this, sizeof(*this));
		CWeapon::GetInternalMemoryUsage(s); // collect memory of parent class
	}

	virtual void PostSerialize();

private:
	virtual bool GetProbableHit(EntityId weaponId, const IFireMode* pFireMode, Vec3& hit);
	virtual bool GetFiringPos(EntityId weaponId, const IFireMode* pFireMode, Vec3& pos);
	virtual bool GetFiringDir(EntityId weaponId, const IFireMode* pFireMode, Vec3& dir, const Vec3& probableHit, const Vec3& firingPos);
	virtual bool GetActualWeaponDir(EntityId weaponId, const IFireMode* pFireMode, Vec3& dir, const Vec3& probableHit, const Vec3& firingPos);
	virtual bool GetFiringVelocity(EntityId weaponId, const IFireMode* pFireMode, Vec3& vel, const Vec3& firingDir);
	virtual void WeaponReleased();
	void SetFiringPos(const char* boneName);

	bool m_waitingForAnimEvent;
	Vec3 m_grenadeLaunchPosition;
	Vec3 m_grenadeLaunchVelocity;
};
