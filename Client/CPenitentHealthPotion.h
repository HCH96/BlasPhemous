#pragma once
#include "CState.h"
class CPenitentHealthPotion :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentHealthPotion);
    CPenitentHealthPotion();
    ~CPenitentHealthPotion();
};

