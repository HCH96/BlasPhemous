#pragma once
#include "CState.h"
class CPenitentCrouchUp :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentCrouchUp);
    CPenitentCrouchUp();
    ~CPenitentCrouchUp();
};

