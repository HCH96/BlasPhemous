#pragma once
#include "CObj.h"

class CTexture;

class CTwisterBackground :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    CTexture*  m_pTex;
    float      m_fAlpha;
    float      m_fMaxAlpha;
    float      m_fMinAlpha;
    bool       m_bAlphaUP;
    float      m_fSpeed;
    
public:
    void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }
    void SetAlpha(float _fAlpha) { m_fAlpha = _fAlpha; }
    void SetMaxAlpha(float _fAlpha) { m_fMaxAlpha = _fAlpha; }
    void SetMinAlpha(float _fAlpha) { m_fMinAlpha = _fAlpha; }


public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE_DISABLE(CTwisterBackground);
    CTwisterBackground();
    ~CTwisterBackground();

};

