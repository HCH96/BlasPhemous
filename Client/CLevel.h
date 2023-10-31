#pragma once

#include "CEntity.h"
#include "CLayer.h"


class CObj;
class CLayer;

class CLevel : 
	public CEntity
{
private:
	CLayer*			m_arrLayer[(UINT)LAYER::END];

	UINT			m_iTileRow;
	UINT			m_iTileCol;

public:
	template<typename T>
	void GetObjects(vector<T*>& _Out);

	const vector<CObj*>& GetObjects(LAYER _eLayer) { return m_arrLayer[(UINT)_eLayer]->GetObjects(); }
	CLayer* GetLayer(int LayerIdx)
	{
		assert(!(LayerIdx < 0 || (UINT)LAYER::END <= LayerIdx));
		return m_arrLayer[LayerIdx];
	}

	UINT GetTileRow() { return m_iTileRow; }
	UINT GetTileCol() { return m_iTileCol; }

	CObj* FindObjectByName(const wstring& _Name);

protected:
	void AddObject(LAYER _eLayer, CObj* _Object);
	void DeleteAllObjects();
	void DeleteObjectsByLayer(LAYER _eLayer);

public:
	void CreateTile(UINT _iRow, UINT _iCol);

public:
	virtual void init() = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;

	virtual void begin();
	virtual void tick();
	virtual void render(HDC _dc);

public:
	CLONE_DISABLE(CLevel);
	CLevel();
	CLevel(const CLevel& _Origin) = delete;
	~CLevel();

	friend class CLevelMgr;
	friend class CTaskMgr;
};


template<typename T>
void CLevel::GetObjects(vector<T*>& _Out)
{
	for (UINT j = 0; j < (UINT)LAYER::END; ++j)
	{
		for (size_t i = 0; i < m_arrLayer[j]->m_vecObjects.size(); ++i)
		{
			T* pObj = dynamic_cast<T*>(m_arrLayer[j]->m_vecObjects[i]);

			if (pObj != nullptr)
			{
				_Out.push_back(pObj);
			}
		}
	}
}