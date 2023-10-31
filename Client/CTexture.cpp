#include "pch.h"
#include "CTexture.h"

#include "CEngine.h"
#include "CPathMgr.h"

CTexture::CTexture()
	: m_hBit(nullptr)
	, m_hDC(nullptr)
	, m_Info{}
{
}

CTexture::~CTexture()
{
	DeleteObject(m_hBit);
	DeleteDC(m_hDC);
}


void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	m_hBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _iWidth, _iHeight);
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());

	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	DeleteObject(SelectObject(m_hDC, m_hBit));
	GetObject(m_hBit, sizeof(BITMAP), &m_Info);

}

bool CTexture::Load(const wstring& _strFilePath)
{
	wchar_t szExt[20] = {};
	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 20);

	if (!wcscmp(szExt, L".bmp") || !wcscmp(szExt, L".BMP"))
	{
		m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (nullptr == m_hBit)
		{
			return false;
		}
	}
	else if (!wcscmp(szExt, L".png") || !wcscmp(szExt, L".PNG"))
	{
		ULONG_PTR gdiplusToken = 0;
		GdiplusStartupInput gidstartupInput = {};
		GdiplusStartup(&gdiplusToken, &gidstartupInput, nullptr);
		Image* pImg = Image::FromFile(_strFilePath.c_str(), false);

		Bitmap* pBitmap = (Bitmap*)pImg->Clone();
		Status stat = pBitmap->GetHBITMAP(Color(0, 0, 0, 0), &m_hBit);

		if (Status::Ok != stat)
			return false;
	}

	
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	DeleteObject((HBITMAP)SelectObject(m_hDC, m_hBit));
	GetObject(m_hBit, sizeof(BITMAP), &m_Info);

	return true;
}
