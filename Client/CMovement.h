#pragma once
#include "CComponent.h"

class CMovement :
    public CComponent
{
private:
    Vec2    m_vForce;
    Vec2    m_vAccel;
    Vec2    m_vVelocity;
    float   m_fMass;
    float   m_fInitSpeed;
    float   m_fJumpVel;

    float   m_fMaxSpeed;
    float   m_fMaxDown;
    float   m_fFrictionScale;

    Vec2    m_vGravityForce;
    bool    m_bUseGravity;
    bool    m_bGround;

public:
    Vec2 GetForce() { return m_vForce; }
    Vec2 GetVelocity() { return m_vVelocity; }
    float GetJumpVel() { return m_fJumpVel; }
    float GetMaxDown() { return m_fMaxDown; }
    float GetMass() { return m_fMass; }
    float GetInitSpeed() { return m_fInitSpeed; }
    float GetMaxSpeed() { return m_fMaxSpeed; }
    float GetFrictionScale() { return m_fFrictionScale; }
    Vec2 GetGravityDir() { return Vec2(m_vGravityForce.Normalize()); }
    bool IsUseGravity() { return m_bUseGravity; }
    bool IsGround() { return m_bGround; }

public:
    void SetJumpVel(float _f) { m_fJumpVel = _f; }
    void SetMaxDown(float _f) { m_fMaxDown = _f; }
    void AddForce(Vec2 _vForce) { m_vForce += _vForce; }
    void AddVelocity(Vec2 _vAdd) { m_vVelocity += _vAdd; }
    void SetVelocity(Vec2 _vVelocity) { m_vVelocity = _vVelocity; }
    void SetMass(float _fMass) { m_fMass = _fMass; }
    void SetInitSpeed(float _fSpeed) { m_fInitSpeed = _fSpeed; }
    void SetMaxSpeed(float _fSpeed) { m_fMaxSpeed = _fSpeed; }
    void SetFrictionScale(float _F) { m_fFrictionScale = _F; }
    void UseGravity(bool _bUse) { m_bUseGravity = _bUse; }
    void SetGravity(Vec2 _vGravity) { m_vGravityForce = _vGravity; }
    void SetGround(bool _bGround) 
    {
        if (_bGround)
        {
            m_vVelocity.y = 0.f;
        }
        m_bGround = _bGround;
    }
    



public:
    virtual void finaltick(float _DT) override;

public:
    CLONE(CMovement);
    CMovement(CObj* _Owner);
    ~CMovement();
};
