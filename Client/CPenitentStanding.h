#pragma once
#include "CState.h"
class CPenitentStanding :
    public CState
{
private:

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentStanding);
    CPenitentStanding();
    ~CPenitentStanding();
};

