#pragma once
#include "CObj.h"
class CWall :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    class CCollider* m_pCollider;


public:
    void SetAngle(float _f) { m_pCollider->SetAngle(_f); }

public:
    virtual void begin() override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE(CWall);
    CWall();
    CWall(const CWall& _Origin);
    ~CWall();

};

