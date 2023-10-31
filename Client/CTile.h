#pragma once
#include "CObj.h"

class CTexture;

class CTile :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    CTexture*           m_pAtlas;
    int                 m_Idx;


public:
    void SetAtlas(CTexture* _pAtlas) { m_pAtlas = _pAtlas; }
    void SetImgIdx(int _ImgIdx) { m_Idx = _ImgIdx; }
    void AddImgIdx();

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CTile);
    CTile();
    ~CTile();
};

