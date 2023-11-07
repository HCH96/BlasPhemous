#pragma once
#include "CComponent.h"

class CState;

class CStateMachine :
    public CComponent
{
private:
    map<UINT, CState*>  m_mapState;
    CState*             m_pCurState;
    CState*             m_pGlobalState;
    
    UINT                m_iPrevState;
    UINT                m_iCurState;

    map<wstring, void*> m_mapBlackboard;

public:
    UINT GetCurState() { return m_iCurState; }
    
    void SetGlobalState(UINT _id);


public:
    CState* FindState(UINT _id);
    void AddState(UINT _id, CState* _State);
    void ChangeState(UINT _NextID);

    void RevertToPrevState() { ChangeState(m_iPrevState); }

    template<typename T>
    void AddDataToBlackboard(const wstring& _strKey, const T& _Data);

    template<typename T>
    void EditDataToBlackboard(const wstring& _strKey, const T& _Data);
    void* GetDataFromBlackboard(const wstring _strKey);


public:
    virtual void finaltick(float _DT) override;


public:
    CLONE(CStateMachine);

    CStateMachine(CObj* _Owner);
    CStateMachine(const CStateMachine& _Origin);
    ~CStateMachine();
};

template<typename T>
inline void CStateMachine::AddDataToBlackboard(const wstring& _strKey, const T& _Data)
{
    map<wstring, void*>::iterator iter = m_mapBlackboard.find(_strKey);
    if (iter != m_mapBlackboard.end())
    {
        LOG(LOG_LEVEL::ERR, L"!!블랙보드에 해당 데이터 키 이미 있음!!");
        return;
    }

    T* pData = new T;
    *pData = _Data;
    m_mapBlackboard.insert(make_pair(_strKey, pData));
}

template<typename T>
inline void CStateMachine::EditDataToBlackboard(const wstring& _strKey, const T& _Data)
{
    map<wstring, void*>::iterator iter = m_mapBlackboard.find(_strKey);
    if (iter == m_mapBlackboard.end())
    {
        LOG(LOG_LEVEL::ERR, L"!!블랙보드에 해당 데이터 키 없음!!");
        return;
    }

    T* pData = static_cast<T*>(iter->second);
    *pData = _Data;
}
