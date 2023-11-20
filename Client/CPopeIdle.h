#pragma once
#include "CState.h"
class CPopeIdle :
    public CState
{
private:
    CObj* m_pTarget;

    float m_fDuration;
    float m_fAcc;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPopeIdle);
    CPopeIdle();
    ~CPopeIdle();

};

