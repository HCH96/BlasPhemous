#pragma once
#include "CState.h"
class CPenitentRising :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentRising);
    CPenitentRising();
    ~CPenitentRising();

};

