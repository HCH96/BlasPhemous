#pragma once
#include "CObj.h"

class CFireboltSpawner;
class CMagicMissileSpawner;
class CToxicSpawner;
class CLightningSpawner;

class CPope :
	public CObj
{

	GENERATED_OBJECT(CObj);

private:
	CAnimator* m_pAnimator;
	CAnimator* m_pEffector;
	CAnimator* m_pSymbol;
	CAnimator* m_pBlock;

	CCollider* m_pCollider;
	CStateMachine* m_pAI;

	CFireboltSpawner* m_pFireSpawner;
	CMagicMissileSpawner* m_pMagicMissileSpawner;
	CToxicSpawner* m_pToxicSpawner;
	CLightningSpawner* m_pLightningSpawner;

	float       m_fHP;

public:
	float GetHP() { return m_fHP; }
	CFireboltSpawner* GetFireSpawner() { return m_pFireSpawner; }
	CMagicMissileSpawner* GetMagicSpawner() { return m_pMagicMissileSpawner; }
	CToxicSpawner* GetToxicSpawner() { return m_pToxicSpawner; }
	CLightningSpawner* GetLightningSpawner() { return m_pLightningSpawner; }

	void RegisterFireSpawner(CFireboltSpawner* _pSpawner) { m_pFireSpawner = _pSpawner; }
	void RegisterMagicSpawner(CMagicMissileSpawner* _pSpawner) { m_pMagicMissileSpawner = _pSpawner; }
	void RegisterToxicSpawner(CToxicSpawner* _pSpawner) { m_pToxicSpawner = _pSpawner; }
	void RegisterLightningSpawner(CLightningSpawner* _pSpawner) { m_pLightningSpawner = _pSpawner; }

public:
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc) override;

	void OnHit();

public:
	virtual void BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) override;

public:
	CLONE_DISABLE(CPope);
	CPope();
	~CPope();
};

