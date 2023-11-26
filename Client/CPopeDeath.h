#pragma once
#include "CState.h"
class CPopeDeath :
    public CState
{
private:
    bool m_bEnd;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPopeDeath);
    CPopeDeath();
    ~CPopeDeath();

};

