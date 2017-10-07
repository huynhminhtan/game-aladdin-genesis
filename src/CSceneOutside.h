#pragma once

#include "Header.h"

#define SPRITE_TITLE L"kitty_right.bmp"
#define SPRITE_TITLE_BACKGROUND L"background_aladdin.png"

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
	CAnimationSprite*	_aspBackground;

	float				_PosBackGround_X;
};



