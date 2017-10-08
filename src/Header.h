#pragma once

#define SPRITE_TITLE_BACKGROUND L"background_aladdin.png"
#define SPRITE_TITLE_ALADDIN_STAND L"sprite_aladdin_stand.bmp"
#define SPRITE_TITLE_ALADDIN_STAND_XML "sprite_aladdin_stand.xml"
#define SPRITE_TITLE_ALADDIN_WALK L"sprite_aladdin_walk.bmp"
#define SPRITE_TITLE_ALADDIN_WALK_XML "sprite_aladdin_walk.xml"

enum DIRECTION { NONE, LEFT, RIGHT, UP, DOWN };
enum	 STATE { STAND, WALK, CLIMB, SWING, DROP };

// include lib WINDOWS API
#include <windows.h>

// include lib DIRECTX
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

// include lib extend
#include "tinyxml.h"

// include lib STL
#include <list>
using namespace std;

// include component game
#include "Global.h"

#include "CScene.h"

#include "CAnimationSprite.h"

#include "CManagerScene.h"

#include "CSprite.h"
#include "CScene.h"

#include "CInput.h"

#include "trace.h"

// include object
//#include "CAladdinAction.h"
//
//#include "CAladdinStand.h"
//#include "CAladdinWalk.h"
//
//#include "CAladdin.h"
