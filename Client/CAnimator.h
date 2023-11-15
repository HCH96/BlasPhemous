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

    bool                    m_bPosLock;
    Vec2                    m_vTmpPos;

public:
    int GetAlpha() { return m_iAlpha; }
    float GetAcc() { return m_fAcc; }
    bool IsFinish();
    int GetCurFrame();
    bool IsLock() { return m_bPosLock; }
    Vec2 GetTmpPos() { return m_vTmpPos; }
    CAnim* GetCurAnimp() { return m_pCurAnim; }


    void SetLock(bool _b) { m_bPosLock = _b; }
    void SetTmpPos(Vec2 _v) { m_vTmpPos = _v; }
    void SetFrame(int _i);



public:
    void Play(const wstring& _strName, bool _bRepeat);
    void PlayNoReset(const wstring& _strName, bool _bRepeat);
    void PlayFromFrame(const wstring& _strName, UINT _iFrame, bool _bRepeat);
    void Stop();

    void SetAnimDuration(const wstring& _strName, float _fDuration);
    void SetAnimDuration(const wstring& _strName, UINT _iFrame, float _fDuration);

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

