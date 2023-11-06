#pragma once
#include "CState.h"
class CPenitentStartRun :
    public CState
{
private:

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentStartRun);
    CPenitentStartRun();
    ~CPenitentStartRun();
};

