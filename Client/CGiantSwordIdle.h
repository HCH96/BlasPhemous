#pragma once
#include "CState.h"


class CGiantSwordIdle :
    public CState
{
private:
    CObj* m_pTarget;
    Vec2 m_vVelocity;



public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CGiantSwordIdle);
    CGiantSwordIdle();
    ~CGiantSwordIdle();

};

