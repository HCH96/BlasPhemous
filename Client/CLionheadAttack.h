#pragma once
#include "CState.h"
class CLionheadAttack :
    public CState
{
private:
    int m_iPrevFrame;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CLionheadAttack);
    CLionheadAttack();
    ~CLionheadAttack();

};

