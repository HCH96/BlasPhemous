#pragma once
#include "CObj.h"
class CBossIntro :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    class CCollider* m_pCollider;

public:
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE_DISABLE(CBossIntro);
    CBossIntro();
    CBossIntro(const CBossIntro& _Origin) = delete;
    ~CBossIntro();

};

