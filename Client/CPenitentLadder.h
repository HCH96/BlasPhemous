#pragma once
#include "CState.h"
class CPenitentLadder :
    public CState
{
private:
    int m_iCount;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentLadder);
    CPenitentLadder();
    ~CPenitentLadder();
};

