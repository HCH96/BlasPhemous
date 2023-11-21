#include "pch.h"
#include "CAnim.h"

#include "CEngine.h"

#include "CObj.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CAssetMgr.h"

#include "CKeyMgr.h"


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

bool CAnim::LoadMeta(CTexture* _pTexture, const wstring& _strAnimKey, const wstring& _strMetaRelativePath)
{
	SetName(_strAnimKey);
	m_pAtlas = _pTexture;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _strMetaRelativePath.c_str(), L"r");

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

		if (!wcscmp(szRead, L"%YAML"))
		{
			FFrame frm = {};
			frm.vLeftTop = Vec2(0.f, 0.f);
			frm.vCutSize = Vec2(0.f, 0.f);
			frm.vOffset = Vec2(0.f, 0.f);
			frm.fDuration = 0.1f;


			while (true)
			{
				fwscanf_s(pFile, L"%s", szRead, 256);

				if (!wcscmp(szRead, L"m_Rect:"))
				{
					while (true)
					{
						fwscanf_s(pFile, L"%s", szRead, 256);

						if (!wcscmp(szRead, L"x:"))
						{
							fwscanf_s(pFile, L"%f", &frm.vLeftTop.x);
						}

						if (!wcscmp(szRead, L"y:"))
						{
							fwscanf_s(pFile, L"%f", &frm.vLeftTop.y);
						}

						if (!wcscmp(szRead, L"width:"))
						{
							fwscanf_s(pFile, L"%f", &frm.vCutSize.x);
						}
						if (!wcscmp(szRead, L"height:"))
						{
							fwscanf_s(pFile, L"%f", &frm.vCutSize.y);
						}

						if (!wcscmp(szRead, L"m_Offset:"))
						{
							frm.vLeftTop.y = _pTexture->GetHeight() - frm.vLeftTop.y - frm.vCutSize.y;
							break;
						}



					}
				}

				if (!wcscmp(szRead, L"m_Offset:"))
				{
					while (true)
					{
						fwscanf_s(pFile, L"%s", szRead, 256);

						if (!wcscmp(szRead, L"{x:"))
						{
							fwscanf_s(pFile, L"%f", &frm.vOffset.x);

							frm.vOffset.x = frm.vOffset.x * -1;
						}
						if (!wcscmp(szRead, L"y:"))
						{
							fwscanf_s(pFile, L"%s", szRead, 256);

							int length = (int)wcslen(szRead);

							if (length > 0) {
								szRead[length - 1] = '\0';
							}

							wchar_t* end;
							float tmp = wcstof(szRead, &end);
							if (*end == L'\0') {
								frm.vOffset.y = tmp;
							}
							break;
						}
						if (!wcscmp(szRead, L"m_Border:"))
						{
							break;
						}
					}
				}
				if (!wcscmp(szRead, L"m_Border:"))
					break;

			}
			m_vecFrm.push_back(frm);

		}


	}

	fclose(pFile);
	return true;
}

bool CAnim::LoadMetaReverse(CTexture* _pTexture, const wstring& _strAnimKey, const wstring& _strMetaRelativePath)
{
	SetName(_strAnimKey);
	m_pAtlas = _pTexture;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _strMetaRelativePath.c_str(), L"r");

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

		if (!wcscmp(szRead, L"%YAML"))
		{
			FFrame frm = {};
			frm.vLeftTop = Vec2(0.f, 0.f);
			frm.vCutSize = Vec2(0.f, 0.f);
			frm.vOffset = Vec2(0.f, 0.f);
			frm.fDuration = 0.1f;

			// x = texture.x - x - sclae.x +1;
			float tmpX = 0.f;

			while (true)
			{
				fwscanf_s(pFile, L"%s", szRead, 256);

				if (!wcscmp(szRead, L"m_Rect:"))
				{
					while (true)
					{
						fwscanf_s(pFile, L"%s", szRead, 256);

						if (!wcscmp(szRead, L"x:"))
						{
							fwscanf_s(pFile, L"%f", &frm.vLeftTop.x);
						}

						if (!wcscmp(szRead, L"y:"))
						{
							fwscanf_s(pFile, L"%f", &frm.vLeftTop.y);
						}

						if (!wcscmp(szRead, L"width:"))
						{
							fwscanf_s(pFile, L"%f", &frm.vCutSize.x);
						}
						if (!wcscmp(szRead, L"height:"))
						{
							fwscanf_s(pFile, L"%f", &frm.vCutSize.y);
						}

						if (!wcscmp(szRead, L"m_Offset:"))
						{
							frm.vLeftTop.x = _pTexture->GetWidth() - frm.vLeftTop.x - frm.vCutSize.x;
							frm.vLeftTop.y = _pTexture->GetHeight() - frm.vLeftTop.y - frm.vCutSize.y;
							break;
						}



					}
				}

				if (!wcscmp(szRead, L"m_Offset:"))
				{
					while (true)
					{
						fwscanf_s(pFile, L"%s", szRead, 256);

						if (!wcscmp(szRead, L"{x:"))
						{
							fwscanf_s(pFile, L"%f", &frm.vOffset.x);

						}
						if (!wcscmp(szRead, L"y:"))
						{
							fwscanf_s(pFile, L"%s", szRead, 256);

							int length = (int)wcslen(szRead);

							if (length > 0) {
								szRead[length - 1] = '\0';
							}

							wchar_t* end;
							float tmp = wcstof(szRead, &end);
							if (*end == L'\0') {
								frm.vOffset.y = tmp;
							}
							break;
						}
						if (!wcscmp(szRead, L"m_Border:"))
						{
							break;
						}
					}
				}
				if (!wcscmp(szRead, L"m_Border:"))
					break;

			}
			m_vecFrm.push_back(frm);

		}


	}

	fclose(pFile);
	return true;
}

