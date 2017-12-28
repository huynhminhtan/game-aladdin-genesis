#include "CompleteScene.h"
#include "../GameComponents/Graphics.h"
#include "../GameComponents/Sound.h"

CompleteScene::CompleteScene() :Scene(0x000000, Scene::SceneName::CompleteScene)
{
	LoadContent();
}

CompleteScene::~CompleteScene()
{
	delete _title;
	_title = NULL;

	delete _animationAladdin;
	_animationAladdin = NULL;

	delete _animationMonkey;
	_animationMonkey = NULL;
}

void CompleteScene::LoadContent()
{
	_camera = new Camera(NULL);

	_title = new Text(L"Mission Complete", 40, 50, FW_BOLD);

	_animationAladdin = new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Win", ResourceManager::GetInstance()->GetTextureAladdin(), true, 1.5f);

	_animationMonkey = new Animation(ResourceManager::GetInstance()->GetAnimationXMLMonkey(), "Win", ResourceManager::GetInstance()->GetTextureMonkey(), true, 1.5f);

	_animationAladdin->SetPosition(Graphics::GetInstance()->GetScreenWidth() - 100, Graphics::GetInstance()->GetScreenHeight() / 2);
	_animationMonkey->SetPosition(Graphics::GetInstance()->GetScreenWidth() - 50 - 100, Graphics::GetInstance()->GetScreenHeight() / 2);

	RECT sourceRect;

	sourceRect.left = 0;
	sourceRect.right = 320;
	sourceRect.top = 0;
	sourceRect.bottom = 256;

	_bg = new Sprite(ResourceManager::GetInstance()->GetTextureSelect(), true, sourceRect);
	_bg->SetPosition(Graphics::GetInstance()->GetScreenWidth()/2 -165, Graphics::GetInstance()->GetScreenHeight() / 2 + 100);

	Sound::GetInstance()->Play("LevelComplete", false, 1);

}

void CompleteScene::Update(float deltatime)
{
	//Scene::Update(deltatime);

	D3DXVECTOR2 _positonAladin = _animationAladdin->GetPosition();
	D3DXVECTOR2 _positonMonkey = _animationMonkey->GetPosition();

	_animationAladdin->SetPosition(_positonAladin.x - 30 * deltatime, Graphics::GetInstance()->GetScreenHeight() / 2 + 180);
	_animationMonkey->SetPosition(_positonMonkey.x - 30 * deltatime, Graphics::GetInstance()->GetScreenHeight() / 2 + 180);

	_animationAladdin->Update(deltatime);
	_animationMonkey->Update(deltatime);
}

void CompleteScene::Draw()
{
	//Scene::Draw();
	_bg->Draw(_camera);
	//_title->Draw(D3DXVECTOR2(Graphics::GetInstance()->GetScreenWidth() / 2 - 300, 50));
	_animationAladdin->Draw(_camera);
	_animationMonkey->Draw(_camera);
}
