#pragma once
#include "CState.h"

class CSpawner;

class CElderBrotherAttack :
    public CState
{
private:
    CObj* m_pTarget;
    CSpawner* m_pSpawner;

    int m_PrevFrame;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CElderBrotherAttack);
    CElderBrotherAttack();
    ~CElderBrotherAttack();

};

