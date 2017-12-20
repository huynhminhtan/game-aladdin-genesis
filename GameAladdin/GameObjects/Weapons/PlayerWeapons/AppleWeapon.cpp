#include "AppleWeapon.h"
#include "../../../GameComponents/Sound.h"

AppleWeapon::AppleWeapon(int damage):Weapon(Weapon::WeaponType::PlayerWeapons, damage)
{
	_animationFly = new Animation(ResourceManager::GetInstance()->GetAnimationXMLAppleWeapon(), "Fly", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.5f);
	_animationExplode = new Animation(ResourceManager::GetInstance()->GetAnimationXMLAppleWeapon(), "Explode", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.4f);

	_animation = _animationFly;
	_width = _animation->GetWidth();
	_height = _animation->GetHeight();

	_velocity.x = 50;//left or right
	_velocity.y = -20;

	_mass = 10;
	_acceleration.y = _mass;
}


AppleWeapon::~AppleWeapon()
{
	delete _animationFly;
	delete _animationExplode;
}

void AppleWeapon::Update(float deltaTime)
{
	Weapon::Update(deltaTime);

	if (_animation->IsFinish() && _animation == _animationExplode)
	{
		_isVisible = false;
	}
}

void AppleWeapon::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	//prevent collision with EnemiesWeapons
	if (target->GetTag() == GameObjectType::Weapons)
	{
		Weapon* weapon = dynamic_cast<Weapon*>(target);
		if (weapon->GetWeaponType() == Weapon::WeaponType::EnemiesWeapons)
			return;
	}

	if (target->GetTag() != GameObjectType::Players
		&& target->GetTag() != GameObject::GameObjectType::Apple
		&& _animation == _animationFly)
	{
		_animation = _animationExplode;
		_width = _animation->GetWidth();
		_height = _animation->GetHeight();

		_acceleration.y = 0;
		_velocity.x = _velocity.y = 0;

		Sound::GetInstance()->Play("Apple_Splat", false, 1);
	}
}
