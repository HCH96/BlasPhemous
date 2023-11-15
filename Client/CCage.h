#pragma once
#include "CObj.h"
class CCage :
    public CObj
{


private:
    bool       m_bIsClosed;

    CAnimator* m_pAnimator;
    CCollider* m_pCollider;


public:
    void Open();

public:
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE_DISABLE(CCage);
    CCage();
    ~CCage();


};

