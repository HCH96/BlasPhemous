#pragma once
#include "CComponent.h"
class CCollider :
    public CComponent
{
private:
    Vec2    m_vOffsetPos;       // Owner�κ��� ������ �ڸ�
    Vec2    m_vScale;           // Collider ũ��
    Vec2    m_vFinalPos;        // �浹ü�� ���� ��ġ

    float   m_fAngle;           // ȸ�� ����

    int     m_iCollisionCount;

public:
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

