#include "ResourceManager.h"
#include "../GameComponents/Sound.h"

ResourceManager* ResourceManager::_instance = NULL;

ResourceManager::ResourceManager()
{
	Graphics* graphics = Graphics::GetInstance();

	_animationXMLItemSpark = new tinyxml2::XMLDocument();
	_animationXMLItemSpark->LoadFile("Resources/Items/Item_spark.xml");


	_animationXMLEnemyDead = new tinyxml2::XMLDocument();
	_animationXMLEnemyDead->LoadFile("Resources/Enemies/Enemy_dead_e_f_2.xml");       ///////////////////

	_animationXMLEnemy3Dead = new tinyxml2::XMLDocument();
	_animationXMLEnemy3Dead->LoadFile("Resources/Enemies/enemy3_dead.xml");

	_animationXMLItemsRubby = new tinyxml2::XMLDocument();
	_animationXMLItemsRubby->LoadFile("Resources/Items/rubby_item.xml");

	_animationXMLPlayerClimbThrow = new tinyxml2::XMLDocument();
	_animationXMLPlayerClimbThrow->LoadFile("Resources/Aladdin/climb_throw_new.xml");

	_animationXMLClimbAttack = new tinyxml2::XMLDocument();
	_animationXMLClimbAttack->LoadFile("Resources/Aladdin/climb_attack_1.xml");

	_animationXMLSpringItem = new tinyxml2::XMLDocument();
	_animationXMLSpringItem->LoadFile("Resources/Items/spring_item.xml");

	_animationXMLAladdinUp = new tinyxml2::XMLDocument();
	_animationXMLAladdinUp->LoadFile("Resources/Aladdin/aladdin_up.xml");

	_animationXMLAladdin = new tinyxml2::XMLDocument();
	_animationXMLAladdin->LoadFile("Resources/Aladdin/Aladdin-Animations.xml");

	_animationXMLEnemy1 = new tinyxml2::XMLDocument();
	_animationXMLEnemy1->LoadFile("Resources/Enemies/Enemy-1-Animations.xml");

	_animationXMLEnemy2 = new tinyxml2::XMLDocument();
	_animationXMLEnemy2->LoadFile("Resources/Enemies/Enemy-2-Animations.xml");

	_animationXMLEnemy3 = new tinyxml2::XMLDocument();
	_animationXMLEnemy3->LoadFile("Resources/Enemies/Enemy-3-Animations.xml");

	_animationXMLEnemy4 = new tinyxml2::XMLDocument();
	_animationXMLEnemy4->LoadFile("Resources/Enemies/Enemy-4-Animations.xml");

	_animationXMLEnemy5 = new tinyxml2::XMLDocument();
	_animationXMLEnemy5->LoadFile("Resources/Enemies/Enemy-5-Animations.xml");

	_animationXMLEnemy6 = new tinyxml2::XMLDocument();
	_animationXMLEnemy6->LoadFile("Resources/Enemies/Enemy-6-Animations.xml");

	_animationXMLAppleWeapon = new tinyxml2::XMLDocument();
	_animationXMLAppleWeapon->LoadFile("Resources/Weapons/PlayerWeapons/AppleWeapon-Animation.xml");

	_animationXMLCamelWeapon = new tinyxml2::XMLDocument();
	_animationXMLCamelWeapon->LoadFile("Resources/Weapons/PlayerWeapons/CamelWeapon-Animation.xml");

	_animationXMLEnemy3Weapon = new tinyxml2::XMLDocument();
	_animationXMLEnemy3Weapon->LoadFile("Resources/Weapons/EnemiesWeapons/Enemy-3-Weapon-Animations.xml");

	_animationXMLEnemy6Weapon = new tinyxml2::XMLDocument();
	_animationXMLEnemy6Weapon->LoadFile("Resources/Weapons/EnemiesWeapons/Enemy-6-Weapon-Animations.xml");

	_animationXMLCamel = new tinyxml2::XMLDocument();
	_animationXMLCamel->LoadFile("Resources/Items/Camel-Animation.xml");

	_animationXMLCoalFire = new tinyxml2::XMLDocument();
	_animationXMLCoalFire->LoadFile("Resources/Items/CoalFire-Animation.xml");

	_animationXMLBottle = new tinyxml2::XMLDocument();
	_animationXMLBottle->LoadFile("Resources/Items/Bottle-Animations.xml");

	_animationXMLPlayerHealthMeter = new tinyxml2::XMLDocument();
	_animationXMLPlayerHealthMeter->LoadFile("Resources/Items/HealthMeter-Animation.xml");

	_textureAladdin = graphics->LoadTexture(L"Resources/Aladdin/Aladdin_Sprite.png", D3DCOLOR_XRGB(255, 0, 255));
	_textureItemSpark = graphics->LoadTexture(L"Resources/Items/item_spark_strip11_22_20.png", D3DCOLOR_XRGB(255, 0, 255));
	//////////////////////////////
	_textureEnemyDead = graphics->LoadTexture(L"Resources/Enemies/enemy_explosion_strip10_89_114_e_f_2.png", D3DCOLOR_XRGB(255, 0, 255));/////////////////
	_textureEnemy3Dead = graphics->LoadTexture(L"Resources/Enemies/guard_knife_hit_strip8_47_64.png", D3DCOLOR_XRGB(255, 0, 255));
	_textureAladdinUp = graphics->LoadTexture(L"Resources/Aladdin/aladdin_look_strip3_51_117.png", D3DCOLOR_XRGB(255, 0, 255));
	_textureAladdinUp = graphics->LoadTexture(L"Resources/Aladdin/aladdin_throw4_strip6_79_161.png", D3DCOLOR_XRGB(255, 0, 255));

	///////////////////////////////////
	_textureSpringItem = graphics->LoadTexture(L"Resources/Items/spring_strip10_1_33_r.png", D3DCOLOR_XRGB(255, 0, 255));
	_textureClimbAttack = graphics->LoadTexture(L"Resources/Aladdin/aladdin_attack4_strip7_83_185.png", D3DCOLOR_XRGB(255, 0, 255));

	_texturePlayerClimbThrow = graphics->LoadTexture(L"Resources/Aladdin/aladdin_throw4_strip6_79_161.png", D3DCOLOR_XRGB(255, 0, 255));

	_textureEnemies1 = graphics->LoadTexture(L"Resources/Enemies/Enemies_Sprite_1.png", D3DCOLOR_XRGB(120, 193, 152));
	_textureEnemies2 = graphics->LoadTexture(L"Resources/Enemies/Enemies_Sprite_2.png", D3DCOLOR_XRGB(120, 193, 152));
	_textureItems = graphics->LoadTexture(L"Resources/Items/Items.png", D3DCOLOR_XRGB(248, 0, 248));
	_textureCamel = graphics->LoadTexture(L"Resources/Items/Camel.png", D3DCOLOR_XRGB(248, 0, 248));
	_textureAgrabahMarket = graphics->LoadTexture(L"Resources/Maps/AgrabahMarket/AgrabahMarket.png");

	//man boss:
	_textureMapBoss = graphics->LoadTexture(L"Resources/Maps/JafarPlace/jafar.png");
	_textureMapBossBg = graphics->LoadTexture(L"Resources/Maps/JafarPlace/pillars.png");

	_animationXMLJafar = new tinyxml2::XMLDocument();
	_animationXMLJafar->LoadFile("Resources/Enemies/Jafar-Animations.xml");

	_animationXMLSnake = new tinyxml2::XMLDocument();
	_animationXMLSnake->LoadFile("Resources/Enemies/Snake-Animations.xml");

	_animationXMLExplosions = new tinyxml2::XMLDocument();
	_animationXMLExplosions->LoadFile("Resources/Enemies/Enemy-Explosions-Animations.xml");

	_animationXMLJafarWeapon1 = new tinyxml2::XMLDocument();
	_animationXMLJafarWeapon1->LoadFile("Resources/Weapons/EnemiesWeapons/Jafar-Weapon-1-Animation.xml");

	_animationXMLJafarWeapon2 = new tinyxml2::XMLDocument();
	_animationXMLJafarWeapon2->LoadFile("Resources/Weapons/EnemiesWeapons/Jafar-Weapon-2-Animation.xml");

	_textureBossJafar = graphics->LoadTexture(L"Resources/Enemies/Boss_Sprite.png", D3DCOLOR_XRGB(186, 254, 202));
	_textureExplosions = graphics->LoadTexture(L"Resources/Enemies/Enemy_Explosions_Sprite.png", D3DCOLOR_XRGB(186, 254, 202));

	Sound::GetInstance()->LoadSound("Resources/Sounds/Apple_Splat.wav", "Apple_Splat");
	Sound::GetInstance()->LoadSound("Resources/Sounds/Apple_Collect.wav", "Apple_Collect");
	Sound::GetInstance()->LoadSound("Resources/Sounds/Camel_Spit.wav", "Camel_Spit");
	Sound::GetInstance()->LoadSound("Resources/Sounds/Clay_Pot.wav", "Clay_Pot");//noi dat rot
	Sound::GetInstance()->LoadSound("Resources/Sounds/Low_Sword.wav", "Low_Sword");//Aladin attack

	Sound::GetInstance()->LoadSound("Resources/Sounds/Aladdin_Hurt.wav", "Aladdin_Hurt");

	Sound::GetInstance()->LoadSound("Resources/Sounds/Jafar_Snake.wav", "Jafar_Snake");//Jafar chuyen dang Snake
	Sound::GetInstance()->LoadSound("Resources/Sounds/Jafar_Laugh.wav", "Jafar_Laugh");

	Sound::GetInstance()->LoadSound("Resources/Sounds/PrinceAli.wav", "PrinceAli");
	Sound::GetInstance()->LoadSound("Resources/Sounds/BossTune.wav", "BossTune");
	Sound::GetInstance()->LoadSound("Resources/Sounds/LevelComplete.wav", "LevelComplete");
	Sound::GetInstance()->LoadSound("Resources/Sounds/MenuSelect_Background.wav", "MenuSelect_Background");
	Sound::GetInstance()->LoadSound("Resources/Sounds/MenuSelect_SelectChange.wav", "MenuSelect_SelectChange");
	Sound::GetInstance()->LoadSound("Resources/Sounds/MenuSelect_Selected.wav", "MenuSelect_Selected");
}


