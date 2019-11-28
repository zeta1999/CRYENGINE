// Copyright 2001-2019 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#if USE_LAGOMETER

#include "Actor.h"
#include "ITelemetryCollector.h"
#include <CryInput/IInput.h>
#include "ItemString.h"

struct HitInfo;
class CItem;
struct IDebugHistoryManager;
struct IDebugHistory;


class CLagOMeter : public IInputEventListener
{
public:
	enum EBandwidthGraph
	{
		eBG_None = 0,
		eBG_Upload = BIT(0),
		eBG_Download = BIT(1),
		eBG_Both = eBG_Upload|eBG_Download,
	};


	CLagOMeter();
	~CLagOMeter();

	void OnClientRequestHit(HitInfo &hitInfo);
	void OnClientReceivedKill(const CActor::KillParams &killParams);
	void OnClientRequestPurchase(int purchaseSlot);
	void OnClientPickupItem(CItem* pItem);
	void Update();
	void UpdateBandwidthGraphVisibility();
	
	// IInputEventListener
	bool OnInputEvent( const SInputEvent &event );

protected:
	struct SHitRequestHistory
	{
		SHitRequestHistory() {}
		CTimeValue requestTime;
	};

	enum { HIT_HISTORY_COUNT = 16 };		// Note this should match up with serialization policy in HitInfo & KillParams
	typedef std::map<ItemString, CTimeValue> TStringTimeMap;

	IDebugHistoryManager* m_pDebugHistoryManager;
	IDebugHistory* m_pUploadGraph;
	IDebugHistory* m_pDownloadGraph;
	SHitRequestHistory m_hitHistory[HIT_HISTORY_COUNT];
	int m_rollingHitId;
	TStringTimeMap m_purchaseRequests;
	CTimeValue m_prevTime;

	bool m_buttonHeld;
	bool m_perceivedLagEventRecorded;
	float m_timeSinceLastPerceivedLagEvent;
};

#endif // USE_LAGOMETER
