#pragma once
#include "CObj.h"

class CTexture;
class CAnimator;


class CImage :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    CTexture*       m_pTex;
    CAnimator*      m_pAnimator;


public:
    void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }
    void SetScaleToTex();
    CAnimator* GetAnimator() { return m_pAnimator; }


public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;


public:
    CLONE_DISABLE(CImage);
    CImage();
    CImage(const CImage& _Origin) = delete;
    ~CImage();

};

