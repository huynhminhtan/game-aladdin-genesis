#include "Apple.h"

Apple::Apple():GameObject(GameObject::GameObjectType::Apple, false)
{
	_entryVisible = false;

	RECT appleSourceRect;
	appleSourceRect.left = 341;
	appleSourceRect.right = 352;
	appleSourceRect.top = 17;
	appleSourceRect.bottom = 29;

	_appleSprite = new Sprite(ResourceManager::GetInstance()->GetTextureItems(), true, appleSourceRect);
	_width = _appleSprite->GetWidth();
	_height = _appleSprite->GetHeight();

	_animationSprite = new Animation(ResourceManager::GetInstance()->GetAnimationXMLItemSpark(), "item_spark", ResourceManager::GetInstance()->GetTextureItemSpark(), true, 0.8f);
	//_animationSprite->SetScale(D3DXVECTOR2(1.5f, 1.5f));
}


Apple::~Apple()
{
	delete _appleSprite;
	delete _animationSprite;
}

void Apple::Update(float dt)
{
	GameObject::Update(dt);

	_animationSprite->Update(dt);
}

void Apple::Draw(Camera * camera)
{
	//if (_isVisible)
	//{
	//	_appleSprite->SetPosition(_position);
	//	_appleSprite->Draw(camera);

	//	/*_animationSprite->SetPosition(_position);
	//	_animationSprite->Draw(camera);*/
	//}
	//else
	//{
	//	_animationSprite->SetPosition(_position);
	//	_animationSprite->Draw(camera);
	//}

	if (_entryVisible)
	{
		_animationSprite->SetPosition(_position);
		_animationSprite->Draw(camera);
		if (_animationSprite->IsFinish())
		{
			_isVisible = false;
		}
	}else
	{
		_appleSprite->SetPosition(_position);
		_appleSprite->Draw(camera);
	}
}

void Apple::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	if (target->GetTag() == GameObjectType::Players)
	{
	//	_isVisible = false;
		_entryVisible = true;
	}
}
