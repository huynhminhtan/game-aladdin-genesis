#include "CSceneOutside.h"

CSceneOutSide::CSceneOutSide()
{
	_PosBackGround_X = 0;
	_AspAladdin = nullptr;
	_SpriteBackground = nullptr;
	//_SpriteHandler

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

	// init animation sprite
	_AspAladdin = new CAnimationSprite(d3ddv);
	_AspAladdin->Init();
	// load sprite
	_AspAladdin->Load(SPRITE_TITLE_ALADDIN, SPRITE_TITLE_ALADDIN_XML, D3DCOLOR_XRGB(255, 0, 255));
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
	_SpriteBackground->Render(0, 0, (int)_PosBackGround_X, 190, 1024, 640, 1.3);
	//_SpriteBackground->Render(0, 0, 1.3);

	// render animation sprite Aladdin
	_AspAladdin->Render(100, 450, 3);
	
}

void CSceneOutSide::Destroy()
{
	_SpriteBackground->Release();
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