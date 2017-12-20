#include "ScoreObject1.h"



ScoreObject1::ScoreObject1(int score) : ScoreObject(score)
{
	RECT rect;
	rect.left = 335;
	rect.right = 373;
	rect.top = 45;
	rect.bottom = 95;
	_sprite = new Sprite(ResourceManager::GetInstance()->GetTextureItems(), true, rect);
	_width = _sprite->GetWidth();
	_height = _sprite->GetHeight();
}


ScoreObject1::~ScoreObject1()
{
	delete _sprite;
}

void ScoreObject1::Draw(Camera * camera)
{
	if (_isVisible)
	{
		_sprite->SetPosition(_position);
		_sprite->Draw(camera);
	}
}
