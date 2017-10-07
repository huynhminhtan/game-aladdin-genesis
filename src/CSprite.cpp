#include "CSprite.h"
#include "trace.h"

#include <d3dx9.h>

CSprite::CSprite(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, int Width, int Height, int Count, int SpritePerRow)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	_Image = NULL;
	_SpriteHandler = SpriteHandler;

	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = SpritePerRow;
	_Index = 0;

	result = D3DXGetImageInfoFromFile(FilePath, &info);
	if (result != D3D_OK)
	{
		trace(L"[ERROR] Failed to get information from image file '%s'", FilePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv;
	SpriteHandler->GetDevice(&d3ddv);

	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		FilePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0),
		&info,
		NULL,
		&_Image);

	if (result != D3D_OK)
	{
		trace(L"[ERROR] Failed to create texture from file '%s'", FilePath);
		return;
	}
}

void CSprite::Render(int X, int Y)
{
	//this->Render(NULL, X, Y);


	// tạo 1 biến để (Cframe) lưu tọa độ frame

	RECT srect1;
	srect1.left = 10;
	srect1.top = 10;
	srect1.bottom = 100;
	srect1.right = 100;

	D3DXVECTOR3 position((float)X, (float)Y, 0);

	_SpriteHandler->Draw(
		_Image,
		&srect1,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}


void CSprite::Render(LPDIRECT3DSURFACE9 Target, int X, int Y)
{
	/*RECT srect;

	srect.left = (_Index % _SpritePerRow)*(_Width)+1;
	srect.top = (_Index / _SpritePerRow)*(_Height)+1;
	srect.right = srect.left + _Width;
	srect.bottom = srect.top + _Height + 1;
*/
	/*RECT srect1;
	srect1.left = 10;
	srect1.top = 10;
	srect1.bottom = 100;
	srect1.right = 100;
	
	D3DXVECTOR3 position((float)X, (float)Y, 0);

	_SpriteHandler->Draw(
		_Image,
		&srect1,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
	);*/
}


CSprite::~CSprite()
{
	_Image->Release();
}