ResourceManager::~ResourceManager()
{
	delete _animationXMLAladdin;
	delete _animationXMLItemSpark;
	delete _animationXMLEnemyDead;       /////////////////////////////
	delete _animationXMLEnemy3Dead;
	delete _animationXMLItemsRubby;
	delete _animationXMLSpringItem;
	delete _animationXMLAladdinUp;
	delete _animationXMLEnemy1;
	delete _animationXMLEnemy2;
	delete _animationXMLEnemy3;
	delete _animationXMLEnemy4;
	delete _animationXMLEnemy5;
	delete _animationXMLClimbAttack;
	delete _animationXMLEnemy6;
	delete _animationXMLAppleWeapon;
	delete _animationXMLCamelWeapon;
	delete _animationXMLEnemy3Weapon;
	delete _animationXMLEnemy6Weapon;
	delete _animationXMLPlayerHealthMeter;
	delete _animationXMLCamel;
	delete _animationXMLCoalFire;

	_textureAladdin->Release();
	_textureItemSpark->Release();
	_textureEnemyDead->Release();      ///////////////////////////
	_textureEnemy3Dead->Release();
	_textureSpringItem->Release();
	_textureAladdinUp->Release();
	_textureEnemies1->Release();
	_textureClimbAttack->Release();
	_textureEnemies2->Release();
	_textureItems->Release();
	_textureCamel->Release();
	_textureAgrabahMarket->Release();

	//man boss:
	delete _animationXMLJafar;
	delete _animationXMLSnake;
	delete _animationXMLJafarWeapon1;
	delete _animationXMLJafarWeapon2;
	delete _animationXMLExplosions;

	_textureBossJafar->Release();
	_textureExplosions->Release();
	_textureMapBoss->Release();
	_textureMapBossBg->Release();
}


