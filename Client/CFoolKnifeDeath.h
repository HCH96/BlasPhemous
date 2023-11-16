#pragma once
#include "CState.h"
class CFoolKnifeDeath :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CFoolKnifeDeath);
    CFoolKnifeDeath();
    ~CFoolKnifeDeath();
};

