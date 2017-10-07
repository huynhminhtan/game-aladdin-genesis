#include "CAnimationSprite.h"

CAnimationSprite::CAnimationSprite(LPDIRECT3DDEVICE9 d3ddv)
{
	_Texture = nullptr;
	_SpriteHandler = nullptr;
	_d3ddv = d3ddv;
	//_info
}

CAnimationSprite::~CAnimationSprite()
{
}

bool CAnimationSprite::Init()
{
	// sprite handler associate main Direct3D and Device that how to draw sprite at backbuffer
	HRESULT res = D3DXCreateSprite(_d3ddv, &_SpriteHandler);

	if (res != D3D_OK)
	{
		trace(L"[ERROR] Link device vs handler.");
		return false;
	}

	return true;
}

bool CAnimationSprite::Load(LPWSTR FilePath, D3DCOLOR Transcolor)
{
	// get infomation (widht, height) sprite sheet
	HRESULT result = D3DXGetImageInfoFromFile(FilePath, &_Info);
	
	if (result != D3D_OK)
	{
		trace(L"[ERROR] Failed to get information from image file '%s'", FilePath);
		return false;
	}

	// create texture from sprite sheet
	result = D3DXCreateTextureFromFileEx(
		_d3ddv,
		FilePath,
		_Info.Width,
		_Info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		Transcolor,
		&_Info,
		NULL,
		&_Texture 
	);

	if (result != D3D_OK)
	{
		trace(L"[ERROR] Failed to create texture from file '%s'", FilePath);
		return false;
	}
	return true;
}

void CAnimationSprite::Render(float X, float Y, int Left, int Top, int Width, int Height, float ScaleSize)
{
	D3DXMATRIX Combined;

	D3DXMATRIX Scale;
	D3DXMATRIX Translate;

	// Initialize the Combined matrix.
	D3DXMatrixIdentity(&Combined);
	// Scale the sprite.
	D3DXMatrixScaling(&Scale, ScaleSize, ScaleSize, ScaleSize);
	Combined *= Scale;
	// Translate the sprite
	D3DXMatrixTranslation(&Translate, X, Y, 0.0f);
	Combined *= Translate;
	// Apply the transform.
	_SpriteHandler->SetTransform(&Combined);



	// set scope render in Texture
	RECT srect;
	srect.left = Left;
	srect.right = Left + Width;
	srect.top = Top;
	srect.bottom = Top + Height;

	// set location
	//D3DXVECTOR3 position((float)X, (float)Y, 0);

	//  rander
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	_SpriteHandler->Draw(
		_Texture,
		&srect, // NULL get full _Texture
		NULL,
		NULL, //&position, //  apply scale
		D3DCOLOR_XRGB(255, 255, 255)
	);

	_SpriteHandler->End();
	
}

void CAnimationSprite::Render(float X, float Y, float ScaleSize)
{
	D3DXMATRIX Combined;

	D3DXMATRIX Scale;
	D3DXMATRIX Translate;

	// Initialize the Combined matrix.
	D3DXMatrixIdentity(&Combined);

	// set location
	D3DXVECTOR3 position((float)X, (float)Y, 0);
	// Scale the sprite.
	D3DXMatrixScaling(&Scale, ScaleSize, ScaleSize, ScaleSize);
	Combined *= Scale;
	// Translate the sprite
	D3DXMatrixTranslation(&Translate, X, Y, 0.0f);
	Combined *= Translate;
	// Apply the transform.
	_SpriteHandler->SetTransform(&Combined);
	
	//  rander
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	_SpriteHandler->Draw(
		_Texture,
		NULL, // NULL get full _Texture
		NULL,
		NULL,//&position, //  apply scale
		D3DCOLOR_XRGB(255, 255, 255)
	);

	_SpriteHandler->End();

}


void CAnimationSprite::Release()
{
	if(_Texture != nullptr)
	_Texture->Release();

	if (_d3ddv != nullptr) 
		_d3ddv->Release();
}
