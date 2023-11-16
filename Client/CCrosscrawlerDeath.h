#pragma once
#include "CState.h"
class CCrosscrawlerDeath :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CCrosscrawlerDeath);
    CCrosscrawlerDeath();
    ~CCrosscrawlerDeath();

};

