#pragma once
#include "CObj.h"

class CTexture;
class CCollider;
class CAnimator;
class CMovement;

class CPlayer :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    CCollider*                      m_pCollider;
    CAnimator*                      m_pAnimator;
    CMovement*                      m_pMovement;

public:
    virtual void tick(float _DT) override;

public:
    virtual void BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) override;
    virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE(CPlayer);
    CPlayer();
    CPlayer(const CPlayer& _Origin);
    ~CPlayer();

};

