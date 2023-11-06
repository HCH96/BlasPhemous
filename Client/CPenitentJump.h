#pragma once
#include "CState.h"
class CPenitentJump :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentJump);
    CPenitentJump();
    ~CPenitentJump();
};

