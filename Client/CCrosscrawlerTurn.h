#pragma once
#include "CState.h"

class CCrosscrawlerTurn :
    public CState
{

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CCrosscrawlerTurn);
    CCrosscrawlerTurn();
    ~CCrosscrawlerTurn();
};
