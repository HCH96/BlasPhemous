#pragma once
#include "CUI.h"

class CTexture;
class CObj;

class CBossHP :
    public CUI
{
    GENERATED_OBJECT(CUI);

private:
    CTexture* m_pHP;
    CTexture* m_pHPBack;
    CObj* m_pBoss;

    float       m_fCurHP;
    float       m_fPrevHP;
    float       m_fDecreasingSpeed;
    float       m_fMaxHP;

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE_DISABLE(CBossHP);
    CBossHP();
    ~CBossHP();

};

