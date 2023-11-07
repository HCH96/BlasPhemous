#pragma once
#include "CState.h"
class CPenitentCrouching :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentCrouching);
    CPenitentCrouching();
    ~CPenitentCrouching();
};