ResourceManager* ResourceManager::GetInstance()
{
	if (!_instance)
		_instance = new ResourceManager();
	return _instance;
}

tinyxml2::XMLDocument* ResourceManager::GetAnimationXMLAladdin()
{
	return _animationXMLAladdin;
}

tinyxml2::XMLDocument* ResourceManager::GetAnimationXMLItemSpark()
{
	return _animationXMLItemSpark;
}

tinyxml2::XMLDocument* ResourceManager::GetAnimationXMLEnemyDead()         /////////////
{
	return _animationXMLEnemyDead;
}

tinyxml2::XMLDocument* ResourceManager::GetAnimationXMLClimbAttack()         /////////////
{
	return _animationXMLClimbAttack;
}

tinyxml2::XMLDocument* ResourceManager::GetAnimationXMLSpringItem()         
{
	return _animationXMLSpringItem;
}

tinyxml2::XMLDocument* ResourceManager::GetAnimationXMLAladdinUp()         
{
	return _animationXMLAladdinUp;
}

tinyxml2::XMLDocument* ResourceManager::GetAnimationXMLEnemy3Dead()       
{
	return _animationXMLEnemy3Dead;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLItemsRubby()
{
	return _animationXMLItemsRubby;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLPlayerClimbThrow()
{
	return _animationXMLPlayerClimbThrow;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLEnemy1()
{
	return _animationXMLEnemy1;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLEnemy2()
{
	return _animationXMLEnemy2;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLEnemy3()
{
	return _animationXMLEnemy3;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLEnemy4()
{
	return _animationXMLEnemy4;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLEnemy5()
{
	return _animationXMLEnemy5;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLEnemy6()
{
	return _animationXMLEnemy6;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLAppleWeapon()
{
	return _animationXMLAppleWeapon;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLCamelWeapon()
{
	return _animationXMLCamelWeapon;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLEnemy3Weapon()
{
	return _animationXMLEnemy3Weapon;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLEnemy6Weapon()
{
	return _animationXMLEnemy6Weapon;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLPlayerHealthMeter()
{
	return _animationXMLPlayerHealthMeter;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLCamel()
{
	return _animationXMLCamel;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLCoalFire()
{
	return _animationXMLCoalFire;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLBottle()
{
	return _animationXMLBottle;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLJafar()
{
	return _animationXMLJafar;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLSnake()
{
	return _animationXMLSnake;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLExplosions()
{
	return _animationXMLExplosions;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLJafarWeapon1()
{
	return _animationXMLJafarWeapon1;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLJafarWeapon2()
{
	return _animationXMLJafarWeapon2;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureAladdin()
{
	return _textureAladdin;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureItemSpark()
{
	return _textureItemSpark;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureEnemyDead()
{
	return _textureEnemyDead;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureEnemy3Dead()
{
	return _textureEnemy3Dead;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTexturePlayerClimbThrow()
{
	return _texturePlayerClimbThrow;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureAladdinUp() ////////////////
{
	return _textureAladdinUp;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureSpringItem() ////////////////
{
	return _textureSpringItem;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureClimbAttack() ////////////////
{
	return _textureClimbAttack;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureEnemies1()
{
	return _textureEnemies1;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureEnemies2()
{
	return _textureEnemies2;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureItems()
{
	return _textureItems;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureCamel()
{
	return _textureCamel;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureAgrabahMarket()
{
	return _textureAgrabahMarket;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureExplosions()
{
	return _textureExplosions;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureBossJafar()
{
	return _textureBossJafar;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureMapBoss()
{
	return _textureMapBoss;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureMapBossBg()
{
	return _textureMapBossBg;
}
