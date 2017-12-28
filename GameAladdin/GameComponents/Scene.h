#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "QuadTree.h"
#include "GameMap.h"

class Scene
{


public:
	enum SceneName
	{
		None,
		Jafar,
		Market
	};

	Scene(D3DCOLOR backgroundColor = 0x000000, Scene::SceneName name = None);
	virtual ~Scene();

	D3DCOLOR GetBackcolor();
	QuadTree* GetQuadTree();

	Camera* GetCamera();
	void SetCamera(Camera* camera);

	GameMap* GetGameMap();

	void AddGameObjectToWeaponList(GameObject*gameObject);

	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void LoadContent() {};

	Scene::SceneName GetSceneName();

protected:
	D3DCOLOR _backgroundColor;
	QuadTree* _quadTree;

	Camera* _camera;
	GameMap* _gameMap;

	/*
	list gameObject phát sinh trong game. Vd: AppleWeapon
	thêm vào list đê gọi hàm Update
	*/
	std::vector<GameObject*> _listWeapon;

	Scene::SceneName _name;
};

