#pragma once
#include "CState.h"
class CCrosscrawlerAttack :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CCrosscrawlerAttack);
    CCrosscrawlerAttack();
    ~CCrosscrawlerAttack();
};

