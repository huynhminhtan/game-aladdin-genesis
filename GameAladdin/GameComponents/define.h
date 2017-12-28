#pragma once
#ifndef __NS_FRAMEWORK__
#define __NS_FRAMEWORK__

#define _USE_MATH_DEFINES

#include <windows.h>
#include <exception>
#include <math.h>
#include <string>
#include <map>
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include <algorithm>

//#include "..\debug.h"
//#include "utils.h"
using namespace std;

#define WINDOW_WIDTH 640 
#define WINDOW_HEIGHT 448

#define SCALE_FACTOR 2.0f

#define SPACE_CAMERA 40
#define SPACE_ALADIN_UP 10

#define HEATH_ENEMY 130
#define HEATH_PLAYER 1000

#define DAMAGE_COAL_OF_ENEMY 10
#define DAMAGE_OF_PLAYER 50
#define DAMAGE_WEAPON_OF_PLAYER_AND_ENEMY 40

#define PLAYER_MASS 35
#define PLAYER_SPEED 45
#define PLAYER_JUMP_FORCE 70
#define PLAYER_JUMP_RUN_FORCE 80

#define NUM_APPLE_WEAPON 7
#define NUM_RUBBY 0

#define ENABLE_SWEPTAABB false
#define FPS 60

#define HURT_APPLE 5
#define HURT_HEALTH 30

////////////////////////////////////////////////////////////////////////////////////////

#define C_WHITE D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) // màu trắnng
#define COLOR_KEY D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f)	// màu khi mà load hình nó bỏ qua > trong suốt

#define VECTOR2ZERO GVector2(0.0f, 0.0f)
#define VECTOR2ONE  GVector2(1.0f, 1.0f)

#define ACTOR_SCENARIO [event_receiver(native)]

#define NS_FRAMEWORK		namespace FrameWork

#define NS_FRAMEWORK_BEGIN	{

#define NS_FRAMEWORK_END	}

#define US_FRAMEWORK		using namespace FrameWork;

#ifndef SAFE_DELETE

#define SAFE_DELETE(p) \
if(p) \
{\
	delete (p); \
	p = nullptr; \
} \

#endif // !SAFE_DELETE

#endif // !__NS_FRAMEWORK__

