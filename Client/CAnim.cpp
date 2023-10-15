#include "pch.h"
#include "CAnim.h"

#include "CObj.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CAssetMgr.h"

CAnim::CAnim()
	: m_pAnimator(nullptr)
	, m_pAtlas(nullptr)
	, m_iCurFrm(0)
	, m_bFinish(false)
	, m_fAccTime(0.f)
{
}

CAnim::~CAnim()
{
}



void CAnim::Create(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _fDuration, int _iMaxFrm)
{
	SetName(_strName);

	m_pAtlas = _pAtlas;
	m_vecFrm.reserve(_iMaxFrm);

	for (size_t i = 0; i < _iMaxFrm; ++i)
	{
		FFrame frm = {};
		frm.vLeftTop = _vLeftTop + Vec2(_vCutSize.x * i, 0.f);
		frm.vCutSize = _vCutSize;
		frm.fDuration = _fDuration;
		frm.vOffset = _vOffset;

		m_vecFrm.push_back(frm);
	}
}

bool CAnim::Save(const wstring& _FilePath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _FilePath.c_str(), L"w");

	if (nullptr == pFile)
	{
		LOG(LOG_LEVEL::ERR, L"파일 열기 실패");
		return false;
	}

	// Animation 이름 저장
	fwprintf_s(pFile, L"[ANIM_NAME]\n");

	wstring strName = GetName();
	fwprintf_s(pFile, strName.c_str());
	fwprintf_s(pFile, L"\n\n");

	// 키, 경로
	fwprintf_s(pFile, L"[ATLAS_TEXTURE]\n");

	wstring strKey;
	wstring strRelativePath;

	if (IsValid(m_pAtlas))
	{
		strKey = m_pAtlas->GetKey();
		strRelativePath = m_pAtlas->GetRelativePath();
	}

	fwprintf_s(pFile, strKey.c_str());
	fwprintf_s(pFile, L"\n");
	fwprintf_s(pFile, strRelativePath.c_str());
	fwprintf_s(pFile, L"\n\n");

	// 프레임 데이터
	// 프레임 숫자
	fwprintf_s(pFile, L"[FRAME_COUNT]\n");
	fwprintf_s(pFile, L"%zd\n\n", m_vecFrm.size());


	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		fwprintf_s(pFile, L"[FRAME_NUM]\n");
		fwprintf_s(pFile, L"%zd\n", i);

		fwprintf_s(pFile, L"[LEFT_TOP]\n");
		fwprintf_s(pFile, L"%f %f\n", m_vecFrm[i].vLeftTop.x, m_vecFrm[i].vLeftTop.y);

		fwprintf_s(pFile, L"[CUT_SIZE]\n");
		fwprintf_s(pFile, L"%f %f\n", m_vecFrm[i].vCutSize.x, m_vecFrm[i].vCutSize.y);

		fwprintf_s(pFile, L"[OFFSET]\n");
		fwprintf_s(pFile, L"%f %f\n", m_vecFrm[i].vOffset.x, m_vecFrm[i].vOffset.y);

		fwprintf_s(pFile, L"[DURATION]\n");
		fwprintf_s(pFile, L"%f\n\n", m_vecFrm[i].fDuration);
	}
	fclose(pFile);

	return true;
}

bool CAnim::Load(const wstring& _FilePath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _FilePath.c_str(), L"r");

	if (nullptr == pFile)
	{
		LOG(LOG_LEVEL::ERR, L"파일 열기 실패");
		return false;
	}

	// Animation 이름 로드
	while (true)
	{
		wchar_t szRead[256] = {};
		if (EOF == fwscanf_s(pFile, L"%s", szRead, 256))
		{
			break;
		}

		if (!wcscmp(szRead, L"[ANIM_NAME]"))
		{
			fwscanf_s(pFile, L"%s", szRead, 256);
			SetName(szRead);
		}
		else if (!wcscmp(szRead, L"[ATLAS_TEXTURE]"))
		{
			wstring strKey, strRelativePath;

			fwscanf_s(pFile, L"%s", szRead, 256);
			strKey = szRead;

			fwscanf_s(pFile, L"%s", szRead, 256);
			strRelativePath = szRead;

			m_pAtlas = CAssetMgr::GetInst()->LoadTexture(strKey, strRelativePath);
		}
		else if (!wcscmp(szRead, L"[FRAME_COUNT]"))
		{
			size_t iFrameCount = 0;
			fwscanf_s(pFile, L"%zd", &iFrameCount);
			m_vecFrm.resize(iFrameCount);

			size_t iCurFrame = 0;
			while (true)
			{
				fwscanf_s(pFile, L"%s", szRead, 256);

				if (!wcscmp(szRead, L"[FRAME_NUM]"))
				{
					fwscanf_s(pFile, L"%zd", &iCurFrame);
				}
				else if (!wcscmp(szRead, L"[LEFT_TOP]"))
				{
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vLeftTop.x);
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vLeftTop.y);
				}
				else if (!wcscmp(szRead, L"[CUT_SIZE]"))
				{
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vCutSize.x);
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vCutSize.y);
				}
				else if (!wcscmp(szRead, L"[OFFSET]"))
				{
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vOffset.x);
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vOffset.y);
				}
				else if (!wcscmp(szRead, L"[DURATION]"))
				{
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].fDuration);

					if (iFrameCount - 1 <= iCurFrame)
						break;
				}
			}
		}
	}

	fclose(pFile);
	return true;

}

void CAnim::finaltick(float _DT)
{
	if (m_bFinish)
		return;

	m_fAccTime += _DT;

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		m_fAccTime = 0.f;

		if (m_vecFrm.size() - 1 <= m_iCurFrm)
		{
			m_bFinish = true;
		}
		else
		{
			++m_iCurFrm;
		}
	}

}

void CAnim::render(HDC _dc)
{
	const FFrame& frm = m_vecFrm[m_iCurFrm];

	CObj* pOwnerObject = m_pAnimator->GetOwner();
	Vec2 vRenderPos = pOwnerObject->GetRenderPos();

	TransparentBlt(_dc, int(vRenderPos.x - (frm.vCutSize.x / 2.f) + frm.vOffset.x)
					  , int(vRenderPos.y - (frm.vCutSize.y / 2.f) + frm.vOffset.y)
					  , int(frm.vCutSize.x), int(frm.vCutSize.y)
					  , m_pAtlas->GetDC()
					  , int(frm.vLeftTop.x), int(frm.vLeftTop.y)
					  , int(frm.vCutSize.x), int(frm.vCutSize.y)
					  , RGB(255, 0, 255));

}

