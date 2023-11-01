#pragma once

#define SINGLETON(ClassType)		public:\
										 static ClassType* GetInst()\
										{\
											static ClassType mgr;\
											return &mgr;\
										}\
										public:\
											ClassType* operator = (const ClassType& _Origin) = delete;\
										private:\
											ClassType();\
											ClassType(const ClassType& _Origin) = delete;\
											~ClassType();
// 게임 이름
#define GAME_FOLDER MyGame

#define DEBUG_RENDER CEngine::GetInst()->DebugRender()
#define DT CTimeMgr::GetInst()->GetDeltaTime()

#define SELECT_PEN(DC,PEN) FSelectGDI TempPenSelect(DC, PEN)
#define SELECT_BRUSH(DC,BRUSH) FSelectGDI TempBrushSelect(DC, BRUSH)
#define SELECT_GDI(DC,PEN,BRUSH) FSelectGDI TempBrushSelect(DC,PEN, BRUSH)

// Key Manager
#define KEY_CHECK(Key,State) CKeyMgr::GetInst()->GetKeyState(Key) == State

#define KEY_TAP(Key) KEY_CHECK(Key, KEY_STATE::TAP)
#define KEY_PRESSED(Key) KEY_CHECK(Key, KEY_STATE::PRESSED)
#define KEY_RELEASED(Key) KEY_CHECK(Key, KEY_STATE::RELEASED)
#define KEY_NONE(Key) KEY_CHECK(Key, KEY_STATE::NONE)


// math
#define PI 3.14159265348979f


// Object
#define GENERATED_OBJECT(type) typedef type Super;
#define CLONE(type) virtual type* Clone() {return new type(*this);}
#define CLONE_DISABLE(type) virtual type* Clone() {return nullptr;}

// Tile
#define TILE_SIZE 64

#define CheckPosAndScale Vec2 vPos = GetPos();\
Vec2 vScale = GetScale();\
if (KEY_TAP(KEY::W)) {\
    SetPos({ vPos.x, vPos.y - 1 });\
    wstring buffer = L"";\
    buffer += L"vPos x : " + std::to_wstring(GetPos().x) + L" y: " + std::to_wstring(GetPos().y);\
    CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });\
}\
if (KEY_TAP(KEY::S)) {\
    SetPos({ vPos.x, vPos.y + 1 });\
    wstring buffer = L"";\
    buffer += L"vPos x : " + std::to_wstring(GetPos().x) + L" y: " + std::to_wstring(GetPos().y);\
    CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });\
}\
if (KEY_TAP(KEY::A)) {\
    SetPos({ vPos.x - 1, vPos.y });\
    wstring buffer = L"";\
    buffer += L"vPos x : " + std::to_wstring(GetPos().x) + L" y: " + std::to_wstring(GetPos().y);\
    CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });\
}\
if (KEY_TAP(KEY::D)) {\
    SetPos({ vPos.x + 1, vPos.y });\
    wstring buffer = L"";\
    buffer += L"vPos x : " + std::to_wstring(GetPos().x) + L" y: " + std::to_wstring(GetPos().y);\
    CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });\
}\
\
if (KEY_TAP(KEY::UP)) {\
    SetScale({ vScale.x, vScale.y + 0.1f });\
    wstring buffer = L"";\
    buffer += L"vPos x : " + std::to_wstring(GetScale().x) + L" y: " + std::to_wstring(GetScale().y);\
    CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });\
}\
if (KEY_TAP(KEY::DOWN)) {\
    SetScale({ vScale.x, vScale.y - 0.1f });\
    wstring buffer = L"";\
    buffer += L"vPos x : " + std::to_wstring(GetScale().x) + L" y: " + std::to_wstring(GetScale().y);\
    CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });\
}\
if (KEY_TAP(KEY::LEFT)) {\
    SetScale({ vScale.x - 0.1f, vScale.y });\
    wstring buffer = L"";\
    buffer += L"vPos x : " + std::to_wstring(GetScale().x) + L" y: " + std::to_wstring(GetScale().y);\
    CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });\
}\
if (KEY_TAP(KEY::RIGHT)) {\
    SetScale({ vScale.x + 0.1f, vScale.y });\
    wstring buffer = L"";\
    buffer += L"vPos x : " + std::to_wstring(GetScale().x) + L" y: " + std::to_wstring(GetScale().y);\
    CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });\
}

    //TransparentBlt(_dc, int(vRenderPos.x - (frm.vCutSize.x / 2.f) + frm.vOffset.x)
    //				  , int(vRenderPos.y - (frm.vCutSize.y / 2.f) + frm.vOffset.y)
    //				  , int(frm.vCutSize.x), int(frm.vCutSize.y)
    //				  , m_pAtlas->GetDC()
    //				  , int(frm.vLeftTop.x), int(frm.vLeftTop.y)
    //				  , int(frm.vCutSize.x), int(frm.vCutSize.y)
    //				  , RGB(255, 0, 255));