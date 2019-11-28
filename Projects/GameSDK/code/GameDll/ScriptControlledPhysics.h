// Copyright 2001-2019 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include "IGameObject.h"

class CScriptControlledPhysics: public CGameObjectExtensionHelper<CScriptControlledPhysics, IGameObjectExtension>,
	CScriptableBase
{
public:
	CScriptControlledPhysics();
	virtual ~CScriptControlledPhysics();

	virtual void GetMemoryUsage(ICrySizer *pSizer) const;

	// IGameObjectExtension
	virtual bool Init( IGameObject * pGameObject );
	using CScriptableBase::Init;

	virtual void InitClient(int channelId) {};
	virtual void PostInit( IGameObject * pGameObject );
	virtual void PostInitClient(int channelId) {};
	virtual bool ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params );
	virtual void PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) {}
	virtual bool GetEntityPoolSignature( TSerialize signature );
	virtual void Release();
	virtual void FullSerialize( TSerialize ser );
	virtual bool NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags ) { return true; }
	virtual void PostSerialize() {}
	virtual void SerializeSpawnInfo( TSerialize ser ) {}
	virtual ISerializableInfoPtr GetSpawnInfo() {return 0;}
	virtual void Update( SEntityUpdateContext& ctx, int slot ) {};
	virtual void HandleEvent( const SGameObjectEvent& );
	virtual void ProcessEvent(const SEntityEvent& ) {};
	virtual Cry::Entity::EventFlags GetEventMask() const { return Cry::Entity::EventFlags(); }
	virtual void SetChannelId(uint16 id) {};
	virtual void PostUpdate(float frameTime) { CRY_FUNCTION_NOT_IMPLEMENTED; }
	virtual void PostRemoteSpawn() {};

	//~IGameObjectExtension
	int Reset(IFunctionHandler *pH);
	int GetSpeed(IFunctionHandler *pH);
	int GetAcceleration(IFunctionHandler *pH);

	int GetAngularSpeed(IFunctionHandler *pH);
	int GetAngularAcceleration(IFunctionHandler *pH);

	int MoveTo(IFunctionHandler *pH, Vec3 point, float initialSpeed, float speed, float acceleration, float stopTime);
	int RotateTo(IFunctionHandler *pH, Vec3 dir, float roll, float initialSpeed, float speed, float acceleration, float stopSpeed);
	int RotateToAngles(IFunctionHandler *pH, Vec3 angles, float initialSpeed, float speed, float acceleration, float stopSpeed);

	int HasArrived(IFunctionHandler *pH);

	void OnPostStep(EventPhysPostStep *pPostStep);
private:
	void RegisterGlobals();
	void RegisterMethods();

	bool m_moving;
	Vec3  m_moveTarget;
	Vec3	m_lastVelocity;
	float m_speed;
	float m_maxSpeed;
	float m_acceleration;
	float m_stopTime;

	bool m_rotating;
	Quat m_rotationTarget;
	float m_rotationSpeed;
	float m_rotationMaxSpeed;
	float m_rotationAcceleration;
	float m_rotationStopTime;
};
