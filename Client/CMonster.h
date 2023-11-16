#pragma once
#include "CObj.h"

class CMonster :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    FMonInfo        m_Info;
    CCollider*      m_pCollider;
    CStateMachine*  m_pAI;
    CTexture*       m_pTexture;

    float           m_fHP;


public:
    void SetMonsterInfo(const FMonInfo& _Info) { m_Info = _Info; }

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    virtual void BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) override;

public:
    CLONE(CMonster);
    CMonster();
    CMonster(const CMonster& _Origin);
    ~CMonster();
};