#pragma once
#include "CState.h"


class CElderBrotherAttack :
    public CState
{
private:
    CObj* m_pTarget;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CElderBrotherAttack);
    CElderBrotherAttack();
    ~CElderBrotherAttack();

};

