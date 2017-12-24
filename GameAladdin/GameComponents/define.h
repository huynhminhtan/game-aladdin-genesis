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
//#include "..\debug.h"
//#include "utils.h"
using namespace std;

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 448
#define SCALE_FACTOR 2.0f

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

