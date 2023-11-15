#pragma once
#include "CObj.h"
class CLedge :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    class CCollider* m_pCollider;

public:
    virtual void begin() override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE(CLedge);
    CLedge();
    CLedge(const CLedge& _Origin);
    ~CLedge();

};

