#pragma once
#include "CState.h"
class CGiantSwordVanish :
    public CState
{
public:
    float m_fDeadTime;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CGiantSwordVanish);
    CGiantSwordVanish();
    ~CGiantSwordVanish();


};

