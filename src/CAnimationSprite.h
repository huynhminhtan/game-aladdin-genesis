#pragma once

#include "Header.h"

class CAnimationSprite
{
public:
	CAnimationSprite(LPDIRECT3DDEVICE9);
	~CAnimationSprite();

	bool Init();
	
	bool Load(LPWSTR, D3DCOLOR);

	// Render sprite (x,y,width,height) at location (X, Y) in backbuffer 
	void Render(float, float, int, int, int, int, float);
	// Render full sprite at location (X, Y) in backbuffer 
	void Render(float, float, float);

	void Release();

private:
	
	// texture store sprite sheet
	LPDIRECT3DTEXTURE9		_Texture;
	// handler to sprite sheet
	LPD3DXSPRITE			_SpriteHandler;
	// store device
	LPDIRECT3DDEVICE9		_d3ddv;
	// sotre infomation sprite sheet
	D3DXIMAGE_INFO			_Info;

};