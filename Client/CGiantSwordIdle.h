#pragma once
#include "CState.h"

class Pontiff;

class CGiantSwordIdle :
    public CState
{
private:
    CObj* m_pTarget;
    Vec2 m_vVelocity;


    bool m_bSpinReady;


public:
    void Spin() { m_bSpinReady = true; }


public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CGiantSwordIdle);
    CGiantSwordIdle();
    ~CGiantSwordIdle();

};

