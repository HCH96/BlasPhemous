#pragma once
#include "CObj.h"
class CPlatform :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    class CCollider* m_pCollider;


public:
    virtual void tick(float _DT) override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CPlatform();
    ~CPlatform();
};

