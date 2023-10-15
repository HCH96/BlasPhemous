#pragma once
#include "CEntity.h"

#include "CCamera.h"

class CComponent;
class CCollider;

class CObj :
	public CEntity
{
private:
	Vec2				m_vPos;
	Vec2				m_vScale;
	int					m_iLayerIdx;
	
	vector<CComponent*> m_vecComponent;		// ÄÄÆ÷³ÍÆ® º¤ÅÍ

public:
	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	Vec2 GetRenderPos() { return CCamera::GetInst()->GetRenderPos(m_vPos); }

	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	int  GetLayerIdx() { return m_iLayerIdx; }
	

protected:
	template<typename T>
	T* AddComponent(const wstring& _strName = L"")
	{
		T* pNewComponent = new T(this);
		pNewComponent->SetName(_strName);
		m_vecComponent.push_back(pNewComponent);
		return pNewComponent;
	}

public:
	virtual void BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) {}
	virtual void Overlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) {}
	virtual void EndOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) {}

public:
	virtual void begin() {}
	virtual void tick(float _DT);
	virtual void finaltick(float _DT) final;
	virtual void render(HDC _dc);
	void Destroy();

private:
	void SetDead();

private:
	virtual void Abstract() = 0;

public:
	CObj();
	virtual ~CObj();

	friend class CLevel;
	friend class CTaskMgr;
};