void CAnim::finaltick(float _DT)
{


	// Frame test code

	if (KEY_PRESSED(KEY::SPACE))
	{
		if (KEY_TAP(KEY::RIGHT))
		{
			++m_iCurFrm;
			if (m_vecFrm.size() <= m_iCurFrm)
			{
				m_iCurFrm = 0;
			}
		}

		if (KEY_TAP(KEY::LEFT))
		{
			--m_iCurFrm;
			if (0 > m_iCurFrm)
			{
				m_iCurFrm = (int)m_vecFrm.size() - 1;
			}
		}
	}
	else
	{
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


}

void CAnim::render(HDC _dc)
{
	const FFrame& frm = m_vecFrm[m_iCurFrm];

	CObj* pOwnerObject = m_pAnimator->GetOwner();
	Vec2 vScale = pOwnerObject->GetScale();
	Vec2 vPos = pOwnerObject->GetPos();

	Vec2 vRenderPos = pOwnerObject->GetRenderPos();

	if (m_pAnimator->IsLock())
	{
		vRenderPos = m_pAnimator->GetTmpPos();
		vRenderPos = CCamera::GetInst()->GetRenderPos(vRenderPos);
	}

	Vec2 vSize = frm.vCutSize * vScale;
	Vec2 vOffset = frm.vOffset * vScale;
	int iAlpha = m_pAnimator->GetAlpha();


	float fAngle = DegreeToRadian(pOwnerObject->GetAngle());


	HDC mainDC = CEngine::GetInst()->GetMainDC();


	//회전 0일때,
	if (0.f == fAngle)
	{
		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;

		blend.SourceConstantAlpha = iAlpha; // 0 ~ 255
		blend.AlphaFormat = AC_SRC_ALPHA; // 0

		AlphaBlend(_dc, int(vRenderPos.x - (vSize.x / 2.f) + vOffset.x)
			, int(vRenderPos.y - (vSize.y / 2.f) + vOffset.y)
			, int(vSize.x), int(vSize.y)
			, m_pAtlas->GetDC()
			, int(frm.vLeftTop.x), int(frm.vLeftTop.y)
			, int(frm.vCutSize.x), int(frm.vCutSize.y)
			, blend);

	}
	//회전이 0이아닐때
	else
	{


		//
		// (destDC, 0, 0, dest_width, dest_height, PATCOPY);                           // 선택된 브러시로, 회전할 비트맵을 출력받을 DC에, 미리 색상을 채워 지움   

		

		float cosine = (float)cos(fAngle);                                              // 회전이동변환 행렬에 들어갈 cos세타 값을 구함          
		float sine = (float)sin(fAngle);                                              // 회전이동변환 행렬에 들어갈 sin세타 값을 구함   

		SetGraphicsMode(_dc, GM_ADVANCED);                                               // 윈도우 좌표계의 회전을 위하여, 그래픽모드를 확장모드로 변경합니다.(요구사항:윈98,NT이상)   

		// 회전이동변환 행렬을 정의.   
		// (윈도우즈 API정복 개정판 2권 Page(1279) 참조.)   
		// (게임 프로그래머를 위한 기초수학과 물리 Page(196) 참조.)   

		XFORM xform;                                                                        // 방정식을 표현하는 3행3열의 행렬 선언   
		xform.eM11 = cosine;                                                                // 1행 1열 성분 설정 (회전성분)   
		xform.eM12 = sine;                                                                  // 1행 2열 성분 설정 (회전성분)   
		xform.eM21 = -sine;                                                                 // 2행 1열 성분 설정 (회전성분)   
		xform.eM22 = cosine;                                                                // 2행 2열 성분 설정 (회전성분)   
		xform.eDx = vRenderPos.x;                                               // 3행 1열 성분 설정 (X축 이동 성분)   
		xform.eDy = vRenderPos.y;                                              // 3행 2열 성분 설정 (Y축 이동 성분)   

		// 설정한 행렬로, 인수DC의 윈도우즈 좌표계를 변환.   
		// 인수DC는 출력대상으로 메모리비트맵을 가지므로,   
		// 선택하고 있는 메모리비트맵의 좌표체계가 회전된다.   

		SetWorldTransform(_dc, &xform);

		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;

		blend.SourceConstantAlpha = 255; // 0 ~ 255
		blend.AlphaFormat = AC_SRC_ALPHA; // 0

		AlphaBlend(_dc
			, -int(vSize.x / 2.f) + vOffset.x
			, -int(vSize.y / 2.f) + vOffset.y
			, int(vSize.x)
			, int(vSize.y)
			, m_pAtlas->GetDC()
			, int(frm.vLeftTop.x), int(frm.vLeftTop.y)
			, int(frm.vCutSize.x), int(frm.vCutSize.y)
			, blend);


		xform.eM11 = 1.f;
		xform.eM12 = 0.f;
		xform.eM21 = 0.f;
		xform.eM22 = 1.f;
		xform.eDx = 0.f;
		xform.eDy = 0.f;
		SetWorldTransform(_dc, &xform);

	}

}


//
//{
//	void CAnim::render(HDC _dc)
//	{
//
//
//		const FFrame& frm = m_vecFrm[m_iCurFrm];
//
//		CObj* pOwnerObject = m_pAnimator->GetOwner();
//		Vec2 vRenderPos = pOwnerObject->GetRenderPos();
//		float offsetx = frm.vOffset.x;
//
//		HDC tmpdc = frm.m_Atlas->GetDC();
//		if (ORT_RIGHT == m_pAnimator->GetOwner()->ort) {
//			tmpdc = frm.m_Atlas_r->GetDC();
//			offsetx *= -1;
//		}
//
//}