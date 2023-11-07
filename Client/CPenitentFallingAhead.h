#pragma once
#include "CState.h"
class CPenitentFallingAhead :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentFallingAhead);
    CPenitentFallingAhead();
    ~CPenitentFallingAhead();
};

