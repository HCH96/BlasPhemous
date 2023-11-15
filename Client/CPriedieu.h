#pragma once
#include "CObj.h"

class CAnimator;
class CCollider;

class CPriedieu :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    bool isPopup;

    CAnimator* m_pAnimator;
    CCollider* m_pCollider;
    CTexture* m_pPopupTex;


public:
    virtual void render(HDC _dc) override;

public:
    virtual void Overlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) override;
    virtual void EndOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) override;

public:
    CLONE_DISABLE(CPriedieu);
    CPriedieu();
    ~CPriedieu();



};

