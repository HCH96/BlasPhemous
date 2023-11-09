#pragma once

class CTexture;
class CObj;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
};

struct FCamEvent
{
	CAM_EFFECT	Type;
	float		AccTime;
	float		Duration;
};

class CCamera
{
	SINGLETON(CCamera);

private:

	Vec2		m_vPrevLookAt;	// ī�޶� ���� �����ӿ� ���� �ִ� ����
	Vec2		m_vCurLookAt;	// ī�޶� ���� �����ִ� ����
	Vec2		m_vLookAt;		// ī�޶� �ٶ������ ����
	Vec2		m_vDiff;		// realPos�� renderPos ����

	Vec2		m_vCameraLimit; // ī�޶� �ٶ� �� �ִ� ���� ����
	Vec2		m_vLookAtOffset;// ī�޶� �ٶ������ ������ ������
	float		m_fSpeed;		// Ÿ���� ���󰡴� �ӵ�

	


	CTexture*	m_pVeil;
	CObj*		m_pTarget;


	list<FCamEvent>		m_EventList;
	UINT				m_Alpha;

public:
	Vec2 GetRenderPos(Vec2 _vRealPos) { return _vRealPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }
	Vec2 GetCurLookAt() { return m_vCurLookAt; }

	void SetLookAt(Vec2 _vLookAt) { m_vLookAt = _vLookAt; }
	void InitLookAt(Vec2 _vLookAt)
	{
		m_vPrevLookAt = _vLookAt;
		m_vCurLookAt = _vLookAt;
	}
	void SetCameraLimit(Vec2 _vLimit) { m_vCameraLimit = _vLimit; }
	void SetLookAtOffset(Vec2 _vOffset) { m_vLookAtOffset = _vOffset; }
	void SetLookAtOffsetX(float _f) { m_vLookAtOffset.x = _f; }
	void SetLookAtOffsetY(float _f) { m_vLookAtOffset.y = _f; }

	void SetTarget(CObj* _pTarget) { m_pTarget = _pTarget; }
public:
	void tick();
	void render(HDC _dc);

public:
	void FadeIn(float _time)
	{
		FCamEvent evnt = {};
		evnt.Type = CAM_EFFECT::FADE_IN;
		evnt.AccTime = 0.f;
		evnt.Duration = _time;
		m_EventList.push_back(evnt);
	}

	void FadeOut(float _time)
	{
		FCamEvent evnt = {};
		evnt.Type = CAM_EFFECT::FADE_OUT;
		evnt.AccTime = 0.f;
		evnt.Duration = _time;
		m_EventList.push_back(evnt);
	}
};

