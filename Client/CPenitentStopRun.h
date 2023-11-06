#pragma once
#include "CState.h"
class CPenitentStopRun :
    public CState
{
private:

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentStopRun);
    CPenitentStopRun();
    ~CPenitentStopRun();
};

