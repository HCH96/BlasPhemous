#pragma once
#include "CObj.h"

class CAnimator;
class CStatemachine;

class CGiantSword :
    public CObj
{
	GENERATED_OBJECT(CObj);

private:
    CAnimator* m_pAnimator;
    CAnimator* m_pEye;
	CCollider* m_pCollider;

    CStateMachine* m_pAI;

	bool m_bActive;
    float m_fHP;

public:
    float GetHP() { return m_fHP; }
	float GetActive() { return m_bActive; }

	void SetActive(bool _b) { m_bActive = _b; }

public:
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc) override;

	void OnHit();

public:
	virtual void BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) override;

public:
	CLONE_DISABLE(CGiantSword);
	CGiantSword();
	~CGiantSword();


};

