#pragma once
#include "CState.h"
class CPenitentCrouch :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentCrouch);
    CPenitentCrouch();
    ~CPenitentCrouch();
};

