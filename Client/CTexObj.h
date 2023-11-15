#pragma once
#include "CObj.h"

class CTexture;

class CTexObj :
    public CObj
{
private:
    CTexture* m_pTex;

public:
    void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }

    virtual void render(HDC _dc) override;


public:
    CLONE_DISABLE(CTexObj);

    CTexObj();
    ~CTexObj();

};

