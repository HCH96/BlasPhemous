#pragma once

class CTexture;

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
	Vec2		m_vLookAt;
	Vec2		m_vDiff;
	CTexture*	m_pVeil;

	list<FCamEvent>		m_EventList;
	UINT				m_Alpha;

public:
	Vec2 GetRenderPos(Vec2 _vRealPos) { return _vRealPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }
	void SetLookAt(Vec2 _vLookAt) { m_vLookAt = _vLookAt; }

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

