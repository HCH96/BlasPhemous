#pragma once
#include "CState.h"
class CShieldMaidenStun :
    public CState
{
private:
    float m_fAcc;
    float m_fDuration;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CShieldMaidenStun);
    CShieldMaidenStun();
    ~CShieldMaidenStun();

};

