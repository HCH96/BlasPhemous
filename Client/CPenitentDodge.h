#pragma once
#include "CState.h"
class CPenitentDodge :
    public CState
{
private:
    int m_iCurFrame;
    bool m_iDir;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentDodge);
    CPenitentDodge();
    ~CPenitentDodge();
};

