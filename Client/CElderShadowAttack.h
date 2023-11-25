#pragma once
#include "CState.h"
class CElderShadowAttack :
    public CState
{
private:
    int m_PrevFrame;
    int m_iCount;


public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CElderShadowAttack);
    CElderShadowAttack();
    ~CElderShadowAttack();

};

