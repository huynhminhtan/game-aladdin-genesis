#pragma once

//#include "Header.h"
#include "d3d9.h"

class Global
{
public:
	Global();
	~Global();

	void SetDirectDevice(LPDIRECT3DDEVICE9);
	LPDIRECT3DDEVICE9 GetDirectDevice();


	static Global* GetInstance();

private:

	LPDIRECT3DDEVICE9	_DirectDevice;
	
	static Global*		_instance;
};