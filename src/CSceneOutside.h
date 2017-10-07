#pragma once

#include "Header.h"

#define SPRITE_TITLE L"kitty_right.bmp"
#define SPRITE_TITLE_BACKGROUND L"background_aladdin.png"
#define SPRITE_TITLE_ALADDIN L"sprite_aladdin.bmp"
#define SPRITE_TITLE_ALADDIN_XML "sprite_aladdin.xml"

class CSceneOutSide :public CScene
{
public:
	CSceneOutSide();
	~CSceneOutSide();

	void Init(LPDIRECT3DDEVICE9);
	void Update(float dt);
	void Render();
	void Destroy();

	// event key press / short time
	void OnKeyDown(int);
	void OnKeyUP(int);

private:

	LPD3DXSPRITE		_SpriteHandler;

	// background
	CSprite*			_SpriteBackground;

	// aladdin
	CAnimationSprite*	_AspAladdin;

	float				_PosBackGround_X;
};



