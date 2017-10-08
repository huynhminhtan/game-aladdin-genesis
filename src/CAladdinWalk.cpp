#include "CAladdinWalk.h"

CAladdinWalk::CAladdinWalk()
{
}

CAladdinWalk::~CAladdinWalk()
{
}

void CAladdinWalk::Init()
{
	// init animation sprite
	_AspAladdin = new CAnimationSprite(Global::GetInstance()->GetDirectDevice());
	_AspAladdin->Init();
	// load sprite
	_AspAladdin->Load(SPRITE_TITLE_ALADDIN_WALK, SPRITE_TITLE_ALADDIN_WALK_XML, D3DCOLOR_XRGB(255, 0, 255));
}

void CAladdinWalk::Release()
{
	_AspAladdin->Release();
}

void CAladdinWalk::Activities(STATE state, DIRECTION direction)
{
	// render animation sprite Aladdin
	_AspAladdin->Render(350, 420, 2.6, 1, direction);
}
