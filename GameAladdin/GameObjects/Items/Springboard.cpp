#include "Springboard.h"

Springboard::Springboard() : GameObject(GameObject::GameObjectType::Springboard, false)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLSpringItem(), "spring", ResourceManager::GetInstance()->GetTextureSpringItem(), true, 0.3f);

	_width = _animation->GetWidth();
	_height = _animation->GetHeight();
	_animation->Pause();
}


Springboard::~Springboard()
{
	if (_animation)
	{
		delete _animation;
		_animation = NULL;
	}
}

void Springboard::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	_animation->SetPosition(_position);
	_animation->Update(deltaTime);
	SetPosition(_animation->GetPosition());

	_width = _animation->GetWidth();
	_height = _animation->GetHeight();

	//reset _isCreatedWeapon

	if (_animation->IsFinish())
	{
		_animation->Pause();
	}
}


void Springboard::Draw(Camera * camera)
{
	_animation->Draw(camera);
}


void Springboard::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	if (target->GetTag() == GameObject::GameObjectType::Players
		&& (side == GameCollision::SideCollisions::Top
			|| side == GameCollision::SideCollisions::TopLeft
			|| side == GameCollision::SideCollisions::TopRight))
	{
		_animation->SetCurrentIndex(1);
		_animation->Play();
	}
}