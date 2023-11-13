#include "pch.h"
#include "CStateMachine.h"

#include "CState.h"
#include "CLogMgr.h"

CStateMachine::CStateMachine(CObj* _Owner)
	: CComponent(_Owner)
	, m_pGlobalState(nullptr)
	, m_pCurState(nullptr)
	, m_iPrevState(0)
	, m_iCurState(0)
{

}

CStateMachine::CStateMachine(const CStateMachine& _Origin)
	: CComponent(_Origin)
	, m_pGlobalState(nullptr)
	, m_pCurState(nullptr)
	, m_iPrevState(_Origin.m_iPrevState)
	, m_iCurState(_Origin.m_iCurState)
{
	for (const auto& pair : _Origin.m_mapState)
	{
		CState* pClonedState = pair.second->Clone();
		pClonedState->m_pSM = this;
		m_mapState.insert(make_pair(pair.first, pClonedState));
	}

	if (nullptr != _Origin.m_pCurState)
	{
		UINT ID = _Origin.m_pCurState->GetStateID();
		map<UINT, CState*>::iterator iter = m_mapState.find(ID);
		if (iter != m_mapState.end())
		{
			m_pCurState = iter->second;
		}
	}
}

CStateMachine::~CStateMachine()
{
	for (const auto& pair : m_mapState)
	{
		delete pair.second;
	}

	for (const auto& pair : m_mapBlackboard)
	{
		delete pair.second;
	}
}

void CStateMachine::finaltick(float _DT)
{

	if (nullptr != m_pGlobalState)
	{
		m_pGlobalState->finaltick(_DT);
	}

	if (nullptr != m_pCurState)
	{
		m_pCurState->finaltick(_DT);
	}
}

void CStateMachine::AddState(UINT _id, CState* _State)
{
	CState* pFindState = FindState(_id);

	if (nullptr != pFindState)
	{
		LOG(LOG_LEVEL::ERR, L"!!�̹� ���� ���̵��� State �� StateMachine �� ����!!");
		return;
	}

	m_mapState.insert(make_pair(_id, _State));
	_State->m_pSM = this;
}

void CStateMachine::SetGlobalState(UINT _id)
{
	CState* pFindState = FindState(_id);

	if (nullptr == pFindState)
	{
		LOG(LOG_LEVEL::ERR, L"!!�ش��ϴ� State�� �����ϴ�!!");
		return;
	}

	m_pGlobalState = pFindState;
}

CState* CStateMachine::FindState(UINT _id)
{
	map<UINT, CState*>::iterator iter = m_mapState.find(_id);

	if (iter == m_mapState.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CStateMachine::ChangeState(UINT _NextID)
{
	//wchar_t m_reportFileName[256];

	//swprintf_s(m_reportFileName, L"%d", _NextID);

	//LOG(LOG_LEVEL::LOG, m_reportFileName);

	CState* pNextState = FindState(_NextID);

	if (nullptr == pNextState)
	{
		LOG(LOG_LEVEL::ERR, L"!!������ ���� ���°� ����!!");
		return;
	}

	if (pNextState == m_pCurState)
		return;

	// ���� ������Ʈ ����
	m_iPrevState = m_iCurState;

	// ���� ������Ʈ ������
	if (nullptr != m_pCurState)
	{
		m_pCurState->Exit();
	}

	// ���ο� ������Ʈ�� ���� ������Ʈ�� ����
	m_pCurState = pNextState;
	m_iCurState = _NextID;

	// ���ο� ������Ʈ�� ����(�ʱ��۾� ����)
	m_pCurState->Enter();
}




void* CStateMachine::GetDataFromBlackboard(const wstring _strKey)
{
	map<wstring, void*>::iterator iter = m_mapBlackboard.find(_strKey);
	if (iter == m_mapBlackboard.end())
	{
		LOG(LOG_LEVEL::ERR, L"!!�����忡 �ش� Ű ������ ����!!");
		return nullptr;
	}
	return iter->second;
}