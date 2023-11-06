#pragma once
#include "CState.h"
class CPenitentFowardFall :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentFowardFall);
    CPenitentFowardFall();
    ~CPenitentFowardFall();
};

