#pragma once
#include "CObj.h"

class CTexture;

class CAshCloud :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:

    CTexture* m_pTex;
    float m_fAcc;

public:
    void SetTexture(CTexture* pTex) { m_pTex = pTex; }


public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;



public:
    CLONE_DISABLE(CAshCloud);
    CAshCloud();
    ~CAshCloud();


};

