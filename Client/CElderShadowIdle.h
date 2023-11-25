#pragma once
#include "CState.h"
class CElderShadowIdle :
    public CState
{
private:
    int m_PrevFrame;
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CElderShadowIdle);
    CElderShadowIdle();
    ~CElderShadowIdle();

};

