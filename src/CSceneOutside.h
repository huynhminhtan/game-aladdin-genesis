#pragma once

#include "Header.h"
#include "CAladdin.h"

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

	CSprite*			_SpriteBackground; 

	CAladdin*			_Aladdin;
	STATE				_StateAladdin;
	DIRECTION			_DirectionAladdin;

	float				_PosBackGround_X;
};



