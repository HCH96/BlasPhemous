#pragma once
#include "CObj.h"

class CAnimator;
class CCollider;

enum class ASHSTATE
{
    NONE,
    APPEAR,
    ACTIVE,
    VANISH,
};

class CAshPlatform :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    CCollider* m_pCollider;
    CAnimator* m_pAnimator;

    float m_fAcc;
    ASHSTATE m_eState;
    


public:
    void SetAcc(float _fAcc) { m_fAcc = _fAcc; }
    virtual void tick(float _DT) override;

public:
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE(CAshPlatform);
    CAshPlatform();
    CAshPlatform(const CAshPlatform& _Origin);
    ~CAshPlatform();

};

