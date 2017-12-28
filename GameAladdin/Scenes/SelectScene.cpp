#include "SelectScene.h"
#include "../GameComponents/Graphics.h"
#include "../GameComponents/Sound.h"

SelectScene::SelectScene() :Scene(0x000000, Scene::SceneName::SelectScene)
{
	LoadContent();
}

SelectScene::~SelectScene()
{
	delete _title;
	_title = NULL;

	delete _animationAladdin;
	_animationAladdin = NULL;

	delete _animationMonkey;
	_animationMonkey = NULL;
}

void SelectScene::LoadContent()
{
	Select = 0;
	State = 0;
	Fade = 255;


	_camera = new Camera(NULL);

	_title = new Text(L"ABRABAH MARKET", 20, 20, FW_BOLD);
	List.push_back(_title);
	_title = new Text(L"JAFAR FIGHT", 20, 20, FW_BOLD);
	List.push_back(_title);
	_title = new Text(L"EXIT", 20, 20, FW_BOLD);
	List.push_back(_title);

	/*List.push_back("ABRABAH MARKET");
	List.push_back("JAFAR FIGHT");
	List.push_back("EXIT");*/


	RECT sourceRect;

	sourceRect.left = 0;
	sourceRect.right = 320;
	sourceRect.top = 0;
	sourceRect.bottom = 256;

	_bg = new Sprite(ResourceManager::GetInstance()->GetTextureSelect(), true, sourceRect);
	_bg->SetPosition(Graphics::GetInstance()->GetScreenWidth() / 2 - 160, Graphics::GetInstance()->GetScreenHeight() / 2 + 100);

	sourceRect.left = 0;
	sourceRect.right = 32;
	sourceRect.top = 0;
	sourceRect.bottom = 11;

	_bg2 = new Sprite(ResourceManager::GetInstance()->GetTextureSelectKni(), true, sourceRect);
	_bg2->SetPosition(Graphics::GetInstance()->GetScreenWidth() / 2 + 10, Graphics::GetInstance()->GetScreenHeight() / 2 - 100);
	//Sound::GetInstance()->Play("LevelComplete", false, 1);

}

void SelectScene::Update(float deltatime)
{
	//Scene::Update(deltatime);

	bool Up = Input::GetInstance()->IsKeyPressed(DIK_UP);
	bool Down = Input::GetInstance()->IsKeyPressed(DIK_DOWN);
	bool Enter = Input::GetInstance()->IsKeyPressed(DIK_RETURN);

	switch (State)
	{
	case 0:
		if (Enter)
		{
			//Resource->PlaySound("Audio/MenuChange.wav", 0);
			State = 1;
		}
		else if (Down)
		{
			int max = List.size() - 1;
			if (++Select > max)
				Select = max;
			//	else
					//Resource->PlaySound("Audio/MenuSelect.wav", 0);
		}
		else if (Up)
		{
			if (--Select < 0)
				Select = 0;
			//else
				//Resource->PlaySound("Audio/MenuSelect.wav", 0);
		}
		break;

	case 1:
		if (Fade > 1)
			Fade *= 0.6f;
		else
			switch (Select)
			{
			/*case 2:
				PostMessage(0, WM_QUIT, 0, 0);
				break;*/

			case 0:
				//Next = MARKET;
				SceneManager::GetInstance()->ReplaceScene(new MainScene());
				break;

			case 2:
				//Next = PALACE;
				SceneManager::GetInstance()->ReplaceScene(new JafarScene());
				break;
			}
		break;
	}

	//_bg2->SetPosition(Graphics::GetInstance()->GetScreenWidth() / 4 - 100, Graphics::GetInstance()->GetScreenHeight() / 2 + 100);
}

void SelectScene::Draw()
{
	//Scene::Draw();
	_bg->Draw(_camera);
	_bg2->Draw(_camera);

	float x = 48;
	float y = Graphics::GetInstance()->GetScreenHeight() / 2 + 100;

	for (unsigned i = 0; i < List.size(); ++i)
	{
		//Text(Resource, List[i], x, y + 20 * i);
		if (i == Select)
		{
			_bg2->SetPosition(x - 5 - abs(sin((float)GetTickCount() / 125) * 10), y + 15 * i);
			_bg2->Draw(_camera);
		}

		//char buffer[100];
		//sprintf_s(buffer, " %d \n", i);
		//OutputDebugStringA(buffer);
	}

	y -= 125;
	x += 100;

	List[0]->Draw(D3DXVECTOR2(x, y));
	List[1]->Draw(D3DXVECTOR2(x, y + 65));

	/*CGameLevel::Draw();
	if (State == 1 && Fade > 0)
	{
		LPD3DXLINE line;
		D3DXCreateLine(Resource->getDevice(), &line);
		D3DXVECTOR2 lines[] = { D3DXVECTOR2(0, BUFFER_HEIGHT / 2),
			D3DXVECTOR2(BUFFER_WIDTH, BUFFER_HEIGHT / 2) };
		line->SetWidth(BUFFER_HEIGHT);
		line->Begin();
		line->Draw(lines, 2, D3DCOLOR_ARGB(255 - (int)Fade, 0, 0, 0));
		line->End();
		line->Release();
	}*/

	//_title->Draw(D3DXVECTOR2(Graphics::GetInstance()->GetScreenWidth() / 2 - 300, 50));
	//_animationAladdin->Draw(_camera);
	//_animationMonkey->Draw(_camera);


}
