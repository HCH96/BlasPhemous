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


    int                     m_iAlpha;
    float                   m_fAcc;

public:
    int GetAlpha() { return m_iAlpha; }
    float GetAcc() { return m_fAcc; }


public:
    void Play(const wstring& _strName, bool _bRepeat);
    void Stop();

    void SetAnimDuration(const wstring& _strName, float _fDuration);

    CAnim* FindAnimation(const wstring& _strName);

    void CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _fDuration, int _iMaxFrm);
    void SaveAnimations(const wstring& _strRelativePath);
    void LoadAnimation(const wstring& _strRelativePath);
    void LoadAnimation(CTexture* _pTexture, const wstring& _strAnimKey, const wstring& _strMetaRelativePath, bool _bReverse = false);

public:
    virtual void finaltick(float _DT) override;
    virtual void render(HDC _dc) override;


public:
    CLONE(CAnimator);
    CAnimator(CObj* _Owner);
    CAnimator(const CAnimator& _Origin);
    ~CAnimator();
};

