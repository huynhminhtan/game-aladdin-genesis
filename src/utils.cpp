#include <d3dx9.h>

#include "utils.h"
#include "trace.h"


LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, LPWSTR FilePath)
{
	D3DXIMAGE_INFO info; 

	HRESULT result = D3DXGetImageInfoFromFile(FilePath,&info);
	if (result!=D3D_OK)
	{
		trace(L"[ERROR] Failed to get image info '%s'",FilePath);
		return NULL;
	}

	LPDIRECT3DSURFACE9 surface;

	d3ddv->CreateOffscreenPlainSurface(
			info.Width,				// width
			info.Height,			// height
			D3DFMT_X8R8G8B8,		// format
			D3DPOOL_DEFAULT,		
			&surface,
			NULL);

	result = D3DXLoadSurfaceFromFile(
			surface, 		// surface
			NULL,			// destination palette	
			NULL,			// destination rectangle 
			FilePath,			
			NULL,			// source rectangle
			D3DX_DEFAULT, 	// filter image
			D3DCOLOR_XRGB(0,0,0),				// transparency (0 = none)
			NULL);			// reserved

	if (result!=D3D_OK)
	{
		trace(L"[ERROR] D3DXLoadSurfaceFromFile() failed");
		return NULL;
	}

	return surface;
}