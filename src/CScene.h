#pragma once
#include "Header.h"

class CScene 
{
public:
	virtual void Init(LPDIRECT3DDEVICE9) = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;

	virtual void OnKeyDown(int) = 0;
	virtual void OnKeyUP(int) = 0;
};
