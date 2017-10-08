#pragma once

#include "Header.h"

class CTile
{
public:
	CTile();
	~CTile();

	void SetTile(const char* Name, int X, int Y, int Width, int Height);
	CTile GetTile();

	RECT GETLocaTionTile();

private:
	RECT		_RectTile;
	const char*	_NameTile;
};


class CAnimationSprite
{
public:
	CAnimationSprite(LPDIRECT3DDEVICE9);
	~CAnimationSprite();

	bool Init();

	bool Load(LPWSTR ImagePath, D3DCOLOR Transcolor);
	bool Load(LPWSTR ImagePath, const char* XMLPath, D3DCOLOR Transcolor);

	// Render sprite (x,y,width,height) at location (X, Y) in backbuffer 
	void Render(float, float, int, int, int, int, float);
	// Render full sprite at location (X, Y) in backbuffer
	// X; Y; Scale; AnimationRate; Direction
	void Render(float sX, float Y, float Scale, int AnamationRate, DIRECTION direction);

	void Release();

	void ReadXML(const char* XMLPath);

private:

	list<CTile>				_ListTile;

	int						_IndexTile;

	int						_AnimationRate_Index;

	// texture store sprite sheet
	LPDIRECT3DTEXTURE9		_Texture;
	// handler to sprite sheet
	LPD3DXSPRITE			_SpriteHandler;
	// store device
	LPDIRECT3DDEVICE9		_d3ddv;
	// sotre infomation sprite sheet
	D3DXIMAGE_INFO			_Info;

	
};

