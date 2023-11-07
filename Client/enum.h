#pragma once

// Level
enum class LEVEL_TYPE
{
	START_LEVEL,
	PLAY_LEVEL,
	EDITOR_LEVEL,

	TITLE_LEVEL,
	MAINMENU_LEVEL,

	END,
};



// Object layer
enum class LAYER
{
	DEFAULT,
	TILE,
	MONSTER,
	PLAYER,
	PLATFORM,
	PLAYER_PJ,
	MONST_PJ,
	WORLD_STATIC,


	UI = 31,
	END = 32,
};

// Task
enum class TASK_TYPE
{
	// Param1 : Layer Type, Param2 : Object Adress
	CREATE_OBJECT,

	// Param1 : Object Adress
	DELETE_OBJECT,

	// Param1 : LEVEL_TYPE
	LEVEL_CHANGE,


	END,
};

// GDI
enum class BRUSH_TYPE
{
	RED,
	GREEN,
	BLUE,
	BLACK,
	END,
};
enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

// KeyMgr
enum class KEY_STATE
{
	NONE,
	TAP,
	PRESSED,
	RELEASED,
	END,
};
enum class KEY
{
	_0, _1, _2, _3, _4, _5, _6, _7, _8, _9,

	NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9,

	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,

	TAB,
	LSHIFT,
	LALT,
	LCTRL,
	SPACE,

	ESC,
	ENTER,
	BACK,

	LEFT,
	RIGHT,
	UP,
	DOWN,

	LBTN,
	RBTN,

	KEY_END,
};


// Log
enum class LOG_LEVEL
{
	LOG,
	WARNING,
	ERR,
	END,
};


// State
enum class ENORMAL_MON_STATE
{
	NORMAL_MON_IDLE,
	NORMAL_MON_TRACE,
};

// Penitent 
enum class PENITENT_STATE
{
	FALLINGAHEAD,
	RISING,
	IDLE,
	STARTRRUN,
	RUN,
	ENDRUN,
	STOPRUN,
	JUMP,
	FALL,
	JUMPFORWARD,
	FALLFORWARD,
	ATTACK,
	UPWARDATTACK,
	UPWARDATTACKJUMP,
	DODGE,
	DODGETORUN,
	JUMPATT,
	HEALTHPOTION,
	CROUCH,
	CROUCHING,
	CROUCHATT,
	CROUCHUP,


};