#include "pch.h"
#include "CTile.h"

#include "CAssetMgr.h"
#include "CTexture.h"

CTile::CTile()
	: m_pAtlas(nullptr)
	, m_Idx(0)
{
	m_pAtlas = CAssetMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\TILE.bmp");
}

CTile::~CTile()
{
}



void CTile::AddImgIdx()
{
	if (m_pAtlas == nullptr)
		return;

	++m_Idx;

	UINT iWidth = m_pAtlas->GetWidth();
	UINT iHeight = m_pAtlas->GetHeight();

	UINT iMaxRow = iHeight / TILE_SIZE;
	UINT iMaxCol = iWidth / TILE_SIZE;

	UINT iMaxTileCount = iMaxRow * iMaxCol;

	if (int(iMaxTileCount) <= m_Idx)
	{
		m_Idx = 0;
	}

}

void CTile::tick(float _DT)
{

}

void CTile::render(HDC _dc)
{
	Vec2 vRenderPos = GetRenderPos();

	if (nullptr == m_pAtlas)
	{
		Rectangle(_dc, int(vRenderPos.x), int(vRenderPos.y)
			, int(vRenderPos.x + TILE_SIZE)
			, int(vRenderPos.y + TILE_SIZE));
	}
	else
	{
		UINT width = m_pAtlas->GetWidth();
		UINT height = m_pAtlas->GetHeight();

		UINT maxRow = height / TILE_SIZE;
		UINT maxCol = width / TILE_SIZE;

		UINT maxTileCount = maxRow * maxCol;

		if ((int)maxTileCount <= m_Idx)
		{
			return;
		}

		UINT iRow = m_Idx / maxCol;
		UINT iCol = m_Idx % maxCol;

		Vec2 vLeftTop = Vec2(TILE_SIZE * iCol, TILE_SIZE * iRow);

		BitBlt(_dc, (int)vRenderPos.x, (int)vRenderPos.y
			, TILE_SIZE, TILE_SIZE
			, m_pAtlas->GetDC()
			, (int)vLeftTop.x, (int)vLeftTop.y, SRCCOPY);
	}


}

