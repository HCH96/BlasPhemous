#pragma once
#include "CState.h"
class CPenitentClimb :
    public CState
{
private:

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentClimb);
    CPenitentClimb();
    ~CPenitentClimb();

};

