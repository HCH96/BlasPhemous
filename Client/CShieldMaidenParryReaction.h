#pragma once
#include "CState.h"
class CShieldMaidenParryReaction :
    public CState
{

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CShieldMaidenParryReaction);
    CShieldMaidenParryReaction();
    ~CShieldMaidenParryReaction();

};

