#pragma once
#include "CEntity.h"

class CTexture;

struct FFrame
{
    Vec2    vLeftTop;
    Vec2    vCutSize;
    Vec2    vOffset;
    float   fDuration;
};

class CAnimator;

class CAnim :
    public CEntity
{
private:
    CAnimator*      m_pAnimator;
    
    vector<FFrame>  m_vecFrm;
    CTexture*       m_pAtlas;

    int             m_iCurFrm;
    float           m_fAccTime;
    bool            m_bFinish;

public:
    void Create(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _fDuration, int _iMaxFrm);
    bool Save(const wstring& _FilePath);
    bool Load(const wstring& _FilePath);

    bool IsFinish() { return m_bFinish; }
    void Reset()
    {
        m_iCurFrm = 0;
        m_fAccTime = 0.f;
        m_bFinish = false;
    }

public:
    void finaltick(float _DT);
    void render(HDC _dc);

public:
    CAnim();
    ~CAnim();

    friend class CAnimator;
};

