// Copyright 2001-2019 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include <CryGame/IGameStatistics.h>
#include <CrySystem/XML/IXml.h>

//////////////////////////////////////////////////////////////////////////

struct SStatNode
{
	typedef std::map<uint32, SStatNode*> TNodes;

	SNodeLocator						locator;
	XmlNodeRef							xml;
	SStatNode*							parent;
	TNodes									children;
	IStatsContainer&				container;

	SStatNode(const SNodeLocator& loc, IStatsContainer& cont, SStatNode* prnt = 0);
	SStatNode* addOrFindChild(const SNodeLocator& loc, IStatsContainer& cont);
	void removeChild(const SNodeLocator& loc);
};

//////////////////////////////////////////////////////////////////////////

// Implements statistic serializers
// This one serializes to a file based on kiev game code
class CXMLStatsSerializer : public IStatsSerializer
{
public:
	CXMLStatsSerializer(IGameStatistics* pGS, CStatsRecordingMgr* pMissionStats);
	virtual void VisitNode(const SNodeLocator& locator, const char* serializeName, IStatsContainer& container, EStatNodeState state);
	virtual void LeaveNode(const SNodeLocator& locator, const char* serializeName, IStatsContainer& container, EStatNodeState state);

private:
	void OnNodeSaved(const SNodeLocator& locator, XmlNodeRef node);
	void SaveContainerData(const IStatsContainer& container, XmlNodeRef node);
	void SaveEventTrack(XmlNodeRef n, const char* name, const IStatsContainer& container, size_t eventID);
	void SaveStatValToXml(XmlNodeRef node, const char* name, const SStatAnyValue& val);

	SStatNode* m_rootNode;
	SStatNode* m_currentNode;
	IGameStatistics* m_stats;
	CStatsRecordingMgr* m_statsRecorder;
};

//////////////////////////////////////////////////////////////////////////
