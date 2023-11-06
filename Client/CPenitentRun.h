#pragma once
#include "CState.h"
class CPenitentRun :
    public CState
{
private:

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentRun);
    CPenitentRun();
    ~CPenitentRun();
};

