#pragma once
#include "CObj.h"


class CLightning :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    CAnimator* m_pAnimator;
    CCollider* m_pCollider;

    CSound* m_pSound;

    bool m_bIsOn;
    int m_iPrevFrame;


public:
    void On(Vec2 _vPos);
    void Off();

    void SetSound(CSound* _pSound) { m_pSound = _pSound; }

    bool IsOn() { return m_bIsOn; }


public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;



public:
    CLONE_DISABLE(CLightning);
    CLightning();
    ~CLightning();

};

