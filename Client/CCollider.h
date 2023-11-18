#pragma once
#include "CComponent.h"
class CCollider :
    public CComponent
{
private:
    Vec2    m_vOffsetPos;       // Owner�κ��� ������ �ڸ�
    Vec2    m_vScale;           // Collider ũ��
    Vec2    m_vFinalPos;        // �浹ü�� ���� ��ġ

    bool    m_bOn;              // Collider On/Off
    float   m_fAcc;             // Collider ���� ���� �ð�
    float   m_fDuration;        // Collider ��ȿ �ð�

    float   m_fAngle;           // ȸ�� ����

    int     m_iCollisionCount;

public:
    void On() { m_bOn = true; m_fAcc = 0.f; }
    void Off() { m_bOn = false; }

    void SetTime(float _fDuration) {
        m_fAcc = 0.f;
        m_fDuration = _fDuration;
    }

    void SetFinalPos(Vec2 _vPos) { m_vFinalPos = _vPos; }

    bool IsOn() { return m_bOn; }
    bool IsOff() { return !m_bOn; }

    Vec2 GetPos() { return m_vFinalPos; }
    Vec2 GetOffsetPos() { return m_vOffsetPos; }
    Vec2 GetScale() { return m_vScale; }
    float GetAngle() { return m_fAngle; }

    void SetOffsetPos(Vec2 _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }
    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
    void SetAngle(float _fAngle) { m_fAngle = _fAngle; }

public:
    void BeginOverlap(CCollider* _pOtherCol);
    void Overlap(CCollider* _pOtherCol);
    void EndOverlap(CCollider* _pOtherCol);

public:
    virtual void finaltick(float _DT) override;
    virtual void render(HDC _dc) override;


public:
    CLONE(CCollider);
    CCollider(CObj* _pOwner);
    CCollider(const CCollider& _Origin);
    ~CCollider();
};

