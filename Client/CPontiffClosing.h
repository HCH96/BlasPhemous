#pragma once
#include "CState.h"
class CPontiffClosing :
    public CState
{
private:
    bool m_bSound;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPontiffClosing);
    CPontiffClosing();
    ~CPontiffClosing();
};

