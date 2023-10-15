#pragma once
#include "CProjectile.h"


class CMonster;

class CProjectile3 :
    public CProjectile
{
private:
    CMonster* m_pTarget;

    Vec2 m_vDir;
    float m_fSpeed;
    float m_fTheta; // �� ��ȭ��
    Vec2 m_vDiff;   // �Ѿ� -> monster ����

public:
    virtual void tick(float _DT) override;

    void AdjustDir(float _DT);
    void Targeting();


public:
    CProjectile3();
    ~CProjectile3();

};