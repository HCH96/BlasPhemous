#pragma once
#include "CState.h"
class CShieldMaidenDeath :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CShieldMaidenDeath);
    CShieldMaidenDeath();
    ~CShieldMaidenDeath();
};

