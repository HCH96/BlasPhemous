#pragma once
#include "CState.h"
class CShieldMaidenToIdle :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CShieldMaidenToIdle);
    CShieldMaidenToIdle();
    ~CShieldMaidenToIdle();

};

