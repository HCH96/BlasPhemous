#pragma once
#include "CState.h"
class CPenitentUpwardATT :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentUpwardATT);
    CPenitentUpwardATT();
    ~CPenitentUpwardATT();

};

