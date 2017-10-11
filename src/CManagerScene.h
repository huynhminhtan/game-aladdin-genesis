#pragma once

#include "Header.h"

class CManagerScene
{
public:
	CManagerScene();
	~CManagerScene();

	void SetScenceCurrent(CScene*);
	void SetScenceNext(CScene*);
	void StartGame(CScene*);
	void StartGame(CScene*, LPDIRECT3DDEVICE9);

	void Render();
	void Update(float dt);

	// event key press
	void OnKeyDown(int);
	void OnKeyUp(int);

	static CManagerScene* GetInstance();

private:
	CScene*					_sceneCurrent;
	CScene*					_sceneNext;

	static CManagerScene*	_instance;
};