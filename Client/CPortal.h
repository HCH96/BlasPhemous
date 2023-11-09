#pragma once
#include "CObj.h"
class CPortal :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    class CCollider* m_pCollider;

    LEVEL_TYPE m_eNextLevel;


public:
    void SetNextLevel(LEVEL_TYPE _eNext) { m_eNextLevel = _eNext; }

public:
    virtual void begin() override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE_DISABLE(CPortal);
    CPortal();
    CPortal(const CPortal& _Origin) = delete;
    ~CPortal();


};

