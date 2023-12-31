#pragma once
#include "CState.h"

class CPopeSpell :
    public CState
{
private:
    int m_iSpellIdx;
    int m_iPrevFrame;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPopeSpell);
    CPopeSpell();
    ~CPopeSpell();

};

