#pragma once
#include "CState.h"
class CPenitentIdle :
    public CState
{
private:

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentIdle);
    CPenitentIdle();
    ~CPenitentIdle();

};

