#pragma once
#include "CState.h"
class CPenitentLadderDown :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentLadderDown);
    CPenitentLadderDown();
    ~CPenitentLadderDown();
};

