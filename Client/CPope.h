#pragma once
#include "CObj.h"

class CFireboltSpawner;

class CPope :
    public CObj
{

    GENERATED_OBJECT(CObj);

private:
    CAnimator* m_pAnimator;
    CAnimator* m_pEffector;
    CAnimator* m_pSymbol;
    CAnimator* m_pBlock;

    CCollider* m_pCollider;
    CStateMachine* m_pAI;

    CFireboltSpawner* m_pFireSpawner;


    float       m_fHP;

public:
    float GetHP() { return m_fHP; }
    CFireboltSpawner* GetFireSpawner() { return m_pFireSpawner; }

    void RegisterFireSpawner(CFireboltSpawner* _pSpawner) { m_pFireSpawner = _pSpawner; }

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    void OnHit();

public:
    virtual void BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) override;

public:
    CLONE_DISABLE(CPope);
    CPope();
    ~CPope();
};

