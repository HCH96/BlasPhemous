#include "pch.h"
#include "CLevel.h"

#include "CTimeMgr.h"
#include "CLayer.h"
#include "CObj.h"

#include "CTile.h"


CLevel::CLevel()
	: m_iTileCol(0)
	, m_iTileRow(0)
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		m_arrLayer[i] = new CLayer;
	}
}

CLevel::~CLevel()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		if(m_arrLayer != nullptr)
			delete m_arrLayer[i];
	}

}

void CLevel::begin()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		m_arrLayer[i]->begin();
	}
}

void CLevel::tick()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		m_arrLayer[i]->clear();
	}

	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		m_arrLayer[i]->tick(DT);
	}

	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		m_arrLayer[i]->finaltick(DT);
	}

}

void CLevel::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		m_arrLayer[i]->render(_dc);
	}

}

void CLevel::AddObject(LAYER _eLayer, CObj* _Object)
{
	m_arrLayer[(UINT)_eLayer]->AddObject(_Object);

	_Object->m_iLayerIdx = (int)_eLayer;
}

void CLevel::DeleteAllObjects()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		m_arrLayer[i]->DeleteAllObjects();
	}

}

void CLevel::DeleteObjectsByLayer(LAYER _eLayer)
{
	m_arrLayer[(UINT)_eLayer]->DeleteAllObjects();
}

void CLevel::CreateTile(UINT _iRow, UINT _iCol)
{
	DeleteObjectsByLayer(LAYER::TILE);

	m_iTileRow = _iRow;
	m_iTileCol = _iCol;


	for (UINT i = 0; i < m_iTileRow; ++i)
	{
		for (UINT j = 0; j < m_iTileCol; ++j)
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vec2(TILE_SIZE * j, TILE_SIZE * i));
			AddObject(LAYER::TILE, pTile);
		}
	}

}

