#include "MainScene.h"
#include "../GameComponents/Sound.h"

MainScene::MainScene() :Scene(0x9090b0)
{
	LoadContent();
}

MainScene::~MainScene()
{
	for (size_t i = 0; i < _backgroundTextures.size(); i++)
	{
		delete _backgroundTextures[i];
		_backgroundTextures[i] = NULL;
	}
	_backgroundTextures.clear();

	delete _spriteCountApple;
	_spriteCountApple = NULL;


	delete _spriteCountRubby;
	_spriteCountRubby = NULL;

	delete _txtCountApple;
	_txtCountApple = NULL;

	delete _txtCountRubby;
	_txtCountRubby = NULL;

	delete _spriteTimesPlay;
	_spriteTimesPlay = NULL;

	delete _txtTimesPlay;
	_txtTimesPlay = NULL;

	delete _txtScore;
	_txtScore = NULL;

	delete _playerHealthMeter;
	_playerHealthMeter = NULL;

}

void MainScene::LoadContent()
{
	Sprite *sprite;
	RECT sourceRect;

	sourceRect.left = 0;
	sourceRect.right = 4773;
	sourceRect.top = 0;
	sourceRect.bottom = 689;

	sprite = new Sprite(ResourceManager::GetInstance()->GetTextureAgrabahMarket(), true, sourceRect);
	sprite->SetPosition(sprite->GetWidth() / 2.0f, sprite->GetHeight() / 2.0f);
	_backgroundTextures.push_back(sprite);

	//sourceRect.top = 689;
	//sourceRect.bottom = 1378;
	sourceRect.top = 689;
	sourceRect.bottom = 1378;
	sprite = new Sprite(ResourceManager::GetInstance()->GetTextureAgrabahMarket(), true, sourceRect);
	sprite->SetPosition(sprite->GetWidth() / 2.0f, sprite->GetHeight() / 2.0f);
	_backgroundTextures.push_back(sprite);

	_gameMap = new GameMap("Resources/Maps/AgrabahMarket/AgrabahMarket.tmx", _quadTree);

	_camera = new Camera(_gameMap->GetPlayer());

	//apple weapon counter
	RECT appleSourceRect;
	appleSourceRect.left = 341;
	appleSourceRect.right = 352;
	appleSourceRect.top = 17;
	appleSourceRect.bottom = 29;
	_spriteCountApple = new Sprite(ResourceManager::GetInstance()->GetTextureItems(), true, appleSourceRect);
	_spriteCountApple->SetScale(D3DXVECTOR2(2, 2));
	_txtCountApple = new Text(L"0", 15, 15, FW_BOLD);

	RECT rubbySourceRect;
	rubbySourceRect.left = 340;
	rubbySourceRect.right = 357;
	rubbySourceRect.top = 111;
	rubbySourceRect.bottom = 127;

	_spriteCountRubby = new Sprite(ResourceManager::GetInstance()->GetTextureItems(), true, rubbySourceRect);
	_spriteCountRubby->SetScale(D3DXVECTOR2(2, 2));
	_txtCountRubby = new Text(L"0", 15, 15, FW_BOLD);

	//times play counter
	RECT temp;
	temp.left = 367;
	temp.right = 391;
	temp.top = 140;
	temp.bottom = 165;
	_spriteTimesPlay = new Sprite(ResourceManager::GetInstance()->GetTextureItems(), true, temp);
	_spriteTimesPlay->SetScale(D3DXVECTOR2(2, 2));
	_txtTimesPlay = new Text(L"0", 15, 15, FW_BOLD);

	//score
	_txtScore = new Text(L"0", 25, 25, FW_BOLD);

	_playerHealthMeter = new PlayerHealthMeter();

	// hurt
	_hurtApple = 0;
	_hurtHealth = 0;
}

void MainScene::Update(float dt)
{
	Scene::Update(dt);

	// check hurt
	if (_hurtApple > 0)
		_hurtApple = max(--_hurtApple, 0);

	if (_gameMap->GetPlayer()->GetNumAppleWeapon() <= HURT_APPLE)
	{
		if (_hurtApple == 0)
			_hurtApple = 100;
	}

	// check hurt
	if (_hurtHealth > 0)
		_hurtHealth = max(--_hurtHealth, 0);

	if (_gameMap->GetPlayer()->GetHealth() <= HURT_HEALTH)
	{
		if (_hurtHealth == 0)
			_hurtHealth = 100;
	}

	//check if move to next scene
	if ((int)_gameMap != 0xDDDDDDDD)
	{
		_txtCountApple->SetString(_gameMap->GetPlayer()->GetNumAppleWeapon());
		_txtCountRubby->SetString(_gameMap->GetPlayer()->GetNumRubby());
		_txtTimesPlay->SetString(Player::GetTimesPlay());
		_txtScore->SetString(Player::GetScore());
		/*	if (_gameMap->GetPlayer()->GetVelocity().y == 0)
				_txtScore->SetString(_gameMap->GetPlayer()->GetVelocity().y);*/

		_txtScore->SetString(_gameMap->GetPlayer()->AXA());

		char buffer[100];
		sprintf_s(buffer, " %d \n", _gameMap->GetPlayer()->GetHealth());
		OutputDebugStringA(buffer);

		_playerHealthMeter->ChangeAnimation(_gameMap->GetPlayer()->GetHealth());
		_playerHealthMeter->Update(dt);
	}
}

void MainScene::Draw()
{
	_backgroundTextures[0]->Draw(_camera);
	Scene::Draw();
	_backgroundTextures[1]->Draw(_camera);


	// draw apple
	if ((_hurtApple / 5) % 4 == 0)
	{
		_spriteCountApple->Draw(D3DXVECTOR3(Graphics::GetInstance()->GetScreenWidth() - 80, Graphics::GetInstance()->GetScreenHeight() - 50, 0));
		_txtCountApple->Draw(D3DXVECTOR2(Graphics::GetInstance()->GetScreenWidth() - 50, Graphics::GetInstance()->GetScreenHeight() - 50));
	}

	// draw rubby
	if (_gameMap->GetPlayer()->GetNumRubby() > 0)
	{
		_spriteCountRubby->Draw(D3DXVECTOR3(Graphics::GetInstance()->GetScreenWidth() - 180, Graphics::GetInstance()->GetScreenHeight() - 50, 0));
		_txtCountRubby->Draw(D3DXVECTOR2(Graphics::GetInstance()->GetScreenWidth() - 150, Graphics::GetInstance()->GetScreenHeight() - 50));
	}

	_spriteTimesPlay->Draw(D3DXVECTOR3(50, Graphics::GetInstance()->GetScreenHeight() - 50, 0));
	_txtTimesPlay->Draw(D3DXVECTOR2(90, Graphics::GetInstance()->GetScreenHeight() - 50));

	_txtScore->Draw(D3DXVECTOR2(Graphics::GetInstance()->GetScreenWidth() - 250, 50));

	if ((_hurtHealth / 5) % 4 == 0)
	{
		_playerHealthMeter->Draw(D3DXVECTOR3(_playerHealthMeter->GetWidth() / 2 + 10, _playerHealthMeter->GetHeight() / 2 + 10, 0));
	}
}
