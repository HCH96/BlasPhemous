#pragma once
#include "CState.h"

class CElderBrotherJump :
    public CState
{
private:
    CObj* m_pTarget;


    float m_fStart;
    float m_fEnd;
    float m_fDuration;
    float m_fAcc;
    int m_PrevFrame;

    float m_fJumpStart;
    float m_fJumpEnd;



public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CElderBrotherJump);
    CElderBrotherJump();
    ~CElderBrotherJump();

};

