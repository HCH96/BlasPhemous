#pragma once
#include "CState.h"
class CPenitentNone :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentNone);
    CPenitentNone();
    ~CPenitentNone();

};

