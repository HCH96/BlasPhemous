#pragma once
#include "CState.h"
class CPenitentPushBack :
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
    CLONE(CPenitentPushBack);
    CPenitentPushBack();
    ~CPenitentPushBack();

};

