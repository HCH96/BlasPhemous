#pragma once
#include "CState.h"
class CPenitentDodgeToRun :
    public CState
{
private:
    bool m_bDir;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentDodgeToRun);
    CPenitentDodgeToRun();
    ~CPenitentDodgeToRun();
};

