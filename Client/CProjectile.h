#pragma once
#include "CObj.h"

class CCollider;

class CProjectile :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    float   m_fSpeed;
    float   m_fTheta;
    CCollider* m_pCollider;

public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

    float GetTheta() { return m_fTheta; }
    float GetSpeed() { return m_fSpeed; }
    CCollider* GetCollider() { return m_pCollider; }

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE(CProjectile);
    CProjectile();
    CProjectile(const CProjectile& _Origin);
    ~CProjectile();

};

