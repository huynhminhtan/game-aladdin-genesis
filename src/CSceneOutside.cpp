#include "CSceneOutside.h"

CSceneOutSide::CSceneOutSide()
{
	_PosBackGround_X = 0;
	_aspBackground = nullptr;
	//_SpriteHandler
}

CSceneOutSide::~CSceneOutSide()
{
}

void CSceneOutSide::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	// init animation sprite
	_aspBackground = new CAnimationSprite(d3ddv);
	_aspBackground->Init();
	_aspBackground->Load(SPRITE_TITLE_BACKGROUND, D3DCOLOR_XRGB(0, 0, 255));

}

void CSceneOutSide::Update(float dt)
{
	if (CInput::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		_PosBackGround_X += 0.1 * dt;
	}

	if (CInput::GetInstance()->IsKeyDown(DIK_LEFT))
	{
		_PosBackGround_X -= 0.1 * dt;
	}

}

void CSceneOutSide::Render()
{
	// render background
	_aspBackground->Render(0, 0, _PosBackGround_X, 190, 1024, 640, 1.3);
	//_aspBackground->Render(0, 0, 1.3);

}

void CSceneOutSide::Destroy()
{
	_aspBackground->Release();
}

void CSceneOutSide::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		_PosBackGround_X -= 10;
		break;
	}
}

void CSceneOutSide::OnKeyUP(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_LEFT:
		_PosBackGround_X += 10;
		break;
	}
}