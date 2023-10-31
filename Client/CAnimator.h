#pragma once
#include "CComponent.h"

class CAnim;
class CTexture;

class CAnimator :
    public CComponent
{
private:
    CAnim*                  m_pCurAnim;
    map<wstring, CAnim*>    m_mapAnim;
    bool                    m_bRepeat;

public:
    void Play(const wstring& _strName, bool _bRepeat);
    void Stop();

    void CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _fDuration, int _iMaxFrm);
    CAnim* FindAnimation(const wstring& _strName);

    void SaveAnimations(const wstring& _strRelativePath);
    void LoadAnimation(const wstring& _strRelativePath);

public:
    virtual void finaltick(float _DT) override;
    virtual void render(HDC _dc) override;


public:
    CLONE(CAnimator);
    CAnimator(CObj* _Owner);
    CAnimator(const CAnimator& _Origin);
    ~CAnimator();
};

