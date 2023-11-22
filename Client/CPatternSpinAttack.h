#pragma once
#include "CState.h"
class CPatternSpinAttack :
    public CState
{
private:
    float m_fAcc;
    bool m_bAttack;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPatternSpinAttack);
    CPatternSpinAttack();
    ~CPatternSpinAttack();

};

