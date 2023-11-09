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

	Vec2		m_vPrevLookAt;	// 카메라가 직전 프레임에 보고 있던 지점
	Vec2		m_vCurLookAt;	// 카메라가 지금 보고있는 지점
	Vec2		m_vLookAt;		// 카메라가 바라봐야할 지점
	Vec2		m_vDiff;		// realPos와 renderPos 차이

	Vec2		m_vCameraLimit; // 카메라가 바라볼 수 있는 제한 지점
	Vec2		m_vLookAtOffset;// 카메라가 바라봐야할 지점의 오프셋
	float		m_fSpeed;		// 타겟을 따라가는 속도

	


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

