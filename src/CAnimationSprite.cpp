#include "CAnimationSprite.h"

CAnimationSprite::CAnimationSprite(LPDIRECT3DDEVICE9 d3ddv)
{
	_Texture = nullptr;
	_SpriteHandler = nullptr;
	_d3ddv = d3ddv;
	//_info
	_IndexTile = 0;
	_FPS = 0;
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

bool CAnimationSprite::Load(LPWSTR ImagePath, const char* XMLPath, D3DCOLOR Transcolor)
{
	// get infomation (widht, height) sprite sheet
	HRESULT result = D3DXGetImageInfoFromFile(ImagePath, &_Info);

	if (result != D3D_OK)
	{
		trace(L"[ERROR] Failed to get information from image file '%s'", ImagePath);
		return false;
	}

	// create texture from sprite sheet
	result = D3DXCreateTextureFromFileEx(
		_d3ddv,
		ImagePath,
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
		trace(L"[ERROR] Failed to create texture from file '%s'", ImagePath);
		return false;
	}

	// read file XML
	ReadXML(XMLPath);

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


	auto l_front = _ListTile.begin();
	advance(l_front, _IndexTile);

	// set position tile
	RECT srect;
	srect.left = l_front->GETLocaTionTile().left;
	srect.top = l_front->GETLocaTionTile().top;
	srect.bottom = srect.top + l_front->GETLocaTionTile().bottom;
	srect.right = srect.left + l_front->GETLocaTionTile().right;

	//  rander
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	_SpriteHandler->Draw(
		_Texture,
		&srect, // NULL get full _Texture
		NULL,
		NULL,//&position, //  apply scale
		D3DCOLOR_XRGB(255, 255, 255)
	);

	_SpriteHandler->End();

	if (_FPS > 20)
	{
		_IndexTile = ((_IndexTile + 1) % _ListTile.size());
		_FPS = 0;
	}

	_FPS++;

}

void CAnimationSprite::Release()
{
	if (_Texture != nullptr)
		_Texture->Release();

	if (_d3ddv != nullptr)
		_d3ddv->Release();
}

void CAnimationSprite::ReadXML(const char* XMLPath)
{
	TiXmlDocument doc(XMLPath);

	if (!doc.LoadFile())
	{
		trace(L"[ERROR] Failed to create texture from file '%s'", doc.ErrorDesc());
		return;
	}

	// get info root
	TiXmlElement* root = doc.RootElement();
	TiXmlElement* tile = nullptr;

	//// loop to get element name, x, y, width, height
	for (tile = root->FirstChildElement(); tile != NULL; tile = tile->NextSiblingElement())
	{
		int x, y, w, h;
		const char* nameTileTemp;
		CTile TileTemp;

		// get value from file xml
		nameTileTemp = tile->Attribute("n");
		tile->QueryIntAttribute("x", &x);
		tile->QueryIntAttribute("y", &y);
		tile->QueryIntAttribute("w", &w);
		tile->QueryIntAttribute("h", &h);

		TileTemp.SetTile(nameTileTemp, x, y, w, h);

		// add into ListTile
		_ListTile.push_back(TileTemp);
	};

}

// define class CTile //

CTile::CTile()
{
	_RectTile.top = 0;
	_RectTile.bottom = 0;
	_RectTile.left = 0;
	_RectTile.right = 0;

	_NameTile = nullptr;
}

CTile::~CTile()
{

}

void CTile::SetTile(const char* Name, int X, int Y, int Width, int Height)
{
	_NameTile = Name;

	_RectTile.left = X;
	_RectTile.top = Y;
	_RectTile.right = Width;
	_RectTile.bottom = Height;
}

CTile CTile::GetTile()
{
	CTile temp;

	temp._NameTile = _NameTile;
	temp._RectTile = _RectTile;

	return temp;
}

RECT CTile::GETLocaTionTile()
{
	RECT rectTemp;
	rectTemp.top = _RectTile.top;
	rectTemp.left = _RectTile.left;
	rectTemp.bottom = _RectTile.bottom;
	rectTemp.right = _RectTile.right;

	return rectTemp;
}
