#pragma once
#include "CState.h"
class CPenitentSpellAttack :
    public CState
{
private:
    int m_iPrevFrame;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentSpellAttack);
    CPenitentSpellAttack();
    ~CPenitentSpellAttack();

};

