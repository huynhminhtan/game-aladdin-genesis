#include "CAladdinStand.h"

CAladdinStand::CAladdinStand()
{
}

CAladdinStand::~CAladdinStand()
{
	//delete _AspAladdin;
}

void CAladdinStand::Init()
{
	// init animation sprite
	_AspAladdin = new CAnimationSprite(Global::GetInstance()->GetDirectDevice());
	_AspAladdin->Init();
	// load sprite
	_AspAladdin->Load(SPRITE_TITLE_ALADDIN_STAND, SPRITE_TITLE_ALADDIN_STAND_XML, D3DCOLOR_XRGB(255, 0, 255));
}

void CAladdinStand::Release()
{
	_AspAladdin->Release();
}

void CAladdinStand::Activities(STATE state, DIRECTION direction)
{
	//
	// render animation sprite Aladdin
		_AspAladdin->Render(350, 450, 3, 15, direction);
}
