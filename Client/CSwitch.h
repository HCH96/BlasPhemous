#pragma once
#include "CObj.h"

class CCage;

class CSwitch :
    public CObj
{
private:
    CCage*      m_pCage;
    CAnimator*  m_pAnimator;
    CCollider*  m_pCollider;

public:
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE_DISABLE(CSwitch);
    CSwitch(CCage* _Cage);
    ~CSwitch();
};

