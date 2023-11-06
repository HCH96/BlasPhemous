#pragma once
#include "CState.h"
class CPenitentJumpForward :
    public CState
{
private:

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentJumpForward);
    CPenitentJumpForward();
    ~CPenitentJumpForward();
};

