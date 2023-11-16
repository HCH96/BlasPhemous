#pragma once
#include "CState.h"
class CFoolKnifeWalk :
    public CState
{
private:
    CPenitent* m_pTarget;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CFoolKnifeWalk);
    CFoolKnifeWalk();
    ~CFoolKnifeWalk();
};

