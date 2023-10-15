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
#define GENERATED_OBJECT(type) typedef type Super;\
							   virtual void Abstract() override {}

// Tile
#define TILE_SIZE 64