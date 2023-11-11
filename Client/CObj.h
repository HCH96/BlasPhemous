#pragma once
#include "CEntity.h"

#include "CCamera.h"
#include "components.h"

class CObj :
	public CEntity
{
private:
	Vec2				m_vPos;
	Vec2				m_vScale;
	int					m_iLayerIdx;
	bool				m_bPrevDir;
	bool				m_bDir;
	bool                m_bIsFix;

	vector<CComponent*> m_vecComponent;		// ÄÄÆ÷³ÍÆ® º¤ÅÍ

public:
	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	Vec2 GetRenderPos() { return CCamera::GetInst()->GetRenderPos(m_vPos); }
	bool GetIsFix() { return m_bIsFix; }

	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetDir(bool _bDir) { m_bDir = _bDir; }
	void SetPrevDir(bool _bPrev) { m_bPrevDir = _bPrev; }
	void SetLayerIdx(int _iIdx) { m_iLayerIdx = _iIdx; }
	void SetIsFix(bool _b) { m_bIsFix = _b; }

	int  GetLayerIdx() { return m_iLayerIdx; }
	bool GetDir() { return m_bDir; }
	bool GetPrevDir() { return m_bPrevDir; }

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
	template<typename T>
	T* GetComponent()
	{
		for (size_t i = 0; i < m_vecComponent.size(); ++i)
		{
			if (dynamic_cast<T*>(m_vecComponent[i]))
			{
				return (T*)m_vecComponent[i];
			}
		}

		return nullptr;
	}

	template<typename T>
	T* GetComponent(const wstring& _strName)
	{
		for (size_t i = 0; i < m_vecComponent.size(); ++i)
		{
			T* pComponent = dynamic_cast<T*>(m_vecComponent[i]);
			if (pComponent && pComponent->GetName() == _strName)
			{
				return (T*)m_vecComponent[i];
			}
		}

		return nullptr;
	}


	template<typename T>
	void GetComponents(vector<T*>& _out)
	{
		for (size_t i = 0; i < m_vecComponent.size(); ++i)
		{
			if (dynamic_cast<T>(m_vecComponent[i]))
			{
				_out.push_back((T*)m_vecComponent[i]);
			}
		}
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

public:
	virtual CObj* Clone() = 0;
	CObj();
	CObj(const CObj& _Origin);
	virtual ~CObj();

	friend class CLevel;
	friend class CTaskMgr;
};

