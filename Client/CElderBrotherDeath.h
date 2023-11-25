#pragma once
#include "CState.h"
class CElderBrotherDeath :
    public CState
{
private:
    Vec2 m_vDeathPos;

    bool m_bEnd;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CElderBrotherDeath);
    CElderBrotherDeath();
    ~CElderBrotherDeath();

};

