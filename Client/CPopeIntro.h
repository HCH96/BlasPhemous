#pragma once
#include "CState.h"
class CPopeIntro :
    public CState
{
private:
    float m_fAcc;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPopeIntro);
    CPopeIntro();
    ~CPopeIntro();

};

