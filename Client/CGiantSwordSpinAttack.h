#pragma once
#include "CState.h"


class CGiantSwordSpinAttack :
    public CState
{
private:
    Vec2 m_vTarget;
    Vec2 m_vInitPos;
    float m_fAcc;

    bool m_bSound;


public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CGiantSwordSpinAttack);
    CGiantSwordSpinAttack();
    ~CGiantSwordSpinAttack();

};

