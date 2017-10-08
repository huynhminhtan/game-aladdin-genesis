#include "CSceneOutside.h"

CSceneOutSide::CSceneOutSide()
{
	_PosBackGround_X = 0;
	//_AspAladdin = nullptr;
	_SpriteBackground = nullptr;
	//_SpriteHandler
	_Aladdin = nullptr;
	_StateAladdin = STATE::STAND;
	_DirectionAladdin = DIRECTION::RIGHT;
}

CSceneOutSide::~CSceneOutSide()
{
}

void CSceneOutSide::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	// init sprite Background
	_SpriteBackground = new CSprite(d3ddv);
	_SpriteBackground->Init();
	// load sprite
	_SpriteBackground->Load(SPRITE_TITLE_BACKGROUND, D3DCOLOR_XRGB(0, 0, 255));

	_Aladdin = new CAladdin();
	// init Aladdin
	_Aladdin->Init();
}

void CSceneOutSide::Update(float dt)
{
	if (CInput::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		// translate background
		_PosBackGround_X += 0.1 * dt;

		// set state Aladdin
		_StateAladdin = STATE::WALK;
		_DirectionAladdin = DIRECTION::RIGHT;
	}
	else
	{
		_StateAladdin = STATE::STAND;
	}


	if (CInput::GetInstance()->IsKeyDown(DIK_LEFT))
	{
		// translate background
		_PosBackGround_X -= 0.1 * dt;

		// set state Aladdin
		_StateAladdin = STATE::WALK;
		_DirectionAladdin = DIRECTION::LEFT;
	}

}

void CSceneOutSide::Render()
{
	// render background
	_SpriteBackground->Render(0, 0, (int)_PosBackGround_X, 420, 1024, 640, 2.4);
	//_SpriteBackground->Render(0, 0, 1.3);

	switch (_StateAladdin)
	{
	case  (STATE::WALK):
		_Aladdin->Activities(STATE::WALK, _DirectionAladdin);
		break;
	case  (STATE::STAND):
		_Aladdin->Activities(STATE::STAND, _DirectionAladdin);
		break;
	}

}

void CSceneOutSide::Destroy()
{
	_SpriteBackground->Release();

	_Aladdin->Release();
}

void CSceneOutSide::OnKeyDown(int KeyCode)
{
	/*switch (KeyCode)
	{
	case DIK_SPACE:
		_PosBackGround_X -= 10;
		break;
	}*/
}

void CSceneOutSide::OnKeyUP(int KeyCode)
{
	/*switch (KeyCode)
	{
	case DIK_LEFT:
		_PosBackGround_X += 10;
		break;
	}*/
}