#pragma once
#include "CEntity.h"

class CObj;
class CCollider;

class CLayer : 
	public CEntity
{
private:
	vector<CObj*>	m_vecObjects;
	vector<CCollider*>	m_vecCollider;

public:
	void clear() { m_vecCollider.clear(); }
	void AddObject(CObj* _pObject) { m_vecObjects.push_back(_pObject); }
	void DeleteAllObjects();
	void RegisterCollider(CCollider* _pCollider) { m_vecCollider.push_back(_pCollider); }

	const vector<CObj*>& GetObjects() { return m_vecObjects; }
	const vector<CCollider*>& GetColliders() { return m_vecCollider; }


public:
	void begin();
	void tick(float _DT);
	void finaltick(float _DT);
	void render(HDC _dc);

	
public:
	CLONE_DISABLE(CLayer);
	CLayer();
	CLayer(const CLayer& _Origin) = delete;
	~CLayer();

	friend class CLevel;
	friend class CUIMgr;
};

