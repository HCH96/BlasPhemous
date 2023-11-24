#pragma once
#include "CState.h"
class CPenitentCrouchATT :
    public CState
{
private:
    bool m_bDir;

    int m_iPrevFrame;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentCrouchATT);
    CPenitentCrouchATT();
    ~CPenitentCrouchATT();
};

