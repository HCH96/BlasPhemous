#pragma once
#include "CState.h"
class CElderBrotherIntroJump :
    public CState
{
private:
    int m_PrevFrame;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CElderBrotherIntroJump);
    CElderBrotherIntroJump();
    ~CElderBrotherIntroJump();

};

