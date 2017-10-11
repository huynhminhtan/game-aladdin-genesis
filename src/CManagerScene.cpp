#include "CManagerScene.h"

CManagerScene* CManagerScene::_instance = nullptr;

CManagerScene::CManagerScene()
{
}

CManagerScene::~CManagerScene()
{
}

void CManagerScene::SetScenceCurrent(CScene *scene)
{
	_sceneCurrent = scene;
}

void CManagerScene::SetScenceNext(CScene *scene)
{
	_sceneNext = scene;
}

void CManagerScene::StartGame(CScene *scene)
{
	/*_sceneCurrent = scene;
	_sceneCurrent->Init();

	_sceneNext = nullptr;*/
}

void CManagerScene::StartGame(CScene *scene, LPDIRECT3DDEVICE9 d3ddv)
{
	_sceneCurrent = scene;
	_sceneCurrent->Init(d3ddv);

	_sceneNext = nullptr;
}

void CManagerScene::Render()
{
	_sceneCurrent->Render();
}

void CManagerScene::Update(float dt)
{
	_sceneCurrent->Update(dt);
}

void CManagerScene::OnKeyDown(int KeyCode)
{
	_sceneCurrent->OnKeyDown(KeyCode);
}

void CManagerScene::OnKeyUp(int KeyCode)
{
	_sceneCurrent->OnKeyUp(KeyCode);
}

CManagerScene* CManagerScene::GetInstance()
{
	if (_instance == nullptr)
		_instance = new CManagerScene();

	return _instance;
}



