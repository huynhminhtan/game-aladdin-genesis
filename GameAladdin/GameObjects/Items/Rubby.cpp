#include "Rubby.h"

Rubby::Rubby() :GameObject(GameObject::GameObjectType::Rubby, false)
{
	_entryVisible = false;

	RECT rubbySourceRect;
	rubbySourceRect.left = 340;
	rubbySourceRect.right = 357;
	rubbySourceRect.top = 111;
	rubbySourceRect.bottom = 127;

	//_appleSprite = new Sprite(ResourceManager::GetInstance()->GetTextureItems(), true, rubbySourceRect);
	//_width = _appleSprite->GetWidth();
	//_height = _appleSprite->GetHeight();

	_animationSprite = new Animation(ResourceManager::GetInstance()->GetAnimationXMLItemSpark(), "item_spark", ResourceManager::GetInstance()->GetTextureItemSpark(), true, 0.8f);
	//_animationSprite->SetScale(D3DXVECTOR2(1.5f, 1.5f));

	_animationRubby = new Animation(ResourceManager::GetInstance()->GetAnimationXMLItemsRubby(), "rubby", ResourceManager::GetInstance()->GetTextureItems(), true, 0.8f);
	_width = _animationRubby->GetWidth();
	_height = _animationRubby->GetHeight();
}



Rubby::~Rubby()
{
	delete _appleSprite;
	delete _animationSprite, _animationRubby;
}

void Rubby::Update(float dt)
{
	GameObject::Update(dt);

	_animationRubby->Update(dt);
	_animationSprite->Update(dt);
}

void Rubby::Draw(Camera * camera)
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
	}
	else
	{
	/*	_appleSprite->SetPosition(_position);
		_appleSprite->Draw(camera);*/

		_animationRubby->SetPosition(_position);
		_animationRubby->Draw(camera);
	}
}

void Rubby::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	if (target->GetTag() == GameObjectType::Players)
	{
		//	_isVisible = false;
		_entryVisible = true;
	}
}
