#pragma once
#include "CState.h"
class CLionheadDeath :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CLionheadDeath);
    CLionheadDeath();
    ~CLionheadDeath();

};

