#pragma once
#include "CState.h"
class CPenitentLadderUp :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentLadderUp);
    CPenitentLadderUp();
    ~CPenitentLadderUp();
};

