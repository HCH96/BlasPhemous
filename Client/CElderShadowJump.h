#pragma once
#include "CState.h"
class CElderShadowJump :
    public CState
{
private:
    int m_PrevFrame;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CElderShadowJump);
    CElderShadowJump();
    ~CElderShadowJump();

};

