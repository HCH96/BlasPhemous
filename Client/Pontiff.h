#pragma once
#include "CObj.h"

class CGiantSword;
class CFireboltSpawner;
class CMagicMissileSpawner2;
class CToxicSpawner;
class CLightningSpawner2;


class Pontiff :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    

    CStateMachine* m_pPatternAI;
    CStateMachine* m_pAI;
    float       m_fHP;


public:
    CGiantSword* m_pSword;
    CAnimator* m_pHelmet;
    CAnimator* m_pFace;
    CAnimator* m_pBody;
    CAnimator* m_pSymbolLeft;
    CAnimator* m_pSymbolRight;
    CCollider* m_pCollider;

    CToxicSpawner* m_pToxicSpawner;
    CLightningSpawner2* m_pLightningSpawner;
    vector<CFireboltSpawner*> m_vecFireboltSpawner;
    vector<CMagicMissileSpawner2*> m_vecMagicMissileSpawner;



public:
	float GetHP() { return m_fHP; }

    void RegisterSword(CGiantSword* _pSword) { m_pSword = _pSword; }
	void RegisterFireSpawner(CFireboltSpawner* _pSpawner) { m_vecFireboltSpawner.push_back(_pSpawner); }
	void RegisterMagicSpawner(CMagicMissileSpawner2* _pSpawner) { m_vecMagicMissileSpawner.push_back(_pSpawner); }
	void RegisterToxicSpawner(CToxicSpawner* _pSpawner) { m_pToxicSpawner = _pSpawner; }
	void RegisterLightningSpawner(CLightningSpawner2* _pSpawner) { m_pLightningSpawner = _pSpawner; }

public:
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc) override;

	void OnHit();

public:
	virtual void BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) override;

public:
	CLONE_DISABLE(Pontiff);
	Pontiff();
	~Pontiff();

};

